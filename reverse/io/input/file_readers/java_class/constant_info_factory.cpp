/*  Constant_Info_Factory.cpp

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

#include "Constant_Info_Factory.h"
#include "Constant_Pool_Tags.h"
#include "Constant_Class_Info.h"
#include "Constant_Double_Info.h"
#include "Constant_Fieldref_Info.h"
#include "Constant_Float_Info.h"
#include "Constant_Integer_Info.h"
#include "Constant_InterfaceMethodref_Info.h"
#include "Constant_Long_Info.h"
#include "Constant_Methodref_Info.h"
#include "Constant_Name_And_Type_Info.h"
#include "Constant_String_Info.h"
#include "Constant_Utf8_Info.h"

#include "errors/IO_Exception.h"

#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {


    java_types::Constant_Pool_Info::ptr_t
    Constant_Info_Factory::create ( boost::uint16_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Constant_Info_Factory::create" );
#endif /* LIBREVERSE_DEBUG */


        java_types::Constant_Pool_Info::ptr_t result;

        if ( Constant_Pool_Tags::is_Valid_Tag ( id ) )
            {
                if ( Constant_Pool_Tags::UTF8 == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Utf8_Info () );
                    }
                else if ( Constant_Pool_Tags::INTEGER == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Integer_Info() );
                    }
                else if ( Constant_Pool_Tags::FLOAT == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Float_Info() );
                    }
                else if ( Constant_Pool_Tags::LONG == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Long_Info() );
                    }
                else if ( Constant_Pool_Tags::DOUBLE == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Double_Info() );
                    }
                else if ( Constant_Pool_Tags::CLASS == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Class_Info() );
                    }
                else if ( Constant_Pool_Tags::STRING == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_String_Info () );
                    }
                else if ( Constant_Pool_Tags::FIELD_REF == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Fieldref_Info () );
                    }
                else if ( Constant_Pool_Tags::METHOD_REF == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Methodref_Info () );
                    }
                else if ( Constant_Pool_Tags::INTERFACE_METHOD_REF == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_InterfaceMethodref_Info() );
                    }
                else if ( Constant_Pool_Tags::NAME_AND_TYPE == id )
                    {
                        result = java_types::Constant_Pool_Info::ptr_t ( new Constant_Name_And_Type_Info() );
                    }
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::ERROR,
				   boost::str ( boost::format("Unexpected value received: %1%") % id ) );
#endif /* LIBREVERSE_DEBUG */


	      throw errors::IO_Exception ( errors::IO_Exception::BAD_INPUT );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Constant_Info_Factory::create" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

} /* namespace java_module */
} /* namespace reverse */
