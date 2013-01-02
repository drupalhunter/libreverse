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
#include <reverse/components/input/grnn/windows_training_data.hpp>
#include <reverse/components/input/grnn/configuration.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/reverse.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>
#include <iostream>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	const boost::uint8_t windows_training_data::attribute_count = 8;
	const boost::uint8_t windows_training_data::classifier_target = windows_training_data::attribute_target_id;

	windows_training_data::windows_training_data ()
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data constructor" );
	}

	windows_training_data::~windows_training_data ()
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data destructor" );
	}

	variable_map::map_t
	windows_training_data::get_candidate_data ( boost::shared_ptr < configuration<windows_training_data> > config ) const
	{
	  trace::grnn_detail ( "Entering Windows_Training_Data::get_Candidate_Data" );

	  variable_map::map_t output;

	  for ( boost::uint32_t index = 0;
		index < windows_training_data::attribute_count;
		++index )
	    {
	      if ( config->get_attribute ( index ) )
		{
		  output[index] = m_data.get_attribute ( index );
		}
	    }

	  trace::grnn_detail ( "Exiting Windows_Training_Data::get_Candidate_Data" );

	  return output;
	}

	std::string
	windows_training_data::get_attribute_string_list ( boost::shared_ptr < configuration<windows_training_data> > config )
	{
	  trace::grnn_detail ( "Entering Windows_Training_Data::get_Attribute_String_List" );
      
	  std::stringstream output;

	  output << "Windows_Training_Data #%1%" << std::endl;
	
	  if ( config->get_attribute ( windows_training_data::attribute_target_id ) )
	    {
	      output << "Target_ID" << std::endl;
	    }
	  
	  if ( config->get_attribute ( windows_training_data::attribute_filesize ) )
	    {
	      output << "filesize" << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_exe_header_address ) )
	    {
	      output << "dos exe header address" << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_coff_section_count ) )
	    {
	      output << "coff number of section headers" << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_code_size ) )
	    {
	      output << "optional header code size" << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_base_of_data ) )
	    {
	      output << "optional header base of data" << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_entry_point ) )
	    {
	      output << "optional header entry point" << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_image_size ) )
	    {
	      output << "optional header image size" << std::endl;
	    }

	  trace::grnn_detail ( "Exiting Windows_Training_Data::get_Attribute_String_List" );

	  return output.str();
	}

	std::string
	windows_training_data::to_string ( boost::shared_ptr < configuration<windows_training_data> > config ) const
	{
	  trace::grnn_detail ( "Entering Windows_Training_Data::to_String" );

	  std::stringstream output;

	  output << "windows_training_data" << std::endl;
	
	  if ( config->get_attribute ( windows_training_data::attribute_target_id ) )
	    {
	      output << boost::format ( "  target id...........: %1%" )
		% m_data.get_attribute ( attribute_target_id ) << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_filesize ) )
	    {
	      output << boost::format ( "  file size.............: %1% bytes" )
		% m_data.get_attribute ( attribute_filesize )  << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_exe_header_address ) )
	    {
	      output << boost::format ( "  exe header address.............: %1%" )
		% m_data.get_attribute ( attribute_exe_header_address )  << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_coff_section_count ) )
	    {
	      output << boost::format ( "  coff section header count......: %1%" )
		% m_data.get_attribute ( attribute_coff_section_count )  << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_code_size ) )
	    {
	      output << boost::format ( "  pe code size...................: %1%" )
		% m_data.get_attribute ( attribute_pe_opt_code_size )  << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_base_of_data ) )
	    {
	      output << boost::format ( "  pe base of data................: %1%" )
		% m_data.get_attribute ( attribute_pe_opt_base_of_data )  << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_entry_point ) )
	    {
	      output << boost::format ( "  pe entry point................: %1%" )
		% m_data.get_attribute ( attribute_pe_opt_entry_point )  << std::endl;
	    }

	  if ( config->get_attribute ( windows_training_data::attribute_pe_opt_image_size ) )
	    {
	      output << boost::format ( "  pe image size.................: %1%" )
		% m_data.get_attribute ( attribute_pe_opt_image_size )  << std::endl;
	    }

	  trace::grnn_detail ( "Exiting Windows_Training_Data::to_String" );

	  return output.str();
	}

	std::string
	windows_training_data::to_xml ( boost::shared_ptr < configuration<windows_training_data> > config ) const
	{
	  trace::grnn_detail ( "Entering Windows_Training_Data::to_XML" );

	  std::stringstream output;

	  output << "windows_training_data:" << std::endl
		 << boost::format ( "  compiler id.................: %1%" ) % this->get_attribute ( attribute_target_id )  << std::endl
		 << boost::format ( "  file size...................: %1% bytes" ) % this->get_attribute ( attribute_filesize )  << std::endl
		 << boost::format ( "  dos exe header address......: 0x%1$x" ) % this->get_attribute ( attribute_exe_header_address ) << std::endl
		 << boost::format ( "  optional header code size...: 0x%1%" ) % this->get_attribute ( attribute_pe_opt_code_size ) << std::endl
		 << boost::format ( "  optional base of data.......: 0x%1$x" ) % this->get_attribute ( attribute_pe_opt_base_of_data ) << std::endl
		 << boost::format ( "  optional entry point........: 0x%1$x" ) % this->get_attribute ( attribute_pe_opt_entry_point ) << std::endl
	    	 << boost::format ( "  optional image size.........: 0x%1$x" ) % this->get_attribute ( attribute_pe_opt_image_size ) << std::endl;

	  trace::grnn_detail ( "Exiting Windows_Training_Data::to_XML" );

	  return output.str();
	}

	variable_map::map_t::const_iterator
	windows_training_data::begin ( void ) const
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data::begin (const)" );

	  return m_data.begin();
	}

	variable_map::map_t::iterator
	windows_training_data::begin ( void )
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data::begin" );

	  return m_data.begin();
	}

	variable_map::map_t::const_iterator
	windows_training_data::end ( void ) const
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data::end (const)" );

	  return m_data.end();
	}

	variable_map::map_t::iterator
	windows_training_data::end ( void )
	{
	  trace::grnn_detail ( "Inside Windows_Training_Data::end" );

	  return m_data.end();
	}

	void
	windows_training_data::set_attribute ( boost::uint32_t index, double value )
	{
	  if ( index < windows_training_data::attribute_count )
	    {
	      m_data.set_attribute ( index, value );
	    }
	}

	double
	windows_training_data::get_attribute ( boost::uint32_t index ) const
	{
	  if ( index < windows_training_data::attribute_count )
	    {
	      return m_data.get_attribute ( index );
	    }
	  else
	    {
	      throw errors::internal_exception ( errors::internal_exception::invalid_index );
	    }
	}

	bool
	windows_training_data::empty ( void ) const
	{
	  return m_data.empty();
	}

      } // namespace input
    } // namespace grnn
  } // namespace components
} // namespace reverse

