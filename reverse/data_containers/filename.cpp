/*  Filename.cpp

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

#include "Filename.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace data_container {

    Filename::Filename (std::string data)
        : m_data ( data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Filename constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Filename::Filename ( Filename const& rhs )
        : m_data ( rhs.m_data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Filename copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Filename&
    Filename::operator= ( Filename const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Filename::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Filename temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Filename::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Filename::swap ( Filename& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Filename::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_data, rhs.m_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Filename::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Filename::data () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Filename::data" );
#endif /* LIBREVERSE_DEBUG */

        return m_data;
    }

}  /* namespace data_types */
} /* namespace libreverse */
