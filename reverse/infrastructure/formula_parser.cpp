/*  Formula_Parser.cpp

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

#include "Formula_Parser.h"
#include <iostream>
#include "infrastructure/Component.h"
#include "infrastructure/Component_Graph.h"
#include "infrastructure/Component_State.h"
#include "components/Component_Factory.h"
#include "errors/Parsing_Exception.h"
#include <boost/format.hpp>
#include <sstream>
#include <fstream>
#include "data_containers/memory_map.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    const int Formula_Parser::MATCH = 0;

    Formula_Parser::Formula_Parser ()
        : m_id ( 0 ),
          m_name ( "" ),
          m_file ( "" )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Formula_Parser constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Component::ptr_t
    Formula_Parser::get_Component ( boost::uint32_t id,
                                    std::string name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::get_Component" );
#endif /* LIBREVERSE_DEBUG */


        boost::shared_ptr<Component> obj_ptr;

        // Add Component_State object
        infrastructure_types::Component_State::ptr_t state_ptr ( new Component_State ( id ) );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             boost::str ( boost::format ( "  Creating component: %s" ) % name ) );
#endif /* LIBREVERSE_DEBUG */


        if (name.compare("file_type") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_File_Type_Detector ( state_ptr );
            }
        else if (name.compare("arch_type") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_Arch_Type_Detector ( state_ptr );
            }
        else if (name.compare("meta_writer") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_Meta_Writer ( state_ptr );
            }
        else if (name.compare("unpacker") == MATCH  )
            {
                obj_ptr = Component_Factory::Instance().get_Unpacker ( state_ptr );
            }
        else if (name.compare("code_section") == MATCH  )
            {
                obj_ptr = Component_Factory::Instance().get_Code_Section ( state_ptr );
            }
        else if (name.compare("data_section") == MATCH  )
            {
                obj_ptr = Component_Factory::Instance().get_Data_Section ( state_ptr );
            }
        else if (name.compare("entry_point") == MATCH  )
            {
                obj_ptr = Component_Factory::Instance().get_Entry_Point ( state_ptr );
            }
        else if (name.compare("null") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_Null_Component ( state_ptr );
            }
        else if (name.compare("memory_map_producer") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_memory_map_Producer ( state_ptr );
            }
        else if (name.compare("file_header_printer") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_File_Header_Printer ( state_ptr );
            }
        else if (name.compare("tevis_zero_filled_checker") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_Tevis_Zero_Filled_Checker ( state_ptr );
            }
        else if (name.compare("tevis_unknown_region_checker") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_Tevis_Unknown_Region_Checker ( state_ptr );
            }
        else if (name.compare("compiler_classifier") == MATCH )
            {
                obj_ptr = Component_Factory::Instance().get_Compiler_Classifier ( state_ptr );
            }

        if ( ! obj_ptr )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format ( "Unknown component, %s, requested in formula.\nDouble check formula file." )
						  % name ) );

                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("Exception throw in %s at line %d")
						  % __FILE__
						  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::Parsing_Exception
                    (errors::Parsing_Exception::UNKNOWN_COMPONENT);
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::get_Component" );
#endif /* LIBREVERSE_DEBUG */

        return obj_ptr;
    }

    void
    Formula_Parser::construct_Component ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::construct_Component" );
#endif /* LIBREVERSE_DEBUG */

        boost::shared_ptr<Component> obj_ptr = this->get_Component ( m_id, m_name);

        for ( std::vector<int>::iterator pos = m_predecessor_list.begin();
              pos != m_predecessor_list.end();
              ++pos )
            {
                obj_ptr->add_Input_Source (*pos);
            }

        m_graph->add_Component ( obj_ptr );
        m_predecessor_list.clear();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::construct_Component" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::shared_ptr<Component_Graph>
    Formula_Parser::get_Graph ( std::string filename,
                                std::string directory )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::get_Graph" );
#endif /* LIBREVERSE_DEBUG */

        m_graph.reset ( new Component_Graph() );

        // Parse file and generate graph

        std::stringstream full_path;
        full_path << directory << "/" << filename;
        m_file = full_path.str();

        std::ifstream input ( m_file.c_str() );
        data_container::memory_map input_data ( input );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::INFO,
                             boost::str ( boost::format ( "Parsing %s" ) % m_file ) );
#endif /* LIBREVERSE_DEBUG */


        // Create parser
        if ( ! this->createParser() )
            {
                // Error creating
                std::cerr << "(EE) Formula_Parser::parse_Data - error creating parser"
                          << std::endl;

                // Throw exception
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::UNKNOWN_PARSING_ERROR );
            }

        // Parse file

        if ( ! this->parse ( reinterpret_cast<const char*>(&(*input_data.begin())),
                             input_data.size() ) )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("%s at line %d in %s")
						  % getErrorString ( getErrorCode() )
						  % getCurrentLineNumber()
						  % m_file ) );

                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("Exception throw in %s at line %d")
						  % __FILE__
						  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                // Throw exception
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::INVALID_FORMAT );
            }
                           
        this->destroyParser();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::get_Graph" );
#endif /* LIBREVERSE_DEBUG */


        // return graph
        return m_graph;
    }

    void
    Formula_Parser::startElement ( const std::string& element_name,
                                   const Attribute_Map_t& attributes )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */


        m_element_list.push ( element_name );

        if ( element_name.compare ( m_tag.TAG_NODE_REF ) == 0 )
            {
                
                Attribute_Map_t::const_iterator cpos = attributes.find ( m_tag.ATTRIBUTE_IDREF );

                if ( cpos == attributes.end() )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     "Formula_Parser::handle_Elements - missing idref atrribute in <node_ref> element." );

                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::INVALID_FORMAT);
                    }

                int ref_num = 0;
                std::stringstream int_string;
                int_string << (*cpos).second;
                int_string >> ref_num;

                m_predecessor_list.push_back ( ref_num );
            }
        else if ( element_name.compare ( m_tag.TAG_NAME ) == 0 )
            {
                Attribute_Map_t::const_iterator cpos = attributes.find ( m_tag.ATTRIBUTE_ID );

                if ( cpos == attributes.end() )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     "Formula_Parser::handle_Elements - missing id atrribute in <node> element");

                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::INVALID_FORMAT);
                    }

                m_id = 0;
                std::stringstream int_string;
                int_string << (*cpos).second;
                int_string >> m_id;

                // Check id has a value greater than 0
                if ( ! ( m_id > 0 ) )
                    {

#ifdef LIBREVERSE_DEBUG
		      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					   TraceLevel::ERROR,
					   "Formula_Parser::handle_Elements - Valid id atrribute for <name> element must be greater than zero." );

		      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					   TraceLevel::ERROR,
					   boost::str ( boost::format ( "Id attribute should start at 1 for the first node. Node id found was %d") % m_id ) );

		      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					   TraceLevel::ERROR,
					   boost::str ( boost::format("Exception throw in %s at line %d")
							% __FILE__
							% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::INVALID_FORMAT);
                    }
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */


    }

    void Formula_Parser::charData ( const std::string& element_value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */


        std::string present_element = m_element_list.top();

        if ( present_element.compare ( m_tag.TAG_NAME ) == 0 )
            {
                m_name = element_value;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Formula_Parser::endElement ( const std::string& element_name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */


        if ( element_name.compare ( m_tag.TAG_NODE ) == 0 )
            {
                this->construct_Component ();
            }

        m_element_list.pop();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Formula_Parser::print_Component_List (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Formula_Parser::print_Component_List" );
#endif /* LIBREVERSE_DEBUG */


        std::cout << "file_type:    Determine the file type of the input file" << std::endl
                  << "arch_type:    Determine the target CPU of the input file" << std::endl
                  << "meta_writer:  Output all the meta information found" << std::endl
                  << "unpacker:     Uncompress a compressed input file" << std::endl
                  << "code_section: Produce the address and size of code section" << std::endl
                  << "data_section: Produce the address and size of data section" << std::endl
                  << "entry_point:  Produce the address of the entry point" << std::endl
                  << "null:         Does nothing (useful for testing formulas)" << std::endl
                  << "memory_map_producer: Read the input file into a Memory Map" << std::endl
                  << "file_header_printer: Print out the file header information to the console"
                  << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Formula_Parser::print_Component_List" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
