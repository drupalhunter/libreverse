/*  Field_Access_Flags.cpp

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

#include "Field_Access_Flags.h"

#ifdef LIBREVERSE_DEBUG
#include "reverse/Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    boost::uint16_t const Field_Access_Flags::ACC_PUBLIC    = 0x0001;
    boost::uint16_t const Field_Access_Flags::ACC_PRIVATE   = 0x0002;
    boost::uint16_t const Field_Access_Flags::ACC_PROTECTED = 0x0004;
    boost::uint16_t const Field_Access_Flags::ACC_STATIC    = 0x0008;
    boost::uint16_t const Field_Access_Flags::ACC_FINAL     = 0x0010;
    boost::uint16_t const Field_Access_Flags::ACC_VOLATILE  = 0x0040;
    boost::uint16_t const Field_Access_Flags::ACC_TRANSIENT = 0x0080;
    boost::uint16_t const Field_Access_Flags::ACC_SYNTHETIC = 0x1000;
    boost::uint16_t const Field_Access_Flags::ACC_ENUM      = 0x4000;
    boost::uint16_t const Field_Access_Flags::ACC_RESERVED  = 0xFF20;

    bool Field_Access_Flags::has_Valid_Flags ( boost::uint16_t )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Field_Access_Flags::has_Valid_Flags" );
#endif /* LIBREVERSE_DEBUG */


        bool result = true;

        // --------------------------------------------
        //              CLASS CHECKS
        // --------------------------------------------

        /*
        // A specific field of a class may have at most one of its
        // ACC_PRIVATE, ACC_PROTECTED, and ACC_PUBLIC set and must NOT
        // have booth its ACC_FINAL and ACC_VOLATILE set.
        if ( value & ACC_PUBLIC )
        {
        // ACC_PRIVATE and ACC_PROTECTED must not be set
        if ( ( value & ACC_PRIVATE ) ||
        ( value & ACC_PROTECTED ) )
        {
	    result = false;
	    break;
        }	
        }
        else if ( value & ACC_PRIVATE )
        {
        // ACC_PUBLIC and ACC_PROTECTED must not be set
        if ( ( value & ACC_PUBLIC ) ||
        ( value & ACC_PROTECTED ) )
        {
	    result = false;
	    break;
        }	
        }
        else if ( value & ACC_PROTECTED )
        {
        // ACC_PUBLIC and ACC_PROTECTED must not be set
        if ( ( value & ACC_PUBLIC ) ||
        ( value & ACC_PRIVATE ) )
        {
	    result = false;
	    break;
        }	
        }
        */


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Field_Access_Flags::has_Valid_Flags" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

} /* namespace java_module */
} /* namespace reverse */
