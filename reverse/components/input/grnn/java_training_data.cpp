
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
#include <reverse/components/input/grnn/configuration.hpp>
#include <reverse/components/input/grnn/java_training_data.hpp>
#include <reverse/components/input/grnn/java_training_data_parser.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/io/input/file_readers/java_class/constant_pool_tags.hpp>
#include <reverse/reverse.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>
#include <iostream>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {


	const boost::uint8_t java_training_data::attribute_count = 32;
	const boost::uint8_t java_training_data::classifier_target = java_training_data::attribute_target_id;

	java_training_data::java_training_data ()
	{
	  trace::grnn_detail ( "inside java_training_data constructor" );
	}

	java_training_data::~java_training_data ()
	{
	  trace::grnn_detail ( "inside java_training_data destructor" );
	}

	std::string
	java_training_data::get_attribute_string_list ( boost::shared_ptr < configuration<java_training_data> > config )
	{
	  trace::grnn_detail ( "Entering Java_Training_Data::get_Attribute_String_List" );
      
	  std::stringstream output;

	  output << "Java_Training_Data #%1%" << std::endl;
	
	  if ( config->get_attribute ( java_training_data::attribute_target_id ) )
	    {
	      output << "Target_ID" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_filesize ) )
	    {
	      output << "Filesize" << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_this_index ) )
	    {
	      output << "This_index" << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_super_index ) )
	    {
	      output << "Super_index" << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_version ) )
	    {
	      output << "Version" << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_constant_pool_count ) )
	    {
	      output << "Constant Pool count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_utf8_count ) )
	    {
	      output << "Constant UTF-8 count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_utf8_ratio ) )
	    {
	      output << "Constant UTF-8 ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_reserved_count ) )
	    {
	      output << "Reserved count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_reserved_ratio ) )
	    {
	      output << "Reserved ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_integer_count ) )
	    {
	      output << "Constant Pool Integer count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_integer_ratio ) )
	    {
	      output << "Constant Pool Integer ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_float_count ) )
	    {
	      output << "Constant Pool Float count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_float_ratio ) )
	    {
	      output << "Constant Pool Float ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_long_count ) )
	    {
	      output << "Constant Pool Long count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_long_ratio ) )
	    {
	      output << "Constant Pool Long ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_double_count ) )
	    {
	      output << "Constant Pool Double count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_double_ratio ) )
	    {
	      output << "Constant Pool Double ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_class_count ) )
	    {
	      output << "Constant Pool Class count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_class_ratio ) )
	    {
	      output << "Constant Pool Class ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_string_count ) )
	    {
	      output << "Constant Pool String count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_string_ratio ) )
	    {
	      output << "Constant Pool String ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_fieldref_count ) )
	    {
	      output << "Constant Pool Fieldref count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_fieldref_ratio ) )
	    {
	      output << "Constant Pool Fieldref ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_methodref_count ) )
	    {
	      output << "Constant Pool Methodref count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_methodref_ratio ) )
	    {
	      output << "Constant Pool Methodref ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_interface_methodref_count ) )
	    {
	      output << "Constant Pool Interface Methodref count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_interface_methodref_ratio ) )
	    {
	      output << "Constant Pool Interface Methodref ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_name_and_type_count ) )
	    {
	      output << "Constant Pool Name and Type count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_name_and_type_ratio ) )
	    {
	      output << "Constant Pool Name and Type ratio" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_field_count ) )
	    {
	      output << "Field Count" << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_method_count ) )
	    {
	      output << "Method Count" << std::endl;
	    }

	  trace::grnn_detail ( "Exiting Java_Training_Data::get_Attribute_String_List" );

	  return output.str();
	}

	std::string
	java_training_data::to_string ( boost::shared_ptr < configuration<java_training_data> > config ) const
	{

	  trace::grnn_detail ( "Entering Java_Training_Data::to_String" );

	  std::stringstream output;
	  output << "Java_Training_Data #%1%" << std::endl;
	
	  if ( config->get_attribute ( java_training_data::attribute_target_id ) )
	    {
	      output << boost::format ( "  target id...........: %1%" )
		% m_data.get_attribute ( attribute_target_id ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_filesize ) )
	    {
	      output << boost::format ( "  file size.............: %1% bytes" )
		% m_data.get_attribute ( attribute_filesize )  << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_this_index ) )
	    {
	      output << boost::format ( "  this index............: %1%" )
		%  m_data.get_attribute ( attribute_this_index ) << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_super_index ) )
	    {
	      output << boost::format ( "  super index...........: %1%" )
		%  m_data.get_attribute ( attribute_super_index ) << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_version ) )
	    {
	      output << boost::format ( "  version...............: %1%" )
		%  m_data.get_attribute ( attribute_version ) << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_constant_pool_count ) )
	    {
	      output << boost::format ( "  constant pool count...: %1%" )
		%  m_data.get_attribute ( attribute_constant_pool_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_utf8_count ) )
	    {
	      output << boost::format ( "  constant UTF-8 count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_utf8_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_utf8_ratio ) )
	    {
	      output << boost::format ( "  constant UTF-8 ratio..: %1%" )
		%  m_data.get_attribute ( attribute_constant_utf8_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_reserved_count ) )
	    {
	      output << boost::format ( "  constant Reserved count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_reserved_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_reserved_ratio ) )
	    {
	      output << boost::format ( "  constant Reserved ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_reserved_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_integer_count ) )
	    {
	      output << boost::format ( "  constant Integer count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_integer_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_integer_ratio ) )
	    {
	      output << boost::format ( "  constant Integer ratio..: %1%" )
		%  m_data.get_attribute ( attribute_constant_integer_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_float_count ) )
	    {
	      output << boost::format ( "  constant Float count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_float_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_float_ratio ) )
	    {
	      output << boost::format ( "  constant Float ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_float_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_long_count ) )
	    {
	      output << boost::format ( "  constant Long count..: %1%" )
 		%  m_data.get_attribute ( attribute_constant_long_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_long_ratio ) )
	    {
	      output << boost::format ( "  constant Long ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_long_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_double_count ) )
	    {
	      output << boost::format ( "  constant Double count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_double_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_double_ratio ) )
	    {
	      output << boost::format ( "  constant Double ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_double_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_class_count ) )
	    {
	      output << boost::format ( "  constant Class count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_class_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_class_ratio ) )
	    {
	      output << boost::format ( "  constant Class ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_class_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_string_count ) )
	    {
	      output << boost::format ( "  constant String count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_string_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_string_ratio ) )
	    {
	      output << boost::format ( "  constant String ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_string_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_fieldref_count ) )
	    {
	      output << boost::format ( "  constant Fieldref count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_fieldref_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_fieldref_ratio ) )
	    {
	      output << boost::format ( "  constant Fieldref ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_fieldref_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_methodref_count ) )
	    {
	      output << boost::format ( "  constant Methodref count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_methodref_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_methodref_ratio ) )
	    {
	      output << boost::format ( "  constant Methodref ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_methodref_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_interface_methodref_count ) )
	    {
	      output << boost::format ( "  constant Interface Methodref count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_interface_methodref_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_interface_methodref_ratio ) )
	    {
	      output << boost::format ( "  constant Interface Methodref ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_interface_methodref_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_name_and_type_count ) )
	    {
	      output << boost::format ( "  constant Name and Type count..: %1%" )
		%  m_data.get_attribute ( attribute_constant_name_and_type_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_name_and_type_ratio ) )
	    {
	      output << boost::format ( "  constant Name and Type ratio..: %1%"  )
		%  m_data.get_attribute ( attribute_constant_name_and_type_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_field_count ) )
	    {
	      output << boost::format ( "  Field count..: %1%" )
		%  m_data.get_attribute ( attribute_field_count ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_method_count ) )
	    {
	      output << boost::format ( "  Method count..: %1%" )
		%  m_data.get_attribute ( attribute_method_count ) << std::endl;
	    }

	  trace::grnn_detail ( "Exiting Java_Training_Data::to_String" );

	  return output.str();
	}

	std::string
	java_training_data::to_xml ( boost::shared_ptr < configuration<java_training_data> > config ) const
	{

	  trace::grnn_detail ( "Entering Java_Training_Data::to_XML" );

	  std::stringstream output;
	  output << boost::format ( "  <%1%>" ) % java_input_tag_names::tag_file << std::endl;
	
	  if ( config->get_attribute ( java_training_data::attribute_target_id ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_target_id
		% m_data.get_attribute ( attribute_target_id )
		% java_input_tag_names::tag_target_id << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_filesize ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_filesize
		% m_data.get_attribute ( attribute_filesize )
		% java_input_tag_names::tag_filesize << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_this_index ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_this_index
		%  m_data.get_attribute ( attribute_this_index )
		% java_input_tag_names::tag_this_index << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_super_index ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_super_index
		%  m_data.get_attribute ( attribute_super_index )
		% java_input_tag_names::tag_super_index << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_version ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_version
		%  m_data.get_attribute ( attribute_version )
		% java_input_tag_names::tag_version << std::endl;
	    }
        
	  if ( config->get_attribute ( java_training_data::attribute_constant_pool_count ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_constant_pool_count
		%  m_data.get_attribute ( attribute_constant_pool_count )
		% java_input_tag_names::tag_constant_pool_count << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_utf8_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_utf8_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::utf8_tag
		%  m_data.get_attribute ( attribute_constant_utf8_count )
		%  m_data.get_attribute ( attribute_constant_utf8_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_reserved_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_reserved_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::reserved_tag
		%  m_data.get_attribute ( attribute_constant_reserved_count )
		%  m_data.get_attribute ( attribute_constant_reserved_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_integer_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_integer_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		% io::input::file_readers::java_class::constant_pool_tags::integer_tag
		% m_data.get_attribute ( attribute_constant_integer_count )
		% m_data.get_attribute ( attribute_constant_integer_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_float_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_float_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::float_tag
		%  m_data.get_attribute ( attribute_constant_float_count )
		%  m_data.get_attribute ( attribute_constant_float_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_long_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_long_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::long_tag
		%  m_data.get_attribute ( attribute_constant_long_count )
		%  m_data.get_attribute ( attribute_constant_long_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_double_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_double_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::double_tag
		%  m_data.get_attribute ( attribute_constant_double_count )
		%  m_data.get_attribute ( attribute_constant_double_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_class_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_class_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::class_tag
		%  m_data.get_attribute ( attribute_constant_class_count )
		%  m_data.get_attribute ( attribute_constant_class_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_string_count ) |
	       config->get_attribute ( java_training_data::attribute_constant_string_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::string_tag
		%  m_data.get_attribute ( attribute_constant_string_count )
		%  m_data.get_attribute ( attribute_constant_string_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_fieldref_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_fieldref_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::field_ref_tag
		%  m_data.get_attribute ( attribute_constant_fieldref_count )
		%  m_data.get_attribute ( attribute_constant_fieldref_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_methodref_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_methodref_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::method_ref_tag
		%  m_data.get_attribute ( attribute_constant_methodref_count )
		%  m_data.get_attribute ( attribute_constant_methodref_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_interface_methodref_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_interface_methodref_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::interface_method_ref_tag
		%  m_data.get_attribute ( attribute_constant_interface_methodref_count )
		%  m_data.get_attribute ( attribute_constant_interface_methodref_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_constant_name_and_type_count ) ||
	       config->get_attribute ( java_training_data::attribute_constant_name_and_type_ratio ) )
	    {
	      output << boost::format ( "    <%1% tag=\"%2%\" count=\"%3%\" ratio=\"%4%\"/>" )
		% java_input_tag_names::tag_constant_pool_info
		%  io::input::file_readers::java_class::constant_pool_tags::name_and_type_tag
		%  m_data.get_attribute ( attribute_constant_name_and_type_count )
		%  m_data.get_attribute ( attribute_constant_name_and_type_ratio ) << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_field_count ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_field_count
		%  m_data.get_attribute ( attribute_field_count )
		% java_input_tag_names::tag_field_count << std::endl;
	    }

	  if ( config->get_attribute ( java_training_data::attribute_method_count ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% java_input_tag_names::tag_method_count
		%  m_data.get_attribute ( attribute_method_count )
		% java_input_tag_names::tag_method_count << std::endl;
	    }

	  output << boost::format ( "  </%1%>" ) % java_input_tag_names::tag_file << std::endl;

	  trace::grnn_detail ( "Exiting Java_Training_Data::to_XML" );

	  return output.str();
	}

	variable_map::map_t::const_iterator
	java_training_data::begin ( void ) const
	{
	  trace::grnn_detail ( "Inside Java_Training_Data::begin (const)" );

	  return m_data.begin();
	}

	variable_map::map_t::iterator
	java_training_data::begin ( void )
	{

	  trace::grnn_detail ( "Inside Java_Training_Data::begin" );

	  return m_data.begin();
	}

	variable_map::map_t::const_iterator
	java_training_data::end ( void ) const
	{

	  trace::grnn_detail ( "Inside Java_Training_Data::end (const)" );

	  return m_data.end();
	}

	variable_map::map_t::iterator
	java_training_data::end ( void )
	{

	  trace::grnn_detail ( "Inside Java_Training_Data::end" );

	  return m_data.end();
	}

	void
	java_training_data::set_attribute ( boost::uint32_t index, double value )
	{
	  if ( index < java_training_data::attribute_count )
	    {
	      m_data.set_attribute ( index, value );
	    }
	}

	double
	java_training_data::get_attribute ( boost::uint32_t index )
	{
	  if ( index < java_training_data::attribute_count )
	    {
	      return m_data.get_attribute ( index );
	    }
	  else
	    {
	      throw errors::internal_exception ( errors::internal_exception::invalid_index );
	    }
	}

	bool
	java_training_data::empty ( void ) const
	{
	  return m_data.empty();
	}

      } // namespace grnn
    } // namespace input 
  } // namespace components
} // namespace reverse

