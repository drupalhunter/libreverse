/*  Attribute_Info_Factory.cpp

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

#include "Attribute_Info_Factory.h"
#include "Attribute_Tags.h"
#include "Constant_Value_Attribute.h"
#include "Source_File_Attribute.h"
#include "Stack_Map_Table_Attribute.h"
#include "Code_Attribute.h"
#include "Exceptions_Attribute.h"
#include "Enclosing_Method_Attribute.h"
#include "Inner_Classes_Attribute.h"
#include "Synthetic_Attribute.h"
#include "Signature_Attribute.h"
#include "Line_Number_Table_Attribute.h"
#include "Local_Variable_Table_Attribute.h"
#include "Deprecated_Attribute.h"
#include "Unknown_Attribute.h"
#include "errors/IO_Exception.h"
#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {


    java_types::Attribute_Info::ptr_t
    Attribute_Info_Factory::create ( boost::uint16_t tag_index, std::string tag )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Attribute_Info_Factory::create" );
#endif /* LIBREVERSE_DEBUG */


        Attribute_Info::ptr_t result;

        if ( !tag.empty() )
            {
                if ( matches ( Attribute_Tags::SOURCE_FILE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Source_File_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::CONSTANT_VALUE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Constant_Value_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::CODE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Code_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::STACK_MAP_TABLE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Stack_Map_Table_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::EXCEPTIONS, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Exceptions_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::INNER_CLASSES, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Inner_Classes_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::ENCLOSING_METHOD, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Enclosing_Method_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::SYNTHETIC, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Synthetic_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::SIGNATURE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Signature_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::LINE_NUMBER_TABLE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Line_Number_Table_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::LOCAL_VARIABLE_TABLE, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Local_Variable_Table_Attribute ( tag_index ) );
                    }
                else if ( matches ( Attribute_Tags::DEPRECATED, tag ) )
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Deprecated_Attribute ( tag_index ) );
                    }
                else
                    {
                        result = java_types::Attribute_Info::ptr_t ( new Unknown_Attribute ( tag ) );
                    }
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::ERROR,
                                     "Input tag was empty" );

                Trace::write_Trace
                    ( TraceArea::IO,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::IO_Exception ( errors::IO_Exception::BAD_INPUT );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Attribute_Info_Factory::create" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Attribute_Info_Factory::matches ( std::string target,
                                      std::string input )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Attribute_Info_Factory::matches" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( target == input )
            {
                result = true;
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Attribute_Info_Factory::matches" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

} /* namespace java_module */
} /* namespace reverse */
