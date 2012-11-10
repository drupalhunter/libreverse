/*  Memory_Data_Source_Config.cpp

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

#include "Memory_Data_Source_Config.h"
#include "Reverse.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    boost::uint32_t const Memory_Data_Source_Config::type =
        api::Transfer_Types::MEMORY;

    Memory_Data_Source_Config::Memory_Data_Source_Config ()
      : m_id ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Source_Config constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Data_Source_Config::Memory_Data_Source_Config ( Memory_Data_Source_Config const& rhs )
        : Data_Source_Config_Base ( rhs ),
          m_id ( rhs.m_id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Source_Config copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Data_Source_Config::~Memory_Data_Source_Config ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Source_Config destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Memory_Data_Source_Config::get_Type() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Source_Config::get_Type" );
#endif /* LIBREVERSE_DEBUG */

        return type;
    }

    Memory_Data_Source_Config&
    Memory_Data_Source_Config::operator= ( Memory_Data_Source_Config const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Memory_Data_Source_Config::operator=" );
#endif /* LIBREVERSE_DEBUG */


        Memory_Data_Source_Config temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Data_Source_Config::operator=" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Memory_Data_Source_Config::swap ( Memory_Data_Source_Config& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Memory_Data_Source_Config::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_id, rhs.m_id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Data_Source_Config::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    void Memory_Data_Source_Config::set_ID ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Source_Config::set_ID" );
#endif /* LIBREVERSE_DEBUG */

        m_id = id;
    }

    boost::uint32_t
    Memory_Data_Source_Config::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Source_Config::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return m_id;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
