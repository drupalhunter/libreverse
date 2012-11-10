
/*  Component_Data.cpp

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

#include "Component_Data.h"
#include "Component_Actor.h"
#include "meta/Meta_Object.h"
#include "infrastructure/data_source/Data_Source_Factory.h"
#include <boost/format.hpp>
#include "errors/API_Exception.h"
#include "data_source/Data_Object.h"
#include "data_source/Data_Source_Base.h"
#include "data_containers/Filename.h"
#include "data_containers/Control_Flow_Graph_Sequence.h"
#include "data_containers/Memory_Map.h"

#include "Assert.h"

using namespace libreverse::assert;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Component_Data::Component_Data ( boost::uint32_t id )
        : m_id ( id ),
          m_data_obj_ptr ( new Data_Object() ),
          m_meta_ptr ( new meta::Meta_Object() ),
          m_filename_ptr (),
          m_graph_ptr (),
          m_map_ptr ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_Data::Component_Data ( Component_Data const& rhs )
        : m_id ( rhs.m_id ),
          m_data_obj_ptr ( new Data_Object ( *rhs.m_data_obj_ptr ) ),
          m_meta_ptr ( new meta::Meta_Object ( *rhs.m_meta_ptr ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data copy constructor" );
#endif /* LIBREVERSE_DEBUG */

        if ( rhs.m_filename_ptr.get() != 0 )
            {
                m_filename_ptr.reset ( new data_container::Filename ( *rhs.m_filename_ptr ) );
            }

        if ( rhs.m_graph_ptr.get() != 0 )
            {
                m_graph_ptr.reset ( new data_container::Control_Flow_Graph_Sequence ( *rhs.m_graph_ptr ) );
            }

        if ( rhs.m_map_ptr.get() != 0 )
            {
                m_map_ptr.reset ( new data_container::Memory_Map ( *rhs.m_map_ptr ) );
            }

        std::copy ( rhs.m_source_list.begin(),
                    rhs.m_source_list.end(),
                    std::inserter ( m_source_list, m_source_list.begin() ) );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Component_Data::~Component_Data ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data destructor" );
#endif /* LIBREVERSE_DEBUG */


        m_source_list.clear();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Component_Data::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return m_id;
    }

    void
    Component_Data::add_Input_Source ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::add_Input_Source" );
#endif /* LIBREVERSE_DEBUG */


        if ( ! m_source_list.insert ( std::make_pair ( id, false ) ).second )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::WARN,
                      boost::str(boost::format("Attempted to add a duplicate component id (%d). Ignoring component.") % id ));
#endif /* LIBREVERSE_DEBUG */

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::add_Input_Source" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Data::received_Input_Source_Data ( boost::uint32_t id )
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::received_Input_Source_Data" );

        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::INFO,
			     boost::str ( boost::format
					  ("Component(%d)::init - dump m_source_list (size = %d)")
					  % m_id
					  % m_source_list.size() ) );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Data::Input_Token_t::iterator pos =
            m_source_list.find ( id );

        if ( pos != m_source_list.end() )
            {
                pos->second = true;


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::INFO,
				     boost::str ( boost::format
						  ("(%d) - initialized with data from component #%d")
						  % m_id
						  % id ) );
#endif /* LIBREVERSE_DEBUG */

            }
        else
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format ("Invalid index given was %d")
                                                  % id ) );

                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format("Exception throw in %s at line %d")
                                                  % __FILE__
                                                  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::Component_Exception
                    ( errors::Component_Exception::INVALID_INDEX );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::received_Input_Source_Data" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Data::gather_Inputs ( infrastructure_types::Component_Graph::Data_Map_t* data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::gather_Inputs" );

        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             boost::str ( boost::format ( "Component_Data::gather_Inputs - size of source list = %d" )
                                          % m_source_list.size() ) );
#endif /* LIBREVERSE_DEBUG */


        for ( infrastructure_types::Component_Data::Input_Token_t::iterator pos = m_source_list.begin();
              pos != m_source_list.end();
              ++pos )
            {

                infrastructure_types::Component_Graph::Data_Map_t::const_iterator cpos = data_ptr->find ( pos->first );

                if ( cpos == data_ptr->end() )
                    {

#ifdef LIBREVERSE_DEBUG
		      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					   TraceLevel::ERROR,
					   boost::str ( boost::format("(%d)::gather_Inputs (EE) - input data %d missing from node #%d")
							% m_id
							% pos->first ) );

		      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					   TraceLevel::ERROR,
					   "  Dumping data_ref\n  Src, (Data ptr, # of children)\n  ------------------" );
                        
		      for ( infrastructure_types::Component_Graph::Data_Map_t::const_iterator content_pos = data_ptr->begin();
			    content_pos != data_ptr->end();
			    ++content_pos )
			{
			  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					       TraceLevel::ERROR,
					       boost::str ( boost::format("%d, (%p, %d )")
							    % content_pos->first
							    % content_pos->second.first
							    % content_pos->second.second ) );
			}

                        Trace::write_Trace
                            ( TraceArea::INFRASTRUCTURE,
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

#ifdef LIBREVERSE_DEBUG
                else
                    {


                        Trace::write_Trace
                            ( TraceArea::INFRASTRUCTURE,
                              TraceLevel::INFO,
                              boost::str ( boost::format("Found data from node %d")
                                           % pos->first ) );
                    }
#endif /* LIBREVERSE_DEBUG */


                infrastructure_types::Component_Graph::Result_Data_t data_pos = cpos->second;

                infrastructure_types::Data_Source_Base::const_ptr_t input_data_ptr = data_pos.first;

                Assert::null_check ( input_data_ptr.get(), "input_data_ptr.get())" );
                

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::DATA,
                                     input_data_ptr->to_String() );
#endif /* LIBREVERSE_DEBUG */

                
                // Get input data from data source
                infrastructure_types::Data_Object::const_ptr_t d_obj_ptr = input_data_ptr->get();

                m_filename_ptr = d_obj_ptr->get_Filename();
                m_graph_ptr = d_obj_ptr->get_Control_Flow_Graph_Sequence();
                m_map_ptr = d_obj_ptr->get_Memory_Map();

                // Copy meta information
                meta::Meta_Object::const_ptr_t m_obj_ptr = d_obj_ptr->getMeta();

                m_meta_ptr->append ( m_obj_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::gather_Inputs" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Component_Data::find ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::find" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        infrastructure_types::Component_Data::Input_Token_t::iterator pos = m_source_list.find ( id );
        if ( pos != m_source_list.end() )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::find" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    infrastructure_types::Data_Source_Base::ptr_t
    Component_Data::get_Data_Source (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::get_Data_Source" );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Data_Source_Factory::ptr_t fact_ptr = infrastructure::Data_Source_Factory::Instance();

        infrastructure_types::Data_Source_Base::ptr_t output_data_source = fact_ptr->get_Data_Source ( this->get_ID() );
        
        output_data_source->put ( m_data_obj_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DATA,
                             output_data_source->to_String() );

        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::get_Data_Source" );
#endif /* LIBREVERSE_DEBUG */


        return output_data_source;
    }

    bool
    Component_Data::is_Filename_Set (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::is_Filename_Set" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( m_filename_ptr.get() != 0 )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::is_Filename_Set" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Component_Data::is_Control_Flow_Graph_Sequence_Set (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::is_Control_Flow_Graph_Sequence_Set" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( m_graph_ptr.get() != 0 )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::is_Control_Flow_Graph_Sequence_Set" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Component_Data::is_Memory_Map_Set (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::is_Memory_Map_Set" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( m_map_ptr.get() != 0 )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::is_Memory_Map_Set" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    data_types::Filename::const_ptr_t
    Component_Data::get_Input_Filename(void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_Input_Filename" );
#endif /* LIBREVERSE_DEBUG */

        return m_filename_ptr;
    }

    data_types::Control_Flow_Graph_Sequence::const_ptr_t
    Component_Data::get_Input_Control_Flow_Graph_Sequence(void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_Input_Control_Flow_Graph_Sequence" );
#endif /* LIBREVERSE_DEBUG */

        return m_graph_ptr;
    }

    data_types::Memory_Map::const_ptr_t
    Component_Data::get_Input_Memory_Map(void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_Input_Memory_Map" );
#endif /* LIBREVERSE_DEBUG */

        return m_map_ptr;
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Component_Data::get_Source_List_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_Source_List_Begin (const)" );
#endif /* LIBREVERSE_DEBUG */

        return m_source_list.begin();
    }

    infrastructure_types::Component_Data::Input_Token_t::const_iterator
    Component_Data::get_Source_List_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_Source_List_End (const)" );
#endif /* LIBREVERSE_DEBUG */

        return m_source_list.end();
    }

    void
    Component_Data::set_Output_Data ( data_types::Filename::const_ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::set_Output_Data (Filename)" );
#endif /* LIBREVERSE_DEBUG */

        m_data_obj_ptr->set_Data ( file_ptr );        


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::set_Output_Data (Filename)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Data::set_Output_Data ( data_types::Control_Flow_Graph_Sequence::const_ptr_t graph_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::set_Output_Data (Control_Flow_Graph_Sequence)" );
#endif /* LIBREVERSE_DEBUG */


        m_data_obj_ptr->set_Data ( graph_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::set_Output_Data (Control_Flow_Graph_Sequence)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Component_Data::set_Output_Data ( data_types::Memory_Map::const_ptr_t map_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::set_Output_Data (Memory_Map)" );
#endif /* LIBREVERSE_DEBUG */


        m_data_obj_ptr->set_Data ( map_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::set_Output_Data (Memory_Map)" );
#endif /* LIBREVERSE_DEBUG */
    }
    
    void
    Component_Data::set_Output_Meta_Data ( meta::Meta_Object::const_ptr_t meta_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::set_Output_Data" );
#endif /* LIBREVERSE_DEBUG */


        m_meta_ptr->append ( meta_ptr );
        m_data_obj_ptr->put_Meta ( m_meta_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::set_Output_Data" );
#endif /* LIBREVERSE_DEBUG */
    }

    meta::Meta_Object::const_ptr_t
    Component_Data::get_Input_Meta_Data (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Component_Data::get_Input_Meta_Data" );
#endif /* LIBREVERSE_DEBUG */

        return m_meta_ptr;
    }

    Component_Data&
    Component_Data::operator= ( Component_Data const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Component_Data temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Component_Data::swap ( Component_Data& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_id, rhs.m_id );
        std::swap ( m_source_list, rhs.m_source_list );

        m_data_obj_ptr.swap ( rhs.m_data_obj_ptr );
        m_meta_ptr.swap ( rhs.m_meta_ptr );
        m_filename_ptr.swap ( rhs.m_filename_ptr );
        m_graph_ptr.swap ( rhs.m_graph_ptr );
        m_map_ptr.swap ( rhs.m_map_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Component_Data::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Component_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

        output << boost::format ( "ID: %d" ) % m_id << std::endl
               << "  Input sources: " << std::endl;

        for ( infrastructure_types::Component_Data::Input_Token_t::const_iterator cpos = m_source_list.begin();
              cpos != m_source_list.end();
              ++cpos )
            {
                std::string found = "true";

                if ( ! cpos->second )
                    {
                        found = "false";
                    }

                output << boost::format("    id: %d => %s")
                    % cpos->first
                    % found << std::endl;
            }

        if ( m_data_obj_ptr )
            {
                output << m_data_obj_ptr->to_String() << std::endl;
            }

        if ( m_meta_ptr )
            {
                output << m_meta_ptr->to_String() << std::endl;
            }

        if ( m_filename_ptr )
            {
                output << boost::format("  Filename: %s") % m_filename_ptr->to_String() << std::endl;
            }

        if ( m_graph_ptr )
            {
                output << m_graph_ptr->to_String() << std::endl;
            }

        if ( m_map_ptr )
            {
                output << m_map_ptr->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Component_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output.str();
    }
} /* namespace infrastructure */
} /* namespace libreverse */

