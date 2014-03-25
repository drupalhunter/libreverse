/*  Component_Graph.cpp

   Copyright (C) 2008 Stephen Torri

   This file is part of Libreverse.

   Libreverse is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   Libreverse is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

#include <reverse/errors/api_exception.hpp>
#include <reverse/errors/component_exception.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>

#include <iostream>
#include <sstream>

namespace reverse {
  namespace infrastructure {

    component_graph::component_graph ()
    {
      trace::infrastructure_detail ( "Entering Component_Graph constructor" );

      m_comp_map = get( boost::vertex_name, m_graph );

      trace::infrastructure_detail ( "Exiting Component_Graph constructor" );
    }

    component_graph::component_graph ( component_graph const& rhs )
        : m_graph ( rhs.m_graph )
    {
      trace::infrastructure_detail ( "Entering Component_Graph copy constructor" );

      std::copy ( rhs.m_index.begin(),
		  rhs.m_index.end(),
		  std::inserter ( m_index, m_index.end() ) );
      
      m_comp_map = get( boost::vertex_name, m_graph );

      trace::infrastructure_detail ( "Exiting Component_Graph copy constructor" );
    }

    void
    component_graph::add_component ( boost::shared_ptr < infrastructure::component >& obj_ptr )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::add_Component" );

      bool no_duplicate = false;
      infrastructure::component_graph::idvertexmap_t::iterator pos;
      infrastructure::component_graph::vertex_t node;

        if ( ! obj_ptr )
            {
	      trace::infrastructure_error ( "Exception throw in %s at line %d",
					    __FILE__,
					    __LINE__ );

	      throw errors::component_exception ( errors::component_exception::null_pointer );
            }

        trace::infrastructure_data ( "Add Component for id %d", obj_ptr->get_id() );
	
        boost::tie (pos, no_duplicate) = m_index.insert ( std::make_pair ( obj_ptr->get_id(),
									   infrastructure::component_graph::vertex_t() ) );
    
        if ( no_duplicate )
	  {
	    trace::infrastructure_data ( "no duplicate with id = %d", obj_ptr->get_id() );

	    // Insertion was successful
	    // Make a new vertex and return handle to 'node'
	    node = add_vertex ( m_graph );

	    // Assign component to vertex position
	    m_comp_map[node] = obj_ptr;

	    // Add vertex handle to map position
	    pos->second = node;

	    for ( infrastructure::component_data::input_token_t::const_iterator cpos = obj_ptr->get_source_list_begin();
		  cpos != obj_ptr->get_source_list_end();
		  ++cpos )
	      {
		trace::infrastructure_data ( "parent(id=%d) for child(id=%d)", 
					     (*cpos).first,
					     obj_ptr->get_id() );

		this->add_child ( (*cpos).first, node );
	      }
	  }
        else
	  {
	    trace::infrastructure_error ( "ERROR: Duplicate source found. Skipping Component" );
	  }

        trace::infrastructure_detail ( "Exiting Component_Graph::add_Component" );
    }

    void
    component_graph::add_child ( boost::uint32_t parent_id,
                                 infrastructure::component_graph::vertex_t& child_node )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::add_Child (uint32,vertex)" );

      infrastructure::component_graph::idvertexmap_t::iterator parent_pos;

        parent_pos = m_index.find (parent_id);
	
        if ( parent_pos == m_index.end() )
	  {
	    boost::shared_ptr < infrastructure::component > obj_ptr = m_comp_map[child_node];

	    trace::infrastructure_error ( "ERROR: Cannot find parent. Skipping adding component #%d (%s)",
					  obj_ptr->get_id(),
					  obj_ptr->get_name() );
	    return;
	  }

        infrastructure::component_graph::vertex_t parent_node = parent_pos->second;

        if (! (add_edge ( parent_node, child_node, m_graph).second ) )
	  {
	    boost::shared_ptr < infrastructure::component > obj_ptr = m_comp_map[child_node];

	    trace::infrastructure_error ( "ERROR: duplicate edge exists from %d to %s",
					  parent_id,
					  obj_ptr->get_id() );
	    
	    trace::infrastructure_error ( "Skipping the edge" );
	  }

        trace::infrastructure_detail ( "Exiting Component_Graph::add_Child (uint32,vertex)" );
    }

    infrastructure::component_graph::graph_t const&
    component_graph::get_graph () const
    {
      trace::infrastructure_detail ( "Inside Component_Graph::get_Graph ()" );

      return m_graph;
    }

    boost::shared_ptr < infrastructure::component >
    component_graph::get_component ( infrastructure::component_graph::vertex_t const& node) const
    {
      trace::infrastructure_detail ( "Inside Component_Graph::get_Component (vertex)" );

      return m_comp_map[node];
    }

    boost::shared_ptr < infrastructure::component >
    component_graph::get_end_component ( void ) const
    {
      trace::infrastructure_detail ( "Entering Component_Graph::get_End_Component" );

      typedef std::vector<infrastructure::component_graph::vertex_t> m_container;
      m_container comp_list;
      boost::topological_sort ( m_graph, std::back_inserter ( comp_list ) );
      m_container::const_iterator pos = comp_list.begin();

      infrastructure::component_graph::vertex_t node = (*pos);

      trace::infrastructure_detail ( "Exiting Component_Graph::get_End_Component" );

      return m_comp_map[node];
    }

    infrastructure::component_graph::vertex_t const&
    component_graph::get_vertex (  boost::uint32_t id ) const
    {
      trace::infrastructure_detail ( "Entering Component_Graph::get_Vertex (uint32)" );

      infrastructure::component_graph::idvertexmap_t::const_iterator pos = m_index.find ( id );

      if ( pos == m_index.end() )
	{
	  trace::infrastructure_error ( "Exception throw in %s at line %d", 
					__FILE__,
					__LINE__ );

	  throw errors::component_exception ( errors::component_exception::invalid_index );
	}

        trace::infrastructure_detail ( "Exiting Component_Graph::get_Vertex (uint32)" );

        return pos->second;
    }

    void
    component_graph::initialize_source ( boost::shared_ptr < infrastructure::component >& source_ptr )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::initialize_Source" );

      if ( ! source_ptr )
	{
	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
					__LINE__ );

	  throw errors::component_exception ( errors::component_exception::null_pointer );
	}

      // Previous object ( data from previous graph / input to framework ): id = 0
      // Source object: id = 1
      infrastructure::component_graph::idvertexmap_t::const_iterator pos = m_index.find ( 1 );

      if ( pos == m_index.end() )
	{
	  trace::infrastructure_data ( "Used index of 1" );
	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
					__LINE__ );
	       
                throw errors::component_exception ( errors::component_exception::invalid_index );
	}
      
        infrastructure::component_graph::vertex_t node = pos->second;
	boost::shared_ptr < infrastructure::component > first_comp_ptr = m_comp_map[node];

        first_comp_ptr->add_input_source (0);

        first_comp_ptr->received_input_source_data (0);

        trace::infrastructure_detail ( "Exiting Component_Graph::initialize_Source" );
    }

    bool
    component_graph::empty () const
    {
        trace::infrastructure_detail ( "Inside Component_Graph::empty ()" );

        return boost::num_vertices ( m_graph ) == 0;
    }

    infrastructure::component_graph::component_list_t
    component_graph::get_parent_list ( const infrastructure::component_graph::vertex_t& v_ref )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::get_Parent_List (vertex)" );

      infrastructure::component_graph::component_list_t output;

      boost::shared_ptr < infrastructure::component > comp_ptr = this->get_component ( v_ref );

      // For each entry, X,  in the source list of this component
      for ( infrastructure::component_data::input_token_t::const_iterator cpos =
	      comp_ptr->get_source_list_begin();
	    cpos != comp_ptr->get_source_list_end();
	    ++cpos )
            {
	      //   Get component for X
	      //   Add X to output list
	      output.push_back ( this->get_component ( (*cpos).first ) );
	      cpos++;
            }

        trace::infrastructure_detail ( "Exiting Component_Graph::get_Parent_List (vertex)" );

        return output;
    }

    infrastructure::component_graph::component_list_t
    component_graph::get_parent_list ( boost::uint32_t id  )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::get_Parent_List (uint32)" );

      infrastructure::component_graph::idvertexmap_t::const_iterator pos = m_index.find ( id );
      if ( pos == m_index.end() )
	{
	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
					__LINE__ );

	  throw errors::component_exception ( errors::component_exception::invalid_index );
	}

        infrastructure::component_graph::component_list_t output;

        // Grab component for this id
	boost::shared_ptr < infrastructure::component > comp_ptr = this->get_component ( id );

        // For each entry, X,  in the source list of this component
    
        for ( infrastructure::component_data::input_token_t::const_iterator cpos = comp_ptr->get_source_list_begin();
              cpos != comp_ptr->get_source_list_end();
              ++cpos )
	  {
	    //   Get component for X
	    //   Add X to output list
	    output.push_back ( this->get_component ( (*cpos).first ) );
	    cpos++;
	  }

        trace::infrastructure_detail ( "Exiting Component_Graph::get_Parent_List (uint32)" );

        return output;
    }

    component_graph&
    component_graph::operator= ( component_graph const& rhs )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::operator= (assignment)" );

      component_graph temp ( rhs );
      swap ( temp );

      trace::infrastructure_detail ( "Exiting Component_Graph::operator= (assignment)" );

      return *this;
    }

    void
    component_graph::swap ( component_graph& rhs )
    {
      trace::infrastructure_detail ( "Entering Component_Graph::swap" );

      m_graph.swap ( rhs.m_graph );
      std::swap ( m_index, rhs.m_index );
      std::swap ( m_comp_map, rhs.m_comp_map );

      trace::infrastructure_detail ( "Exiting Component_Graph::swap" );
    }

    std::string
    component_graph::to_string ( void ) const
    {
      trace::infrastructure_detail ( "Entering Component_Graph::to_String" );

      std::stringstream output;

      infrastructure::component_graph::graph_t::out_edge_iterator pos;
      infrastructure::component_graph::graph_t::out_edge_iterator end;
      infrastructure::component_graph::graph_t::vertex_descriptor node;
      boost::shared_ptr < infrastructure::component > child_comp_ptr;

      for ( infrastructure::component_graph::idvertexmap_t::const_iterator cpos = m_index.begin();
	    cpos != m_index.end();
	    ++cpos )
	{
	  boost::shared_ptr < infrastructure::component > comp_ptr = this->get_component( (*cpos).second );

	  output << boost::format("%s(%d) - children = ")
	    % comp_ptr->get_name()
	    % (*cpos).first << std::endl;

	  // For all children, print out path from vertex id to child id
	  for ( boost::tie(pos,end) = out_edges( (*cpos).second, m_graph );
		pos != end;
		++pos )
	    {
	      node = target (*pos, m_graph);
	      child_comp_ptr = this->get_component(node);
	      output << boost::format("    %d -> %d;")
		% comp_ptr->get_id()
		% child_comp_ptr->get_id()
		     << std::endl;
	    }
	}

        trace::infrastructure_detail ( "Exiting Component_Graph::to_String" );

        return output.str();
    }

  } /* namepsace infrastructure */
} /* namespace reverse */
