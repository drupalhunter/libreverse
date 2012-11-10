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

#include "Java_Training_Data_Parser.h"
#include "Java_Training_Data.h"
#include "Training_Data.h"
#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>
#include <boost/cstdint.hpp>
#include <vector>
#include <boost/format.hpp>

#include "Reverse.h"
#include "Create.h"

using namespace libreverse::api;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace classifier
  {
    Java_Training_Data_Parser::Java_Training_Data_Parser ()
      : m_training_data ( new classifier::Training_Data<Java_Training_Data> () ),
	m_constant_pool_index ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_COUNT )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data_Parser constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Java_Training_Data_Parser::~Java_Training_Data_Parser()
    {}

    void
    Java_Training_Data_Parser::startElement ( const std::string& element_name,
					      const Attribute_Map_t& attributes )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::startElement" );

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

      if ( element_name.compare ( m_tag.TAG_CONSTANT_POOL_INFO ) == 0 )
        {
	  double count = convert_String_To_Double ( get_Attribute ( m_tag.TAG_CONSTANT_INFO_TAG_COUNT, attributes ) );
	  double ratio = convert_String_To_Double ( get_Attribute ( m_tag.TAG_CONSTANT_INFO_TAG_RATIO, attributes ) );

	  m_training_data->set_Attribute ( m_constant_pool_index, count );
	  m_training_data->set_Attribute ( m_constant_pool_index + 1, ratio );
	  m_constant_pool_index += 2;
        }
      else if ( element_name.compare ( m_tag.TAG_VALUE ) == 0 )
        {
	  boost::uint32_t key_value = convert_String_To_UInt ( get_Attribute ( m_tag.TAG_MAX_VALUE_KEY, attributes ) );
	  double max_value = convert_String_To_Double ( get_Attribute ( m_tag.TAG_MAX_VALUE_FLOAT, attributes ) );

	  m_max_values.insert ( std::make_pair ( key_value, max_value ) );
        }

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Java_Training_Data_Parser::charData ( const std::string& element_value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::charData" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_value = %s" ) % element_value ) );
#endif /* LIBREVERSE_DEBUG */


      std::string present_element = m_element_list.top();

      if ( present_element.compare ( m_tag.TAG_TARGET_ID ) == 0 )
        {
	  float target_id = convert_String_To_Double ( element_value );


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target id = %1%" ) % target_id ) );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_TARGET_ID,
					   target_id );
        }
      else if ( present_element.compare ( m_tag.TAG_FILESIZE ) == 0 )
        {
	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_FILESIZE,
					   convert_String_To_Double ( element_value ) );


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "filesize = %1%" ) % convert_String_To_Double ( element_value ) ) );
#endif /* LIBREVERSE_DEBUG */

        }
      else if ( present_element.compare ( m_tag.TAG_VERSION ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Processing VERSION tag" );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_VERSION,
					   convert_String_To_Double ( element_value ) );
        }
      else if ( present_element.compare ( m_tag.TAG_THIS_INDEX ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Processing THIS_INDEX tag" );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_THIS_INDEX,
					   convert_String_To_Double ( element_value ) );
        }
      else if ( present_element.compare ( m_tag.TAG_SUPER_INDEX ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Processing SUPER_INDEX tag" );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_SUPER_INDEX,
					   convert_String_To_Double ( element_value ) );
        }
      else if ( present_element.compare ( m_tag.TAG_CONSTANT_POOL_COUNT ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Processing CONSTANT_POOL_COUNT tag" );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_POOL_COUNT,
					   convert_String_To_Double ( element_value ) );
        }
      else if ( present_element.compare ( m_tag.TAG_FIELD_COUNT ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Processing TAG FIELD COUNT tag" );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_FIELD_COUNT,
					   convert_String_To_Double ( element_value ) );
        }
      else if ( present_element.compare ( m_tag.TAG_METHOD_COUNT ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Processing METHOD_COUNT tag" );
#endif /* LIBREVERSE_DEBUG */


	  m_training_data->set_Attribute ( Java_Training_Data::ATTRIBUTE_METHOD_COUNT,
					   convert_String_To_Double ( element_value ) );
        }


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Java_Training_Data_Parser::endElement ( const std::string& element_name )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::endElement" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "element_name = %s" ) % element_name ) );
#endif /* LIBREVERSE_DEBUG */


      if ( element_name.compare ( m_tag.TAG_FILE ) == 0 )
        {


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       "Closing FILE tag" );
#endif /* LIBREVERSE_DEBUG */


	  // Save parsed training data
	  this->m_data.push_back ( m_training_data );

	  // Reset for next <FILE> tag
	  m_constant_pool_index = Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_COUNT;
	  m_training_data = alloc::Create::shared_pointer < Training_Data<Java_Training_Data> > ();
        }


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */

    }

    classifier_types::Training_Set<Java_Training_Data>::Data_List_t&
    Java_Training_Data_Parser::get_Data ( std::string target_file )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::get_Data" );

      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   boost::str ( boost::format ( "Reading data from %s" ) % target_file ) );
#endif /* LIBREVERSE_DEBUG */


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

      for ( classifier_types::Training_Set<Java_Training_Data>::Data_List_t::const_iterator cpos = m_data.begin();
	    cpos != m_data.end();
	    ++cpos )
        {
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DETAIL,
			       ( *cpos )->to_String () );
        }
#endif /* LIBREVERSE_DEBUG */


      this->destroyParser();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data_Parser::get_Data" );
#endif /* LIBREVERSE_DEBUG */


      return m_data;
    }

    boost::uint32_t
    Java_Training_Data_Parser::convert_String_To_UInt ( std::string element_value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::convert_String_To_UInt" );

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
			   "Exiting Java_Training_Data_Parser::convert_String_To_UInt" );
#endif /* LIBREVERSE_DEBUG */


      return value;
    }

    double
    Java_Training_Data_Parser::convert_String_To_Double ( std::string element_value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::convert_String_To_Double" );

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
			   "Exiting Java_Training_Data_Parser::convert_String_To_Double" );
#endif /* LIBREVERSE_DEBUG */


      return value;
    }

    std::string
    Java_Training_Data_Parser::get_Attribute ( std::string name, const Attribute_Map_t& attributes )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data_Parser::get_Attribute" );
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


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_PARSER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data_Parser::get_Attribute" );
#endif /* LIBREVERSE_DEBUG */


      return ( *pos ).second;
    }

    classifier_types::Variable_Map::map_type&
    Java_Training_Data_Parser::get_Max_Values ( void )
    {
      return m_max_values;
    }
  } /* namespace classifier */
} /* namespace libreverse */
