/*  control_flow_graph.cpp

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

#include <reverse/data_containers/control_flow_graph.hpp>
#include <reverse/errors/component_exception.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/data_containers/basic_block.hpp>
#include <reverse/preconditions.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>

namespace reverse {
    namespace data_containers {

        control_flow_graph::control_flow_graph ( std::string name )
            : m_name ( name )
        {
            trace::data_containers_detail ( "Entering control_flow_graph constructor" );

            m_basic_block_map = get ( boost::vertex_name, m_graph );

            trace::data_containers_detail ( "Exiting control_flow_graph constructor" );
        }

        control_flow_graph::control_flow_graph ( control_flow_graph const& rhs )
            : m_graph ( rhs.m_graph )
        {
            trace::data_containers_detail ( "Inside control_flow_graph copy constructor" );
        }

        void
        control_flow_graph::add_basic_block ( boost::shared_ptr<basic_block>& input_block_ptr )
        {
            trace::data_containers_detail ( "Entering control_flow_graph::add_Basic_Block" );

            reverse::preconditions::is_set ( input_block_ptr );

            trace::data_containers_data ( "Add Block Block #%d", input_block_ptr->get_id() );

            bool no_duplicate;
            data_containers::control_flow_graph::id_vertex_map_t::iterator pos;
            data_containers::control_flow_graph::vertex_t node;

            boost::tie ( pos, no_duplicate ) = m_index.insert ( std::make_pair ( input_block_ptr->get_id(),
                                               data_containers::control_flow_graph::vertex_t() ) );

            if ( no_duplicate ) {
                // Insertion was successful
                // Make a new vertex and return handle to 'node'
                node = add_vertex ( m_graph );

                // Assign component to vertex position
                m_basic_block_map[node] = input_block_ptr;

                // Add vertex handle to map position
                pos->second = node;
            }

            trace::data_containers_detail ( "Exiting control_flow_graph::add_Basic_Block" );
        }

        void
        control_flow_graph::add_edge ( boost::uint32_t source_id,
                                       boost::uint32_t destination_id )
        {
            trace::data_containers_detail ( "Entering control_flow_graph::add_Child (uint32,uint32)" );

            // Get the source vertex
            data_containers::control_flow_graph::vertex_t const& source_vertex = this->get_vertex ( source_id );

            // Get the source vertex
            data_containers::control_flow_graph::vertex_t const& dest_vertex = this->get_vertex ( destination_id );

            // Use the internal index for each in creating the edge
            data_containers::control_flow_graph::add_edge_result_t result = boost::add_edge ( source_vertex,
                    dest_vertex,
                    m_graph );


            if ( ! result.second ) {
                trace::data_containers_data ( "Attempted to add a duplicate edge from %d to %d",
                                              source_id,
                                              destination_id );
                trace::data_containers_error ( "Duplicate edge is ignored." );
            }

            trace::data_containers_detail ( "Exiting control_flow_graph::add_Edge (uint32,uint32)" );

        }

        boost::shared_ptr < basic_block >
        control_flow_graph::get_basic_block ( data_containers::control_flow_graph::vertex_t node ) const
        {
            trace::data_containers_data ( "Inside control_flow_graph::get_Basic_Block (%1%)", node );

            return m_basic_block_map[node];
        }

        data_containers::control_flow_graph::graph_t const&
        control_flow_graph::get_graph () const
        {
            trace::data_containers_detail ( "Inside control_flow_graph::get_Graph ()" );

            return m_graph;
        }

        bool
        control_flow_graph::empty () const
        {
            trace::data_containers_detail ( "Inside control_flow_graph::empty ()" );

            return boost::num_vertices ( m_graph ) == 0;
        }

        control_flow_graph&
        control_flow_graph::operator= ( control_flow_graph const& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph::operator= (assignment)" );

            control_flow_graph temp ( rhs );
            swap ( temp );

            trace::data_containers_detail ( "Exiting control_flow_graph::operator= (assignment)" );

            return *this;
        }

        void
        control_flow_graph::swap ( control_flow_graph& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph::swap" );

            m_graph.swap ( rhs.m_graph );

            trace::data_containers_detail ( "Exiting control_flow_graph::swap" );
        }

        reverse::data_containers::control_flow_graph::id_vertex_map_t::const_iterator control_flow_graph::vertex_begin() const
        {
            return m_index.begin();
        }

        reverse::data_containers::control_flow_graph::id_vertex_map_t::const_iterator control_flow_graph::vertex_end() const
        {
            return m_index.end();
        }



        std::ostream& operator<< ( std::ostream& os, control_flow_graph const& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph::to_String" );
            trace::data_containers_data ( "Basic Block count: %1%", rhs.size() );

            for ( data_containers::control_flow_graph::id_vertex_map_t::const_iterator pos = rhs.vertex_begin();
                    pos != rhs.vertex_end();
                    ++pos ) {
                boost::shared_ptr< basic_block > block_ptr = rhs.get_basic_block ( ( *pos ).second );

                // print out text version of graph
                os << block_ptr << std::endl;
            }

            trace::data_containers_detail ( "Exiting control_flow_graph::to_String" );

            return os;
        }

        data_containers::control_flow_graph::vertex_t const&
        control_flow_graph::get_vertex ( boost::uint32_t id ) const
        {
            trace::data_containers_detail ( "Entering control_flow_graph::get_vertex (uint32)" );

            data_containers::control_flow_graph::id_vertex_map_t::const_iterator pos = m_index.find ( id );

            if ( pos == m_index.end() ) {

                trace::data_containers_error ( "Exception throw in %s at line %d",
                                               __FILE__,
                                               __LINE__ );

                throw errors::component_exception ( errors::component_exception::invalid_index );
            }

            trace::data_containers_detail ( "Exiting control_flow_graph::get_vertex (uint32)" );

            return pos->second;
        }


        data_containers::control_flow_graph::graph_t::vertices_size_type
        control_flow_graph::size () const
        {
            trace::data_containers_detail ( "Inside control_flow_graph::size" );

            return boost::num_vertices ( m_graph );
        }

        std::string control_flow_graph::get_name() const
        {
            trace::data_containers_detail ( "Inside control_flow_graph::get_Name" );

            return m_name;

        }

    }  /* namespace data_containers */
} /* namespace reverse */
