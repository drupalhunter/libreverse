/*  Tevis_Zero_Filled_Checker.cpp

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

#include "Tevis_Zero_Filled_Checker.h"
#include "Tevis_Zero_Filled_Checker_Algorithm.h"
#include "Tevis_Zero_Filled_Checker_Algorithm_Factory.h"
#include "meta/meta_object.h"
#include <iostream>
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/File_Reader.h"
#include "data_containers/filename.h"
#include "data_containers/memory_map.h"
#include "infrastructure/data_source/data_object.h"
#include "infrastructure/Component_Data.h"
#include "infrastructure/Component_State.h"
#include <boost/format.hpp>
#include "Trace.h"

using namespace reverse::api;
using namespace reverse::trace;
using namespace reverse::meta;

namespace reverse { namespace component {

    const std::string Tevis_Zero_Filled_Checker::m_name = "Tevis_Zero_Filled_Checker";

    Tevis_Zero_Filled_Checker::Tevis_Zero_Filled_Checker ()
        : m_state_ptr ( new infrastructure::Component_State (0) )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    Tevis_Zero_Filled_Checker::Tevis_Zero_Filled_Checker ( infrastructure_types::Component_State::ptr_t state_ptr )
        : m_state_ptr ( state_ptr )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    Tevis_Zero_Filled_Checker::Tevis_Zero_Filled_Checker ( Tevis_Zero_Filled_Checker const& rhs )
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<Tevis_Zero_Filled_Checker> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker copy constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    Tevis_Zero_Filled_Checker::~Tevis_Zero_Filled_Checker ()
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    void
    Tevis_Zero_Filled_Checker::received_Input_Source_Data ( boost::uint32_t id )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Tevis_Zero_Filled_Checker::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );

        std::cout <<
            boost::format("Tevis_Zero_Filled_Checker(%d)::init")
            % m_state_ptr->get_ID()
                  << std::endl;


        m_state_ptr->received_Input_Source_Data ( id );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Tevis_Zero_Filled_Checker::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }

    void
    Tevis_Zero_Filled_Checker::add_Input_Source ( boost::uint32_t id )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Tevis_Zero_Filled_Checker::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr->add_Input_Source ( id );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Tevis_Zero_Filled_Checker::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }

    std::string
    Tevis_Zero_Filled_Checker::get_Name (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker::get_Name (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_name;
    }

    void Tevis_Zero_Filled_Checker::process ()
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Tevis_Zero_Filled_Checker::process (id=%d)")
                           % m_state_ptr->get_ID() ) );

        infrastructure_types::Component_Data::ptr_t data_ptr =
            m_state_ptr->get_Data();

	/*---------------------------------*/
	/*          Get File Type          */
	/*---------------------------------*/
        meta::meta_object::const_ptr_t input_meta_ptr = data_ptr->get_Input_Meta_Data();

        meta_object::Data_Pair_t file_type_meta_value = input_meta_ptr->get_Value ( "file_type" );

        assert ( file_type_meta_value.second == meta_object::STRING );

        std::string file_type = file_type_meta_value.first;

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/
        boost::shared_ptr<Tevis_Zero_Filled_Checker_Algorithm> algorithm_ptr =
            Tevis_Zero_Filled_Checker_Algorithm_Factory::Instance().get_Algorithm ( file_type );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/

        std::string meta_output = algorithm_ptr->run ( data_ptr->get_Input_filename()->to_String() );

        meta::meta_object::ptr_t output_meta_ptr ( new meta::meta_object() );

        output_meta_ptr->add ( "suspicious_zero_regions",
                               meta_output,
                               meta::meta_object::STRING );

        data_ptr->set_Output_Meta_Data ( output_meta_ptr );

        data_ptr->set_Output_Data ( data_ptr->get_Input_filename() );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Tevis_Zero_Filled_Checker::process (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    void
    Tevis_Zero_Filled_Checker::run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Tevis_Zero_Filled_Checker::run (id=%d)")
                           % m_state_ptr->get_ID() ) );

        std::cout << std::endl
                  << "--------------------------------" << std::endl
                  << boost::format ( "%s(%d) - run" )
            % m_name
            % m_state_ptr->get_ID() << std::endl
                  << "--------------------------------" << std::endl;

        m_state_ptr->run ( this->shared_from_this(),
                           m_input_data );        

        std::cout << "--------------------------------" << std::endl
                  << boost::format ( "%s(%d) - done" )
            % m_name
            % m_state_ptr->get_ID() << std::endl
                  << "--------------------------------" << std::endl
                  << std::endl;

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Tevis_Zero_Filled_Checker::run (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    infrastructure_types::Data_Source_Base::ptr_t
    Tevis_Zero_Filled_Checker::results (void)
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker::results (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->results();
    }

    void
    Tevis_Zero_Filled_Checker::set_State ( boost::uint32_t mode )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker::set_State (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr->switch_State ( mode );
    }

    boost::uint32_t
    Tevis_Zero_Filled_Checker::get_ID (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker::get_ID (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Tevis_Zero_Filled_Checker::get_Source_List_Begin (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker::get_Source_List_Begin (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_Source_List_Begin ();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Tevis_Zero_Filled_Checker::get_Source_List_End (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Tevis_Zero_Filled_Checker::get_Source_List_End (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_Source_List_End ();
    }

    Tevis_Zero_Filled_Checker&
    Tevis_Zero_Filled_Checker::operator= ( Tevis_Zero_Filled_Checker const& rhs )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Tevis_Zero_Filled_Checker::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr.reset
            ( new infrastructure::Component_State( *rhs.m_state_ptr ) );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Tevis_Zero_Filled_Checker::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return *this;
    }

} /* namespace component */
} /* namespace reverse */
