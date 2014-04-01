/*  Unpacker.cpp

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

#include "Unpacker.h"
#include "Unpacker_Algorithm.h"
#include "Unpacker_Algorithm_Factory.h"
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

using namespace libreverse::api;
using namespace libreverse::trace;
using namespace libreverse::meta;

namespace libreverse { namespace component {

    const std::string Unpacker::m_name = "Unpacker";

    Unpacker::Unpacker ()
        : m_state_ptr ( new infrastructure::Component_State (0) )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    Unpacker::Unpacker ( infrastructure_types::Component_State::ptr_t state_ptr )
        : m_state_ptr ( state_ptr )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    Unpacker::Unpacker ( Unpacker const& rhs )
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<Unpacker> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker copy constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    Unpacker::~Unpacker ()
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    void
    Unpacker::received_Input_Source_Data ( boost::uint32_t id )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Unpacker::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );

        std::cout <<
            boost::format("Unpacker(%d)::init")
            % m_state_ptr->get_ID()
                  << std::endl;


        m_state_ptr->received_Input_Source_Data ( id );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Unpacker::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }

    void
    Unpacker::add_Input_Source ( boost::uint32_t id )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Unpacker::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr->add_Input_Source ( id );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Unpacker::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }

    std::string
    Unpacker::get_Name (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker::get_Name (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_name;
    }

    void Unpacker::process ()
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Unpacker::process (id=%d)")
                           % m_state_ptr->get_ID() ) );

        infrastructure_types::Component_Data::ptr_t data_ptr =
            m_state_ptr->get_Data();

	/*---------------------------------*/
	/*          Get File Type          */
	/*---------------------------------*/

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/

        data_types::memory_map::const_ptr_t input_file_map_ptr =
            data_ptr->get_Input_memory_map();

        meta::meta_object::const_ptr_t meta_ptr =
            data_ptr->get_Input_Meta_Data();

        meta_object::Data_Pair_t arch_meta_value =
            meta_ptr->get_Value ( "arch_type" );

        assert ( arch_meta_value.second == meta_object::STRING );
        std::string arch_str_val = arch_meta_value.first;

        boost::shared_ptr<Unpacker_Algorithm> algorithm_ptr =
            Unpacker_Algorithm_Factory::Instance().get_Algorithm ( arch_str_val );

        data_types::memory_map::const_ptr_t output_file_map_ptr =
            algorithm_ptr->run ( meta_ptr,
                                 input_file_map_ptr );

        data_ptr->set_Output_Data ( output_file_map_ptr );

        /**
         * add input filename to output information
         */
        data_ptr->set_Output_Data ( data_ptr->get_Input_filename() );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Unpacker::process (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    void
    Unpacker::run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Unpacker::run (id=%d)")
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
              boost::str ( boost::format ( "Exiting Unpacker::run (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    infrastructure_types::Data_Source_Base::ptr_t
    Unpacker::results (void)
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker::results (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->results();
    }

    void
    Unpacker::set_State ( boost::uint32_t mode )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker::set_State (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr->switch_State ( mode );
    }

    boost::uint32_t
    Unpacker::get_ID (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker::get_ID (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Unpacker::get_Source_List_Begin (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker::get_Source_List_Begin (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_Source_List_Begin ();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Unpacker::get_Source_List_End (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Unpacker::get_Source_List_End (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_Source_List_End ();
    }

    Unpacker&
    Unpacker::operator= ( Unpacker const& rhs )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Unpacker::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr.reset
            ( new infrastructure::Component_State( *rhs.m_state_ptr ) );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Unpacker::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return *this;
    }

} /* namespace component */
} /* namespace libreverse */
