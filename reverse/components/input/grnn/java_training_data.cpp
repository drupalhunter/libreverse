
/*  Java_Training_Data.cpp

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
#include "Java_Training_Data.h"
#include "Java_Training_Data_Parser.h"
#include "Configuration.h"

#include <sstream>
#include <iostream>
#include <boost/format.hpp>

#include "Reverse.h"

#include "Create.h"

#include "errors/Internal_Exception.h"
#include "errors/Internal_Exception.h"
#include "io/input/File_Readers/Java_Class/Constant_Pool_Tags.h"

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

    const boost::uint8_t Java_Training_Data::ATTRIBUTE_COUNT = 32;
    const boost::uint8_t Java_Training_Data::CLASSIFIER_TARGET = Java_Training_Data::ATTRIBUTE_TARGET_ID;

    Java_Training_Data::Java_Training_Data ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Java_Training_Data::~Java_Training_Data ()
    {
      
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Java_Training_Data::get_Attribute_String_List ( classifier_types::Configuration<Java_Training_Data>::ptr_t config )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */

      
      std::stringstream output;

      output << "Java_Training_Data #%1%" << std::endl;
	
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << "Target_ID" << std::endl;
        }

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << "Filesize" << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_THIS_INDEX ) )
        {
	  output << "This_index" << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_SUPER_INDEX ) )
        {
	  output << "Super_index" << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_VERSION ) )
        {
	  output << "Version" << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_POOL_COUNT ) )
        {
	  output << "Constant Pool count" << std::endl;
        }

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_COUNT ) )
	{
	  output << "Constant UTF-8 count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_RATIO ) )
	{
	  output << "Constant UTF-8 ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_RESERVED_COUNT ) )
	{
	  output << "Reserved count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_RESERVED_RATIO ) )
	{
	  output << "Reserved ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTEGER_COUNT ) )
	{
	  output << "Constant Pool Integer count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTEGER_RATIO ) )
	{
	  output << "Constant Pool Integer ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FLOAT_COUNT ) )
	{
	  output << "Constant Pool Float count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FLOAT_RATIO ) )
	{
	  output << "Constant Pool Float ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_LONG_COUNT ) )
	{
	  output << "Constant Pool Long count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_LONG_RATIO ) )
	{
	  output << "Constant Pool Long ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_DOUBLE_COUNT ) )
	{
	  output << "Constant Pool Double count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_DOUBLE_RATIO ) )
	{
	  output << "Constant Pool Double ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_CLASS_COUNT ) )
	{
	  output << "Constant Pool Class count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_CLASS_RATIO ) )
	{
	  output << "Constant Pool Class ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_STRING_COUNT ) )
	{
	  output << "Constant Pool String count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_STRING_RATIO ) )
	{
	  output << "Constant Pool String ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FIELDREF_COUNT ) )
	{
	  output << "Constant Pool Fieldref count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FIELDREF_RATIO ) )
	{
	  output << "Constant Pool Fieldref ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_METHODREF_COUNT ) )
	{
	  output << "Constant Pool Methodref count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_METHODREF_RATIO ) )
	{
	  output << "Constant Pool Methodref ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_COUNT ) )
	{
	  output << "Constant Pool Interface Methodref count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_RATIO ) )
	{
	  output << "Constant Pool Interface Methodref ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_NAME_AND_TYPE_COUNT ) )
	{
	  output << "Constant Pool Name and Type count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_NAME_AND_TYPE_RATIO ) )
	{
	  output << "Constant Pool Name and Type ratio" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_FIELD_COUNT ) )
        {
	  output << "Field Count" << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_METHOD_COUNT ) )
        {
	  output << "Method Count" << std::endl;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Java_Training_Data::to_String ( classifier_types::Configuration<Java_Training_Data>::ptr_t config ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;
      output << "Java_Training_Data #%1%" << std::endl;
	
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << boost::format ( "  target id...........: %1%" )
	    % m_data.get_Attribute ( ATTRIBUTE_TARGET_ID ) << std::endl;
        }

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << boost::format ( "  file size.............: %1% bytes" )
	    % m_data.get_Attribute ( ATTRIBUTE_FILESIZE )  << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_THIS_INDEX ) )
        {
	  output << boost::format ( "  this index............: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_THIS_INDEX ) << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_SUPER_INDEX ) )
        {
	  output << boost::format ( "  super index...........: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_SUPER_INDEX ) << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_VERSION ) )
        {
	  output << boost::format ( "  version...............: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_VERSION ) << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_POOL_COUNT ) )
        {
	  output << boost::format ( "  constant pool count...: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_POOL_COUNT ) << std::endl;
        }

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_COUNT ) )
	{
	  output << boost::format ( "  constant UTF-8 count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_UTF8_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_RATIO ) )
	{
	  output << boost::format ( "  constant UTF-8 ratio..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_UTF8_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_RESERVED_COUNT ) )
	{
	  output << boost::format ( "  constant Reserved count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_RESERVED_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_RESERVED_RATIO ) )
	{
	  output << boost::format ( "  constant Reserved ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_RESERVED_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTEGER_COUNT ) )
	{
	  output << boost::format ( "  constant Integer count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTEGER_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTEGER_RATIO ) )
	{
	  output << boost::format ( "  constant Integer ratio..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTEGER_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FLOAT_COUNT ) )
	{
	  output << boost::format ( "  constant Float count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FLOAT_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FLOAT_RATIO ) )
	{
	  output << boost::format ( "  constant Float ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FLOAT_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_LONG_COUNT ) )
	{
	  output << boost::format ( "  constant Long count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_LONG_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_LONG_RATIO ) )
	{
	  output << boost::format ( "  constant Long ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_LONG_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_DOUBLE_COUNT ) )
	{
	  output << boost::format ( "  constant Double count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_DOUBLE_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_DOUBLE_RATIO ) )
	{
	  output << boost::format ( "  constant Double ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_DOUBLE_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_CLASS_COUNT ) )
	{
	  output << boost::format ( "  constant Class count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_CLASS_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_CLASS_RATIO ) )
	{
	  output << boost::format ( "  constant Class ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_CLASS_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_STRING_COUNT ) )
	{
	  output << boost::format ( "  constant String count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_STRING_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_STRING_RATIO ) )
	{
	  output << boost::format ( "  constant String ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_STRING_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FIELDREF_COUNT ) )
	{
	  output << boost::format ( "  constant Fieldref count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FIELDREF_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FIELDREF_RATIO ) )
	{
	  output << boost::format ( "  constant Fieldref ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FIELDREF_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_METHODREF_COUNT ) )
	{
	  output << boost::format ( "  constant Methodref count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_METHODREF_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_METHODREF_RATIO ) )
	{
	  output << boost::format ( "  constant Methodref ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_METHODREF_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_COUNT ) )
	{
	  output << boost::format ( "  constant Interface Methodref count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_RATIO ) )
	{
	  output << boost::format ( "  constant Interface Methodref ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_NAME_AND_TYPE_COUNT ) )
	{
	  output << boost::format ( "  constant Name and Type count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_NAME_AND_TYPE_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_NAME_AND_TYPE_RATIO ) )
	{
	  output << boost::format ( "  constant Name and Type ratio..: %1%"  )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_NAME_AND_TYPE_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_FIELD_COUNT ) )
        {
	  output << boost::format ( "  Field count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_FIELD_COUNT ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_METHOD_COUNT ) )
        {
	  output << boost::format ( "  Method count..: %1%" )
	    %  m_data.get_Attribute ( ATTRIBUTE_METHOD_COUNT ) << std::endl;
	}

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Java_Training_Data::to_XML ( classifier_types::Configuration<Java_Training_Data>::ptr_t config ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Entering Java_Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;
      output << boost::format ( "  <%1%>" ) % Java_Input_Tag_Names::TAG_FILE << std::endl;
	
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_TARGET_ID ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_TARGET_ID
	    % m_data.get_Attribute ( ATTRIBUTE_TARGET_ID )
	    % Java_Input_Tag_Names::TAG_TARGET_ID << std::endl;
        }

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_FILESIZE ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_FILESIZE
	    % m_data.get_Attribute ( ATTRIBUTE_FILESIZE )
	    % Java_Input_Tag_Names::TAG_FILESIZE << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_THIS_INDEX ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_THIS_INDEX
	    %  m_data.get_Attribute ( ATTRIBUTE_THIS_INDEX )
	    % Java_Input_Tag_Names::TAG_THIS_INDEX << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_SUPER_INDEX ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_SUPER_INDEX
	    %  m_data.get_Attribute ( ATTRIBUTE_SUPER_INDEX )
	    % Java_Input_Tag_Names::TAG_SUPER_INDEX << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_VERSION ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_VERSION
	    %  m_data.get_Attribute ( ATTRIBUTE_VERSION )
	    % Java_Input_Tag_Names::TAG_VERSION << std::endl;
        }
        
      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_POOL_COUNT ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_COUNT
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_POOL_COUNT )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_COUNT << std::endl;
        }

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_UTF8_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::UTF8
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_UTF8_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_UTF8_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_RESERVED_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_RESERVED_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::RESERVED
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_RESERVED_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_RESERVED_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTEGER_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTEGER_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    % java_module::Constant_Pool_Tags::INTEGER
	    % m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTEGER_COUNT )
	    % m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTEGER_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FLOAT_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FLOAT_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::FLOAT
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FLOAT_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FLOAT_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_LONG_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_LONG_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::LONG
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_LONG_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_LONG_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_DOUBLE_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_DOUBLE_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::DOUBLE
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_DOUBLE_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_DOUBLE_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_CLASS_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_CLASS_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::CLASS
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_CLASS_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_CLASS_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_STRING_COUNT ) |
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_STRING_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::STRING
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_STRING_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_STRING_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FIELDREF_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_FIELDREF_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::FIELD_REF
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FIELDREF_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_FIELDREF_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_METHODREF_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_METHODREF_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::METHOD_REF
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_METHODREF_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_METHODREF_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::INTERFACE_METHOD_REF
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_NAME_AND_TYPE_COUNT ) ||
	   config->get_Attribute ( Java_Training_Data::ATTRIBUTE_CONSTANT_NAME_AND_TYPE_RATIO ) )
	{
	  output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
	    % Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    %  java_module::Constant_Pool_Tags::NAME_AND_TYPE
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_NAME_AND_TYPE_COUNT )
	    %  m_data.get_Attribute ( ATTRIBUTE_CONSTANT_NAME_AND_TYPE_RATIO ) << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_FIELD_COUNT ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_FIELD_COUNT
	    %  m_data.get_Attribute ( ATTRIBUTE_FIELD_COUNT )
	    % Java_Input_Tag_Names::TAG_FIELD_COUNT << std::endl;
	}

      if ( config->get_Attribute ( Java_Training_Data::ATTRIBUTE_METHOD_COUNT ) )
        {
	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % Java_Input_Tag_Names::TAG_METHOD_COUNT
	    %  m_data.get_Attribute ( ATTRIBUTE_METHOD_COUNT )
	    % Java_Input_Tag_Names::TAG_METHOD_COUNT << std::endl;
	}

      output << boost::format ( "  </%1%>" ) % Java_Input_Tag_Names::TAG_FILE << std::endl;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Exiting Java_Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    classifier_types::Variable_Map::map_type::const_iterator
    Java_Training_Data::begin ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data::begin (const)" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.begin();
    }

    classifier_types::Variable_Map::map_type::iterator
    Java_Training_Data::begin ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data::begin" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.begin();
    }

    classifier_types::Variable_Map::map_type::const_iterator
    Java_Training_Data::end ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data::end (const)" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.end();
    }

    classifier_types::Variable_Map::map_type::iterator
    Java_Training_Data::end ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside Java_Training_Data::end" );
#endif /* LIBREVERSE_DEBUG */


      return m_data.end();
    }

    void
    Java_Training_Data::set_Attribute ( boost::uint32_t index, double value )
    {
      if ( index < Java_Training_Data::ATTRIBUTE_COUNT )
	{
          m_data.set_Attribute ( index, value );
	}
    }

    double
    Java_Training_Data::get_Attribute ( boost::uint32_t index )
    {
      if ( index < Java_Training_Data::ATTRIBUTE_COUNT )
	{
          return m_data.get_Attribute ( index );
	}
      else
	{
	  throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );
	}
    }

    bool
    Java_Training_Data::empty ( void ) const
    {
      return m_data.empty();
    }

  } /* namespace classifier */
} /* namespace libreverse */
