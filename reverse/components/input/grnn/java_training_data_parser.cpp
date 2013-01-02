/*  Java_Training_Data_Parser.cpp

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

#include <reverse/components/input/grnn/java_training_data_parser.hpp>
#include <reverse/components/input/grnn/java_training_data.hpp>
#include <reverse/components/input/grnn/training_data.hpp>
#include <reverse/components/input/grnn/training_set.hpp>
#include <reverse/reverse.hpp>
#include <reverse/trace.hpp>

#include <boost/cstdint.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>

#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>
#include <vector>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	java_training_data_parser::java_training_data_parser ()
	  : m_training_data ( new training_data<java_training_data> () ),
	    m_constant_pool_index ( java_training_data::attribute_constant_utf8_count )
	{
	  trace::grnn_detail ( "Inside Java_Training_Data_Parser constructor" );
	}
	
	java_training_data_parser::~java_training_data_parser()
	{}
	
	void
	java_training_data_parser::start_element ( const std::string& element_name,
						   const attribute_map_t& attributes )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::startElement" );
	  trace::grnn_data ( "element_name = %1%", element_name );
	  trace::grnn_data_map ( attributes );

	  m_element_list.push ( element_name );

	  if ( element_name.compare ( m_tag.tag_constant_pool_info ) == 0 )
	    {
	      double count = convert_string_to_double ( get_attribute ( m_tag.tag_constant_info_tag_count, attributes ) );
	      double ratio = convert_string_to_double ( get_attribute ( m_tag.tag_constant_info_tag_ratio, attributes ) );
	      
	      m_training_data->set_attribute ( m_constant_pool_index, count );
	      m_training_data->set_attribute ( m_constant_pool_index + 1, ratio );
	      m_constant_pool_index += 2;
	    }
	  else if ( element_name.compare ( m_tag.tag_value ) == 0 )
	    {
	      boost::uint32_t key_value = convert_string_to_uint ( get_attribute ( m_tag.tag_max_value_key, attributes ) );
	      double max_value = convert_string_to_double ( get_attribute ( m_tag.tag_max_value_float, attributes ) );
	      
	      m_max_values.insert ( std::make_pair ( key_value, max_value ) );
	    }
	  
	  trace::grnn_detail ( "Exiting Java_Training_Data_Parser::startElement" );
	}
	
	void
	java_training_data_parser::char_data ( const std::string& element_value )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::charData" );
	  trace::grnn_data ( "element_value = %s", element_value );

	  std::string present_element = m_element_list.top();

	  if ( present_element.compare ( m_tag.tag_target_id ) == 0 )
	    {
	      float target_id = convert_string_to_double ( element_value );

	      trace::grnn_data ( "target id = %1%", target_id );

	      m_training_data->set_attribute ( java_training_data::attribute_target_id,
					       target_id );
	    }
	  else if ( present_element.compare ( m_tag.tag_filesize ) == 0 )
	    {
	      m_training_data->set_attribute ( java_training_data::attribute_filesize,
					       convert_string_to_double ( element_value ) );

	      trace::grnn_data ( "filesize = %1%", convert_string_to_double ( element_value ) );
	      
	    }
	  else if ( present_element.compare ( m_tag.tag_version ) == 0 )
	    {
	      trace::grnn_detail ( "Processing VERSION tag" );

	      m_training_data->set_attribute ( java_training_data::attribute_version,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_this_index ) == 0 )
	    {

	      trace::grnn_detail ( "Processing THIS_INDEX tag" );

	      m_training_data->set_attribute ( java_training_data::attribute_this_index,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_super_index ) == 0 )
	    {
	      trace::grnn_detail ( "Processing SUPER_INDEX tag" );

	      m_training_data->set_attribute ( java_training_data::attribute_super_index,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_constant_pool_count ) == 0 )
	    {

	      trace::grnn_detail ( "Processing CONSTANT_POOL_COUNT tag" );

	      m_training_data->set_attribute ( java_training_data::attribute_constant_pool_count,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_field_count ) == 0 )
	    {
	      trace::grnn_detail ( "Processing TAG FIELD COUNT tag" );

	      m_training_data->set_attribute ( java_training_data::attribute_field_count,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_method_count ) == 0 )
	    {
	      trace::grnn_detail ( "Processing METHOD_COUNT tag" );

	       m_training_data->set_attribute ( java_training_data::attribute_method_count,
						convert_string_to_double ( element_value ) );
	     }

	   trace::grnn_detail ( "Exiting Java_Training_Data_Parser::charData" );
	}

	void
	java_training_data_parser::end_element ( const std::string& element_name )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::end_element" );
	  trace::grnn_data ( "element_name = %s", element_name );

	  if ( element_name.compare ( m_tag.tag_file ) == 0 )
	    {
	      trace::grnn_detail ( "Closing FILE tag" );

	      // Save parsed training data
	      this->m_data->data_push_back ( m_training_data );
	      
	      // Reset for next <FILE> tag
	      m_constant_pool_index = java_training_data::attribute_constant_utf8_count;
	      m_training_data = boost::make_shared < training_data<java_training_data> > ();
	    }

	  trace::grnn_detail ( "Exiting Java_Training_Data_Parser::end_element" );
	}

	boost::shared_ptr < training_set<java_training_data> >
	java_training_data_parser::get_data ( std::string const& target_file )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::get_Data" );
	  trace::grnn_data ( "Reading data from %s", target_file );

	  if ( ! this->create_parser() )
	    {
	      std::cerr << "Unknown Parser Error - error creating parser" << std::endl;
	      abort();
	    }
	  
	  // Reset the compiler id and Training_Set
	  m_data->clear();
	  
	  // Class and local variable initialization
	  std::ifstream input ( target_file.c_str() );
	  
	  std::vector<char> input_data;
	  
	  while ( ! input.eof() )
	    {
	      char input_char;
	      input.get ( input_char );
	      
	      trace::grnn_data ( "Char: %1$X (%2$s)",
				 static_cast<boost::uint16_t>( input_char ),
				 input_char );

	      input_data.push_back ( input_char );
	    }
	  
	  if ( ! this->parse ( & ( *input_data.begin() ), input_data.size() ) )
	    {
	      std::cerr << boost::format ( "Invalid file format (%s) - check the input file for possible error" ) % target_file << std::endl;

	      XML_Error err_ref = this->get_error_code();

	      std::cerr << boost::format ( "error at line %d, column %d: %s" ) % this->get_current_line_number()
		% this->get_current_column_number()
		% this->get_error_string ( err_ref ) << std::endl;
	      abort();
	    }

	  this->destroy_parser();

	  trace::grnn_detail ( "Exiting Java_Training_Data_Parser::get_Data" );

	  return m_data;
	}

	boost::uint32_t
	java_training_data_parser::convert_string_to_uint ( std::string const& element_value )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::convert_String_To_UInt" );
	  trace::grnn_data ( "element_value (string) = %1%", element_value );

	  boost::uint32_t value = 0;

	  std::stringstream input;

	  input << element_value;
	  input >> value;

	  trace::grnn_data ( "element_value (uint) = %1$d", value );
	  trace::grnn_detail ( "Exiting Java_Training_Data_Parser::convert_String_To_UInt" );

	  return value;
	}

	double
	java_training_data_parser::convert_string_to_double ( std::string const& element_value )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::convert_String_To_Double" );
	  trace::grnn_data ( "element_value = %1%", element_value );

	  double value = 0.0;
	  std::stringstream input;

	  input << element_value;
	  input >> value;
	  
	  trace::grnn_data ( "float value = %1$f", value );
	  trace::grnn_detail ( "Exiting Java_Training_Data_Parser::convert_String_To_Double" );

	  return value;
	}

	std::string
	java_training_data_parser::get_attribute ( std::string const& name, const attribute_map_t& attributes )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data_Parser::get_Attribute" );

	  if ( name.size() == 0 )
	    {
	      std::cerr << "Name to search in the list of attributes is empty."
			<< boost::format ( "Attribute count: %1%" ) % attributes.size() << std::endl
			<< "Terminating program. Investigate the input XML file creator or this program to find out why" << std::endl
			<< "we are looking looking for an empty attribute name or have a empty list of attributes." << std::endl;

	      exit ( 1 );
	    }
	  else if ( attributes.size() == 0 )
	    {
	      std::cerr << "Attribute list is empty." << std::endl
			<< boost::format ( "Name: %1$s (%2$d characters)" ) % name % name.size() << std::endl
			<< std::endl
			<< "Terminating program. Investigate the input XML file creator or this program to find out why" << std::endl
			<< "we are looking looking for an empty attribute name or have a empty list of attributes." << std::endl;

	      exit ( 1 );
	    }

	  attribute_map_t::const_iterator pos = attributes.find ( name );

	  if ( pos == attributes.end() )
	    {
	      std::cerr << "FATAL ERROR: The attribute names of the input XML file must match those used in this program." << std::endl
			<< std::endl
			<< "Input target was...: " << name << std::endl
			<< std::endl
			<< "Terminating program. Investigate the input XML file creator or this program to find out why" << std::endl
			<< "we are looking for this input name." << std::endl;
	      exit ( 1 );
	    }
	  

	  trace::grnn_detail ( "Exiting Java_Training_Data_Parser::get_Attribute" );

	  return ( *pos ).second;
	}

	variable_map::map_t&
	java_training_data_parser::get_max_values ( void )
	{
	  return m_max_values;
	}

      } // namespace grnn
    } // namespace input 
  } // namespace components
} // namespace reverse

