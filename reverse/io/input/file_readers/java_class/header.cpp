/*  Header.cpp

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

#include "Header.h"
#include "Class_Header.h"

#include "errors/IO_Exception.h"
#include "io/Preconditions.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace reverse { namespace java_module {

    Header::Header()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void Header::init ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header::init" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Header::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header::convert" );
#endif /* LIBREVERSE_DEBUG */

    }

    java_types::Class_Header::ptr_t
    Header::get_Class_Header (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header::get_Class_Header" );
#endif /* LIBREVERSE_DEBUG */


        return m_class_hdr;
    }

    void
    Header::set_Class_Header ( java_types::Class_Header::ptr_t ch_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header::set_Class_Header" );
#endif /* LIBREVERSE_DEBUG */

	io::Preconditions::is_set ( ch_ptr );

	m_class_hdr = ch_ptr;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header::set_Class_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string const
    Header::to_String ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return m_class_hdr->to_String();
    }

} /* namespace java_module */
} /* namespace reverse */
