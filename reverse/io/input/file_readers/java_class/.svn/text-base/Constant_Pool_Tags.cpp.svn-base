/*  Constant_Pool_Tags.cpp

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

#include "Constant_Pool_Tags.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace java_module {

    const boost::uint16_t Constant_Pool_Tags::UTF8 = 0x1;
    const boost::uint16_t Constant_Pool_Tags::RESERVED = 0x2;
    const boost::uint16_t Constant_Pool_Tags::INTEGER = 0x3;
    const boost::uint16_t Constant_Pool_Tags::FLOAT = 0x4;
    const boost::uint16_t Constant_Pool_Tags::LONG = 0x5;
    const boost::uint16_t Constant_Pool_Tags::DOUBLE = 0x6;
    const boost::uint16_t Constant_Pool_Tags::CLASS = 0x7;
    const boost::uint16_t Constant_Pool_Tags::STRING = 0x8;
    const boost::uint16_t Constant_Pool_Tags::FIELD_REF =0x9;
    const boost::uint16_t Constant_Pool_Tags::METHOD_REF = 0xA;
    const boost::uint16_t Constant_Pool_Tags::INTERFACE_METHOD_REF = 0xB;
    const boost::uint16_t Constant_Pool_Tags::NAME_AND_TYPE = 0xC;

    bool
    Constant_Pool_Tags::is_Valid_Tag ( boost::uint16_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Constant_Pool_Tags::is_Valid_Tag" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( ( id == UTF8 ) ||
             ( ( id >= INTEGER ) && ( id <= NAME_AND_TYPE ) ) )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Constant_Pool_Tags::is_Valid_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

} /* namespace java_module */
} /* namespace libreverse */
