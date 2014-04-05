/*  Constant_Fieldref_Info.cpp

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

#include "Constant_Fieldref_Info.h"
#include "Constant_Pool_Tags.h"
#include "Class_File.h"

#include <boost/format.hpp>

#include "errors/IO_Exception.h"
#include "io/Byte_Converter.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Constant_Fieldref_Info::Constant_Fieldref_Info()
        : m_tag ( Constant_Pool_Tags::FIELD_REF ),
          m_class_index ( 0 ),
          m_name_and_type_index ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Constant_Fieldref_Info::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return boost::str ( boost::format("Fieldref, %1$d (0x%2$X), %3$d (0x%4$X)")
                            % m_class_index
                            % m_class_index
                            % m_name_and_type_index
                            % m_name_and_type_index );
    }

    void
    Constant_Fieldref_Info::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Constant_Fieldref_Info ( this->shared_from_this() );
    }

    bool
    Constant_Fieldref_Info::is_Type ( boost::uint8_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return ( id == Constant_Pool_Tags::FIELD_REF );
    }

    boost::uint8_t
    Constant_Fieldref_Info::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint16_t
    Constant_Fieldref_Info::get_Class_Index (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info::get_Class_Index" );
#endif /* LIBREVERSE_DEBUG */


        return m_class_index;
    }

    boost::uint16_t
    Constant_Fieldref_Info::get_Name_And_Type_Index (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Fieldref_Info::get_Name_And_Type_Index" );
#endif /* LIBREVERSE_DEBUG */


        return m_name_and_type_index;
    }

} /* namespace java_module */
} /* namespace reverse */
