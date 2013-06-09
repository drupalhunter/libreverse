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

#include <reverse/components/input/grnn/configuration.hpp>
#include <reverse/components/input/grnn/elf_training_data.hpp>
#include <reverse/components/input/grnn/elf_input_tag_names.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <iostream>
#include <sstream>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {


	const boost::uint8_t elf_training_data::attribute_count = 8;
	const boost::uint8_t elf_training_data::classifier_target = elf_training_data::attribute_target_id;

	elf_training_data::elf_training_data ()
	{
	  trace::grnn_detail ( "inside elf_training_data constructor" );
	}

	elf_training_data::~elf_training_data ()
	{
	  trace::grnn_detail ( "Inside Elf_Training_Data destructor" );
	}

	std::string
	elf_training_data::get_attribute_string_list ( boost::shared_ptr < const configuration < elf_training_data > > config )
	{
	  trace::grnn_detail ( "Entering Elf_Training_Data::get_Attribute_String_List" );
      
	  std::stringstream output;

	  output << "elf_training_data:" << std::endl;
	
	  if ( config->get_attribute ( elf_training_data::attribute_target_id ) )
	    {
	      output << "Target_ID" << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_filesize ) )
	    {
	      output << "Filesize" << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_entry_point_address ) )
	    {
	      output << "Entry Point Address" << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_section_headers_start ) )
	    {
	      output << "Section headers start" << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_program_header_count ) )
	    {
	      output << "Program header count" << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_section_header_count ) )
	    {
	      output << "Section header count" << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_section_header_string_table_index ) )
	    {
	      output << "Section header string table index" << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_text_section_size ) )
	    {
	      output << "Text section size" << std::endl;
	    }

	  trace::grnn_detail ( "Exiting Elf_Training_Data::get_Attribute_String_List" );

	  return output.str();
	}

	std::string
	elf_training_data::to_string ( boost::shared_ptr < configuration < elf_training_data > > config ) const
	{
	  trace::grnn_detail ( "Entering Elf_Training_Data::to_String" );

	  std::stringstream output;
	  output << "elf_training_data:" << std::endl;
	
	  if ( config->get_attribute ( elf_training_data::attribute_target_id ) )
	    {
	      output << boost::format ( "  target id...........: %1%" )
		% m_data.get_attribute ( attribute_target_id ) << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_filesize ) )
	    {
	      output << boost::format ( "  file size.............: %1% bytes" )
		% m_data.get_attribute ( attribute_filesize )  << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_entry_point_address ) )
	    {
	      output << boost::format ( "  entry point address............: %1%" )
		%  m_data.get_attribute ( attribute_entry_point_address ) << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_section_headers_start ) )
	    {
	      output << boost::format ( "  section headers start...........: %1%" )
		%  m_data.get_attribute ( attribute_section_headers_start ) << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_program_header_count ) )
	    {
	      output << boost::format ( "  program header count...............: %1%" )
		%  m_data.get_attribute ( attribute_section_header_count ) << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_section_header_count ) )
	    {
	      output << boost::format ( "  section header count...: %1%" )
		%  m_data.get_attribute ( attribute_section_header_count ) << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_section_header_string_table_index ) )
	    {
	      output << boost::format ( "  section header string table index..: %1%" )
		%  m_data.get_attribute ( attribute_section_header_string_table_index ) << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_text_section_size ) )
	    {
	      output << boost::format ( "  text section size..: %1%" )
		%  m_data.get_attribute ( attribute_text_section_size ) << std::endl;
	    }

	  trace::grnn_detail ( "Exiting Elf_Training_Data::to_String" );

	  return output.str();
	}

	std::string
	elf_training_data::to_xml ( boost::shared_ptr < configuration < elf_training_data > > config ) const
	{
	  trace::grnn_detail ( "Entering Elf_Training_Data::to_XML" );

	  std::stringstream output;
	  output << boost::format ( "  <%1%>" ) % elf_input_tag_names::tag_file << std::endl;
	
	  if ( config->get_attribute ( elf_training_data::attribute_target_id ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_target_id
		% m_data.get_attribute ( attribute_target_id )
		% elf_input_tag_names::tag_target_id << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_filesize ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_filesize
		% m_data.get_attribute ( attribute_filesize )
		% elf_input_tag_names::tag_filesize << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_entry_point_address ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_entry_point_address
		%  m_data.get_attribute ( attribute_entry_point_address )
		% elf_input_tag_names::tag_entry_point_address << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_section_headers_start ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_section_headers_start
		%  m_data.get_attribute ( attribute_section_headers_start )
		% elf_input_tag_names::tag_section_headers_start << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_program_header_count ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_program_header_count
		%  m_data.get_attribute ( attribute_program_header_count )
		% elf_input_tag_names::tag_program_header_count << std::endl;
	    }
        
	  if ( config->get_attribute ( elf_training_data::attribute_section_header_count ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_section_header_count
		%  m_data.get_attribute ( attribute_section_header_count )
		% elf_input_tag_names::tag_section_header_count << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_section_header_string_table_index ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_section_header_string_table_index
		%  m_data.get_attribute ( attribute_section_header_string_table_index )
		% elf_input_tag_names::tag_section_header_string_table_index << std::endl;
	    }

	  if ( config->get_attribute ( elf_training_data::attribute_text_section_size ) )
	    {
	      output << boost::format ( "    <%1%>%2%</%3%>" )
		% elf_input_tag_names::tag_text_section_size
		%  m_data.get_attribute ( attribute_text_section_size )
		% elf_input_tag_names::tag_text_section_size << std::endl;
	    }

	  output << boost::format ( "  </%1%>" ) % elf_input_tag_names::tag_file << std::endl;
	  
	  trace::grnn_detail ( "Exiting Elf_Training_Data::to_XML" );

	  return output.str();
	}

	variable_map::map_t::const_iterator
	elf_training_data::begin ( void ) const
	{

	  trace::grnn_detail ( "Inside Elf_Training_Data::begin (const)" );

	  return m_data.begin();
	}

	variable_map::map_t::iterator
	elf_training_data::begin ( void )
	{

	  trace::grnn_detail ( "Inside Elf_Training_Data::begin" );

	  return m_data.begin();
	}

	variable_map::map_t::const_iterator
	elf_training_data::end ( void ) const
	{

	  trace::grnn_detail ( "Inside Elf_Training_Data::end (const)" );

	  return m_data.end();
	}

	variable_map::map_t::iterator
	elf_training_data::end ( void )
	{
	  trace::grnn_detail ( "Inside Elf_Training_Data::end" );

	  return m_data.end();
	}

	void
	elf_training_data::set_attribute ( boost::uint32_t index, double value )
	{
	  trace::grnn_detail ( "Inside Elf_Training_Data::set_attribute" );

	  if ( index < elf_training_data::attribute_count )
	    {
	      m_data.set_attribute ( index, value );
	    }
	}

	double
	elf_training_data::get_attribute ( boost::uint32_t index ) const
	{
	  trace::grnn_detail ( "Inside Elf_Training_Data::get_attribute" );

	  if ( index < elf_training_data::attribute_count )
	    {
	      return m_data.get_attribute ( index );
	    }
	  else
	    {
	      throw errors::internal_exception ( errors::internal_exception::invalid_index );
	    }
	}

	bool
	elf_training_data::empty ( void ) const
	{
	  return m_data.empty();
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse
