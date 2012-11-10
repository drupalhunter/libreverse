/*  Control_Flow_Graph.cpp

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

#include "Control_Flow_Graph.h"

#include "errors/Internal_Exception.h"
#include "data_containers/Basic_Block.h"
#include "io/Preconditions.h"
#include "errors/Component_Exception.h"

#include <sstream>
#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace data_container {

    Control_Flow_Graph::Control_Flow_Graph ( std::string name )
      : m_name ( name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph constructor" );
#endif /* LIBREVERSE_DEBUG */


	m_basic_block_map = get ( boost::vertex_name, m_graph );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Control_Flow_Graph::Control_Flow_Graph ( Control_Flow_Graph const& rhs )
        : m_graph ( rhs.m_graph )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Control_Flow_Graph copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Control_Flow_Graph::add_Basic_Block ( data_types::Basic_Block::ptr_t input_block_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph::add_Basic_Block" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( input_block_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format( "Add Block Block #%d") % input_block_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        bool no_duplicate;
        data_types::Control_Flow_Graph::IdVertexMap_t::iterator pos;
        data_types::Control_Flow_Graph::Vertex_t node;

        boost::tie (pos, no_duplicate) = m_index.insert ( std::make_pair ( input_block_ptr->get_ID(),
									   data_types::Control_Flow_Graph::Vertex_t() ) );

	if ( no_duplicate )
	  {
	    // Insertion was successful
	    // Make a new vertex and return handle to 'node'
	    node = add_vertex ( m_graph );

	    // Assign component to vertex position
	    m_basic_block_map[node] = input_block_ptr;

	    // Add vertex handle to map position
	    pos->second = node;
	  }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph::add_Basic_Block" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Control_Flow_Graph::add_Edge ( boost::uint32_t source_id,
				   boost::uint32_t destination_id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph::add_Child (uint32,uint32)" );
#endif /* LIBREVERSE_DEBUG */


	// Get the source vertex
	data_types::Control_Flow_Graph::Vertex_t const& source_vertex = this->get_Vertex ( source_id );

	// Get the source vertex
	data_types::Control_Flow_Graph::Vertex_t const& dest_vertex = this->get_Vertex ( destination_id );

	// Use the internal index for each in creating the edge
	data_types::Control_Flow_Graph::Add_Edge_Result_t result = boost::add_edge ( source_vertex,
										     dest_vertex,
										     m_graph );


#ifdef LIBREVERSE_DEBUG
	if ( ! result.second )
	  {
                Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
				     TraceLevel::WARN,
				     boost::str ( boost::format("Attempted to add a duplicate edge from %d to %d")
						  % source_id
						  % destination_id ) );
                Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
				     TraceLevel::WARN,
				     "Duplicate edge is ignored." );
	  }

        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph::add_Edge (uint32,uint32)" );
#endif /* LIBREVERSE_DEBUG */

    }

    data_types::Basic_Block::ptr_t
    Control_Flow_Graph::get_Basic_Block ( data_types::Control_Flow_Graph::Vertex_t node ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Control_Flow_Graph::get_Basic_Block (%1%)" ) % node ) );

      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
			   TraceLevel::DATA,
			   "CFG before getting basic block" );

      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "%1%" ) % this->to_String() ) );

#endif /* LIBREVERSE_DEBUG */

	return m_basic_block_map[node];
    }

    data_types::Control_Flow_Graph::Graph_t const&
    Control_Flow_Graph::get_Graph () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Control_Flow_Graph::get_Graph ()" );
#endif /* LIBREVERSE_DEBUG */

        return m_graph;
    }

    bool
    Control_Flow_Graph::empty () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Control_Flow_Graph::empty ()" );
#endif /* LIBREVERSE_DEBUG */

        return boost::num_vertices ( m_graph ) == 0;
    }

    Control_Flow_Graph&
    Control_Flow_Graph::operator= ( Control_Flow_Graph const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Control_Flow_Graph temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Control_Flow_Graph::swap ( Control_Flow_Graph& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_graph.swap ( rhs.m_graph );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Control_Flow_Graph::to_String () const
    {
      std::stringstream output;

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph::to_String" );

        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
			     boost::str ( boost::format ( "Basic Block count: %1%" ) % m_index.size() ) );

#endif /* LIBREVERSE_DEBUG */

        for ( data_types::Control_Flow_Graph::IdVertexMap_t::const_iterator pos = m_index.begin();
              pos != m_index.end();
              ++pos )
            {
	      data_types::Basic_Block::ptr_t block_ptr = m_basic_block_map[ (*pos).second ];

	      // print out text version of graph
	      output << block_ptr->to_String() << std::endl;

	    }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    data_types::Control_Flow_Graph::Vertex_t const&
    Control_Flow_Graph::get_Vertex (  boost::uint32_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph::get_Vertex (uint32)" );
#endif /* LIBREVERSE_DEBUG */

        data_types::Control_Flow_Graph::IdVertexMap_t::const_iterator pos = m_index.find ( id );

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

                throw errors::Component_Exception ( errors::Component_Exception::INVALID_INDEX );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph::get_Vertex (uint32)" );
#endif /* LIBREVERSE_DEBUG */


        return pos->second;
    }


    data_types::Control_Flow_Graph::Graph_t::vertices_size_type
    Control_Flow_Graph::size () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Control_Flow_Graph::size" );
#endif /* LIBREVERSE_DEBUG */


        return boost::num_vertices ( m_graph );

    }

    std::string
    Control_Flow_Graph::get_Name () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Control_Flow_Graph::get_Name" );
#endif /* LIBREVERSE_DEBUG */

	return m_name;

    }

}  /* namespace data_types */
} /* namespace libreverse */
