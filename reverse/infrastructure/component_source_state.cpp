/*  Component_Source_State.cpp

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

#include "Component_Source_State.h"
#include "Component_Data.h"
#include "Component_Actor.h"
#include "Component_State.h"
#include "Component.h"
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Component_Source_State::Component_Source_State ( infrastructure_types::Component_Data::ptr_t data_ptr )
        : m_data_ptr ( data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Source_State constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_Source_State::Component_Source_State ( Component_Source_State const& rhs )
        : Component_State_Algorithm (rhs),
          m_data_ptr ( rhs.m_data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Source_State copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Component_Source_State::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Source_State::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return static_cast<boost::uint32_t>(0);
    }

    void
    Component_Source_State::run ( infrastructure_types::Component_Actor::ptr_t,
                                  infrastructure_types::Component_Graph::Data_Map_t* )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Source_State::run" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Source_State::switch_State ( infrastructure_types::Component_State::ptr_t state_ptr,
                                           boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Component_Source_State::switch_State (id=%d)" )
                                          % state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        if ( mode == Component::WORKING_MODE )
            {
                state_ptr->set_State ( state_ptr->m_working_state_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Exiting Component_Source_State::switch_State (id=%d)" )
                                          % state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_Source_State&
    Component_Source_State::operator= ( Component_Source_State const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Source_State::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        Component_Source_State temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Source_State::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Component_Source_State::swap ( Component_Source_State& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Source_State::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_data_ptr.swap ( rhs.m_data_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Source_State::swap" );
#endif /* LIBREVERSE_DEBUG */

    }


} /* namespace infrastructure */
} /* namespace libreverse */
