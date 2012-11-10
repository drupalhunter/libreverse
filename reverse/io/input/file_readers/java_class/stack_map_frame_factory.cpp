/*  Stack_Map_Frame_Factory.cpp

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

#include "Stack_Map_Frame_Factory.h"
#include "Same_Frame.h"
#include "Same_Locals_One_Stack_Item_Frame.h"
#include "Same_Locals_One_Stack_Item_Frame_Extended.h"
#include "Chop_Frame.h"
#include "Same_Frame_Extended.h"
#include "Append_Frame.h"
#include "Full_Frame.h"
#include "Stack_Map_Frame_Tags.h"

#include "errors/IO_Exception.h"

#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace java_module {


    java_types::Stack_Map_Frame::ptr_t
    Stack_Map_Frame_Factory::create ( boost::uint8_t tag )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Stack_Map_Frame_Factory::create" );
#endif /* LIBREVERSE_DEBUG */


        java_types::Stack_Map_Frame::ptr_t result;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "Tag: %d" ) % static_cast<boost::uint16_t>(tag) ) );
#endif /* LIBREVERSE_DEBUG */


        if ( ( tag >= Stack_Map_Frame_Tags::SAME_LOWER_LIMIT ) &&
             ( tag <= Stack_Map_Frame_Tags::SAME_UPPER_LIMIT ) )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Create Same_Frame" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Same_Frame( tag ) );
            }
        else if ( ( tag >= Stack_Map_Frame_Tags::SAME_LOCALS_ONE_ITEM_LOWER_LIMIT ) && 
                  ( tag <= Stack_Map_Frame_Tags::SAME_LOCALS_ONE_ITEM_UPPER_LIMIT ) )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Create Same_Locals_One_Stack_Item_Frame" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Same_Locals_One_Stack_Item_Frame( tag ) );
            }
        else if ( tag == Stack_Map_Frame_Tags::SAME_LOCALS_EXTENDED )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Create Same_Locals_One_Stack_Item_Frame_Extended" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Same_Locals_One_Stack_Item_Frame_Extended( tag ) );
            }
        else if ( ( tag >= Stack_Map_Frame_Tags::CHOP_FRAME_LOWER_LIMIT ) && 
                  ( tag <= Stack_Map_Frame_Tags::CHOP_FRAME_UPPER_LIMIT ) )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Create Chop_Frame" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Chop_Frame( tag ) );
            }
        else if ( tag == Stack_Map_Frame_Tags::SAME_FRAME_EXTENDED )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Create Same_Frame_Extended" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Same_Frame_Extended( tag ) );
            }
        else if ( ( tag >= Stack_Map_Frame_Tags::APPEND_FRAME_LOWER_LIMIT ) &&
                  ( tag <= Stack_Map_Frame_Tags::APPEND_FRAME_UPPER_LIMIT ) )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Create Append_Frame" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Append_Frame( tag ) );
            }
        else if ( tag == Stack_Map_Frame_Tags::FULL_FRAME )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     "Full Append_Frame" );
#endif /* LIBREVERSE_DEBUG */


                result = java_types::Stack_Map_Frame::ptr_t ( new Full_Frame ( tag ) );
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::ERROR,
				     boost::str ( boost::format("Input tag (%d) is unknown") % tag ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::IO_Exception ( errors::IO_Exception::BAD_INPUT );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Stack_Map_Frame_Factory::create" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

} /* namespace java_module */
} /* namespace libreverse */
