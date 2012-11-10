/*  Constant_Integer_Info.cpp

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

#include "Constant_Integer_Info.h"
#include "Constant_Pool_Tags.h"
#include "Class_File.h"

#include "errors/IO_Exception.h"
#include "io/Byte_Converter.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace java_module {

    Constant_Integer_Info::Constant_Integer_Info()
        : m_tag ( Constant_Pool_Tags::INTEGER ),
          m_bytes ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Integer_Info constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Constant_Integer_Info::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Integer_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return boost::str ( boost::format("Integer = %1%") % m_bytes );
    }

    void
    Constant_Integer_Info::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Constant_Integer_Info::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Constant_Integer_Info ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Constant_Integer_Info::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Constant_Integer_Info::is_Type ( boost::uint8_t id ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Integer_Info::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return ( id == Constant_Pool_Tags::INTEGER );
    }

    boost::uint8_t
    Constant_Integer_Info::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Integer_Info::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint32_t
    Constant_Integer_Info::get_Value (void) const
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Constant_Integer_Info::get_Value" );
#endif /* LIBREVERSE_DEBUG */

      return m_bytes;
    }

} /* namespace java_module */
} /* namespace libreverse */
