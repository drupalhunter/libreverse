/*  Verification_Type_Factory.cpp

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

#include "Verification_Type_Factory.h"
#include "Verification_Type_Tags.h"
#include "Verification_Type_Info.h"
#include "Double_Variable_Info.h"
#include "Float_Variable_Info.h"
#include "Integer_Variable_Info.h"
#include "Long_Variable_Info.h"
#include "Null_Variable_Info.h"
#include "Object_Variable_Info.h"
#include "Top_Variable_Info.h"
#include "Uninitialized_This_Variable_Info.h"
#include "Uninitialized_Variable_Info.h"

#include "errors/IO_Exception.h"

#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace java_module {

    java_types::Verification_Type_Info::ptr_t
    Verification_Type_Factory::create ( boost::uint8_t tag )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Constant_Integer_Info::create" );
#endif /* LIBREVERSE_DEBUG */


        java_types::Verification_Type_Info::ptr_t result;

        if ( tag == Verification_Type_Tags::TOP )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Top_Variable_Info() );
            }
        else if ( tag == Verification_Type_Tags::INTEGER )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Integer_Variable_Info() );
            }
        else if ( tag == Verification_Type_Tags::FLOAT )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Float_Variable_Info() );
            }
        else if ( tag == Verification_Type_Tags::LONG )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Long_Variable_Info() );
            }
        else if ( tag == Verification_Type_Tags::DOUBLE )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Double_Variable_Info() );
            }
        else if ( tag == Verification_Type_Tags::NULL_TYPE )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Null_Variable_Info() );
            }
        else if ( tag == Verification_Type_Tags::UNINITIALIZED_THIS )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Uninitialized_This_Variable_Info () );
            }
        else if ( tag == Verification_Type_Tags::OBJECT )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Object_Variable_Info () );
            }
        else if ( tag == Verification_Type_Tags::UNINITIALIZED )
            {
                result = java_types::Verification_Type_Info::ptr_t ( new Uninitialized_Variable_Info () );
            }
        else
            {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format("Input tag (%d) is not valid.") % tag ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::IO_Exception ( errors::IO_Exception::BAD_INPUT );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Constant_Integer_Info::create" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

} /* namespace java_module */
} /* namespace libreverse */
