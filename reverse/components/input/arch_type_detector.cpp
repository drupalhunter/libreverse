/*  Arch_Type_Detector.cpp

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

#include "Arch_Type_Detector.h"
#include "Arch_Type_Detector_Algorithm.h"
#include "Arch_Type_Detector_Algorithm_Factory.h"

#include "meta/Meta_Object.h"
#include "io/File_ID.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/File_Reader.h"
#include "errors/API_Exception.h"
#include "data_containers/Filename.h"
#include "infrastructure/data_source/Data_Object.h"
#include "infrastructure/Component_Data.h"
#include "infrastructure/Component_State.h"

#include <iostream>
#include <boost/format.hpp>


#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace component {

    const std::string Arch_Type_Detector::NAME = "Arch_Type_Detector";

    Arch_Type_Detector::Arch_Type_Detector ()
        : m_state_ptr ( new infrastructure::Component_State ( 0 ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Arch_Type_Detector::Arch_Type_Detector( infrastructure_types::Component_State::ptr_t input_ptr )
        : m_state_ptr ( input_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Arch_Type_Detector::Arch_Type_Detector ( Arch_Type_Detector const& rhs )
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<Arch_Type_Detector> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector copy constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Arch_Type_Detector::~Arch_Type_Detector ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector destructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }


    void
    Arch_Type_Detector::received_Input_Source_Data ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Arch_Type_Detector::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->received_Input_Source_Data ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::received_Input_Source_Data (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Arch_Type_Detector::add_Input_Source ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Arch_Type_Detector::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->add_Input_Source ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::add_Input_Source (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Arch_Type_Detector::get_Name (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector::get_Name (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return NAME;
    }

    void Arch_Type_Detector::process ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Arch_Type_Detector::process (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Data::ptr_t data_ptr = m_state_ptr->get_Data();

        if ( ! data_ptr->is_Filename_Set() )
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::COMPONENTS,
				   TraceLevel::ERROR,
				   "Unable to find the input file name." );

	      Trace::write_Trace ( TraceArea::COMPONENTS,
				   TraceLevel::ERROR,
				   "Cannot find the arch type without it." );
	      
	      Trace::write_Trace ( TraceArea::COMPONENTS,
				   TraceLevel::ERROR,
				   boost::str ( boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                // At this point we have not found the filename somehow
                // the Precondition visitor did not work. So we will
                // will throw an exception
                throw ( errors::API_Exception
                        ( errors::API_Exception::INTERNAL_LIBRARY_ERROR ) );
            }

	/*---------------------------------*/
	/*          Get File Type          */
	/*---------------------------------*/
        meta::Meta_Object::const_ptr_t input_meta_ptr = data_ptr->get_Input_Meta_Data();

	meta::Meta_Object::Data_Pair_t file_type_meta_value = input_meta_ptr->get_Value ( "file_type" );

        assert ( file_type_meta_value.second == meta::Meta_Object::STRING );

        std::string file_type = file_type_meta_value.first;

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/
	Arch_Type_Detector_Algorithm::ptr_t algorithm_ptr =
	  Arch_Type_Detector_Algorithm_Factory::Instance().get_Algorithm ( file_type );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/
        data_types::Filename::const_ptr_t file_ptr = data_ptr->get_Input_Filename();

	io_types::File_ID::const_ptr_t file_id_ptr ( new io::File_ID ( file_ptr->to_String() ) );

        std::string arch_type = algorithm_ptr->run ( file_id_ptr );

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Arch Type Found: %1%" ) % arch_type  ) );
#endif /* LIBREVERSE_DEBUG */


        /**
         * add input filename to output information
         */
        data_ptr->set_Output_Data ( file_ptr );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/
        /*
         * add file type to output meta information
         */
        meta::Meta_Object::ptr_t meta_ptr ( new meta::Meta_Object() );

        meta_ptr->add ( "arch_type",
                        arch_type,
                        meta::Meta_Object::STRING );

        data_ptr->set_Output_Meta_Data ( meta_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::process (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Arch_Type_Detector::run ( infrastructure::Graph_Base::Data_Map_t* m_input_data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Arch_Type_Detector::run (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->run ( this->shared_from_this(),
                           m_input_data );        


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::run (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Data_Source_Base::ptr_t
    Arch_Type_Detector::results (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector::results (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->results();

    }

    void
    Arch_Type_Detector::set_State ( boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Arch_Type_Detector::set_State (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->switch_State ( mode );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::set_State (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Arch_Type_Detector::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector::set_State (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Arch_Type_Detector::get_Source_List_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector::get_Source_List_Begin (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->get_Source_List_Begin ();

    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Arch_Type_Detector::get_Source_List_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Arch_Type_Detector::get_Source_List_End (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return m_state_ptr->get_Source_List_End ();
    }

    Arch_Type_Detector&
    Arch_Type_Detector::operator= ( Arch_Type_Detector const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Arch_Type_Detector::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        Arch_Type_Detector temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::operator= (assignment) (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Arch_Type_Detector::swap ( Arch_Type_Detector& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Entering Arch_Type_Detector::swap (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr.swap ( rhs.m_state_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Exiting Arch_Type_Detector::swap (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Component::ptr_t
    Arch_Type_Detector::operator() ( infrastructure_types::Component_State::ptr_t data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              "Inside Arch_Type_Detector::operator()" );
#endif /* LIBREVERSE_DEBUG */

        return infrastructure_types::Component::ptr_t ( new Arch_Type_Detector ( data_ptr ) );
    }

} /* namespace component */
} /* namespace libreverse */
