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

#include "Java_Classifier_Algorithm.h"
#include "Variable_Map.h"
#include "GRNN.h"

#include "components/input/grnn/IO.h"
#include "components/input/grnn/Candidate_Solution.h"
#include "components/input/grnn/GRNN_Data_Map.h"
#include "components/input/grnn/GRNN_Data_Entry.h"
#include "components/input/grnn/Java_Training_Data.h"
#include "components/input/grnn/Java_Training_Data_Parser.h"

#include "data_containers/Memory_Map.h"
#include "infrastructure/Component_Types.h"
#include "infrastructure/Configurator.h"
#include "io/IO_Types.h"
#include "io/File_ID.h"
#include "io/input/File_Readers/Java_Class/Reader.h"
#include "io/input/File_Readers/Java_Class/Class_Header.h"

#include <boost/format.hpp>
#include <iostream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace classifier
  {

    meta::Meta_Object::ptr_t
    Java_Classifier_Algorithm::execute ( std::string target_filename )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DETAIL,
			   "Entering Java_Classifier_Algorithm::execute" );
#endif /* LIBREVERSE_DEBUG */


      // Grab GRNN Data Map
      classifier_types::GRNN_Data_Map::ptr_t grnn_data = (infrastructure::Configurator::Instance()).get_GRNN_Data();

      // Get GRNN Data Entry
      classifier_types::GRNN_Data_Entry::const_ptr_t grnn_entry = grnn_data->get_Entry ( GRNN_Data_Types::JAVA_CLASS );

      // Get sigma value from data map
      double stored_sigma = grnn_entry->get_Sigma();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Stored sigma: %1%" ) % stored_sigma ) );
#endif /* LIBREVERSE_DEBUG */


      // Get location of final training data
      std::string stored_filename = grnn_entry->get_Filename();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Stored filename: %1%" ) % stored_filename ) );
#endif /* LIBREVERSE_DEBUG */


      // Parse final training data
     classifier_types::Training_Set<Java_Training_Data>::ptr_t stored_data_set =
	IO<classifier::Java_Training_Data,classifier::Java_Training_Data_Parser>::get_Data ( stored_filename );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   "Dumping parsed input data" );

      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   stored_data_set->to_String() );
#endif /* LIBREVERSE_DEBUG */

      
      // Verify input data is correct before starting
      stored_data_set->is_Valid();

      // Collect attributes from target file

      libreverse::io_types::File_ID::ptr_t target_file_obj = alloc::Create::shared_pointer<libreverse::io::File_ID> ( target_filename );
	    
      libreverse::java_module::Reader target_reader ( target_file_obj );
	    
      target_reader.read_Class_Header();

      libreverse::data_types::Memory_Map::ptr_t target_mem_ptr = target_reader.get_Memory_Map();

      classifier_types::Training_Set<Java_Training_Data>::Data_List_t target_data_map;
      classifier_types::Training_Data<Java_Training_Data>::ptr_t target_data_ptr ( new classifier::Training_Data<Java_Training_Data>() );

      // Save filesize
      double normalized_filesize = static_cast<double>( target_mem_ptr->size() ) /
	stored_data_set->get_Attribute_Maximum ( Java_Training_Data::ATTRIBUTE_FILESIZE );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Filesize - original ( %1$d ) == normalized ( %2$1.10f )" )
					% target_mem_ptr->size()
					% normalized_filesize ) );
#endif /* LIBREVERSE_DEBUG */

	
      target_data_ptr->set_Attribute ( Java_Training_Data::ATTRIBUTE_FILESIZE, normalized_filesize );
      
      java_types::Class_Header::ptr_t target_class_header = target_reader.get_Header();

      // Save
      // - This index
      // - super index
      // - version
      // - constant pool count
      double normalized_this_index = static_cast<double>( target_class_header->get_This_Class() ) /
	stored_data_set->get_Attribute_Maximum ( Java_Training_Data::ATTRIBUTE_THIS_INDEX );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "This index - original ( %1$d ) == normalized ( %2$1.10f )" )
					% target_class_header->get_This_Class()
					% normalized_this_index ) );
#endif /* LIBREVERSE_DEBUG */


      target_data_ptr->set_Attribute ( Java_Training_Data::ATTRIBUTE_THIS_INDEX, normalized_this_index );

      double normalized_super_index = static_cast<double>( target_class_header->get_Super_Class() ) /
	stored_data_set->get_Attribute_Maximum ( Java_Training_Data::ATTRIBUTE_SUPER_INDEX );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Super index - original ( %1$d ) == normalized ( %2$1.10f )" )
					% target_class_header->get_Super_Class()
					% normalized_super_index ) );
#endif /* LIBREVERSE_DEBUG */


      target_data_ptr->set_Attribute ( Java_Training_Data::ATTRIBUTE_SUPER_INDEX, normalized_super_index );

      double version_value = 0.0;
      std::stringstream input_version;
      input_version << boost::format ( "%1%.%2%" )
	% target_class_header->get_Major_Version()
	% target_class_header->get_Minor_Version();
      input_version >> version_value;

      double normalized_version_value = version_value /
	stored_data_set->get_Attribute_Maximum ( Java_Training_Data::ATTRIBUTE_VERSION );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Version - original ( %1$1.10f ) == normalized ( %2$1.10f )" )
					% version_value
					% normalized_version_value ) );
#endif /* LIBREVERSE_DEBUG */


      target_data_ptr->set_Attribute ( Java_Training_Data::ATTRIBUTE_VERSION, normalized_version_value );

      double normalized_constant_pool_count = static_cast<double>( target_class_header->get_Constant_Pool_Count() ) /
	stored_data_set->get_Attribute_Maximum ( Java_Training_Data::ATTRIBUTE_CONSTANT_POOL_COUNT );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Constant pool count - original ( %1$d ) == normalized ( %2$1.10f )" )
					% target_class_header->get_Constant_Pool_Count()
					% normalized_constant_pool_count ) );
#endif /* LIBREVERSE_DEBUG */


      target_data_ptr->set_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_POOL_COUNT, normalized_constant_pool_count );

      target_data_map.push_back ( target_data_ptr );

      // Create GRNN
      classifier_types::Configuration<Java_Training_Data>::ptr_t config_ptr =
	alloc::Create::shared_pointer < classifier::Configuration<Java_Training_Data> > (true);

      GRNN<Java_Training_Data> grnn_obj ( stored_sigma,
					  stored_data_set->get_Training_Data (),
					  config_ptr );

      // Execute GRNN
      classifier_types::Training_Set<Java_Training_Data>::Data_List_t::const_iterator target_data_pos = target_data_map.begin();
      double results = grnn_obj.classify ( target_data_pos );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Result of GRNN: %1%" ) % results ) );;
#endif /* LIBREVERSE_DEBUG */


      // Save result
      meta::Meta_Object::ptr_t meta_obj = alloc::Create::shared_pointer<meta::Meta_Object>();

      meta_obj->add ( "compiler_name", 
		      this->get_Compiler_Name ( results ),
		      meta::Meta_Object::STRING );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Classifier_Algorithm::execute" );
#endif /* LIBREVERSE_DEBUG */


      return meta_obj;
    }

    std::string
    Java_Classifier_Algorithm::get_Compiler_Name ( double value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DETAIL,
			   "Entering Java_Classifier_Algorithm::get_Compiler_Name " );

      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Input Value: %1%" ) % value ) );
#endif /* LIBREVERSE_DEBUG */


      boost::int32_t base = static_cast<boost::int32_t>(value);


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Base: %1%" ) % base ) );
#endif /* LIBREVERSE_DEBUG */


      double decimal = value - base;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Decimal: %1%" ) % decimal ) );
#endif /* LIBREVERSE_DEBUG */


      if ( decimal >= 0.5 )
	{
	  base++;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Final Base: %1%" ) % base ) );
#endif /* LIBREVERSE_DEBUG */


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


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Classifier_Algorithm::get_Compiler_Name" );
#endif /* LIBREVERSE_DEBUG */


      return compiler_name;
    }

  } /* namespace classifier */
} /* namespace libreverse */
