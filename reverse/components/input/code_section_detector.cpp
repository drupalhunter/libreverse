/*  Code_Section_Detector.cpp

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

#include <reverse/components/input/code_section_detector.hpp>
#include <reverse/components/input/code_section_detector_algorithm.hpp>
#include <reverse/components/input/code_section_detector_algorithm_factory.hpp>
#include <reverse/data_containers/filename.hpp>
#include <reverse/errors/api_exception.hpp>
#include <reverse/infrastructure/data_source/data_source_factory.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/reader_factory.hpp>
#include <reverse/io/input/file_readers/file_reader.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/meta/meta_object.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

namespace reverse {
  namespace component {
    namespace input {

      const std::string code_section_detector::code_section_address_meta_format = "code_section_address:%1%";
      const std::string code_section_detector::code_section_size_meta_format = "code_section_size:%1%";
      const std::string code_section_detector::m_name = "code_section_detector";

      code_section_detector::code_section_detector ()
	: m_state_ptr ( new infrastructure::component_state (0) )
      {
	trace::components_detail ( "Inside code_section_detector constructor" );
      }

      code_section_detector::code_section_detector( boost::shared_ptr < infrastructure::component_state > state_ptr )
	: m_state_ptr ( state_ptr )
      {
	trace::components_detail ( "Inside code_section_detector constructor (state_ptr) ");
      }

      code_section_detector::code_section_detector ( code_section_detector const& rhs )
	: infrastructure::component ( rhs ),
	  infrastructure::component_actor ( rhs ),
	  boost::enable_shared_from_this<code_section_detector> ( rhs ),
	  m_state_ptr ( new infrastructure::component_state ( *rhs.m_state_ptr ) )
      {
	trace::components_detail ( "Inside code_section_detector copy_constructor" );
      }

      code_section_detector::~code_section_detector ()
      {
	trace::components_detail ( "Inside code_section_detector destructor" );
      }

      void
      code_section_detector::received_input_source_data ( boost::uint32_t id )
      {
	trace::components_detail ( "Entering code_section_detector::received_input_source_data" );

	m_state_ptr->received_input_source_data ( id );

	trace::components_detail ( "Exiting code_section_detector::received_input_source_data" );
      }

      void
      code_section_detector::add_input_source ( boost::uint32_t id )
      {
	trace::components_detail ( "Inside code_section_detector::add_input_source" );

	m_state_ptr->add_input_source ( id );
      }

      std::string
      code_section_detector::get_name (void) const
      {
	trace::components_detail ( "Inside code_section_detector::get_name" );

	return m_name;
      }

      void code_section_detector::process ()
      {
	trace::components_detail ( "Entering Code_Section_Detector::process" );

	boost::shared_ptr < infrastructure::component_data > data_ptr = m_state_ptr->get_data();

	if ( ! data_ptr->is_filename_set() )
	  {
	    trace::components_error ( "Unable to find the input file name." );
	    trace::components_error ( "Cannot find the arch type without it." );
	    trace::components_error ( "Exception throw in %s at line %d", __FILE__,  __LINE__ );

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

	assert ( file_type_meta_value.second == meta::meta_object::string );

	std::string file_type = file_type_meta_value.first;

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/
	boost::shared_ptr < code_section_detector_algorithm > algorithm_ptr =
	  code_section_detector_algorithm_factory::instance().get_algorithm ( file_type );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/
	boost::shared_ptr < const data_container::filename > file_ptr = data_ptr->get_input_filename();
	boost::shared_ptr < const io::file_id > file_id_ptr = boost::make_shared < io::file_id > ( file_ptr->to_string() );
	boost::shared_ptr < meta::meta_object > code_section_meta_ptr = algorithm_ptr->run ( file_id_ptr );

	/**
	 * add input filename to output information
	 */
	data_ptr->set_output_data ( file_ptr );
	data_ptr->set_output_meta_data ( code_section_meta_ptr );

	trace::components_detail ( "Exiting Code_Section_Detector::process" );
      }

      void
      code_section_detector::run ( infrastructure::component_graph::data_map_t* m_input_data )
      {
	trace::components_detail ( "Entering Code_Section_Detector::run" );

	m_state_ptr->run ( this->shared_from_this(),
			   m_input_data );        
      
	trace::components_detail ( "Exiting Code_Section_Detector::run" );
      }

      boost::shared_ptr < infrastructure::data_source::data_source_base >
      code_section_detector::results (void)
      {
	trace::components_detail ( "Inside Code_Section_Detector::results" );

	return m_state_ptr->results();
      }

      void
      code_section_detector::set_state ( boost::uint32_t mode )
      {
	trace::components_detail ( "Inside Code_Section_Detector::set_State" );

	m_state_ptr->switch_state ( mode );
      }

      boost::uint32_t
      code_section_detector::get_id (void) const
      {
	trace::components_detail ( "Inside Code_Section_Detector::get_ID (id=%d)" );

	return m_state_ptr->get_id();
      }
       
      infrastructure::component_data::input_token_t::const_iterator
      code_section_detector::get_source_list_begin (void) const
      {
	trace::components_detail ( "Inside Code_Section_Detector::get_Source_List_Begin" );
      	
	return m_state_ptr->get_source_list_begin ();
      }

      infrastructure::component_data::input_token_t::const_iterator
      code_section_detector::get_source_list_end (void) const
      {
	trace::components_detail ( "Inside Code_Section_Detector::get_Source_List_End" );

	return m_state_ptr->get_source_list_end ();
      }

      code_section_detector&
      code_section_detector::operator= ( code_section_detector const& rhs )
      {
	trace::components_detail ( "Entering Code_Section_Detector::operator= (assignment)" );

	code_section_detector temp ( rhs );
	swap ( temp );

	trace::components_detail ( "Exiting Code_Section_Detector::operator= (assignment)" );

	return *this;
      }

      void
      code_section_detector::swap ( code_section_detector& rhs )
      {
	trace::components_detail ( "Entering Code_Section_Detector::swap" );

	m_state_ptr.swap ( rhs.m_state_ptr );

	trace::components_detail ( "Exiting Code_Section_Detector::swap" );
      }

    } // namespace input
  } /* namespace component */
} /* namespace libreverse */
