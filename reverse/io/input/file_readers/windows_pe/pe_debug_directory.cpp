/*  PE_Debug_Directory.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_debug_directory.hpp>
#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  pe_debug_directory::pe_debug_directory()
	    : m_characteristics ( 0 ),
	      m_time_date_stamp ( 0 ),
	      m_major_version ( 0 ),
	      m_minor_version ( 0 ),
	      m_type ( 0 ),
	      m_size_of_data ( 0 ),
	      m_address_of_raw_data ( 0 ),
	      m_pointer_to_raw_data ( 0 )
	  {}

	  boost::uint32_t
	  pe_debug_directory::get_size ( void ) const
	  {
            return static_cast<boost::uint32_t> ( 32 );
	  }

	  std::string
	  pe_debug_directory::to_string ( void )
	  {
            std::stringstream output_str;

            output_str << "pe debug directory:" << std::endl;

            output_str << boost::format ( "  characteristics:             %1x" ) %
	      m_characteristics
		       << std::endl;

            boost::posix_time::ptime epoch ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_time_date_stamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << boost::format ( "  time & date:              %1%" ) %
	      boost::posix_time::to_simple_string ( creation_date )
		       << std::endl;

            output_str << boost::format ( "  version:                  %1%.%2%" ) %
	      m_major_version %
	      boost::io::group ( std::setfill ( '0' ),
				 std::setw ( 2 ),
				 m_minor_version )
		       << std::endl;

            output_str << boost::format ( "  type:                     %1s" ) %
	      debug_types::get_type_name ( m_type )
		       << std::endl;

            output_str << boost::format ( "  size of data:             %1x" ) %
	      m_size_of_data
		       << std::endl;

            output_str << boost::format ( "  address of raw data:      %1x" ) %
	      m_address_of_raw_data
		       << std::endl;

            output_str << boost::format ( "  pointers to raw data:     %1x" ) %
	      m_pointer_to_raw_data
		       << std::endl;

            return output_str.str();

	  }

	  void
	  pe_debug_directory::convert ()
	  {
            io::byte_converter::convert ( m_characteristics );
            io::byte_converter::convert ( m_time_date_stamp );
            io::byte_converter::convert ( m_major_version );
            io::byte_converter::convert ( m_minor_version );
            io::byte_converter::convert ( m_type );
            io::byte_converter::convert ( m_size_of_data );
            io::byte_converter::convert ( m_address_of_raw_data );
            io::byte_converter::convert ( m_pointer_to_raw_data );
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


