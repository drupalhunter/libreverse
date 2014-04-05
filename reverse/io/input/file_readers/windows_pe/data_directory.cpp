/*  Data_Directory.cpp

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

#include <reverse/io/input/file_readers/windows_pe/data_directory.hpp>
#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>

#include <iomanip>
#include <sstream>


#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  const char* data_directory::m_directory_names [] = {
	    "Export Directory",
	    "Import Directory",
	    "Resource Directory",
	    "Exception Directory",
	    "Security Directory",
	    "Base Relocation Token",
	    "Debug Directory",
	    "Architecture Specific",
	    "Global Pointer",
	    "TLS Directory",
	    "Load Config Directory",
	    "Bound Import Directory",
	    "Import Address Token",
	    "Delay Load IAT",
	    "CLR Header",
	  };

	  data_directory::data_directory ()
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside Data_Directory() constructor" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  std::string
	  data_directory::to_string ()
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Data_Directory::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream output_str;
	    output_str << "  Data Directory: " << std::endl;

	    boost::uint8_t count = 0;
	    for ( directory_type::const_iterator pos = m_dirs.begin();
		  pos != m_dirs.end();
		  ++pos )
	      {
                output_str << boost::format("    %|24|") %
		  m_directory_names[count++];

                output_str << boost::format("  Addr: 0x%1%") %
		  boost::io::group(std::setfill('0'),
				   std::hex,
				   std::setw(8),
				   pos->second);

                output_str << " Size: " << pos->first << std::endl;

	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Data_Directory::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    return output_str.str();
	  }

	  void
	  data_directory::convert ()
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Data_Directory::convert" );
#endif /* LIBREVERSE_DEBUG */


	    for ( directory_type::iterator pos = m_dirs.begin();
		  pos != m_dirs.end();
		  ++pos )
	      {
		io::byte_converter::convert (pos->first);
		io::byte_converter::convert (pos->second);
	      }
 
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Data_Directory::to_String" );
#endif /* LIBREVERSE_DEBUG */

	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

