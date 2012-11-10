/*  Constant_Class_Info.cpp

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

#include "Constant_Class_Info.h"
#include "Constant_Pool_Tags.h"
#include "Class_File.h"

#include "io/Byte_Converter.h"
#include "errors/IO_Exception.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace java_module {

    Constant_Class_Info::Constant_Class_Info()
        : m_tag ( Constant_Pool_Tags::CLASS ),
          m_name_index ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Constant_Class_Info::~Constant_Class_Info()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Constant_Class_Info::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return boost::str ( boost::format("Class, %1%") % m_name_index );
    }

    void
    Constant_Class_Info::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Constant_Class_Info ( this->shared_from_this() );
    }

    bool
    Constant_Class_Info::is_Type ( boost::uint8_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return ( id == Constant_Pool_Tags::CLASS );
    }

    boost::uint8_t
    Constant_Class_Info::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint16_t
    Constant_Class_Info::get_Name_Index (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Class_Info::get_Name_Index" );
#endif /* LIBREVERSE_DEBUG */


        return m_name_index;
    }
} /* namespace java_module */
} /* namespace libreverse */
