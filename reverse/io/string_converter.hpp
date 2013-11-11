/*  String_Converter.h

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

#ifndef REVERSE_IO_STRING_CONVERTER_HPP_INCLUDED
#define REVERSE_IO_STRING_CONVERTER_HPP_INCLUDED

#include <reverse/trace.hpp>

#include <boost/cstdint.hpp>

#include <unicode/ucnv.h>
#include <unicode/ustring.h>

#include <vector>
#include <string>

namespace reverse {
  namespace io {

    class string_converter {
    public:

      static inline std::string convert_from_utf16_string ( std::vector<UChar> const& input_string )
      {
	trace::io_detail ( "Entering String_Converter::convert_From_UTF16_String" );

        UErrorCode m_error ( U_ZERO_ERROR );
        UConverter* m_conv = ucnv_open ( NULL, &m_error );

        std::vector<char> dest_string ( input_string.size() );

        boost::uint32_t result_length = ucnv_fromUChars ( m_conv,
							  &(*(dest_string.begin())),
							  dest_string.size(),
							  &(*(input_string.begin())),
							  input_string.size(),
							  &m_error );
        
        if ( m_error == U_BUFFER_OVERFLOW_ERROR )
	  {
	    dest_string.reserve ( result_length );
	    result_length = ucnv_fromUChars ( m_conv,
					      &(*(dest_string.begin())),
					      dest_string.size(),
					      &(*(input_string.begin())),
					      input_string.size(),
					      &m_error );
	  }


        std::vector<char>::iterator zero_pos = std::find ( dest_string.begin(),
                                                           dest_string.end(),
                                                           0 );
        
        std::string output ( &(*(dest_string.begin())), zero_pos - dest_string.begin() );

	trace::io_detail ( "Exiting String_Converter::convert_From_UTF16_String" );

        return output;
      }

      static inline std::string convert_from_utf16_string ( std::vector<unsigned char>::const_iterator& input_begin,
							    boost::uint32_t& input_size )
      {
	trace::io_detail ( "Entering String_Converter::convert_From_UTF16_String" );

        UErrorCode m_error ( U_ZERO_ERROR );
        UConverter* m_conv = ucnv_open ( NULL, &m_error );

        std::vector<char> dest_string ( input_size );

        boost::uint32_t result_length =
	  ucnv_fromUChars ( m_conv,
			    &(*(dest_string.begin())),
			    dest_string.size(),
			    reinterpret_cast<const UChar*>(&(*input_begin)),
			    input_size,
			    &m_error );
        
        if ( m_error == U_BUFFER_OVERFLOW_ERROR )
	  {
	    dest_string.reserve ( result_length );
	    result_length = ucnv_fromUChars ( m_conv,
					      &(*(dest_string.begin())),
					      dest_string.size(),
					      reinterpret_cast<const UChar*>(&(*input_begin)),
					      input_size,
					      &m_error );
	  }


        std::vector<char>::iterator zero_pos = std::find ( dest_string.begin(),
                                                           dest_string.end(),
                                                           0 );
        
        std::string output ( &(*(dest_string.begin())), zero_pos - dest_string.begin() );

	trace::io_detail ( "Exiting String_Converter::convert_From_UTF16_String" );

        return output;
      }

      /* Convert UTF-8 string to UTF-16 */
      static inline std::vector<UChar> convert_from_utf8_string ( std::vector<char> const& input_string )
      {
	trace::io_detail ( "Entering String_Converter::convert_From_UTF8_String" );

        UErrorCode m_error ( U_ZERO_ERROR );
        std::vector<UChar> utf16_dest_string;
        boost::int32_t utf16_size = 0;

        // Pre-flight conversion from UTF-8 to UTF-16
        
        UChar* utf16_chars = u_strFromUTF8 ( &(*(utf16_dest_string.begin())),
                                             0,
                                             &utf16_size,
                                             static_cast<const char*>(&(*(input_string.begin()))),
                                             input_string.size(),
                                             &m_error );

        if ( m_error == U_BUFFER_OVERFLOW_ERROR )
	  {

	    m_error = U_ZERO_ERROR;

	    // Set the desination size	
	    utf16_dest_string.resize ( utf16_size );

	    int utf16_size2 = 0;

	    // Convert from UTF-8 to UTF-16
	    utf16_chars = u_strFromUTF8 ( &(*(utf16_dest_string.begin())),
					  utf16_dest_string.size(),
					  &utf16_size2,
					  reinterpret_cast<const char*>(&(*input_string.begin())),
					  input_string.size(),
					  &m_error );

	  }

        if ( U_FAILURE ( m_error ) )
	  {
	    trace::io_data ( "String_Converter::convert_From_UTF8_String: %1X (%2s)",
			      m_error,
			      ( u_errorName ( m_error ) ) );
	  }

	trace::io_detail ( "String_Converter::convert_From_UTF8_String" );

        return utf16_dest_string;
      }

    };

  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_STRING_CONVERTER_HPP_INCLUDED
