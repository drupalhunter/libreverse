/*  Java_Classifier_Algorithm.cpp

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

#include <reverse/components/input/grnn/configuration.hpp>
#include <reverse/components/input/grnn/java_classifier_algorithm.hpp>
#include <reverse/components/input/grnn/grnn_classifier.hpp>
#include <reverse/components/input/grnn/grnn_data_entry.hpp>
#include <reverse/components/input/grnn/grnn_data_map.hpp>
#include <reverse/components/input/grnn/training_data_parser.hpp>
#include <reverse/components/input/grnn/java_training_data.hpp>
#include <reverse/components/input/grnn/java_training_data_parser.hpp>
#include <reverse/infrastructure/configurator.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/java_class/class_header.hpp>
#include <reverse/io/input/file_readers/java_class/reader.hpp>
#include <reverse/meta/meta_object.hpp>

/*
#include <reverse/components/input/grnn/variable_map.hpp>



#include <reverse/components/input/grnn/candidate_solution.hpp>





#include <reverse/data_containers/memory_map.hpp>
#include <reverse/infrastructure/component_types.hpp>


*/

#include <boost/format.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {


	boost::shared_ptr < meta::meta_object >
	java_classifier_algorithm::execute ( std::string const& target_filename )
	{

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::detail,
			       "Entering Java_Classifier_Algorithm::execute" );
#endif /* LIBREVERSE_DEBUG */


	  // Grab GRNN Data Map
	  boost::shared_ptr < grnn_data_map > grnn_data = (infrastructure::configurator::instance()).get_grnn_data();

	  // Get GRNN Data Entry
	  boost::shared_ptr < const grnn_data_entry > grnn_entry = grnn_data->get_entry ( grnn_data_types::java_class );

	  // Get sigma value from data map
	  double stored_sigma = grnn_entry->get_sigma();


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Stored sigma: %1%" ) % stored_sigma ) );
#endif /* LIBREVERSE_DEBUG */


	  // Get location of final training data
	  std::string stored_filename = grnn_entry->get_filename();


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Stored filename: %1%" ) % stored_filename ) );
#endif /* LIBREVERSE_DEBUG */


	  // Parse final training data
	  boost::shared_ptr < training_set<java_training_data> > stored_data_set =
	    training_data_parser < java_training_data, java_training_data_parser >::get_data ( stored_filename );


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       "Dumping parsed input data" );

	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       stored_data_set->to_String() );
#endif /* LIBREVERSE_DEBUG */

      
	  // Verify input data is correct before starting
	  stored_data_set->is_valid();

	  // Collect attributes from target file

	  boost::shared_ptr < io::file_id > target_file_obj =
	    boost::make_shared < io::file_id > ( target_filename );
	    
	  io::input::file_readers::java_class::reader target_reader ( target_file_obj );
	    
	  target_reader.read_class_header();

	  boost::shared_ptr < data_containers::memory_map > target_mem_ptr = target_reader.get_memory_map();

	  components::input::grnn::training_set<java_training_data> target_data_map;

	  boost::shared_ptr < components::input::grnn::training_data<java_training_data> > target_data_ptr =
	    boost::make_shared < components::input::grnn::training_data<java_training_data> >();

	  // Save filesize
	  double normalized_filesize = static_cast<double>( target_mem_ptr->size() ) /
	    stored_data_set->get_attribute_maximum ( java_training_data::attribute_filesize );


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Filesize - original ( %1$d ) == normalized ( %2$1.10f )" )
					    % target_mem_ptr->size()
					    % normalized_filesize ) );
#endif /* LIBREVERSE_DEBUG */

	
	  target_data_ptr->set_attribute ( java_training_data::attribute_filesize, normalized_filesize );
      
	  boost::shared_ptr < io::input::file_readers::java_class::class_header > target_class_header = target_reader.get_header();

	  // Save
	  // - This index
	  // - super index
	  // - version
	  // - constant pool count
	  double normalized_this_index = static_cast<double>( target_class_header->get_this_class() ) /
	    stored_data_set->get_attribute_maximum ( java_training_data::attribute_this_index );


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "This index - original ( %1$d ) == normalized ( %2$1.10f )" )
					    % target_class_header->get_This_Class()
					    % normalized_this_index ) );
#endif /* LIBREVERSE_DEBUG */

	  target_data_ptr->set_attribute ( java_training_data::attribute_this_index, normalized_this_index );

	  double normalized_super_index = static_cast<double>( target_class_header->get_super_class() ) /
	    stored_data_set->get_attribute_maximum ( java_training_data::attribute_super_index );

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Super index - original ( %1$d ) == normalized ( %2$1.10f )" )
					    % target_class_header->get_Super_Class()
					    % normalized_super_index ) );
#endif /* LIBREVERSE_DEBUG */

	  target_data_ptr->set_attribute ( java_training_data::attribute_super_index, normalized_super_index );

	  double version_value = 0.0;
	  std::stringstream input_version;
	  input_version << boost::format ( "%1%.%2%" )
	    % target_class_header->get_major_version()
	    % target_class_header->get_minor_version();
	  input_version >> version_value;

	  double normalized_version_value = version_value /
	    stored_data_set->get_attribute_maximum ( java_training_data::attribute_version );

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Version - original ( %1$1.10f ) == normalized ( %2$1.10f )" )
					    % version_value
					    % normalized_version_value ) );
#endif /* LIBREVERSE_DEBUG */

	  target_data_ptr->set_attribute ( java_training_data::attribute_version, normalized_version_value );

	  double normalized_constant_pool_count = static_cast<double>( target_class_header->get_constant_pool_count() ) /
	    stored_data_set->get_attribute_maximum ( java_training_data::attribute_constant_pool_count );

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::CLASSIFIER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Constant pool count - original ( %1$d ) == normalized ( %2$1.10f )" )
					    % target_class_header->get_Constant_Pool_Count()
					    % normalized_constant_pool_count ) );
#endif /* LIBREVERSE_DEBUG */

	  target_data_ptr->set_attribute ( java_training_data::attribute_constant_pool_count, normalized_constant_pool_count );

	  target_data_map.data_push_back ( target_data_ptr );

	  // Create GRNN
	  boost::shared_ptr < configuration<java_training_data> > config_ptr =
	    boost::make_shared < configuration<java_training_data> > (true);

	  grnn_classifier<java_training_data> grnn_obj ( stored_sigma,
							 stored_data_set->get_training_data (),
							 config_ptr );

	  // Execute GRNN
	  std::vector< boost::shared_ptr < reverse::components::input::grnn::training_set<java_training_data> > >::const_iterator target_data_pos =
	    target_data_map.data_begin();

	  double results = grnn_obj.classify ( target_data_pos );

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Result of GRNN: %1%" ) % results ) );;
#endif /* LIBREVERSE_DEBUG */


	  // Save result
	  boost::shared_ptr < meta::meta_object > meta_obj = boost::make_shared <meta::meta_object> ();

	  meta_obj->add ( "compiler_name", 
			  this->get_compiler_name ( results ),
			  meta::meta_object::string );


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::detail,
			       "Exiting Java_Classifier_Algorithm::execute" );
#endif /* LIBREVERSE_DEBUG */


	  return meta_obj;
	}

	std::string
	java_classifier_algorithm::get_compiler_name ( double value )
	{

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::detail,
			       "Entering Java_Classifier_Algorithm::get_Compiler_Name " );

	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Input Value: %1%" ) % value ) );
#endif /* LIBREVERSE_DEBUG */


	  boost::int32_t base = static_cast<boost::int32_t>(value);


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Base: %1%" ) % base ) );
#endif /* LIBREVERSE_DEBUG */


	  double decimal = value - base;


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Decimal: %1%" ) % decimal ) );
#endif /* LIBREVERSE_DEBUG */


	  if ( decimal >= 0.5 )
	    {
	      base++;
	    }


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::data,
			       boost::str ( boost::format ( "Final Base: %1%" ) % base ) );
#endif /* LIBREVERSE_DEBUG */


	  std::string compiler_name = "";
	  switch ( base )
	    {
	    case sun_jdk_6:
	      compiler_name = "sun_jdk_6";
	      break;
	    case sun_jdk_5:
	      compiler_name = "sun_jdk_5";
	      break;
	    case ecj:
	      compiler_name = "eclipse_ecj";
	      break;
	    case jikes:
	      compiler_name = "ibm_jikes";
	      break;
	    }


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::classifier,
			       trace_level::detail,
			       "Exiting Java_Classifier_Algorithm::get_Compiler_Name" );
#endif /* LIBREVERSE_DEBUG */


	  return compiler_name;
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

