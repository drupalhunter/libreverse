/*  Method_Access_Flags.cpp

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

#include "Method_Access_Flags.h"

#ifdef LIBREVERSE_DEBUG
#include "reverse/Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    boost::uint16_t const Method_Access_Flags::ACC_PUBLIC        = 0x0001;
    boost::uint16_t const Method_Access_Flags::ACC_PRIVATE       = 0x0002;
    boost::uint16_t const Method_Access_Flags::ACC_PROTECTED     = 0x0004;
    boost::uint16_t const Method_Access_Flags::ACC_STATIC        = 0x0008;
    boost::uint16_t const Method_Access_Flags::ACC_FINAL         = 0x0010;
    boost::uint16_t const Method_Access_Flags::ACC_SYNCHRONIZED  = 0x0020;
    boost::uint16_t const Method_Access_Flags::ACC_NATIVE        = 0x0100;
    boost::uint16_t const Method_Access_Flags::ACC_ABSTRACT      = 0x0400;
    boost::uint16_t const Method_Access_Flags::ACC_STRICT        = 0x0800;
    boost::uint16_t const Method_Access_Flags::ACC_RESERVED      = 0xF2C0;

    bool
    Method_Access_Flags::has_Valid_Flags ( boost::uint16_t )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Method_Access_Flags::has_Valid_Flags" );
#endif /* LIBREVERSE_DEBUG */


        return true;
    }

} /* namespace java_module */
} /* namespace reverse */
