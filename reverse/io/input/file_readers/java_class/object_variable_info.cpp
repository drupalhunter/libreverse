/*  Object_Variable_Info.cpp

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

#include "Object_Variable_Info.h"
#include "Class_File.h"
#include "Verification_Type_Tags.h"

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

    Object_Variable_Info::Object_Variable_Info()
        : m_tag ( Verification_Type_Tags::OBJECT ),
          m_constant_pool_index ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Object_Variable_Info constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Object_Variable_Info::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Object_Variable_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;
	output << io::Output::indent ( index )
	       << "Object_Variable_Info" << std::endl;

        boost::uint16_t new_limit = index + 2;

	output << io::Output::indent ( new_limit )
	       << boost::format("Constant Pool Index: %1%")
	  % m_constant_pool_index
	       << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Object_Variable_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Object_Variable_Info::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Object_Variable_Info::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Object_Variable_Info ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Object_Variable_Info::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint8_t
    Object_Variable_Info::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Object_Variable_Info::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    bool Object_Variable_Info::is_Type ( boost::uint8_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Object_Variable_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( id == Verification_Type_Tags::OBJECT )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Object_Variable_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }


} /* namespace java_module */
} /* namespace reverse */
