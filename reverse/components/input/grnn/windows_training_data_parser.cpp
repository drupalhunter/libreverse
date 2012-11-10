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

#include "Windows_Training_Data_Parser.h"
#include "Windows_Training_Data.h"

#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>
#include <boost/cstdint.hpp>
#include <vector>

namespace libreverse
{
  namespace classifier
  {

    Windows_Training_Data_Parser::Windows_Training_Data_Parser ()
      : m_training_data ( alloc::Create::shared_pointer <Training_Data<Windows_Training_Data> >() )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data_Parser constructor" );
    }

    Windows_Training_Data_Parser::~Windows_Training_Data_Parser()
    {}

    void
    Windows_Training_Data_Parser::startElement ( const std::string& element_name,
						 const Attribute_Map_t& attributes )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::startElement" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_name = %1%" ) % element_name ) );

#ifdef LIBREVERSE_DEBUG
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

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::startElement" );
    }

    void
    Windows_Training_Data_Parser::charData ( const std::string& element_value )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::charData" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_value = %s" ) % element_value ) );

      std::string present_element = m_element_list.top();

      if ( present_element.compare ( m_tag.TAG_TARGET_ID ) == 0 )
        {
	  float target_id = convert_String_To_Float ( element_value );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target id = %1%" ) % target_id ) );

	  m_training_data->set_Attribute ( Windows_Training_Data::ATTRIBUTE_TARGET_ID, target_id );
	}
      else if ( present_element.compare ( m_tag.TAG_FILE_SIZE ) == 0 )
        {
	  float filesize = convert_String_To_Float ( element_value );

	  m_training_data->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, filesize );

	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "file size = %1%" ) % filesize ) );
        }
      else if ( present_element.compare ( m_tag.TAG_EXE_HEADER_ADDRESS ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_EXE_HEADER_ADDRESS,
				Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS,
				element_value );
        }
      else if ( present_element.compare ( m_tag.TAG_COFF_SECTION_COUNT ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_COFF_SECTION_COUNT,
				Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT,
				element_value );
        }
      /*
      else if ( present_element.compare ( m_tag.TAG_PE_OPT_LINKER_VERSION ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_PE_OPT_LINKER_VERSION,
				Windows_Training_Data::ATTRIBUTE_PE_OPT_LINKER_VERSION,
				element_value );
        }
      */
      else if ( present_element.compare ( m_tag.TAG_PE_OPT_CODE_SIZE ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_PE_OPT_CODE_SIZE,
				Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE,
				element_value );
        }
      else if ( present_element.compare ( m_tag.TAG_PE_OPT_BASE_OF_DATA ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_PE_OPT_BASE_OF_DATA,
				Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA,
				element_value );
        }
      else if ( present_element.compare ( m_tag.TAG_PE_OPT_ENTRY_POINT ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_PE_OPT_ENTRY_POINT,
				Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT,
				element_value );
        }
      else if ( present_element.compare ( m_tag.TAG_PE_OPT_IMAGE_SIZE ) == 0 )
        {
	  this->process_Value ( m_tag.TAG_PE_OPT_IMAGE_SIZE,
				Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE,
				element_value );
        }

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::charData" );
    }

    void
    Windows_Training_Data_Parser::endElement ( const std::string& element_name )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::endElement" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_name = %s" ) % element_name ) );

      if ( element_name.compare ( m_tag.TAG_FILE ) == 0 )
        {
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Closing FILE tag" );
	  // Save parsed training data
	  this->m_data.push_back ( m_training_data );

	  m_training_data = alloc::Create::shared_pointer < Training_Data<Windows_Training_Data> > ();
        }

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::endElement" );
    }

    classifier_types::Training_Set<Windows_Training_Data>::Data_List_t
    Windows_Training_Data_Parser::get_Data ( std::string target_file )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::get_Data" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   boost::str ( boost::format ( "Reading data from %s" ) % target_file ) );

      if ( ! this->createParser() )
        {
	  std::cerr << "Unknown Parser Error - error creating parser" << std::endl;
	  abort();
        }

      // Reset the compiler id and Training_Set
      m_data.clear();

      // Class and local variable initialization
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
	  std::cerr << boost::format ( "Invalid file format (%s) - check the input file for possible error" ) % target_file << std::endl;
	  XML_Error err_ref = this->getErrorCode();
	  std::cerr << boost::format ( "Error at line %d, column %d: %s" ) % this->getCurrentLineNumber()
	    % this->getCurrentColumnNumber()
	    % this->getErrorString ( err_ref ) << std::endl;
	  abort();
        }



#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   "Parsed input:" );

      for ( classifier_types::Training_Set<Windows_Training_Data>::Data_List_t::const_iterator cpos = m_data.begin();
	    cpos != m_data.end();
	    ++cpos )
        {
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       ( *cpos )->to_String () );
        }
#endif /* LIBREVERSE_DEBUG */

      this->destroyParser();

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::get_Data" );

      return m_data;
    }

    boost::uint32_t
    Windows_Training_Data_Parser::convert_String_To_UInt ( std::string element_value )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::convert_String_To_UInt" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_value (string) = %1%" ) % element_value ) );

      boost::uint32_t value = 0;

      std::stringstream input;

      input << element_value;
      input >> value;

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_value (uint) = %1$d" ) % value ) );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::convert_String_To_UInt" );

      return value;
    }

    float
    Windows_Training_Data_Parser::convert_String_To_Float ( std::string element_value )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::convert_String_To_Float" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_value = %1%" ) % element_value ) );

      float value = 0.0;
      std::stringstream input;

      input << element_value;
      input >> value;

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "float value = %1$f" ) % value ) );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::convert_String_To_Float" );

      return value;
    }

    std::string
    Windows_Training_Data_Parser::get_Attribute ( std::string name, const Attribute_Map_t& attributes )
    {
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data_Parser::get_Attribute" );

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

      Attribute_Map_t::const_iterator pos = attributes.find ( name );

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

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data_Parser::get_Attribute" );

      return ( *pos ).second;
    }

  } /* namespace classifier */
} /* namespace libreverse */
