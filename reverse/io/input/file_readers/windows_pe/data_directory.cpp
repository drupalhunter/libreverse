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

#include "Data_Directory.h"

#include "io/Byte_Converter.h"

#include <iomanip>
#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace wpef_module {

    const char* Data_Directory::m_directory_names [] = {
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

    Data_Directory::Data_Directory ()
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Data_Directory() constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Data_Directory::to_String ()
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Data_Directory::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;
        output_str << "  Data Directory: " << std::endl;

        boost::uint8_t count = 0;
        for ( Directory_Type::const_iterator pos = m_dirs.begin();
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
    Data_Directory::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Data_Directory::convert" );
#endif /* LIBREVERSE_DEBUG */


	for ( Directory_Type::iterator pos = m_dirs.begin();
	      pos != m_dirs.end();
	      ++pos )
	  {
	    io::Byte_Converter::convert (pos->first);
	    io::Byte_Converter::convert (pos->second);
	  }
 
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Data_Directory::to_String" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace wpef_module */
} /* namespace libreverse */
