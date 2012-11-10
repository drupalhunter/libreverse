/*  Elf_Training_Data.cpp

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

//
// C++ Implementation: Training_Data
//
// Description:
//
//
// Author: Stephen Torri, Winard Britt <storri@dell>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Configuration.h"
#include "Create.h"
#include "Elf_Training_Data.h"
#include "Elf_Training_Data_Parser.h"

#include <sstream>
#include <iostream>
#include <boost/format.hpp>

#include "Reverse.h"
#include "Create.h"
#include "errors/Internal_Exception.h"

using namespace libreverse::api;

using namespace libreverse::alloc;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace classifier
  {

    const boost::uint8_t Elf_Training_Data::ATTRIBUTE_COUNT = 8;
    const boost::uint8_t Elf_Training_Data::CLASSIFIER_TARGET = Elf_Training_Data::ATTRIBUTE_TARGET_ID;

    Elf_Training_Data::Elf_Training_Data ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Elf_Training_Data constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Elf_Training_Data::~Elf_Training_Data ()
    {
      
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Elf_Training_Data destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Elf_Training_Data::get_Attribute_String_List ( classifier_types::Configuration<Elf_Training_Data>::ptr_t config )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Elf_Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */

      
      std::stringstream output;

      output << "Elf_Training_Data:" << std::endl;
	
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << "Target_ID" << std::endl;
        }

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << "Filesize" << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_ENTRY_POINT_ADDRESS ) )
        {
	  output << "Entry Point Address" << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADERS_START ) )
        {
	  output << "Section headers start" << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_PROGRAM_HEADER_COUNT ) )
        {
	  output << "Program header count" << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADER_COUNT ) )
        {
	  output << "Section header count" << std::endl;
        }

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADER_STRING_TABLE_INDEX ) )
	{
	  output << "Section header string table index" << std::endl;
	}

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_TEXT_SECTION_SIZE ) )
	{
	  output << "Text section size" << std::endl;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Training_Data::to_String ( classifier_types::Configuration<Elf_Training_Data>::ptr_t config ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Elf_Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;
      output << "Elf_Training_Data:" << std::endl;
	
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << boost::format ( "  target id...........: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_TARGET_ID ) << std::endl;
        }

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << boost::format ( "  file size.............: %1% bytes" )
	    % m_data.get_Attribute ( ATTRIBUTE_FILESIZE )  << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_ENTRY_POINT_ADDRESS ) )
        {
	  output << boost::format ( "  entry point address............: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_ENTRY_POINT_ADDRESS ) << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADERS_START ) )
        {
	  output << boost::format ( "  section headers start...........: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADERS_START ) << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_PROGRAM_HEADER_COUNT ) )
        {
	  output << boost::format ( "  program header count...............: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADER_COUNT ) << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADER_COUNT ) )
        {
	  output << boost::format ( "  section header count...: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADER_COUNT ) << std::endl;
        }

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADER_STRING_TABLE_INDEX ) )
	{
	  output << boost::format ( "  section header string table index..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADER_STRING_TABLE_INDEX ) << std::endl;
	}

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_TEXT_SECTION_SIZE ) )
	{
	  output << boost::format ( "  text section size..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_TEXT_SECTION_SIZE ) << std::endl;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Training_Data::to_XML ( classifier_types::Configuration<Elf_Training_Data>::ptr_t config ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Elf_Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;
      output << boost::format ( "  <%1%>" ) % Elf_Input_Tag_Names::TAG_FILE << std::endl;
	
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_TARGET_ID
	    % m_data.get_Attribute ( ATTRIBUTE_TARGET_ID )
	    % Elf_Input_Tag_Names::TAG_TARGET_ID << std::endl;
        }

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_FILESIZE
	    % m_data.get_Attribute ( ATTRIBUTE_FILESIZE )
	    % Elf_Input_Tag_Names::TAG_FILESIZE << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_ENTRY_POINT_ADDRESS ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_ENTRY_POINT_ADDRESS
	    %  m_data.get_Attribute ( ATTRIBUTE_ENTRY_POINT_ADDRESS )
	    % Elf_Input_Tag_Names::TAG_ENTRY_POINT_ADDRESS << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADERS_START ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_SECTION_HEADERS_START
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADERS_START )
	    % Elf_Input_Tag_Names::TAG_SECTION_HEADERS_START << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_PROGRAM_HEADER_COUNT ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_PROGRAM_HEADER_COUNT
	    %  m_data.get_Attribute ( ATTRIBUTE_PROGRAM_HEADER_COUNT )
	    % Elf_Input_Tag_Names::TAG_PROGRAM_HEADER_COUNT << std::endl;
        }
        
      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADER_COUNT ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_SECTION_HEADER_COUNT
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADER_COUNT )
	    % Elf_Input_Tag_Names::TAG_SECTION_HEADER_COUNT << std::endl;
        }

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_SECTION_HEADER_STRING_TABLE_INDEX ) )
	{
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_SECTION_HEADER_STRING_TABLE_INDEX
	    %  m_data.get_Attribute ( ATTRIBUTE_SECTION_HEADER_STRING_TABLE_INDEX )
	    % Elf_Input_Tag_Names::TAG_SECTION_HEADER_STRING_TABLE_INDEX << std::endl;
	}

      if ( config->get_Attribute ( Elf_Training_Data::ATTRIBUTE_TEXT_SECTION_SIZE ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Elf_Input_Tag_Names::TAG_TEXT_SECTION_SIZE
	    %  m_data.get_Attribute ( ATTRIBUTE_TEXT_SECTION_SIZE )
	    % Elf_Input_Tag_Names::TAG_TEXT_SECTION_SIZE << std::endl;
	}

      output << boost::format ( "  </%1%>" ) % Elf_Input_Tag_Names::TAG_FILE << std::endl;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    classifier_types::Variable_Map::map_type::const_iterator
    Elf_Training_Data::begin ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Elf_Training_Data::begin (const)" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.begin();
    }

    classifier_types::Variable_Map::map_type::iterator
    Elf_Training_Data::begin ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Elf_Training_Data::begin" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.begin();
    }

    classifier_types::Variable_Map::map_type::const_iterator
    Elf_Training_Data::end ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Elf_Training_Data::end (const)" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.end();
    }

    classifier_types::Variable_Map::map_type::iterator
    Elf_Training_Data::end ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Elf_Training_Data::end" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.end();
    }

    void
    Elf_Training_Data::set_Attribute ( boost::uint32_t index, double value )
    {
      if ( index < Elf_Training_Data::ATTRIBUTE_COUNT )
	{
          m_data.set_Attribute ( index, value );
	}
    }

    double
    Elf_Training_Data::get_Attribute ( boost::uint32_t index )
    {
      if ( index < Elf_Training_Data::ATTRIBUTE_COUNT )
	{
          return m_data.get_Attribute ( index );
	}
      else
	{
	  throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );
	}
    }

    bool
    Elf_Training_Data::empty ( void ) const
    {
      return m_data.empty();
    }

  } /* namespace classifier */
} /* namespace libreverse */
