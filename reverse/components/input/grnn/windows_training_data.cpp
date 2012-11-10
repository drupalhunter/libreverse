/*  Windows_Training_Data.cpp

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
#include "Windows_Training_Data.h"
#include "errors/Internal_Exception.h"
#include "Configuration.h"
#include <sstream>
#include <iostream>
#include <boost/format.hpp>

#include "Reverse.h"


using namespace libreverse::api;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace classifier
  {

    const boost::uint8_t Windows_Training_Data::ATTRIBUTE_COUNT = 8;
    const boost::uint8_t Windows_Training_Data::CLASSIFIER_TARGET = Windows_Training_Data::ATTRIBUTE_TARGET_ID;

    Windows_Training_Data::Windows_Training_Data ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Windows_Training_Data::~Windows_Training_Data ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

//     classifier_types::Variable_Map::map_type
//     Windows_Training_Data::get_Candidate_Data ( classifier_types::Configuration<Windows_Training_Data>::ptr_t config ) const
//     {

// #ifdef LIBREVERSE_DEBUG
//       Trace::write_Trace ( TraceArea::GRNN_DATA,
// 			   TraceLevel::DETAIL,
// 			   "Entering Windows_Training_Data::get_Candidate_Data" );
// #endif /* LIBREVERSE_DEBUG */


//       classifier_types::Variable_Map::map_type output;

//       for ( boost::uint32_t index = 0;
// 	    index < Windows_Training_Data::ATTRIBUTE_COUNT;
// 	    ++index )
//         {
// 	  if ( config->get_Attribute ( index ) )
//             {
// 	      classifier_types::Variable_Map::map_type::const_iterator pos = m_data.find ( index );
// 	      output[index] = ( *pos ).second;
//             }
//         }


// #ifdef LIBREVERSE_DEBUG
//       Trace::write_Trace ( TraceArea::GRNN_DATA,
// 			   TraceLevel::DETAIL,
// 			   "Exiting Windows_Training_Data::get_Candidate_Data" );
// #endif /* LIBREVERSE_DEBUG */


//       return output;
//     }

    std::string
    Windows_Training_Data::get_Attribute_String_List ( classifier_types::Configuration<Windows_Training_Data>::ptr_t config )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */

      
      std::stringstream output;

      output << "Windows_Training_Data #%1%" << std::endl;
	
      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << "Target_ID" << std::endl;
        }

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << "Filesize" << std::endl;
        }

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS ) )
	{
	  output << "DOS Exe header address" << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT ) )
	{
	  output << "COFF number of section headers" << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE ) )
	{
	  output << "Optional Header code size" << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA ) )
	{
	  output << "Optional Header base of data" << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT ) )
	{
	  output << "Optional Header entry point" << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE ) )
	{
	  output << "Optional Header image size" << std::endl;
	}

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Windows_Training_Data::to_String ( classifier_types::Configuration<Windows_Training_Data>::ptr_t config ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      output << "Windows_Training_Data" << std::endl;
	
      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << boost::format ( "  target id...........: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_TARGET_ID ) << std::endl;
        }

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << boost::format ( "  file size.............: %1% bytes" )
	    % m_data.get_Attribute ( ATTRIBUTE_FILESIZE )  << std::endl;
        }

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS ) )
	{
	  output << boost::format ( "  Exe header address.............: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_EXE_HEADER_ADDRESS )  << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT ) )
	{
	  output << boost::format ( "  COFF section header count......: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_COFF_SECTION_COUNT )  << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE ) )
	{
	  output << boost::format ( "  PE code size...................: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_PE_OPT_CODE_SIZE )  << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA ) )
	{
	  output << boost::format ( "  PE base of data................: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_PE_OPT_BASE_OF_DATA )  << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT ) )
	{
	  output << boost::format ( "  PE entry point................: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_PE_OPT_ENTRY_POINT )  << std::endl;
	}

      if ( config->get_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE ) )
	{
	  output << boost::format ( "  PE image size.................: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_PE_OPT_IMAGE_SIZE )  << std::endl;
	}

#ifdef LIBREVERSE_DEBUG	
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Windows_Training_Data::to_XML ( classifier_types::Configuration<Windows_Training_Data>::ptr_t ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Windows_Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      /*


      output << boost::format ( "Windows_Training_Data #%1%" ) % index << std::endl
	     << boost::format ( "  compiler id................: %1%" ) % this->get_Attribute ( ATTRIBUTE_TARGET_ID )  << std::endl
	     << boost::format ( "  file size..................: %1% bytes" ) % this->get_Attribute ( ATTRIBUTE_FILESIZE )  << std::endl
	     << boost::format ( "  DOS magic number...........: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_DOS_MAGIC_NUMBER ) << std::endl
	     << boost::format ( "  DOS EXE header address.....: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_EXE_HEADER_ADDRESS ) << std::endl
	     << boost::format ( "  PE magic number............: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_PE_MAGIC_NUMBER ) << std::endl
	     << boost::format ( "  COFF machine...............: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_COFF_MACHINE ) << std::endl
	     << boost::format ( "  COFF timestamp.............: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_COFF_TIMESTAMP ) << std::endl
	     << boost::format ( "  COFF number of symbols.....: %1%" ) % this->get_Attribute ( ATTRIBUTE_COFF_NUMBER_OF_SYMBOLS ) << std::endl
	     << boost::format ( "  Optional Header magic value: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_PE_OPT_MAGIC_VALUE ) << std::endl
	     << boost::format ( "  Optional Header linker version: 0x%1%" ) % this->get_Attribute ( ATTRIBUTE_PE_OPT_LINKER_VERSION ) << std::endl
	     << boost::format ( "  Optional Header code size: 0x%1%" ) % this->get_Attribute ( ATTRIBUTE_PE_OPT_CODE_SIZE ) << std::endl
	     << boost::format ( "  Optional Header initialized data size: 0x%1%" ) % this->get_Attribute ( ATTRIBUTE_PE_OPT_INIT_DATA_SIZE ) << std::endl

	     << boost::format ( "  Optional Header uninitialized data size: 0x%1%" )
	% this->get_Attribute ( ATTRIBUTE_PE_OPT_UNINIT_DATA_SIZE ) << std::endl

	     << boost::format ( "  Optional Header entry point: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_PE_OPT_ENTRY_POINT ) << std::endl
	     << boost::format ( "  Optional Header code address: 0x%1$X" ) % this->get_Attribute ( ATTRIBUTE_PE_OPT_CODE_ADDRESS ) << std::endl

	     << boost::format ( "  Optional Header operating system version: 0x%1%" )
	% this->get_Attribute ( ATTRIBUTE_PE_OPT_OPERATING_SYSTEM_VERSION ) << std::endl;
      */


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    classifier_types::Variable_Map::map_type::const_iterator
    Windows_Training_Data::begin ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data::begin (const)" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.begin();
    }

    classifier_types::Variable_Map::map_type::iterator
    Windows_Training_Data::begin ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data::begin" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.begin();
    }

    classifier_types::Variable_Map::map_type::const_iterator
    Windows_Training_Data::end ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data::end (const)" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.end();
    }

    classifier_types::Variable_Map::map_type::iterator
    Windows_Training_Data::end ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Windows_Training_Data::end" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.end();
    }

    void
    Windows_Training_Data::set_Attribute ( boost::uint32_t index, double value )
    {
      if ( index < Windows_Training_Data::ATTRIBUTE_COUNT )
	{
          m_data.set_Attribute ( index, value );
	}
    }

    double
    Windows_Training_Data::get_Attribute ( boost::uint32_t index ) const
    {
      if ( index < Windows_Training_Data::ATTRIBUTE_COUNT )
	{
	  return m_data.get_Attribute ( index );
	}
      else
	{
	  throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );
	}
    }

    bool
    Windows_Training_Data::empty ( void ) const
    {
      return m_data.empty();
    }

  } /* namespace classifier */
} /* namespace libreverse */
