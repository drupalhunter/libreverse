/*  Byte_Converter.h

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

#ifndef REVERSE_IO_BYTE_CONVERTER_HPP_INCLUDED
#define REVERSE_IO_BYTE_CONVERTER_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace reverse {
  namespace io {

    /*!
     * \class Byte_Converter
     * \date 2003
     * \author Stephen Torri
     */
    class byte_converter
    {
    public:

      /*! \brief Big endian type definition */
      static const bool big_endian_type = true;

      /*! \brief Little endian type definition */
      static const bool little_endian_type = false;

      /*!
       * \brief Convert 16-bit data to correct endian type
       * \return Converted 16-bit data
       */
      static inline void convert ( boost::uint16_t& input )
      {


#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::io,
                             trace_level::detail,
                             "Entering Byte_Converter::convert (uint16)" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint16_t output = (input << 8) | ((input >> 8) & 0x00ff);
        input = output;


#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::io,
                             trace_level::detail,
                             "Exiting Byte_Converter::convert (uint16)" );
#endif /* LIBREVERSE_DEBUG */

      }

      /*!
       * \brief Convert 32-bit data to correct endian type
       * \return Converted 32-bit data
       */
      static inline void convert ( boost::uint32_t& input )
      {


#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::io,
                             trace_level::detail,
                             "Entering Byte_Converter::convert (uint32)" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t output = (input << 24) |
	  ((input << 8) & 0x00ff0000) |
	  ((input >> 8) & 0x0000ff00) |
	  ((input >> 24) & 0x000000ff);
        input = output;


#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::io,
                             trace_level::detail,
                             "Exiting Byte_Converter::convert (uint32)" );
#endif /* LIBREVERSE_DEBUG */

      }

      /*!
       * \brief Convert 64-bit data to correct endian type
       * \return Converted 64-bit data
       */
      static inline void convert ( boost::uint64_t& input )
      {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::io,
                             trace_level::detail,
                             "Entering Byte_Converter::convert (uint64)" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint64_t output = (input << 56) |
	  ((input << 40) & 0x00ff000000000000ULL) |
	  ((input << 24) & 0x0000ff0000000000ULL) |
	  ((input << 8)  & 0x000000ff00000000ULL) |
	  ((input >> 8)  & 0x00000000ff000000ULL) |
	  ((input >> 24) & 0x0000000000ff0000ULL) |
	  ((input >> 40) & 0x000000000000ff00ULL) |
	  ((input >> 56) & 0x00000000000000ffULL);

        input = output;


#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::io,
                             trace_level::detail,
                             "Entering Byte_Converter::convert (uint64)" );
#endif /* LIBREVERSE_DEBUG */


      }

      template <typename value_type>
      static inline value_type check_convert ( value_type val, bool need_convert )
      {
	if ( need_convert )
	  {
	    io::byte_converter::convert ( val );
	  }

	return val;
      }
    };

  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_BYTE_CONVERTER_HPP_INCLUDED
