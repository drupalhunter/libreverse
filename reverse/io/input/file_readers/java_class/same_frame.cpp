/*  Same_Frame.cpp

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

#include "Same_Frame.h"
#include "Class_File.h"

#include "io/Output.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Same_Frame::Same_Frame ( boost::uint8_t tag )
        : m_tag ( tag )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Same_Frame::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Same_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

        output << io::Output::indent ( index )
               << boost::format("frame_type: 0x%1$2X") % static_cast<boost::uint16_t>(m_tag)
               << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Same_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    boost::uint8_t
    Same_Frame::get_Frame_Type ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame::get_Frame_Type" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint8_t
    Same_Frame::get_Offset_Delta ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame::get_Offset_Delta" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint8_t
    Same_Frame::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

} /* namespace java_module */
} /* namespace reverse */
