/*  Same_Frame_Extended.cpp

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

#include "Same_Frame_Extended.h"
#include "Class_File.h"

#include "io/Byte_Converter.h"
#include "io/Output.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Same_Frame_Extended::Same_Frame_Extended ( boost::uint8_t tag )
        : m_tag ( tag )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame_Extended constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Same_Frame_Extended::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Same_Frame_Extended::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( index )
	       << boost::format("frame_type: 0x%1$2X")
            % m_tag
	       << std::endl;

	output << io::Output::indent ( index )
	       << boost::format("offset_delta: 0x%1$2X")
            % m_offset_delta
	       << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Same_Frame_Extended::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Same_Frame_Extended::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Same_Frame_Extended::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Same_Frame_Extended ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Same_Frame_Extended::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint8_t
    Same_Frame_Extended::get_Frame_Type ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame_Extended::get_Frame_Type" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint8_t
    Same_Frame_Extended::get_Tag ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Same_Frame_Extended::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

} /* namespace java_module */
} /* namespace reverse */
