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

#include <reverse/errors/IO_Exception.h>
#include <reverse/errors/Reverse_Exception.h>
#include <reverse/io/File.h>
#include <reverse/io/File_ID.h>
#include <reverse/io/String_Converter.h>

#include <boost/format.hpp>

#include <unicode/ustring.h>

#include <sstream>
#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#ifdef LIBREVERSE_DEBUG
#include <reverse/Trace.h>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
    namespace io {

      File::File ( boost::shared_ptr < const File_ID >& filename )
	: m_error ( U_ZERO_ERROR )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File constructor (file_id)" );
#endif /* LIBREVERSE_DEBUG */

	io::Preconditions::is_set ( filename );

	m_file_id = filename;
	
	m_conv = ucnv_open ( NULL, &m_error );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Exiting File constructor (file id)" );
#endif /* LIBREVERSE_DEBUG */

        }

      File::File ( boost::shared_ptr < data_container::Memory_Map >& file_img_ptr,
                   boost::shared_ptr < const File_ID >& filename )
                : m_error ( U_ZERO_ERROR )
      {
	

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File constructor (memory_map,file_id)" );
#endif /* LIBREVERSE_DEBUG */
	
	io::Preconditions::is_set ( filename );
	io::Preconditions::is_set ( file_img_ptr );
	    
	m_file_id = filename;
	m_file_img = file_img_ptr;
	
	m_conv = ucnv_open ( NULL, &m_error );
	
	
#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Exiting File constructor (memory_map,file_id)" );
#endif /* LIBREVERSE_DEBUG */
	
      }

      
      File::~File ()
      {
	
#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File destructor" );
#endif /* LIBREVERSE_DEBUG */
	
	ucnv_close ( m_conv );
	
	
#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Exiting File destructor" );
#endif /* LIBREVERSE_DEBUG */
	
      }

        io_types::File_ID::const_ptr_t
        File::get_ID () const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Inside File::get_ID" );
#endif /* LIBREVERSE_DEBUG */

            return m_file_id;
        }

        void File::read_Image ()
        {


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering File::read_Image" );
#endif /* LIBREVERSE_DEBUG */


            std::string name = m_file_id->get_Full_Name();

            if ( ! name.empty() )
            {
                std::ifstream file_handle_ref ( name.c_str(),
                                                std::ios::binary | std::ios::in );

                if ( ! file_handle_ref.is_open() ) // Expecting result of is_open() to be true
                {


#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( trace_area::IO,
				       trace_level::ERROR,
				       boost::str ( boost::format ( "Error opening %1%  %2%" )
						    % name
						    % strerror ( errno ) ) );

		  Trace::write_Trace ( trace_area::IO,
				       trace_level::ERROR,
				       boost::str ( boost::format ( "Exception throw in %s at line %d" ) 
						    % __FILE__
						    % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                    throw errors::IO_Exception ( errors::IO_Exception::FATAL_IO_ERROR );
                }


                file_handle_ref.seekg ( 0, std::ios::beg );

                m_file_img.reset ( new data_container::Memory_Map ( file_handle_ref ) );

                file_handle_ref.close();
            }
            else
            {

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( trace_area::IO,
				       trace_level::ERROR,
				       "String name for file is empty" );

		  Trace::write_Trace ( trace_area::IO,
				       trace_level::ERROR,
				       boost::str ( boost::format ( "Exception throw in %s at line %d" )
						    % __FILE__
						    % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

		  throw errors::IO_Exception ( errors::IO_Exception::INVALID_FILE_NAME );
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting File::read_Image" );
#endif /* LIBREVERSE_DEBUG */

        }

        bool File::init ( void )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering File::init" );
#endif /* LIBREVERSE_DEBUG */

            bool result = true;

            std::string name = m_file_id->get_Full_Name();

            if ( m_file_img.get() == 0 )
            {
                try
                {
                    this->read_Image();
                }
                catch ( errors::Reverse_Exception& )
                {
                    result = false;
                }
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting File::init" );
#endif /* LIBREVERSE_DEBUG */

            return result;
        }

        data_types::Memory_Map::const_iterator
        File::begin() const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering File::begin" );
#endif /* LIBREVERSE_DEBUG */

	    io::Preconditions::is_set ( m_file_img );

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting File::begin" );
#endif /* LIBREVERSE_DEBUG */

            return m_file_img->begin();
        }

        data_types::Memory_Map::const_iterator
        File::end() const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering File::end" );
#endif /* LIBREVERSE_DEBUG */


	    io::Preconditions::is_set ( m_file_img );


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting File::end" );
#endif /* LIBREVERSE_DEBUG */

            return m_file_img->end();
        }

        data_types::Memory_Map::ptr_t
        File::get_Map_Ptr ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Inside File::get_Map_Ptr" );
#endif /* LIBREVERSE_DEBUG */

	    io::Preconditions::is_set ( m_file_img );

            return m_file_img;
        }

        boost::uint32_t
        File::size ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering File::size" );
#endif /* LIBREVERSE_DEBUG */


	    io::Preconditions::is_set ( m_file_img );


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting File::size" );
#endif /* LIBREVERSE_DEBUG */

            return m_file_img->size();
        }

        std::string
        File::read_UTF16_String ( boost::uint32_t length )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering File::read_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */


            m_error = U_ZERO_ERROR;

            std::vector<UChar> input_string;
            UChar input_word = 0;

            for ( boost::uint32_t i = 0; i < length; i++ )
            {
                // Read first byte
                this->read ( &input_word );

                input_string.push_back ( input_word );
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting File::read_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */


            return String_Converter::convert_From_UTF16_String ( input_string );
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
