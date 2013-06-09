/*  Arch_Type_Detector.cpp

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

#include <reverse/components/input/arch_type_detector.hpp>
#include <reverse/components/input/arch_type_detector_algorithm.hpp>
#include <reverse/components/input/arch_type_detector_algorithm_factory.hpp>

#include <reverse/meta/meta_object.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/reader_factory.hpp>
#include <reverse/io/input/file_readers/file_reader.hpp>
#include <reverse/errors/api_exception.hpp>
#include <reverse/data_containers/filename.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

#include <iostream>

namespace reverse {
  namespace component {
    namespace input {

      const std::string arch_type_detector::name = "Arch_Type_Detector";

      arch_type_detector::arch_type_detector ()
        : m_state_ptr ( new infrastructure::component_state ( 0 ) )
      {
	trace::components_detail ( "Inside Arch_Type_Detector constructor." );
      }

      arch_type_detector::arch_type_detector( boost::shared_ptr < infrastructure::component_state > input_ptr )
        : m_state_ptr ( input_ptr )
      {
	trace::components_detail ( "Inside Arch_Type_Detector constructor." );
      }

      arch_type_detector::arch_type_detector ( arch_type_detector const& rhs )
        : infrastructure::component ( rhs ),
          infrastructure::component_actor ( rhs ),
          boost::enable_shared_from_this<arch_type_detector> ( rhs ),
          m_state_ptr ( new infrastructure::component_state ( *rhs.m_state_ptr ) )
      {
	trace::components_detail ( "Inside Arch_Type_Detector copy constructor.");
      }

      arch_type_detector::~arch_type_detector ()
      {
	trace::components_detail ( "Inside Arch_Type_Detector destructor.");
      }

      void
      arch_type_detector::received_input_source_data ( boost::uint32_t id )
      {
	trace::components_detail ( "Entering Arch_Type_Detector::received_Input_Source_Data." );
      
	m_state_ptr->received_input_source_data ( id );

	trace::components_detail ( "Exiting Arch_Type_Detector::received_Input_Source_Data.");
      }

      void
      arch_type_detector::add_input_source ( boost::uint32_t id )
      {
	trace::components_detail ( "Entering Arch_Type_Detector::add_Input_Source.");

	m_state_ptr->add_input_source ( id );

	trace::components_detail ( "Exiting Arch_Type_Detector::add_Input_Source/ ");
      }

      std::string
      arch_type_detector::get_name (void) const
      {
	trace::components_detail ( "Inside Arch_Type_Detector::get_Name." );

	return name;
      }

      void arch_type_detector::process ()
      {
	trace::components_detail ( "Entering Arch_Type_Detector::process." );

	boost::shared_ptr < infrastructure::component_data > data_ptr = m_state_ptr->get_data();

	if ( ! data_ptr->is_filename_set() )
	  {
	    trace::components_error ( "Unable to find the input file name." );
	    trace::components_error ( "Cannot find the arch type without it." );
	    trace::components_error ( "Exception throw in %s at line", __FILE__, __LINE__ );

	    // At this point we have not found the filename somehow
	    // the Precondition visitor did not work. So we will
	    // will throw an exception
	    throw ( errors::api_exception ( errors::api_exception::internal_library_error ) );
	  }

	/*---------------------------------*/
	/*          Get File Type          */
	/*---------------------------------*/
	boost::shared_ptr < const meta::meta_object > input_meta_ptr = data_ptr->get_input_meta_data();
	meta::meta_object::data_pair_t file_type_meta_value = input_meta_ptr->get_value ( "file_type" );

	std::string file_type = file_type_meta_value.first;

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/
	boost::shared_ptr < arch_type_detector_algorithm > algorithm_ptr = arch_type_detector_algorithm_factory::instance().get_algorithm ( file_type );
      
	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/
	boost::shared_ptr < const data_container::filename > file_ptr = data_ptr->get_input_filename();

	boost::shared_ptr < const io::file_id > file_id_ptr ( new io::file_id ( file_ptr->to_string() ) );

	std::string arch_type = algorithm_ptr->run ( file_id_ptr );

	trace::components_data ( "Arch Type Found: ", arch_type  );

	/**
	 * add input filename to output information
	 */
	data_ptr->set_output_data ( file_ptr );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/
	/*
	 * add file type to output meta information
	 */
	boost::shared_ptr < meta::meta_object> meta_ptr = boost::make_shared <meta::meta_object>();

	meta_ptr->add ( "arch_type",
			arch_type,
			meta::meta_object::string );

	data_ptr->set_output_meta_data ( meta_ptr );

	trace::components_data ( "Exiting Arch_Type_Detector::process", m_state_ptr->get_id() );
      }

      void
      arch_type_detector::run ( infrastructure::component_graph::data_map_t* m_input_data )
      {
	trace::components_data ( "Entering Arch_Type_Detector::run", m_state_ptr->get_id() );

	m_state_ptr->run ( this->shared_from_this(),
			   m_input_data );        

	trace::components_data ( "Exiting Arch_Type_Detector::run", m_state_ptr->get_id() );
      }

      boost::shared_ptr < infrastructure::data_source::data_source_base >
      arch_type_detector::results (void)
      {
	trace::components_data ( "Inside Arch_Type_Detector::results", m_state_ptr->get_id() );
	
	return m_state_ptr->results();
      }

      void
      arch_type_detector::set_state ( boost::uint32_t mode )
      {
	trace::components_data ( "Entering Arch_Type_Detector::set_State", m_state_ptr->get_id() );
	
	m_state_ptr->switch_state ( mode );

	trace::components_data ( "Exiting Arch_Type_Detector::set_State", m_state_ptr->get_id() );
      }

      boost::uint32_t
      arch_type_detector::get_id (void) const
      {
	trace::components_data ( "Inside Arch_Type_Detector::set_State", m_state_ptr->get_id() );
	
	return m_state_ptr->get_id();
      }
    
      infrastructure::component_data::input_token_t::const_iterator
      arch_type_detector::get_source_list_begin (void) const
      {
	trace::components_data ( "Inside Arch_Type_Detector::get_Source_List_Begin", m_state_ptr->get_id() );

        return m_state_ptr->get_source_list_begin ();
      }

      infrastructure::component_data::input_token_t::const_iterator
      arch_type_detector::get_source_list_end (void) const
      {
	trace::components_data ( "Inside Arch_Type_Detector::get_Source_List_End", m_state_ptr->get_id() );

	return m_state_ptr->get_source_list_end ();
      }

      arch_type_detector&
      arch_type_detector::operator= ( arch_type_detector const& rhs )
      {
	trace::components_data ( "Entering Arch_Type_Detector::operator= (assignment)", m_state_ptr->get_id() );

	arch_type_detector temp ( rhs );
	swap ( temp );

	trace::components_data ( "Exiting Arch_Type_Detector::operator= (assignment)", m_state_ptr->get_id() );

	return *this;
      }

      void
      arch_type_detector::swap ( arch_type_detector& rhs )
      {
	trace::components_data ( "Entering Arch_Type_Detector::swap", m_state_ptr->get_id() );

	m_state_ptr.swap ( rhs.m_state_ptr );

	trace::components_data ( "Exiting Arch_Type_Detector::swap", m_state_ptr->get_id() );
      }

      boost::shared_ptr < infrastructure::component >
      arch_type_detector::operator() ( boost::shared_ptr < infrastructure::component_state > data_ptr )
      {
	trace::components_detail ( "Inside Arch_Type_Detector::operator()" );

	return boost::make_shared < arch_type_detector > ( data_ptr );
      }

    } /* namespace input */
  } /* namespace component */
} /* namespace reverse */
