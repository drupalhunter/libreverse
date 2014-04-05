/*  filename.cpp

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

#include "filename.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace data_container {

    filename::filename (std::string data)
        : m_data ( data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside filename constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    filename::filename ( filename const& rhs )
        : m_data ( rhs.m_data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside filename copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    filename&
    filename::operator= ( filename const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering filename::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        filename temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting filename::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    filename::swap ( filename& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering filename::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_data, rhs.m_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting filename::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    filename::data () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside filename::data" );
#endif /* LIBREVERSE_DEBUG */

        return m_data;
    }

}  /* namespace data_types */
} /* namespace reverse */
