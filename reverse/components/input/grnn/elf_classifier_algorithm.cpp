/*  Elf_Classifier_Algorithm.cpp

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

#include <reverse/components/input/grnn/elf_classifier_algorithm.hpp>
#include <reverse/components/input/grnn/variable_map.hpp>

#include <reverse/components/input/grnn/io.hpp>
#include <reverse/components/input/grnn/candidate_solution.hpp>
#include <reverse/components/input/grnn/grnn_data_map.hpp>
#include <reverse/components/input/grnn/grnn_data_entry.hpp>
#include <reverse/components/input/grnn/elf_training_data.hpp>
#include <reverse/components/input/grnn/elf_training_data_parser.hpp>

#include <reverse/data_containers/memory_map.hpp>
#include <reverse/infrastructure/component_types.hpp>
#include <reverse/infrastructure/configurator.hpp>
#include <reverse/io/io_types.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/elf/elf_reader.hpp>
#include <reverse/io/input/file_readers/elf/elf_header.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <iostream>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {


	boost::shared_ptr < meta::meta_object >
	elf_classifier_algorithm::execute ( std::string const& target_filename )
	{
	  trace::classifier_detail ( "Entering Elf_Classifier_Algorithm::execute" );

	  //-------------------------------
	  //      Read stored data
	  //-------------------------------

	  // Grab GRNN Data Map
	  boost::shared_ptr < grnn_data_map > grnn_data = (infrastructure::configurator::instance()).get_grnn_data();

	  // Get GRNN Data Entry
	  boost::shared_ptr < const grnn_data_entry > grnn_entry = grnn_data->get_entry ( grnn_data_types::elf_class );
	  
	  // Get sigma value from data map
	  double stored_sigma = grnn_entry->get_sigma();

	  trace::classifier_data ( "Stored sigma: %1%", stored_sigma );

	  // Get location of final training data
	  std::string stored_filename = grnn_entry->get_filename();

	  trace::classifier_data ( "Stored filename: %1%", stored_filename );

	  // Parse final training data
	  boost::shared_ptr < training_set<elf_training_data> > stored_data_set =
	    io < elf_training_data, elf_training_data_parser>::get_data ( stored_filename );

	  trace::classifier_data ( "Dumping parsed input data" );
	  trace::classifier_data ( stored_data_set->to_string() );
      
	  // Verify input data is correct before starting
	  stored_data_set->is_valid();

	  // Collect attributes from target file
	  boost::shared_ptr < io::file_id > target_file_obj = boost::make_shared<io::file_id> ( target_filename );

	  //-------------------------------
	  //       Test reader
	  //-------------------------------	    
	  io::input::file_readers::linux_elf::elf_reader_32 const reader32_obj ( file_obj );
	  boost::shared_ptr < meta_object > results;
	  
	  if ( reader32_obj.support_file_type() )
	    {
	      results = process_file ( reader32_obj );
	    }
	  else
	    {
	      libreverse::elf_module::elf_reader_64 const reader64_obj ( file_obj );
	      
	      if ( reader64_obj.support_file_type() )
		{
		  results = process_file ( reader64_obj );
		}
	    }
	  
	  return results;
	}
	
	std::string
	elf_classifier_algorithm::get_compiler_name ( double value )
	{
	  
	  trace::classifier_detail ( "entering elf_classifier_algorithm::get_compiler_name " );
	  trace::classifier_data ( "input value: %1%", value );

	  boost::int32_t base = static_cast<boost::int32_t>(value);

	  trace::classifier_data ( "Base: %1%", base );

	  double decimal = value - base;

	  trace::classifier_data ( "Decimal: %1%", decimal );

	  if ( decimal >= 0.5 )
	    {
	      base++;
	    }

	  trace::classifier_data ( Final Base: %1%, base );

	  std::string compiler_name = "";
	  switch ( base )
	    {
	    case SUN_JDK_6:
	      compiler_name = "sun_jdk_6";
	      break;
	    case SUN_JDK_5:
	      compiler_name = "sun_jdk_5";
	      break;
	    case ECJ:
	      compiler_name = "eclipse_ecj";
	      break;
	    case JIKES:
	      compiler_name = "ibm_jikes";
	      break;
	    }

	  trace::classifier_detail ( "Exiting Elf_Classifier_Algorithm::get_Compiler_Name" );

	  return compiler_name;
	}

	boost::shared_ptr < meta::meta_object > process_file ( io::input::file_readers::linux_elf::elf_reader_32 const& reader32_obj ) const
	{
	  trace::classifier_detail ( "Enering elf_classifier_algorithm ( elf_reader_32 )" );

	  target_reader.read_class_header();

	  boost::shared_ptr < data_containers::memory_map > target_mem_ptr = target_reader.get_memory_map();
	  
	  training_set<elf_training_data>::data_list_t target_data_map;
	  boost::shared_ptr < training_data<elf_training_data> > target_data_ptr =
	    boost::make_shared < training_data<elf_training_data> > ();

	  // save filesize
	  double normalized_filesize = static_cast<double>( target_mem_ptr->size() ) /
	    stored_data_set->get_attribute_maximum ( elf_training_data::attribute_filesize );
	  
	  trace::classifier_data ( "Filesize - original ( %1$d ) == normalized ( %2$1.10f )", 
				   target_mem_ptr->size(),
				   normalized_filesize );
	  
	  target_data_ptr->set_attribute ( elf_training_data::attribute_filesize, normalized_filesize );
      
	  boost::shared_ptr < io::input::file_readers::linux_elf::class_header > target_class_header = target_reader.get_header();
	  
	  // Save
	  // - This index
	  // - super index
	  // - version
	  // - constant pool count
	  double normalized_this_index = static_cast<double>( target_class_header->get_this_class() ) /
	    stored_data_set->get_attribute_maximum ( elf_training_data::attribute_this_index );
	  
	  trace::classifier_data ( "This index - original ( %1$d ) == normalized ( %2$1.10f )",
				   target_class_header->get_this_class(),
				   normalized_this_index );
	  
	  target_data_ptr->set_attribute ( elf_training_data::attribute_this_index, normalized_this_index );
	
	  double normalized_super_index = static_cast<double>( target_class_header->get_super_class() ) /
	    stored_data_set->get_attribute_maximum ( elf_training_data::attribute_super_index );
	  
	  trace::classifier_data ( "super index - original ( %1$d ) == normalized ( %2$1.10f )",
				   target_class_header->get_super_class(),
				   normalized_super_index );

	  target_data_ptr->set_attribute ( elf_training_data::attribute_super_index, normalized_super_index );
	  
	  double version_value = 0.0;
	  std::stringstream input_version;
	  
	  input_version << boost::format ( "%1%.%2%" )
	    % target_class_header->get_Major_Version()
	    % target_class_header->get_Minor_Version();
	  input_version >> version_value;
	  
	  double normalized_version_value = version_value /
	    stored_data_set->get_Attribute_Maximum ( Elf_Training_Data::ATTRIBUTE_VERSION );
	  
	  trace::classifier_data ( "Version - original ( %1$1.10f ) == normalized ( %2$1.10f )",
				   version_value,
				   normalized_version_value );
	  
	  target_data_ptr->set_attribute ( elf_training_data::attribute_version, normalized_version_value );
	
	  double normalized_constant_pool_count = static_cast<double>( target_class_header->get_constant_pool_count() ) /
	    stored_data_set->get_attribute_maximum ( elf_training_data::attribute_constant_pool_count );
	
	  trace::classifier_data ( "constant pool count - original ( %1$d ) == normalized ( %2$1.10f )",
				   target_class_header->get_constant_pool_count(),
				   normalized_constant_pool_count );

	  target_data_ptr->set_attribute ( elf_training_data::attribute_constant_pool_count, normalized_constant_pool_count );
	
	  target_data_map.push_back ( target_data_ptr );
	
	  // Create GRNN
	  classifier_types::configuration<elf_training_data>::ptr_t config_ptr =
	    boost::make_shared < classifier::configuration<elf_training_data> > (true);

	  grnn<elf_training_data> grnn_obj ( stored_sigma,
					     stored_data_set->get_training_data (),
					     target_data_map,
					     config_ptr );

	  // Execute GRNN
	  double results = grnn_obj.classify();

	  trace::classifier_data ( "result of grnn: %1%", results );

	  // Save result
	  boost::shared_ptr < meta::meta_object > meta_obj = boost::make_shared < meta::meta_object > ();

	  meta_obj->add ( "compiler_name", 
			  this->get_compiler_name ( results ),
			  meta::meta_object::string );

	  trace::classifier_detail ( "Exiting Elf_Classifier_Algorithm::execute" );

	  return meta_obj;
	}

      }

      meta::meta_object::ptr_t process_file ( libreverse::elf_module::elf_reader_64 const& reader64_obj ) const;
	
      target_reader.read_class_header();

      boost::shared_ptr < data_containers::memory_map > target_mem_ptr = target_reader.get_memory_map();

      training_set<elf_training_data>::data_list_t target_data_map;
      boost::shared_ptr < training_data<elf_training_data> > target_data_ptr =
	boost::make_shared < training_data<elf_training_data> > ();

      // save filesize
      double normalized_filesize = static_cast<double>( target_mem_ptr->size() ) /
	stored_data_set->get_attribute_maximum ( elf_training_data::attribute_filesize );

      trace::classifier_data ( "Filesize - original ( %1$d ) == normalized ( %2$1.10f )", 
			       target_mem_ptr->size(),
			       normalized_filesize );
	
      target_data_ptr->set_attribute ( elf_training_data::attribute_filesize, normalized_filesize );
      
      boost::shared_ptr < io::input::file_readers::linux_elf::class_header > target_class_header = target_reader.get_header();

      // Save
      // - This index
      // - super index
      // - version
      // - constant pool count
      double normalized_this_index = static_cast<double>( target_class_header->get_this_class() ) /
	stored_data_set->get_attribute_maximum ( elf_training_data::attribute_this_index );

      trace::classifier_data ( "This index - original ( %1$d ) == normalized ( %2$1.10f )",
			       target_class_header->get_this_class(),
			       normalized_this_index );

      target_data_ptr->set_attribute ( elf_training_data::attribute_this_index, normalized_this_index );

      double normalized_super_index = static_cast<double>( target_class_header->get_super_class() ) /
	stored_data_set->get_attribute_maximum ( elf_training_data::attribute_super_index );

      trace::classifier_data ( "super index - original ( %1$d ) == normalized ( %2$1.10f )",
			       target_class_header->get_super_class(),
			       normalized_super_index );

      target_data_ptr->set_attribute ( elf_training_data::attribute_super_index, normalized_super_index );
	
      double version_value = 0.0;
      std::stringstream input_version;
	
      input_version << boost::format ( "%1%.%2%" )
      % target_class_header->get_Major_Version()
      % target_class_header->get_Minor_Version();
      input_version >> version_value;
	
      double normalized_version_value = version_value /
	stored_data_set->get_Attribute_Maximum ( Elf_Training_Data::ATTRIBUTE_VERSION );
	
      trace::classifier_data ( "Version - original ( %1$1.10f ) == normalized ( %2$1.10f )",
			       version_value,
			       normalized_version_value );

      target_data_ptr->set_attribute ( elf_training_data::attribute_version, normalized_version_value );

      double normalized_constant_pool_count = static_cast<double>( target_class_header->get_constant_pool_count() ) /
	stored_data_set->get_attribute_maximum ( elf_training_data::attribute_constant_pool_count );

      trace::classifier_data ( "constant pool count - original ( %1$d ) == normalized ( %2$1.10f )",
			       target_class_header->get_constant_pool_count(),
			       normalized_constant_pool_count );

      target_data_ptr->set_attribute ( elf_training_data::attribute_constant_pool_count, normalized_constant_pool_count );

      target_data_map.push_back ( target_data_ptr );
	
      // Create GRNN
      classifier_types::configuration<elf_training_data>::ptr_t config_ptr =
	boost::make_shared < classifier::configuration<elf_training_data> > (true);

      grnn<elf_training_data> grnn_obj ( stored_sigma,
					 stored_data_set->get_training_data (),
					 target_data_map,
					 config_ptr );

      // Execute GRNN
      double results = grnn_obj.classify();

      trace::classifier_data ( "result of grnn: %1%", results );

      // Save result
      boost::shared_ptr < meta::meta_object > meta_obj = boost::make_shared < meta::meta_object > ();

      meta_obj->add ( "compiler_name", 
		      this->get_compiler_name ( results ),
		      meta::meta_object::string );

      trace::classifier_detail ( "Exiting Elf_Classifier_Algorithm::execute" );

      return meta_obj;
    }
      
  } // namespace grnn
} // namespace input
} // namespace components
} // namespace reverse

