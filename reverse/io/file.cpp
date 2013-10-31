/*  File.cpp

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

#include <reverse/errors/io_exception.hpp>
#include <reverse/errors/reverse_exception.hpp>
#include <reverse/io/file.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/string_converter.hpp>
#include <reverse/preconditions.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

#include <unicode/ustring.h>

#include <cstring>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

namespace reverse {
  namespace io {

    file::file ( boost::shared_ptr < const file_id >& filename )
      : m_error ( U_ZERO_ERROR )
    {
      trace::io_detail ( "Entering File constructor (file_id)" );

      preconditions::is_set ( filename );

      m_file_id = filename;
	
      m_conv = ucnv_open ( NULL, &m_error );

      trace::io_detail ( "Exiting File constructor (file id)" );

    }

    file::file ( boost::shared_ptr < data_containers::memory_map >& file_img_ptr,
		 boost::shared_ptr < const file_id >& filename )
      : m_error ( U_ZERO_ERROR )
    {
	
      trace::io_detail ( "Entering File constructor (memory_map,file_id)" );
	
      preconditions::is_set ( filename );
      preconditions::is_set ( file_img_ptr );
	    
      m_file_id = filename;
      m_file_img = file_img_ptr;
	
      m_conv = ucnv_open ( NULL, &m_error );
	
      trace::io_detail ( "Exiting File constructor (memory_map,file_id)" );
    }

      
    file::~file ()
    {
      trace::io_detail ( "Entering File destructor" );
	
      ucnv_close ( m_conv );
	
      trace::io_detail ( "Exiting File destructor" );
    }

    boost::shared_ptr < const io::file_id > 
    file::get_id () const
    {
      trace::io_detail ( "Inside File::get_ID" );

      return m_file_id;
    }

    void file::read_image ()
    {
      trace::io_detail ( "Entering File::read_Image" );

      std::string name = m_file_id->get_full_name();
	
      if ( ! name.empty() )
	{
	  std::ifstream file_handle_ref ( name.c_str(),
					  std::ios::binary | std::ios::in );

	  if ( ! file_handle_ref.is_open() ) // Expecting result of is_open() to be true
	    {
	      trace::io_data ( "Error opening %1%  %2%",
				name,
				strerror ( errno ) );
	      trace::io_error ( "Exception throw in %s at line %d"
				__FILE__,
				__LINE__ );

	      throw errors::io_exception ( errors::io_exception::fatal_io_error );
	    }


	  file_handle_ref.seekg ( 0, std::ios::beg );
	    
	  m_file_img = boost::make_shared < data_containers::memory_map > ( file_handle_ref );
		
	  file_handle_ref.close();
	}
      else
	{
	  trace::io_error ( "String name for file is empty" );
	  trace::io_error ( "Exception throw in %s at line %d"
			    __FILE__,
			    __LINE__ );
	    
	  throw errors::io_exception ( errors::io_exception::invalid_file_name );
	}

      trace::io_detail ( "Exiting File::read_Image" );
    }

    bool file::init ( void )
    {
      trace::io_detail ( "Entering File::init" );

      bool result = true;
	  
      std::string name = m_file_id->get_full_name();

      if ( m_file_img.get() == 0 )
	{
	  try
	    {
	      this->read_image();
	    }
	  catch ( errors::reverse_exception& )
	    {
	      result = false;
	    }
	}

      trace::io_detail ( "Exiting File::init" );

      return result;
    }

    data_containers::memory_map::const_iterator
    file::begin() const
    {
      trace::io_detail ( "Entering File::begin" );

      preconditions::is_set ( m_file_img );

      trace::io_detail ( "Exiting File::begin" );

      return m_file_img->begin();
    }
      
    data_containers::memory_map::const_iterator
    file::end() const
    {
      trace::io_detail ( "Entering File::end" );

      preconditions::is_set ( m_file_img );

      trace::io_detail ( "Exiting File::end" );

      return m_file_img->end();
    }

    boost::shared_ptr < data_containers::memory_map >
    file::get_map_ptr ( void ) const
    {
      trace::io_detail ( "Inside File::get_Map_Ptr" );

      preconditions::is_set ( m_file_img );
	  
      return m_file_img;
    }

    boost::uint32_t
    file::size ( void ) const
    {
      trace::io_detail ( "Entering File::size" );

      preconditions::is_set ( m_file_img );

      trace::io_detail ( "Exiting File::size" );

      return m_file_img->size();
    }

    std::string
    file::read_utf16_string ( boost::uint32_t length )
    {
      trace::io_detail ( "Entering File::read_UTF16_String" );

      m_error = U_ZERO_ERROR;
	  
      std::vector<UChar> input_string;
      UChar input_word = 0;
	  
      for ( boost::uint32_t i = 0; i < length; i++ )
	{
	  // Read first byte
	  this->read ( &input_word );

	  input_string.push_back ( input_word );
	}

      trace::io_detail ( "Exiting File::read_UTF16_String" );

      return estring_converter::convert_from_utf16_string ( input_string );
    }

    std::string
    File::read_UTF8_String ( boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Entering File::read_UTF8_String" );
#endif /* LIBREVERSE_DEBUG */


      m_error = U_ZERO_ERROR;

      std::vector<char> input_string;

      char input_byte = 0;

      for ( boost::uint32_t i = 0; i < length; i++ )
	{
	  // Read first byte
	  this->read ( &input_byte );

	  input_string.push_back ( input_byte );
	}

      std::vector<UChar> utf16_dest_string = String_Converter::convert_From_UTF8_String ( input_string );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DATA,
			   "Exiting File::read_UTF8_String" );

      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Exiting File::read_UTF8_String" );
#endif /* LIBREVERSE_DEBUG */


      return String_Converter::convert_From_UTF16_String ( utf16_dest_string );
    }

    std::vector<UChar>
    File::read_8bit_Java_Unicode_String ( boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Entering File::read_8bit_Java_Unicode_String" );
#endif /* LIBREVERSE_DEBUG */


      std::vector<UChar> input_string;

      boost::uint8_t x_byte = 0;
      boost::uint8_t y_byte = 0;
      boost::uint8_t z_byte = 0;

      for ( boost::uint32_t i = 0; i < length; )
	{
	  // Read first byte
	  this->read ( &x_byte );


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( trace_area::IO,
			       trace_level::DATA,
			       boost::str ( boost::format ( "(0x%|1$X|) X_Byte: %|2$X|" )
					    % m_file_img->get_Previous_Position_Address()
					    % static_cast<boost::uint16_t> ( x_byte ) ) );
#endif /* LIBREVERSE_DEBUG */


	  // Check to see if the 7th bit is 0
	  if ( ( x_byte & 0x80 ) == 0x0 )
	    {
	      // Single byte representing a 16-bit char
	      boost::uint16_t val = x_byte & 0x7F;


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "    Val: %|1$X|" ) % val ) );
#endif /* LIBREVERSE_DEBUG */


	      input_string.push_back ( val );

	      i += 1;
	    }
	  else if ( ( x_byte & 0xC0 ) == 0xC0 )
	    {
	      // Two bytes representing a 16-bit char
	      this->read ( &y_byte );


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "(0x%|1$X|) Y_Byte: %|2$X|" )
						% m_file_img->get_Previous_Position_Address()
						% static_cast<boost::uint16_t> ( y_byte ) ) );
#endif /* LIBREVERSE_DEBUG */


	      boost::uint16_t high_bits = ( x_byte & 0x1F ) << 6;


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "    high bits: %|1$02X|" ) % high_bits ) );
#endif /* LIBREVERSE_DEBUG */


	      boost::uint16_t low_bits = y_byte & 0x3F;


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "    low bits: %|1$02X|" ) % low_bits ) );
#endif /* LIBREVERSE_DEBUG */


	      boost::uint16_t val = high_bits + low_bits;


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "    Val: %|1$02X|" ) % val ) );
#endif /* LIBREVERSE_DEBUG */


	      input_string.push_back ( val );

	      i += 2;
	    }
	  else if ( ( x_byte & 0xE0 ) == 0xE0 )
	    {
	      // Three bytes representing a 16-bit char
	      this->read ( &y_byte );


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "(0x%|1$X|) X_Byte: %|2$X|" )
						% m_file_img->get_Previous_Position_Address()
						% static_cast<boost::uint16_t> ( y_byte ) ) );
#endif /* LIBREVERSE_DEBUG */


	      this->read ( &z_byte );


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "(0x%|1$X|) X_Byte: %|2$X|" )
						% m_file_img->get_Previous_Position_Address()
						% static_cast<boost::uint16_t> ( z_byte ) ) );
#endif /* LIBREVERSE_DEBUG */


	      boost::uint16_t high_bits = ( x_byte & 0xF ) << 12;
	      boost::uint16_t mid_bits = ( y_byte & 0x3F ) << 6;
	      boost::uint16_t low_bits = z_byte & 0x3F;
	      boost::uint16_t val = high_bits + mid_bits + low_bits;

	      input_string.push_back ( val );
	      i += 3;
	    }
#ifdef LIBREVERSE_DEBUG
	  else
	    {
	      Trace::write_Trace ( trace_area::IO,
				   trace_level::DATA,
				   boost::str ( boost::format ( "Unhandled byte (%X)" )
						% x_byte ) );
	    }
#endif /* LIBREVERSE_DEBUG */

	}

      input_string.push_back ( '\0' );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Exiting File::read_8bit_Java_Unicode_String" );
#endif /* LIBREVERSE_DEBUG */


      return input_string;
    }

    std::string
    File::read_String ( boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Entering File::read_String" );
#endif /* LIBREVERSE_DEBUG */


      std::string input_string ( "" );

      char input_byte = 0;

      if ( length != 0 )
	{
	  for ( boost::uint32_t i = 0; i < length; ++i )
	    {
	      // Read byte
	      this->read ( &input_byte );

	      if ( input_byte != 0x0 )
		{
		  input_string += input_byte;
		}
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DATA,
			   boost::str ( boost::format ( "Input string: %1%" ) % input_string ) );

      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Exiting File::read_String" );
#endif /* LIBREVERSE_DEBUG */


      return input_string;
    }

    std::string
    File::read_Null_Terminated_String ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Entering File::read_Null_Terminated_String" );
#endif /* LIBREVERSE_DEBUG */


      std::string input_string ( "" );

      char input_byte = 0;

      while ( true )
	{
	  // Read byte
	  this->read ( &input_byte );

	  if ( input_byte != 0x0 )
	    {
	      input_string += input_byte;
	    }
	  else
	    {
	      break;
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( trace_area::IO,
			   trace_level::DATA,
			   boost::str ( boost::format ( "Input string: %1%" ) % input_string ) );

      Trace::write_Trace ( trace_area::IO,
			   trace_level::DETAIL,
			   "Exiting File::read_Null_Terminated_String" );
#endif /* LIBREVERSE_DEBUG */


      return input_string;
    }
  } /* Namespace io */
} /* namespace libreverse */
