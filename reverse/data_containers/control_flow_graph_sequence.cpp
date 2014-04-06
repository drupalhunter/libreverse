/*  control_flow_graph_sequence.cpp

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

#include <reverse/data_containers/control_flow_graph_sequence.hpp>
#include <reverse/data_containers/control_flow_graph.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/data_containers/basic_block.hpp>
#include <reverse/preconditions.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>

namespace reverse {
    namespace data_containers {

        control_flow_graph_sequence::control_flow_graph_sequence ()
        {
            trace::data_containers_detail ( "Inside control_flow_graph_sequence constructor" );
        }

        control_flow_graph_sequence::control_flow_graph_sequence ( control_flow_graph_sequence const& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph_sequence copy constructor" );

            for ( control_flow_graph_sequence::sequence_t::const_iterator cpos = rhs.m_graph_list.begin();
                    cpos != rhs.m_graph_list.end();
                    ++cpos ) {
                boost::shared_ptr < const control_flow_graph > cfg_ptr = ( *cpos );
                boost::shared_ptr < control_flow_graph > copied_cfg_ptr ( new data_containers::control_flow_graph ( *cfg_ptr ) );
                m_graph_list.push_back ( copied_cfg_ptr );
            }

            trace::data_containers_detail ( "Exiting control_flow_graph_sequence copy constructor" );
        }

        void
        control_flow_graph_sequence::add_control_flow_graph ( boost::shared_ptr< control_flow_graph >& input_block_ptr )
        {
            trace::data_containers_detail ( "Entering control_flow_graph_sequence::add_Control_Flow_Graph" );

            reverse::preconditions::is_set ( input_block_ptr );

            m_graph_list.push_back ( input_block_ptr );

            trace::data_containers_detail ( "Exiting control_flow_graph_sequence::add_Control_Flow_Graph" );
        }

        control_flow_graph_sequence::sequence_t::iterator
        control_flow_graph_sequence::begin()
        {
            return m_graph_list.begin();
        }

        control_flow_graph_sequence::sequence_t::iterator
        control_flow_graph_sequence::end()
        {
            return m_graph_list.end();
        }

        control_flow_graph_sequence::sequence_t::const_iterator
        control_flow_graph_sequence::begin() const
        {
            return m_graph_list.begin();
        }

        control_flow_graph_sequence::sequence_t::const_iterator
        control_flow_graph_sequence::end() const
        {
            return m_graph_list.end();
        }

        size_t control_flow_graph_sequence::size() const
        {
	    return m_graph_list.size();
        }

        
        bool
        control_flow_graph_sequence::empty () const
        {
            trace::data_containers_detail ( "Inside control_flow_graph_sequence::empty ()" );

            return m_graph_list.empty();
        }

        control_flow_graph_sequence&
        control_flow_graph_sequence::operator= ( control_flow_graph_sequence const& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph_sequence::operator= (assignment)" );

            control_flow_graph_sequence temp ( rhs );
            swap ( temp );

            trace::data_containers_detail ( "Exiting control_flow_graph_sequence::operator= (assignment)" );

            return *this;
        }

        void
        control_flow_graph_sequence::swap ( control_flow_graph_sequence& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph_sequence::swap" );

            m_graph_list.swap ( rhs.m_graph_list );

            trace::data_containers_detail ( "Exiting control_flow_graph_sequence::swap" );
        }

        std::ostream& operator<< ( std::ostream& os, control_flow_graph_sequence const& rhs )
        {
            trace::data_containers_detail ( "Entering control_flow_graph_sequence::to_String" );
            trace::data_containers_data ( "Control Flow Graph count: %1%", rhs.size() );

            for ( control_flow_graph_sequence::sequence_t::const_iterator cpos = rhs.begin();
                    cpos != rhs.end();
                    ++cpos ) {
                boost::shared_ptr < control_flow_graph > cfg_ptr = ( *cpos );

                // print out text version of graph
                os << cfg_ptr << std::endl;
            }

            trace::data_containers_detail ( "Exiting control_flow_graph_sequence::to_String" );

            return os;
        }

    }  /* namespace data_containers */
} /* namespace reverse */
