/*  Null_Component.cpp

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

#include "Null_Component.h"
#include "meta/Meta_Object.h"
#include <iostream>
#include "io/input/File_Readers/Reader_Factory.h"
#include "infrastructure/data_source/Data_Object.h"
#include "infrastructure/Component_Data.h"
#include "infrastructure/Component_State.h"
#include "data_containers/Filename.h"
#include <boost/format.hpp>

#include "errors/Internal_Exception.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace component {

    const std::string Null_Component::NAME = "Null_Component";

    Null_Component::Null_Component ()
        : m_state_ptr ( new infrastructure::Component_State ( 0 ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component constructor (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Null_Component::Null_Component ( infrastructure_types::Component_State::ptr_t state_ptr )
        : m_state_ptr ( state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component constructor (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Null_Component::Null_Component ( Null_Component const& rhs )
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<Null_Component> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component copy constructor (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Null_Component::~Null_Component ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Null_Component constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Null_Component::add_Data_Output ( std::string name )
    {
        if ( name.empty() )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::COMPONENTS,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format("Exception throw in %s at line %d")
                                                  % __FILE__
                                                  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::Internal_Exception ( errors::Internal_Exception::EMPTY_STRING );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::add_Data_Output (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Data::ptr_t data_ptr = m_state_ptr->get_Data();

        data_types::Filename::const_ptr_t file_ptr ( new data_container::Filename ( name ) );

        data_ptr->set_Output_Data ( file_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Exiting Null_Component::add_Data_Output (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Null_Component::received_Input_Source_Data ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::received_Input_Source_Data (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        std::cout <<
            boost::format("Null_Component(%d)::init")
            % m_state_ptr->get_ID()
                  << std::endl;


        m_state_ptr->received_Input_Source_Data ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Exiting Null_Component::received_Input_Source_Data (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Null_Component::add_Input_Source ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::add_Input_Source (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->add_Input_Source ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::add_Input_Source (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Null_Component::get_Name (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::get_Name (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return NAME;
    }

    void
    Null_Component::process (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::process (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        std::cout << "  Did nothing" << std::endl;
    }

    void
    Null_Component::run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::run (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        std::cout << std::endl
                  << "--------------------------------" << std::endl
                  << boost::format ( "%s(%d) - run" )
            % NAME
            % m_state_ptr->get_ID() << std::endl
                  << "--------------------------------" << std::endl;

        m_state_ptr->run ( this->shared_from_this(),
                           m_input_data );

        // Do nothing
        std::cout << "--------------------------------" << std::endl
                  << boost::format ( "%s(%d) - done" )
            % NAME
            % m_state_ptr->get_ID() << std::endl
                  << "--------------------------------" << std::endl
                  << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::run (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Data_Source_Base::ptr_t
    Null_Component::results (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::results (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->results();
    }

    void
    Null_Component::set_State ( boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::switch (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        m_state_ptr->switch_State ( mode );
    }

    boost::uint32_t
    Null_Component::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::get_ID (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Null_Component::get_Source_List_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::get_Source_List_Begin (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->get_Source_List_Begin ();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Null_Component::get_Source_List_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Inside Null_Component::get_Source_List_End (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->get_Source_List_End ();
    }

    Null_Component&
    Null_Component::operator= ( Null_Component const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::operator= (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        Null_Component temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Exiting Null_Component::operator= (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Null_Component::swap ( Null_Component& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Entering Null_Component::swap (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr.swap ( rhs.m_state_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Exiting Null_Component::swap (id=%d)")
                                          % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }
} /* namespace component */
} /* namespace reverse */
