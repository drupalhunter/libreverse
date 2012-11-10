/*  Output.h

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

#ifndef REVERSE_IO_OUTPUT_HPP_INCLUDED
#define REVERSE_IO_OUTPUT_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <sstream>
#include <string>

#ifdef LIBREVERSE_DEBUG
#include <reverse/Trace.h>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace io {

    class Output {
    public:

        static inline std::string indent ( boost::uint32_t size )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Entering Output::indent" );
#endif /* LIBREVERSE_DEBUG */

            
            std::stringstream output;

            if ( size > 0 )
            {
                for (boost::uint16_t i = 0; i < size; ++i )
                    {
                        output << " ";
                    }
            }


#ifdef LIBREVERSE_DEBUG            
            Trace::write_Trace ( trace_area::IO,
                                 trace_level::DETAIL,
                                 "Exiting Output::indent" );
#endif /* LIBREVERSE_DEBUG */

            
            return output.str();
        }

    };

  } /* namespace io */
} /* namespace reverse */

#endif // #ifndef REVERSE_IO_OUTPUT_HPP_INCLUDED
