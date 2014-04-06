/*  Class_Access_Flags.cpp

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

#include "Class_Access_Flags.h"
#include "Class_Access_Flags_Rules.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "reverse/Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    bool
    Class_Access_Flags::has_Valid_Flags ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags::has_Valid_Flags" );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "Value: %1$d ( 0x%2$04X )" )
					  % value
					  % value ) );
#endif /* LIBREVERSE_DEBUG */

	
        //Class_Access_Flags_Rules afr_ref;
        bool result = Class_Access_Flags_Rules::validate_Flags ( value );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags::has_Valid_Flags" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    std::string
    Class_Access_Flags::to_String ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags::to_String" );
#endif /* LIBREVERSE_DEBUG */

        std::stringstream output;
        if ( value & ACC_PUBLIC )
            {
                output << "  public";
            }
        if ( value & ACC_FINAL )
            {
                output << "  final";
            }
        if ( value & ACC_SUPER )
            {
                output << "  super";
            }
        if ( value & ACC_INTERFACE )
            {
                output << "  interface";
            }
        if ( value & ACC_ABSTRACT )
            {
                output << "  abstract";
            }
        if ( value & ACC_SYNTHETIC )
            {
                output << "  synthetic";
            }
        if ( value & ACC_ANNOTATION )
            {
                output << "  annotation";
            }
        if ( value & ACC_ENUM )
            {
                output << "  enum";
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output.str();

    }
} /* namespace java_module */
} /* namespace reverse */
