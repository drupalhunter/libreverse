/*  Chop_Frame.cpp

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

#include "Chop_Frame.h"
#include "Class_File.h"

#include "io/Byte_Converter.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Chop_Frame::Chop_Frame ( boost::uint8_t tag )
        : m_tag ( tag ),
          m_offset_delta ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Chop_Frame constructor(uint8_t)" );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "tag = %1%" ) % static_cast<boost::uint16_t>(tag) ) );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Chop_Frame::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Chop_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

        if ( index > 0 )
            {
                for ( boost::uint16_t i = 0; i < index; i++ )
                    {
                        output << " ";
                    }
            }

        output << boost::format("Tag: Chop_Frame (0x%X)")
            % static_cast<boost::uint16_t>(m_tag)
               << std::endl;

        if ( index > 0 )
            {
                for ( boost::uint16_t i = 0; i < index; i++ )
                    {
                        output << " ";
                    }
            }

        output << boost::format("frame_type: 0x%X")
            % static_cast<boost::uint16_t>(m_tag) << std::endl;

        if ( index > 0 )
            {
                for ( boost::uint16_t i = 0; i < index; i++ )
                    {
                        output << " ";
                    }
            }

        output << boost::format("offset_delta: 0x%1$2X")
            % m_offset_delta;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Chop_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output.str();
    }

    void
    Chop_Frame::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Chop_Frame::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Chop_Frame ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Chop_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */
    }

    boost::uint8_t
    Chop_Frame::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Chop_Frame::get_Tag" );
#endif /* LIBREVERSE_DEBUG */

        return m_tag;
    }

    boost::uint8_t
    Chop_Frame::get_Frame_Type ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Chop_Frame::get_Frame_Type" );
#endif /* LIBREVERSE_DEBUG */

        return m_tag;
    }

} /* namespace java_module */
} /* namespace reverse */
