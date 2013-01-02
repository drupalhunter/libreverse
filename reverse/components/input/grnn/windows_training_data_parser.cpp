/*  Windows_Training_Data_Parser.cpp

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

#include <reverse/components/input/grnn/windows_training_data_parser.hpp>
#include <reverse/components/input/grnn/windows_training_data.hpp>
#include <reverse/components/input/grnn/training_data.hpp>
#include <reverse/components/input/grnn/training_set.hpp>
#include <reverse/trace.hpp>

//#include <boost/cstdint.hpp>
//#include <boost/make_shared.hpp>

#include <fstream>
//#include <exception>
//#include <iostream>
//#include <sstream>
//#include <vector>


namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	windows_training_data_parser::windows_training_data_parser ()
	  : m_training_data ( new training_data<windows_training_data>() )
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data_Parser constructor" );
	}

	windows_training_data_parser::~windows_training_data_parser()
	{}

	void
	windows_training_data_parser::start_element ( const std::string& element_name,
						      const attribute_map_t& attributes )
	{
	  trace::grnn_detail ( "Entering Windows_Training_Data_Parser::startElement" );
	  trace::grnn_data ( "element_name = %1%", element_name );
	  trace::grnn_data_map ( attributes );

	  m_element_list.push ( element_name );
	  
	  trace::grnn_detail ( "Exiting Windows_Training_Data_Parser::startElement" );
	}

	void
	windows_training_data_parser::char_data ( const std::string& element_value )
	{
	  trace::grnn_detail ( "entering windows_training_data_parser::chardata" );
	  trace::grnn_data ( "element_value = %s", element_value );

	  std::string present_element = m_element_list.top();

	  if ( present_element.compare ( m_tag.tag_target_id ) == 0 )
	    {
	      float target_id = convert_string_to_float ( element_value );

	      trace::grnn_data ( "target id = %1%", target_id );

	      m_training_data->set_attribute ( windows_training_data::attribute_target_id, target_id );
	    }
	  else if ( present_element.compare ( m_tag.tag_file_size ) == 0 )
	    {
	      float filesize = convert_string_to_float ( element_value );

	      m_training_data->set_attribute ( windows_training_data::attribute_filesize, filesize );

	      trace::grnn_data ( "file size = %1%", filesize );
	    }
	  else if ( present_element.compare ( m_tag.tag_exe_header_address ) == 0 )
	    {
	      this->process_value ( m_tag.tag_exe_header_address,
				    windows_training_data::attribute_exe_header_address,
				    element_value );
	    }
	  else if ( present_element.compare ( m_tag.tag_coff_section_count ) == 0 )
	    {
	      this->process_value ( m_tag.tag_coff_section_count,
				    windows_training_data::attribute_coff_section_count,
				    element_value );
	    }
	  else if ( present_element.compare ( m_tag.tag_pe_opt_code_size ) == 0 )
	    {
	      this->process_value ( m_tag.tag_pe_opt_code_size,
				    windows_training_data::attribute_pe_opt_code_size,
				    element_value );
	    }
	  else if ( present_element.compare ( m_tag.tag_pe_opt_base_of_data ) == 0 )
	    {
	      this->process_value ( m_tag.tag_pe_opt_base_of_data,
				    windows_training_data::attribute_pe_opt_base_of_data,
				    element_value );
	    }
	  else if ( present_element.compare ( m_tag.tag_pe_opt_entry_point ) == 0 )
	    {
	      this->process_value ( m_tag.tag_pe_opt_entry_point,
				    windows_training_data::attribute_pe_opt_entry_point,
				    element_value );
	    }
	  else if ( present_element.compare ( m_tag.tag_pe_opt_image_size ) == 0 )
	    {
	      this->process_value ( m_tag.tag_pe_opt_image_size,
				    windows_training_data::attribute_pe_opt_image_size,
				    element_value );
	    }
	  
	  trace::grnn_detail ( "exiting windows_training_data_parser::chardata" );
	}

	void
	windows_training_data_parser::end_element ( const std::string& element_name )
	{
	  trace::grnn_detail ( "entering windows_training_data_parser::endelement" );
	  trace::grnn_data ( "element_name = %s", element_name );

	  if ( element_name.compare ( m_tag.tag_file ) == 0 )
	    {
	      trace::grnn_detail ( "closing file tag" );

	      // save parsed training data
	      this->m_data->data_push_back ( m_training_data );

	      m_training_data = boost::make_shared < training_data < windows_training_data > > ();
	    }

	  trace::grnn_detail ( "exiting windows_training_data_parser::endelement" );
	}

	boost::shared_ptr < training_set<windows_training_data> >
	windows_training_data_parser::get_data ( std::string const& target_file )
	{
	  trace::grnn_detail ( "entering windows_training_data_parser::get_data" );
	  trace::grnn_data ( "reading data from %s", target_file );

	  if ( ! this->create_parser() )
	    {
	      std::cerr << "unknown parser error - error creating parser" << std::endl;
	      abort();
	    }

	  // reset the compiler id and training_set
	  m_data->clear();
	  
	  // class and local variable initialization
	  std::ifstream input ( target_file.c_str() );
	  
	  std::vector<char> input_data;
        
	  while ( ! input.eof() )
	    {
	      char input_char;
	      input.get ( input_char );
	      input_data.push_back ( input_char );
	    }
	  
	  if ( ! this->parse ( & ( *input_data.begin() ), input_data.size() ) )
	    {
	      std::cerr << boost::format ( "invalid file format (%s) - check the input file for possible error" ) % target_file << std::endl;
	      XML_Error err_ref = this->get_error_code();

	      std::cerr << boost::format ( "error at line %d, column %d: %s" ) % this->get_current_line_number()
		% this->get_current_column_number()
		% this->get_error_string ( err_ref ) << std::endl;
	      abort();
	    }
	  
	  this->destroy_parser();

	  trace::grnn_detail ( "exiting windows_training_data_parser::get_data" );

	  return m_data;
	}

	  void
	  windows_training_data_parser::process_value ( std::string const& tag_value,
							boost::uint32_t attrib_value,
							std::string const& element_value )
	  {
	    trace::grnn_data ( "processing %s% tag", tag_value );

	    m_training_data->set_attribute ( attrib_value,
					     convert_string_to_float ( element_value ) );
	  }

	boost::uint32_t
	windows_training_data_parser::convert_string_to_uint ( std::string const& element_value )
	{
	  trace::grnn_detail ( "entering windows_training_data_parser::convert_string_to_uint" );
	  trace::grnn_data ( "element_value (string) = %1%", element_value );

	  boost::uint32_t value = 0;
	  
	  std::stringstream input;
	  
	  input << element_value;
	  input >> value;

	  trace::grnn_data ( "element_value (uint) = %1$d", value );
	  trace::grnn_detail ( "exiting windows_training_data_parser::convert_string_to_uint" );

	  return value;
	}

	float
	windows_training_data_parser::convert_string_to_float ( std::string const& element_value )
	{
	  trace::grnn_detail ( "entering windows_training_data_parser::convert_string_to_float" );
	  trace::grnn_data ( "element_value = %1%", element_value );

	  float value = 0.0;
	  std::stringstream input;

	  input << element_value;
	  input >> value;
	  
	  trace::grnn_data ( "float value = %1$f", value );
	  trace::grnn_detail ( "exiting windows_training_data_parser::convert_string_to_float" );

	  return value;
	}

	std::string
	windows_training_data_parser::get_attribute ( std::string const& name,
						      const attribute_map_t& attributes )
	{
	  trace::grnn_detail ( "entering windows_training_data_parser::get_attribute" );
	  
	  if ( name.size() == 0 )
	    {
	      std::cerr << "name to search in the list of attributes is empty."
			<< boost::format ( "attribute count: %1%" ) % attributes.size() << std::endl
			<< "terminating program. investigate the input xml file creator or this program to find out why" << std::endl
			<< "we are looking looking for an empty attribute name or have a empty list of attributes." << std::endl;

	      exit ( 1 );
	    }
	  else if ( attributes.size() == 0 )
	    {
	      std::cerr << "attribute list is empty." << std::endl
			<< boost::format ( "name: %1$s (%2$d characters)" ) % name % name.size() << std::endl
		
			<< std::endl
			<< "terminating program. investigate the input xml file creator or this program to find out why" << std::endl
			<< "we are looking looking for an empty attribute name or have a empty list of attributes." << std::endl;
	      
	      exit ( 1 );
	    }
	  
	  attribute_map_t::const_iterator pos = attributes.find ( name );
	  
	  if ( pos == attributes.end() )
	    {
	      std::cerr << "fatal error: the attribute names of the input xml file must match those used in this program." << std::endl
			<< std::endl
			<< "input target was...: " << name << std::endl
			<< std::endl
			<< "terminating program. investigate the input xml file creator or this program to find out why" << std::endl
			<< "we are looking for this input name." << std::endl;
	      exit ( 1 );
	    }
	  
	  trace::grnn_detail ( "exiting windows_training_data_parser::get_attribute" );

	  return ( *pos ).second;
	}

      } // namespace grnn
    } // namespace input 
  } // namespace components
} // namespace reverse
