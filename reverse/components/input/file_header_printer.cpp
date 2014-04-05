/*  File_Header_Printer.cpp

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

#include "File_Header_Printer.h"
#include "infrastructure/data_source/Data_Source_Factory.h"
#include <iostream>
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/File_Reader.h"
#include "data_containers/filename.h"
#include "infrastructure/data_source/data_object.h"
#include "infrastructure/Component_Data.h"
#include "infrastructure/Component_State.h"
#include <boost/format.hpp>
#include "errors/API_Exception.h"
#include "Trace.h"

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse { namespace component {

    const std::string File_Header_Printer::m_name = "File_Header_Printer";

    File_Header_Printer::File_Header_Printer ()
        : m_state_ptr ( new infrastructure::Component_State (0) )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    File_Header_Printer::File_Header_Printer ( infrastructure_types::Component_State::ptr_t state_ptr )
        : m_state_ptr ( state_ptr )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    File_Header_Printer::File_Header_Printer ( File_Header_Printer const& rhs )
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<File_Header_Printer> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer copy constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    File_Header_Printer::~File_Header_Printer ()
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer destructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    void
    File_Header_Printer::received_Input_Source_Data ( boost::uint32_t id )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering File_Header_Printer::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );

        std::cout <<
            boost::format("File_Header_Printer(%d)::init")
            % m_state_ptr->get_ID()
                  << std::endl;


        m_state_ptr->received_Input_Source_Data ( id );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting File_Header_Printer::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }

    void
    File_Header_Printer::add_Input_Source ( boost::uint32_t id )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr->add_Input_Source ( id );
    }

    std::string
    File_Header_Printer::get_Name (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::get_Name (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_name;
    }

    void File_Header_Printer::process ()
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering File_Header_Printer::process (id=%d)")
                           % m_state_ptr->get_ID() ) );

        infrastructure_types::Component_Data::ptr_t data_ptr = m_state_ptr->get_Data();

        if ( ! data_ptr->is_filename_Set() )
            {
                Trace::write_Trace
                    ( TraceArea::COMPONENTS,
                      TraceLevel::ERROR,
                      "Unable to find the input file name." );

                Trace::write_Trace
                    ( TraceArea::COMPONENTS,
                      TraceLevel::ERROR,
                      "Cannot find the arch type without it." );

                Trace::write_Trace
                    ( TraceArea::COMPONENTS,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );

                // At this point we have not found the filename somehow
                // the Precondition visitor did not work. So we will
                // will throw an exception
                throw ( errors::API_Exception
                        ( errors::API_Exception::INTERNAL_LIBRARY_ERROR ) );
            }

	/*---------------------------------*/
	/*          Get File Type          */
	/*---------------------------------*/

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/

        data_types::filename::const_ptr_t file_ptr =
            data_ptr->get_Input_filename();

        io::File_Reader::ptr_t file_reader_ptr =
            ( io::Reader_Factory::Instance() ).create_File_Reader ( file_ptr->to_String() );

        std::cout << file_reader_ptr->to_String();

        /**
         * add input filename to output information
         */
        data_ptr->set_Output_Data ( file_ptr );

        Trace::write_Trace ( TraceArea::COMPONENTS,
                             TraceLevel::DATA,
                             data_ptr->to_String() );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting File_Header_Printer::process (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }

    void
    File_Header_Printer::run ( infrastructure::Graph_Base::Data_Map_t* m_input_data )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering File_Header_Printer::run (id=%d)")
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
              boost::str ( boost::format ( "Exiting File_Header_Printer::run (id=%d)")
                           % m_state_ptr->get_ID() ) );
    }

    infrastructure_types::Data_Source_Base::ptr_t
    File_Header_Printer::results (void)
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::results (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->results();
    }

    void
    File_Header_Printer::set_State ( boost::uint32_t mode )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::set_State (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr->switch_State ( mode );
    }

    boost::uint32_t
    File_Header_Printer::get_ID (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::get_ID (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    File_Header_Printer::get_Source_List_Begin (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::get_Source_List_Begin (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_Source_List_Begin ();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    File_Header_Printer::get_Source_List_End (void) const
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside File_Header_Printer::get_Source_List_End (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return m_state_ptr->get_Source_List_End ();
    }

    File_Header_Printer&
    File_Header_Printer::operator= ( File_Header_Printer const& rhs )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering File_Header_Printer::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );

        File_Header_Printer temp ( rhs );
        swap ( temp );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting File_Header_Printer::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );

        return *this;
    }

    void
    File_Header_Printer::swap  ( File_Header_Printer& rhs )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering File_Header_Printer::swap (id=%d)")
                           % m_state_ptr->get_ID() ) );

        m_state_ptr.swap ( rhs.m_state_ptr );

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting File_Header_Printer::swap (id=%d)")
                           % m_state_ptr->get_ID() ) );

    }
} /* namespace component */
} /* namespace libreverse */
