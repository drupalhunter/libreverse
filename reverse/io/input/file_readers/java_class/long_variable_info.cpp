/*  Long_Variable_Info.cpp

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

#include "Long_Variable_Info.h"
#include "Verification_Type_Tags.h"

#include "io/Output.h"

#include <string>
#include <sstream>
#include <iostream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace java_module {

    Long_Variable_Info::Long_Variable_Info ()
        : m_tag ( Verification_Type_Tags::LONG )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Long_Variable_Info constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Long_Variable_Info::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Long_Variable_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( index )
	       << "Long_Variable_Info" << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Long_Variable_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    bool
    Long_Variable_Info::is_Type ( boost::uint8_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Long_Variable_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( id == Verification_Type_Tags::LONG )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Long_Variable_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    boost::uint8_t
    Long_Variable_Info::get_Tag ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Long_Variable_Info::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }
} /* namespace java_module */
} /* namespace libreverse */
