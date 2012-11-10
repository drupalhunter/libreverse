/*  Component_State.cpp

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

#include "Component_State.h"
#include "Component_Actor.h"
#include "Component_Data.h"
#include "Component_Source_State.h"
#include "Component_Working_State.h"
#include "Component.h"
#include "infrastructure/data_source/Data_Object.h"
#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Component_State::Component_State ( boost::uint32_t id )
        :  m_data_ptr ( new Component_Data( id ) ),
           m_working_state_ptr ( new Component_Working_State ( m_data_ptr ) ),
           m_source_state_ptr ( new Component_Source_State ( m_data_ptr ) ),
           m_present_state_ptr ( m_working_state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_State constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_State::Component_State ( Component_State const& rhs )
        : boost::enable_shared_from_this<Component_State> (rhs),
          m_data_ptr ( new Component_Data( *rhs.m_data_ptr ) ),
          m_working_state_ptr ( new Component_Working_State ( m_data_ptr ) ),
          m_source_state_ptr ( new Component_Source_State ( m_data_ptr ) ),
          m_present_state_ptr ( m_working_state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_State copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_State::switch_State ( boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::switch_State" );
#endif /* LIBREVERSE_DEBUG */

        if ( this->check_Mode_Value ( mode ) )
            {
                m_present_state_ptr->switch_State ( this->shared_from_this(),
                                                    mode );
            }
        else
            {
                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::Component_Exception
                    ( errors::Component_Exception::INVALID_STATE );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::switch_State" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_State::set_State ( infrastructure_types::Component_State_Algorithm::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::set_State" );
#endif /* LIBREVERSE_DEBUG */

        if ( state_ptr.get() != 0 )
            {
                m_present_state_ptr = state_ptr;
            }
        else
            {
                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::switch_State" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Component_State::check_Mode_Value ( boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::check_Mode_Value" );
#endif /* LIBREVERSE_DEBUG */

        bool result = false;

        if ( ( mode == Component::WORKING_MODE ) ||
             ( mode == Component::SOURCE_MODE ) )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::check_Mode_Value" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    boost::uint32_t
    Component_State::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_State::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return m_present_state_ptr->get_ID();
    }

    void
    Component_State::run ( infrastructure_types::Component_Actor::ptr_t child_ptr,
                           Graph_Base::Data_Map_t* data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_State::run" );
#endif /* LIBREVERSE_DEBUG */

        m_present_state_ptr->run ( child_ptr, data_ptr );
    }

  infrastructure_types::Data_Source_Base::ptr_t
  Component_State::results ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::results" );
#endif /* LIBREVERSE_DEBUG */

        // At this point the Component_State_Algorithm has done its work.
        // The resutling data has been stored in the Component_Data. So
        // all we have to do is return the pointer.
        infrastructure_types::Data_Source_Base::ptr_t resulting_data_ptr = m_data_ptr->get_Data_Source();

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::results" );
#endif /* LIBREVERSE_DEBUG */

        return resulting_data_ptr;
    }


    void
    Component_State::add_Input_Source ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_State::add_Input_Source" );
#endif /* LIBREVERSE_DEBUG */

        m_data_ptr->add_Input_Source ( id );
    }

    void
    Component_State::received_Input_Source_Data ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::received_Input_Source_Data" );
#endif /* LIBREVERSE_DEBUG */

        if ( m_data_ptr->find ( id ) )
            {
                std::cout
                    << boost::format("Node(%d) - initialized with data from component #%d")
                    % m_data_ptr->get_ID()
                    % id
                    << std::endl;

                m_data_ptr->received_Input_Source_Data ( id );
            }
        else
            {
                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::Component_Exception
                    ( errors::Component_Exception::INVALID_INDEX );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::received_Input_Source_Data" );
#endif /* LIBREVERSE_DEBUG */

    }

  infrastructure_types::Component_Data::ptr_t
  Component_State::get_Data (void) const
  {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                           TraceLevel::DETAIL,
                           "Inside Component_State::get_Data" );
#endif /* LIBREVERSE_DEBUG */

      return m_data_ptr;
  }

  infrastructure_types::Component_Data::Input_Token_t::const_iterator
  Component_State::get_Source_List_Begin (void) const
  {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                           TraceLevel::DETAIL,
                           "Inside Component_State::get_Source_List_Begin" );
#endif /* LIBREVERSE_DEBUG */

      return m_data_ptr->get_Source_List_Begin();
  }

  infrastructure_types::Component_Data::Input_Token_t::const_iterator
  Component_State::get_Source_List_End (void) const
  {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                           TraceLevel::DETAIL,
                           "Inside Component_State::get_Source_List_End" );
#endif /* LIBREVERSE_DEBUG */

      return m_data_ptr->get_Source_List_End();
  }

    Component_State&
    Component_State::operator= ( Component_State const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Component_State temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Component_State::swap ( Component_State& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_State::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_data_ptr.swap ( rhs.m_data_ptr );
        m_working_state_ptr.swap ( rhs.m_working_state_ptr );
        m_source_state_ptr.swap ( rhs.m_source_state_ptr );
        m_present_state_ptr.swap ( rhs.m_present_state_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_State::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
