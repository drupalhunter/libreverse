/*  Entry_Point_Detector.cpp

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

#include "Entry_Point_Detector.h"
#include "Entry_Point_Detector_Algorithm.h"
#include "Entry_Point_Detector_Algorithm_Factory.h"

#include "meta/meta_object.h"
#include "infrastructure/data_source/Data_Source_Factory.h"
#include "io/File_ID.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/File_Reader.h"
#include "data_containers/filename.h"
#include "infrastructure/data_source/data_object.h"
#include "infrastructure/Component_Data.h"
#include "infrastructure/Component_State.h"
#include "errors/API_Exception.h"

#include <boost/format.hpp>


#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace reverse { namespace component {

    const std::string Entry_Point_Detector::m_name = "Entry_Point_Detector";

    Entry_Point_Detector::Entry_Point_Detector ()
        : m_state_ptr ( new infrastructure::Component_State (0) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector constructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Entry_Point_Detector::Entry_Point_Detector ( infrastructure_types::Component_State::ptr_t state_ptr )
        : m_state_ptr ( state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector constructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Entry_Point_Detector::Entry_Point_Detector ( Entry_Point_Detector const& rhs)
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<Entry_Point_Detector> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector copy constructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Entry_Point_Detector::~Entry_Point_Detector ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector destructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Entry_Point_Detector::received_Input_Source_Data ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Entry_Point_Detector::received_Input_Source_Data (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->received_Input_Source_Data ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Entry_Point_Detector::received_Input_Source_Data (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Entry_Point_Detector::add_Input_Source ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector::add_Input_Source (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->add_Input_Source ( id );
    }

    std::string
    Entry_Point_Detector::get_Name (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector::get_Name (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_name;
    }

    void Entry_Point_Detector::process ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Entry_Point_Detector::process (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Data::ptr_t data_ptr =
            m_state_ptr->get_Data();

        if ( ! data_ptr->is_filename_Set() )
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
                throw ( errors::API_Exception ( errors::API_Exception::INTERNAL_LIBRARY_ERROR ) );
            }

	/*---------------------------------*/
	/*          Get File Type          */
	/*---------------------------------*/
        meta::meta_object::const_ptr_t input_meta_ptr = data_ptr->get_Input_Meta_Data();

	meta::meta_object::Data_Pair_t file_type_meta_value = input_meta_ptr->get_Value ( "file_type" );

        assert ( file_type_meta_value.second == meta::meta_object::STRING );

        std::string file_type = file_type_meta_value.first;

	/*---------------------------------*/
	/*          Get Algorithm          */
	/*---------------------------------*/
	Entry_Point_Detector_Algorithm::ptr_t algorithm_ptr =
	  Entry_Point_Detector_Algorithm_Factory::Instance().get_Algorithm ( file_type );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/
        data_types::filename::const_ptr_t file_ptr = data_ptr->get_Input_filename();

	io_types::File_ID::const_ptr_t file_id_ptr ( new io::File_ID ( file_ptr->to_String() ) );

	meta::meta_object::ptr_t entry_point_meta_ptr = algorithm_ptr->run ( file_id_ptr );

        /**
         * add input filename to output information
         */
        data_ptr->set_Output_Data ( file_ptr );

        /**
         * add file type to meta information
         */
        data_ptr->set_Output_Meta_Data ( entry_point_meta_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Entry_Point_Detector::process (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Entry_Point_Detector::run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Entry_Point_Detector::run (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->run ( this->shared_from_this(),
                           m_input_data );        


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Entry_Point_Detector::run (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


    }

    infrastructure_types::Data_Source_Base::ptr_t
    Entry_Point_Detector::results (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector::results (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->results();
    }

    void
    Entry_Point_Detector::set_State ( boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector::set_State (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->switch_State ( mode );
    }

    boost::uint32_t
    Entry_Point_Detector::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector::get_ID (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Entry_Point_Detector::get_Source_List_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   boost::str ( boost::format ( "Inside Entry_Point_Detector::get_Source_List_Begin (id=%d)")
					% m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->get_Source_List_Begin ();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Entry_Point_Detector::get_Source_List_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Entry_Point_Detector::get_Source_List_End (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->get_Source_List_End ();
    }

    Entry_Point_Detector&
    Entry_Point_Detector::operator= ( Entry_Point_Detector const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Entry_Point_Detector::operator= (assignment) (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        Entry_Point_Detector temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Entry_Point_Detector::operator= (assignment) (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return *this;
    }

    void
    Entry_Point_Detector::swap ( Entry_Point_Detector& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Entry_Point_Detector::swap (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr.swap ( rhs.m_state_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Entry_Point_Detector::swap (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


    }
} /* namespace component */
} /* namespace reverse */
