/*  DOS_Relocation_Header.cpp

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

#include <reverse/io/input/file_readers/windows_pe/dos_relocation_header.hpp>
#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>

#include <iomanip>
#include <sstream>


namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  dos_relocation_header::dos_relocation_header()
	    : m_offset ( 0 ),
	      m_segment ( 0 )
	  {}

	  void dos_relocation_header::convert ()
	  {
            io::byte_converter::convert ( m_offset );
            io::byte_converter::convert ( m_segment );
	  }

	  boost::uint32_t const
	  dos_relocation_header::get_size ()
	  {
            boost::uint32_t size = 32;
            return size;
	  }

	  std::string dos_relocation_header::to_string ()
	  {
            std::stringstream output_str;

            output_str
	      << boost::format ( "DOS Relocation Header:   Offset: 0x%1%  Segment: 0x%2%" ) %
	      boost::io::group ( std::setfill ( '0' ),
				 std::hex,
				 std::setw ( 4 ),
				 m_offset ) %
	      boost::io::group ( std::setfill ( '0' ),
				 std::hex,
				 std::setw ( 4 ),
				 m_segment );

            return output_str.str();

	  }

    	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

