/*  Compiler_Classifier.cpp

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

#include "Compiler_Classifier.h"

#include "components/input/grnn/Classifier_Algorithm.h"
#include "components/input/grnn/Compiler_Classifier_Algorithm_Factory.h"
#include "meta/meta_object.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/File_Reader.h"
#include "data_containers/filename.h"
#include "data_containers/memory_map.h"
#include "infrastructure/data_source/data_object.h"
#include "infrastructure/Component_Data.h"
#include "infrastructure/Component_State.h"
#include "errors/Internal_Exception.h"

#include <boost/format.hpp>

using namespace libreverse::classifier;
using namespace libreverse::meta;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace component {

    const std::string Compiler_Classifier::m_name = "Compiler_Classifier";

    Compiler_Classifier::Compiler_Classifier ()
        : m_state_ptr ( new infrastructure::Component_State (0) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              boost::str ( boost::format ( "Inside Compiler_Classifier constructor (id=%d)")
                           % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Compiler_Classifier::Compiler_Classifier ( infrastructure_types::Component_State::ptr_t state_ptr )
        : m_state_ptr ( state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier constructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Compiler_Classifier::Compiler_Classifier ( Compiler_Classifier const& rhs )
        : infrastructure::Component ( rhs ),
          infrastructure::Component_Actor ( rhs ),
          boost::enable_shared_from_this<Compiler_Classifier> ( rhs ),
          m_state_ptr ( new infrastructure::Component_State ( *rhs.m_state_ptr ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier copy constructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    Compiler_Classifier::~Compiler_Classifier ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier constructor (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Compiler_Classifier::received_Input_Source_Data ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Compiler_Classifier::received_Input_Source_Data (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->received_Input_Source_Data ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Compiler_Classifier::received_Input_Source_Data (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Compiler_Classifier::add_Input_Source ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Compiler_Classifier::add_Input_Source (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->add_Input_Source ( id );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Compiler_Classifier::add_Input_Source (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


    }

    std::string
    Compiler_Classifier::get_Name (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier::get_Name (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_name;
    }

    void Compiler_Classifier::process ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Compiler_Classifier::process (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Data::ptr_t data_ptr = m_state_ptr->get_Data();

        if ( ! data_ptr->is_filename_Set() )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::COMPONENTS,
				     TraceLevel::ERROR,
				     "Unable to find the input file name." );

                Trace::write_Trace ( TraceArea::COMPONENTS,
				     TraceLevel::ERROR,
				     "Cannot determine the compiler used without it." );

                Trace::write_Trace ( TraceArea::COMPONENTS,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("Exception throw in %s at line %d")
						  % __FILE__
						  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                // At this point we have not found the filename somehow
                // the Precondition visitor did not work. So we will
                // will throw an exception
                throw ( errors::Internal_Exception ( errors::Internal_Exception::IO_ERROR ) );
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
	// Get classifier algorithm from classifier algorithm factory based on file type
	classifier_types::Classifier_Algorithm::ptr_t classifier_algorithm_ptr
	  = Compiler_Classifier_Algorithm_Factory::Instance().get_Classifier ( file_type );

	/*--------------------------------*/
	/*       Execute Algorithm        */
	/*--------------------------------*/

	// Get file type from Meta information
        data_types::filename::const_ptr_t file_ptr = data_ptr->get_Input_filename();

	// Call process ( file_ptr->str() )
	meta::meta_object::ptr_t meta_ptr = classifier_algorithm_ptr->execute ( file_ptr->to_String() );

	// Save result in Meta information for the output data source
        data_ptr->set_Output_Meta_Data ( meta_ptr );

        /**
         * add input filename to output information
         */
        data_ptr->set_Output_Data ( file_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Compiler_Classifier::process (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Compiler_Classifier::run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Compiler_Classifier::run (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->run ( this->shared_from_this(),
                           m_input_data );        


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Compiler_Classifier::run (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Data_Source_Base::ptr_t
    Compiler_Classifier::results (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier::results (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->results();
    }

    void
    Compiler_Classifier::set_State ( boost::uint32_t mode )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier::set_State (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr->switch_State ( mode );
    }

    boost::uint32_t
    Compiler_Classifier::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier::get_ID (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->get_ID();
    }
    
    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Compiler_Classifier::get_Source_List_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier::get_Source_List_Begin (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->get_Source_List_Begin ();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Compiler_Classifier::get_Source_List_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Inside Compiler_Classifier::get_Source_List_End (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return m_state_ptr->get_Source_List_End ();
    }

    Compiler_Classifier&
    Compiler_Classifier::operator= ( Compiler_Classifier const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Entering Compiler_Classifier::operator= (assignment) (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        m_state_ptr.reset ( new infrastructure::Component_State( *rhs.m_state_ptr ) );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::COMPONENTS,
			     TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Exiting Compiler_Classifier::operator= (assignment) (id=%d)")
					  % m_state_ptr->get_ID() ) );
#endif /* LIBREVERSE_DEBUG */


        return *this;
    }

} /* namespace component */
} /* namespace libreverse */
