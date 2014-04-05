/*  Elf_Training_Data_Parser.cpp

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

#include <reverse/components/input/grnn/elf_training_data_parser.hpp>
//#include <reverse/components/input/grnn/elf_training_data.hpp>
//#include <reverse/components/input/grnn/training_data.hpp>

#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <exception>
#include <fstream>
#include <vector>

#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	elf_training_data_parser::elf_training_data_parser ()
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Inside Elf_Training_Data_Parser constructor" );
#endif /* LIBREVERSE_DEBUG */

	}

	elf_training_data_parser::~elf_training_data_parser()
	{}

	void
	elf_training_data_parser::start_element ( const std::string& element_name,
						 const attribute_map_t& attributes )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::startElement" );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "element_name = %1%" ) % element_name ) );

	  for ( Attribute_Map_t::const_iterator pos = attributes.begin();
		pos != attributes.end();
		++pos )
	    {
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "Key (%1%) -> Data (%2%)" ) % ( *pos ).first % ( *pos ).second ) );
	    }
#endif /* LIBREVERSE_DEBUG */

	  m_element_list.push ( element_name );

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */

	}

	void
	elf_training_data_parser::char_data ( const std::string& element_value )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::charData" );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "element_value = %s" ) % element_value ) );
#endif /* LIBREVERSE_DEBUG */


	  std::string present_element = m_element_list.top();

	  if ( present_element.compare ( m_tag.tag_target_id ) == 0 )
	    {
	      float target_id = convert_string_to_double ( element_value );


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "target id = %1%" ) % target_id ) );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_target_id,
					       target_id );
	    }
	  else if ( present_element.compare ( m_tag.tag_filesize ) == 0 )
	    {
	      m_training_data->set_attribute ( elf_training_data::attribute_filesize,
					       convert_string_to_double ( element_value ) );


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "filesize = %1%" ) % convert_String_To_Double ( element_value ) ) );
#endif /* LIBREVERSE_DEBUG */

	    }
	  else if ( present_element.compare ( m_tag.tag_entry_point_address ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Processing ENTRY_POINT_ADDRESS tag" );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_entry_point_address,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_section_headers_start ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Processing SECTION_HEADERS_START tag" );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_section_headers_start,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_program_header_count ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Processing PROGRAM_HEADER_COUNT tag" );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_program_header_count,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_section_header_count ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Processing SECTION_HEADER_COUNT tag" );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_section_header_count,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_section_header_string_table_index ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Processing TAG SECTION_HEADER_STRING_TABLE_INDEX tag" );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_section_header_string_table_index,
					       convert_string_to_double ( element_value ) );
	    }
	  else if ( present_element.compare ( m_tag.tag_text_section_size ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Processing TEXT_SECTION_SIZE tag" );
#endif /* LIBREVERSE_DEBUG */


	      m_training_data->set_attribute ( elf_training_data::attribute_text_section_size,
					       convert_string_to_double ( element_value ) );
	    }


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */

	}

	void
	elf_training_data_parser::end_element ( const std::string& element_name )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::endElement" );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "element_name = %s" ) % element_name ) );
#endif /* LIBREVERSE_DEBUG */


	  if ( element_name.compare ( m_tag.tag_file ) == 0 )
	    {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   "Closing FILE tag" );
#endif /* LIBREVERSE_DEBUG */


	      // Save parsed training data
	      this->m_data->data_push_back ( m_training_data );

	      // Reset for next <FILE> tag
	      m_training_data = boost::make_shared < training_data<elf_training_data> > ();
	    }


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */

	}

	boost::shared_ptr < training_set<elf_training_data> >
	elf_training_data_parser::get_data ( std::string const& target_file )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::get_Data" );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       boost::str ( boost::format ( "Reading data from %s" ) % target_file ) );
#endif /* LIBREVERSE_DEBUG */


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


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "Char: %1$X (%2$s)" )
						% static_cast<boost::uint16_t>( input_char )
						% input_char ) );
#endif /* LIBREVERSE_DEBUG */


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

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Parsed input:" );

	  for ( std::vector < boost::shared_ptr < reverse::components::input::grnn::training_set<elf_training_data>::const_iterator cpos = m_data->begin();
		cpos != m_data->end();
		++cpos )
	    {
	      Trace::write_Trace ( TraceArea::GRNN_PARSER,
				   TraceLevel::DETAIL,
				   ( *cpos )->to_String () );
	    }
#endif /* LIBREVERSE_DEBUG */


	  this->destroy_parser();


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::get_Data" );
#endif /* LIBREVERSE_DEBUG */


	  return m_data;
	}

	boost::uint32_t
	elf_training_data_parser::convert_string_to_uint ( std::string element_value )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::convert_String_To_UInt" );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "element_value (string) = %1%" ) % element_value ) );
#endif /* LIBREVERSE_DEBUG */


	  boost::uint32_t value = 0;

	  std::stringstream input;

	  input << element_value;
	  input >> value;


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "element_value (uint) = %1$d" ) % value ) );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::convert_String_To_UInt" );
#endif /* LIBREVERSE_DEBUG */


	  return value;
	}

	double
	elf_training_data_parser::convert_string_to_double ( std::string element_value )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::convert_String_To_Double" );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "element_value = %1%" ) % element_value ) );
#endif /* LIBREVERSE_DEBUG */


	  double value = 0.0;
	  std::stringstream input;

	  input << element_value;
	  input >> value;


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "float value = %1$f" ) % value ) );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::convert_String_To_Double" );
#endif /* LIBREVERSE_DEBUG */


	  return value;
	}

	std::string
	elf_training_data_parser::get_attribute ( std::string name, const attribute_map_t& attributes )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Entering Elf_Training_Data_Parser::get_Attribute" );
#endif /* LIBREVERSE_DEBUG */


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


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Training_Data_Parser::get_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	  return ( *pos ).second;
	}

	variable_map::map_t&
	elf_training_data_parser::get_max_values ( void )
	{
	  return m_max_values;
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

