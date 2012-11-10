/*  Meta_Writer.cpp

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

#include <reverse/components/output/meta_writer.hpp>
#include <reverse/data_containers/filename.hpp>
#include <reverse/errors/api_exception.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>
#include <reverse/io/input/file_readers/file_reader.hpp>
#include <reverse/io/input/file_readers/reader_factory.hpp>
#include <reverse/meta/meta_object.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <iostream>

namespace reverse {
  namespace component {

    const std::string meta_writer::m_name = "meta_writer";

    meta_writer::meta_writer ()
      : m_state_ptr ( new infrastructure::component_state (0) )
    {
      trace::trace::write_trace ( trace_area::components,
				  trace_level::detail,
				  boost::str ( boost::format ( "inside meta_writer constructor (id=%d)")
					       % m_state_ptr->get_id() ) );
    }

    meta_writer::meta_writer ( boost::shared_ptr < infrastructure::component_state > state_ptr )
        : m_state_ptr ( state_ptr )
    {
      trace::trace::write_trace ( trace_area::components,
				  trace_level::detail,
				  boost::str ( boost::format ( "inside meta_writer constructor (id=%d)")
					       % m_state_ptr->get_id() ) );
    }

    meta_writer::meta_writer ( meta_writer const& rhs )
      : infrastructure::component ( rhs ),
	infrastructure::component_actor ( rhs ),
	boost::enable_shared_from_this<meta_writer> ( rhs ),
	m_state_ptr ( new infrastructure::component_state ( *rhs.m_state_ptr ) )
    {
      trace::trace::write_trace ( trace_area::components,
				  trace_level::detail,
				  boost::str ( boost::format ( "inside meta_writer copy constructor (id=%d)")
					       % m_state_ptr->get_id() ) );
    }

    meta_writer::~meta_writer ()
    {
      trace::trace::write_trace ( trace_area::components,
				  trace_level::detail,
				  boost::str ( boost::format ( "inside meta_writer destructor (id=%d)")
					       % m_state_ptr->get_id() ) );
    }

    void
    meta_writer::received_input_source_data ( boost::uint32_t id )
    {
      trace::trace::write_trace ( trace_area::components,
				  trace_level::detail,
				  boost::str ( boost::format ( "entering meta_writer::received_input_source_data (id=%d)")
					       % m_state_ptr->get_id() ) );

      std::cout << boost::format("meta_writer(%d)::init")
	% m_state_ptr->get_id()
		<< std::endl;
      

      m_state_ptr->received_input_source_data ( id );

      trace::trace::write_trace ( trace_area::components,
				  trace_level::detail,
				  boost::str ( boost::format ( "exiting meta_writer::received_input_source_data (id=%d)")
					       % m_state_ptr->get_id() ) );
      
    }

    void
    meta_writer::add_input_source ( boost::uint32_t id )
    {
      trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "entering meta_writer::add_input_source (id=%d)")
                                          % m_state_ptr->get_id() ) );

        m_state_ptr->add_input_source ( id );

        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "exiting meta_writer::add_input_source (id=%d)")
                                          % m_state_ptr->get_id() ) );

    }

    std::string
    meta_writer::get_name (void) const
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "inside meta_writer::get_name (id=%d)")
                                          % m_state_ptr->get_id() ) );

        return m_name;
    }

    void meta_writer::process ()
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "entering meta_writer::process (id=%d)")
                                          % m_state_ptr->get_id() ) );

	boost::shared_ptr < infrastructure::component_data > data_ptr = m_state_ptr->get_data();

        meta::meta_object::const_ptr_t meta_ptr = data_ptr->get_input_meta_data();

        std::cout << meta_ptr->to_string() << std::endl;

        /**
         * pass on input information
         */
        if ( data_ptr->is_filename_set() )
            {
                data_ptr->set_output_data ( data_ptr->get_input_filename() );
            }
        if ( data_ptr->is_control_flow_graph_sequence_set() )
            {
                data_ptr->set_output_data ( data_ptr->get_input_control_flow_graph_sequence() );
            }
        if ( data_ptr->is_memory_map_set() )
            {
                data_ptr->set_output_data ( data_ptr->get_input_memory_map() );
            }

        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "exiting meta_writer::process (id=%d)")
                                          % m_state_ptr->get_id() ) );

    }

    void
    meta_writer::run ( infrastructure::component_graph::data_map_t* m_input_data )
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "entering meta_writer::run (id=%d)")
                                          % m_state_ptr->get_id() ) );

        std::cout << std::endl
                  << "--------------------------------" << std::endl
                  << boost::format ( "%s(%d) - run" )
            % m_name
            % m_state_ptr->get_id() << std::endl
                  << "--------------------------------" << std::endl;

        m_state_ptr->run ( this->shared_from_this(),
                           m_input_data );        

        std::cout << "--------------------------------" << std::endl
                  << boost::format ( "%s(%d) - done" )
            % m_name
            % m_state_ptr->get_id() << std::endl
                  << "--------------------------------" << std::endl
                  << std::endl;

        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "exiting meta_writer::run (id=%d)")
                                          % m_state_ptr->get_id() ) );
    }

    boost::shared_ptr < infrastructure::data_source::data_source_base >
    meta_writer::results (void)
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "inside meta_writer::results (id=%d)")
                                          % m_state_ptr->get_id() ) );

        return m_state_ptr->results();
    }

    void
    meta_writer::set_state ( boost::uint32_t mode )
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "inside meta_writer::set_state (id=%d)")
                                          % m_state_ptr->get_id() ) );

        m_state_ptr->switch_state ( mode );
    }

    boost::uint32_t
    meta_writer::get_id (void) const
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "inside meta_writer::get_id (id=%d)")
                                          % m_state_ptr->get_id() ) );

        return m_state_ptr->get_id();
    }
    
    infrastructure::component_data::input_token_t::const_iterator
    meta_writer::get_source_list_begin (void) const
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "inside meta_writer::get_source_list_begin (id=%d)")
                                          % m_state_ptr->get_id() ) );

        return m_state_ptr->get_source_list_begin ();
    }

    infrastructure::component_data::input_token_t::const_iterator
    meta_writer::get_source_list_end (void) const
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "inside meta_writer::get_source_list_end (id=%d)")
                                          % m_state_ptr->get_id() ) );

        return m_state_ptr->get_source_list_end ();
    }

    meta_writer&
    meta_writer::operator= ( meta_writer const& rhs )
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "entering meta_writer::operator= (assignment) (id=%d)")
                                          % m_state_ptr->get_id() ) );

        meta_writer temp ( rhs );
        swap ( temp );

        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "exiting meta_writer::operator= (assignment)  (id=%d)")
                                          % m_state_ptr->get_id() ) );

        return *this;
    }

    void
    meta_writer::swap ( meta_writer& rhs )
    {
        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "entering meta_writer::swap (id=%d)")
                                          % m_state_ptr->get_id() ) );

        m_state_ptr.swap ( rhs.m_state_ptr );

        trace::trace::write_trace ( trace_area::components,
                             trace_level::detail,
                             boost::str ( boost::format ( "exiting meta_writer::swap (id=%d)")
                                          % m_state_ptr->get_id() ) );

    }
  } // namespace component
} // namespace reverse
