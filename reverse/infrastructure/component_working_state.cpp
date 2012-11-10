/*  Component_Working_State.cpp

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

#include "Component_Working_State.h"
#include "Component_Actor.h"
#include "Component_Data.h"
#include "Component_State.h"
#include "infrastructure/Component.h"
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Component_Working_State::Component_Working_State ( infrastructure_types::Component_Data::ptr_t data_ptr )
        : m_data_ptr ( data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Working_State constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_Working_State::Component_Working_State( Component_Working_State const& rhs )
        : Component_State_Algorithm ( rhs ),
          m_data_ptr ( rhs.m_data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Working_State copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Component_Working_State::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Working_State::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return m_data_ptr->get_ID();
    }

    void
    Component_Working_State::run ( infrastructure_types::Component_Actor::ptr_t child_ptr,
                                   infrastructure_types::Component_Graph::Data_Map_t* input_data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Working_State::run" );
#endif /* LIBREVERSE_DEBUG */

        m_data_ptr->gather_Inputs ( input_data_ptr );

        // Call child process function to do work.
        child_ptr->process ();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Working_State::run" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Working_State::switch_State ( infrastructure_types::Component_State::ptr_t state_ptr,
                                            boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Component_Working_State::switch_State (id=%d)" )
                                          % state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        if ( mode == Component::SOURCE_MODE )
            {
                state_ptr->set_State ( state_ptr->m_source_state_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Exiting Component_Working_State::switch_State (id=%d)" )
                                          % state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }
    
    Component_Working_State&
    Component_Working_State::operator= ( Component_Working_State const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Working_State::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Component_Working_State temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Working_State::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Component_Working_State::swap ( Component_Working_State& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Working_State::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_data_ptr.swap ( rhs.m_data_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Working_State::swap" );
#endif /* LIBREVERSE_DEBUG */

    }
    
} /* namespace infrastructure */
} /* namespace libreverse */
