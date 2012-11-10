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

#include "Component_Graph.h"
#include "Component.h"
#include <iostream>
#include <sstream>
#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>
#include "errors/API_Exception.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Component_Graph::Component_Graph ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph constructor" );
#endif /* LIBREVERSE_DEBUG */


        m_comp_map = get( boost::vertex_name, m_graph );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_Graph::Component_Graph ( Component_Graph const& rhs )
        : m_graph ( rhs.m_graph )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph copy constructor" );
#endif /* LIBREVERSE_DEBUG */


        std::copy ( rhs.m_index.begin(),
                    rhs.m_index.end(),
                    std::inserter ( m_index, m_index.end() ) );

        m_comp_map = get( boost::vertex_name, m_graph );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Graph::add_Component ( infrastructure_types::Component::ptr_t obj_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::add_Component" );
#endif /* LIBREVERSE_DEBUG */


        bool no_duplicate;
        infrastructure_types::Component_Graph::IdVertexMap_t::iterator pos;
        infrastructure_types::Component_Graph::Vertex_t node;

        if ( ! obj_ptr )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format( "Add Component for id %d")
                                          % obj_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        boost::tie (pos, no_duplicate) = m_index.insert
            ( std::make_pair ( obj_ptr->get_ID(),
                               infrastructure_types::Component_Graph::Vertex_t() ) );
    
        if ( no_duplicate )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::DETAIL,
                      boost::str ( boost::format("no duplicate with id = %d")
                                   % obj_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

                // Insertion was successful
                // Make a new vertex and return handle to 'node'
                node = add_vertex ( m_graph );

                // Assign component to vertex position
                m_comp_map[node] = obj_ptr;

                // Add vertex handle to map position
                pos->second = node;

                for ( infrastructure_types::Component_Data::Input_Token_t::const_iterator cpos =
                          obj_ptr->get_Source_List_Begin();
                      cpos != obj_ptr->get_Source_List_End();
                      ++cpos )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace
                            ( TraceArea::INFRASTRUCTURE,
                              TraceLevel::DETAIL,
                              boost::str ( boost::format("parent(id=%d) for child(id=%d)")
                                           % (*cpos).first
                                           % obj_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

                        this->add_Child ( (*cpos).first, node );
                    }
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::WARN,
                                     "ERROR: Duplicate source found. Skipping Component" );
#endif /* LIBREVERSE_DEBUG */

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::add_Component" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Graph::add_Child ( boost::uint32_t parent_id,
                                 infrastructure_types::Component_Graph::Vertex_t& child_node )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::add_Child (uint32,vertex)" );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Graph::IdVertexMap_t::iterator parent_pos;

        parent_pos = m_index.find (parent_id);

        if ( parent_pos == m_index.end() )
            {
                infrastructure_types::Component::ptr_t obj_ptr = m_comp_map[child_node];


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::WARN,
                      boost::str ( boost::format ( "ERROR: Cannot find parent. Skipping adding component #%d (%s)" )
                                   % obj_ptr->get_ID()
                                   % obj_ptr->get_Name() ) );
#endif /* LIBREVERSE_DEBUG */

                return;
            }

        infrastructure_types::Component_Graph::Vertex_t parent_node = parent_pos->second;

        if (! (add_edge ( parent_node, child_node, m_graph).second ) )
            {

#ifdef LIBREVERSE_DEBUG
                infrastructure_types::Component::ptr_t obj_ptr = m_comp_map[child_node];

                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::WARN,
                      boost::str ( boost::format ( "ERROR: duplicate edge exists from %d to %s" )
                                   % parent_id
                                   % obj_ptr->get_ID() ) );

                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::WARN,
                                     "Skipping the edge" );
#endif /* LIBREVERSE_DEBUG */

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::add_Child (uint32,vertex)" );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Component_Graph::Graph_t const&
    Component_Graph::get_Graph () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Graph::get_Graph ()" );
#endif /* LIBREVERSE_DEBUG */

        return m_graph;
    }

    infrastructure_types::Component::ptr_t
    Component_Graph::get_Component ( infrastructure_types::Component_Graph::Vertex_t node) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Graph::get_Component (vertex)" );
#endif /* LIBREVERSE_DEBUG */

        return m_comp_map[node];
    }

    infrastructure_types::Component::ptr_t
    Component_Graph::get_End_Component ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::get_End_Component" );
#endif /* LIBREVERSE_DEBUG */


        typedef std::vector<infrastructure_types::Component_Graph::Vertex_t> m_container;
        m_container comp_list;
        boost::topological_sort ( m_graph, std::back_inserter ( comp_list ) );

        /*
          infrastructure_types::Component_Graph::IdVertexMap_t::const_reverse_iterator pos = m_index.rbegin();
        */
        m_container::const_iterator pos = comp_list.begin();
        //infrastructure_types::Component_Graph::Vertex_t node = (*pos).second;
        infrastructure_types::Component_Graph::Vertex_t node = (*pos);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::get_End_Component" );
#endif /* LIBREVERSE_DEBUG */


        return m_comp_map[node];
    }

    infrastructure_types::Component_Graph::Vertex_t const&
    Component_Graph::get_Vertex (  boost::uint32_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::get_Vertex (uint32)" );
#endif /* LIBREVERSE_DEBUG */

        infrastructure_types::Component_Graph::IdVertexMap_t::const_iterator pos = m_index.find ( id );

        if ( pos == m_index.end() )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::Component_Exception
                    ( errors::Component_Exception::INVALID_INDEX );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::get_Vertex (uint32)" );
#endif /* LIBREVERSE_DEBUG */


        return pos->second;
    }

    void
    Component_Graph::initialize_Source ( boost::shared_ptr < infrastructure::component >& source_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::initialize_Source" );
#endif /* LIBREVERSE_DEBUG */


        if ( ! source_ptr )
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				   TraceLevel::ERROR,
				   boost::str ( boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

        // Previous object ( data from previous graph / input to framework ): id = 0
        // Source object: id = 1
        infrastructure_types::Component_Graph::IdVertexMap_t::const_iterator pos = m_index.find ( 1 );

        if ( pos == m_index.end() )
            {


#ifdef LIBREVERSE_DEBUG
               Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				    TraceLevel::DATA,
				    "Used index of 1" );

	       Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				    TraceLevel::ERROR,
				    boost::str ( boost::format("Exception throw in %s at line %d")
						 % __FILE__
						 % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

	       
                throw errors::Component_Exception
                    ( errors::Component_Exception::INVALID_INDEX );
            }

        infrastructure_types::Component_Graph::Vertex_t node = pos->second;
        infrastructure_types::Component::ptr_t first_comp_ptr = m_comp_map[node];

        first_comp_ptr->add_Input_Source (0);

        first_comp_ptr->received_Input_Source_Data (0);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::initialize_Source" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Component_Graph::empty () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Graph::empty ()" );
#endif /* LIBREVERSE_DEBUG */

        return boost::num_vertices ( m_graph ) == 0;
    }

    infrastructure_types::Component_Graph::Component_List_t
    Component_Graph::get_Parent_List ( const infrastructure_types::Component_Graph::Vertex_t& v_ref )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::get_Parent_List (vertex)" );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Graph::Component_List_t output;

        infrastructure_types::Component::ptr_t comp_ptr = this->get_Component ( v_ref );

        // For each entry, X,  in the source list of this component
        for ( infrastructure_types::Component_Data::Input_Token_t::const_iterator cpos =
                  comp_ptr->get_Source_List_Begin();
              cpos != comp_ptr->get_Source_List_End();
              ++cpos )
            {
                //   Get component for X
                //   Add X to output list
                output.push_back ( this->get_Component ( (*cpos).first ) );
                cpos++;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::get_Parent_List (vertex)" );
#endif /* LIBREVERSE_DEBUG */

        return output;
    }

    infrastructure_types::Component_Graph::Component_List_t
    Component_Graph::get_Parent_List ( boost::uint32_t id  )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::get_Parent_List (uint32)" );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Graph::IdVertexMap_t::const_iterator pos = m_index.find ( id );
        if ( pos == m_index.end() )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Component_Exception
                    ( errors::Component_Exception::INVALID_INDEX );
            }

        infrastructure_types::Component_Graph::Component_List_t output;

        // Grab component for this id
        infrastructure_types::Component::ptr_t comp_ptr = this->get_Component ( id );

        // For each entry, X,  in the source list of this component
    
        for ( infrastructure_types::Component_Data::Input_Token_t::const_iterator cpos =
                  comp_ptr->get_Source_List_Begin();
              cpos != comp_ptr->get_Source_List_End();
              ++cpos )
            {
                //   Get component for X
                //   Add X to output list
                output.push_back ( this->get_Component ( (*cpos).first ) );
                cpos++;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::get_Parent_List (uint32)" );
#endif /* LIBREVERSE_DEBUG */

        return output;
    }

    Component_Graph&
    Component_Graph::operator= ( Component_Graph const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Component_Graph temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Component_Graph::swap ( Component_Graph& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_graph.swap ( rhs.m_graph );
        std::swap ( m_index, rhs.m_index );
        std::swap ( m_comp_map, rhs.m_comp_map );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::swap" );
#endif /* LIBREVERSE_DEBUG */


    }

    std::string
    Component_Graph::to_String ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Graph::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

        infrastructure_types::Component_Graph::Graph_t::out_edge_iterator pos;
        infrastructure_types::Component_Graph::Graph_t::out_edge_iterator end;
        infrastructure_types::Component_Graph::Graph_t::vertex_descriptor node;
        infrastructure_types::Component::ptr_t child_comp_ptr;

        for ( infrastructure_types::Component_Graph::IdVertexMap_t::const_iterator cpos
                  = m_index.begin();
              cpos != m_index.end();
              ++cpos )
            {
                infrastructure_types::Component::ptr_t comp_ptr =
                    this->get_Component( (*cpos).second );

                output << boost::format("%s(%d) - children = ")
                    % comp_ptr->get_Name()
                    % (*cpos).first
                       << std::endl;

                // For all children, print out path from vertex id to child id
                for ( boost::tie(pos,end) = out_edges( (*cpos).second, m_graph );
                      pos != end;
                      ++pos )
                    {
                        node = target (*pos, m_graph);
                        child_comp_ptr = this->get_Component(node);
                        output << boost::format("    %d -> %d;")
                            % comp_ptr->get_ID()
                            % child_comp_ptr->get_ID()
                               << std::endl;
                    }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Graph::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output.str();
    }
} /* namepsace infrastructure */
} /* namespace libreverse */
