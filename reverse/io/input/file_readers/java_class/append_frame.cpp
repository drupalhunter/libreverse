/*  Append_Frame.cpp

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

#include "Append_Frame.h"
#include "Class_File.h"
#include "Verification_Type_Factory.h"
#include "Verification_Type_Info.h"

#include "io/Byte_Converter.h"

#include <boost/format.hpp>
#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Append_Frame::Append_Frame ( boost::uint8_t tag )
        : m_tag ( tag ),
          m_offset_delta ( tag )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Append_Frame (uint8_t) constructor" );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "tag = %1%" ) % static_cast<boost::uint16_t>(tag) ) );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Append_Frame::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Append_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */

        std::stringstream output;

        if ( index > 0 )
            {
                for ( boost::uint16_t i = 0; i < index; i++ )
                    {
                        output << " ";
                    }
            }

        output << boost::format("Tag: Append_Frame(0x%|1$X|)") % static_cast<boost::uint16_t>(m_tag) << std::endl;

        if ( index > 0 )
            {
                for ( boost::uint16_t i = 0; i < index; i++ )
                    {
                        output << " ";
                    }
            }

        output << boost::format("offset_delta: 0x%|1$X|") % m_offset_delta << std::endl;


        boost::uint16_t new_index = index + 2;

        for ( Append_Data_t::const_iterator cpos = m_data.begin();
              cpos != m_data.end();
              ++cpos )
            {
                output << (*cpos)->to_String ( new_index );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Append_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output.str();
    }

    void
    Append_Frame::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Append_Frame::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Append_Frame ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Append_Frame::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint8_t
    Append_Frame::get_Frame_Type ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Append_Frame::get_Frame_Type" );
#endif /* LIBREVERSE_DEBUG */

        return m_tag;
    }

    boost::uint8_t
    Append_Frame::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Append_Frame::get_Tag" );
#endif /* LIBREVERSE_DEBUG */

        return m_tag;
    }


} /* namespace java_module */
} /* namespace reverse */
