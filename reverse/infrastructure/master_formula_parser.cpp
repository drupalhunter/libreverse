/*  Master_Formula_Parser.cpp

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

#include "Master_Formula_Parser.h"
#include "errors/Parsing_Exception.h"
#include "Reverse.h"
#include "Formula_List.h"
#include <boost/format.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <fstream>
#include "data_containers/Memory_Map.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    const int Master_Formula_Parser::MATCH = 0;

    Master_Formula_Parser::Master_Formula_Parser()
        : m_map ( new infrastructure_types::Configurator::Formula_Map_t() ),
          m_input_type (0),
          m_output_type (0),
          m_input_formula_file (""),
          m_analysis_formula_file (""),
          m_output_formula_file ("")
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Master_Formula_Parser constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Configurator::Formula_Map_ptr_t
    Master_Formula_Parser::get_Formula_Map ( std::string filename )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Master_Formula_Parser::get_Formula_Map" );
#endif /* LIBREVERSE_DEBUG */


        m_map.reset ( new infrastructure_types::Configurator::Formula_Map_t() );
        
        std::cout << "Master_Formula_Parser::get_Formula_Map - reading "
                  << filename << std::endl;

        if ( ! boost::filesystem::exists ( filename ) )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("Exception throw in %s at line %d")
						  % __FILE__
						  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

		
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::MISSING_FILE );
            }

        std::ifstream input ( filename.c_str() );
        data_container::Memory_Map input_data ( input );

        // Create parser
        if ( ! this->createParser() )
            {

#ifdef LIBREVERSE_DEBUG
                // Error creating
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     "Formula_Parser::parse_Data - error creating parser" );

                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("Exception throw in %s at line %d")
						  % __FILE__
						  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                // Throw exception
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::UNKNOWN_PARSING_ERROR );
            }

        // Parse file

        if ( ! this->parse ( reinterpret_cast<const char*>(&(*input_data.begin())),
                             input_data.size() ) )
            {
                std::cerr << boost::format("(EE) %s at line %d in %s")
                    % getErrorString ( getErrorCode() )
                    % getCurrentLineNumber()
                    % filename
                          << std::endl;

                // Throw exception
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::INVALID_FORMAT );
            }
                           
        this->destroyParser();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Master_Formula_Parser::get_Formula_Map" );
#endif /* LIBREVERSE_DEBUG */

        return m_map;
    }

    void
    Master_Formula_Parser::startElement ( const std::string& element_name,
                                          const Attribute_Map_t& )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Master_Formula_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */

        m_element_list.push ( element_name );
    }

    void
    Master_Formula_Parser::charData ( const std::string& element_value )
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Master_Formula_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */


        std::string present_element = m_element_list.top();

        if ( present_element.compare ( m_tag.TAG_INPUT ) == 0 )
            {
                if ( element_value.compare ( "binary" ) == 0 )
                    {
                        m_input_type = api::Input_Types::BINARY;
                    }
                else
                    {


#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception ( errors::Parsing_Exception::UNKNOWN_TYPE );
                    }
            }
        else if ( present_element.compare ( m_tag.TAG_OUTPUT ) == 0 )
            {
                if ( element_value.compare ( "C++" ) == MATCH )
                    {
                        m_output_type = api::Output_Types::CPLUSPLUS;
                    }
                else if ( element_value.compare ( "C" ) == MATCH )
                    {
                        m_output_type = api::Output_Types::C;
                    }
                else if ( element_value.compare ( "Java" ) == MATCH )
                    {
                        m_output_type = api::Output_Types::JAVA;
                    }
                else if ( element_value.compare ( "UML" ) == MATCH )
                    {
                        m_output_type = api::Output_Types::UML;
                    }
                else
                    {


#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::UNKNOWN_TYPE);
                    }
            }
        else if ( present_element.compare ( m_tag.TAG_INPUT_FORMULA ) == 0 )
            {
                m_input_formula_file = element_value;
            }
        else if ( present_element.compare ( m_tag.TAG_ANALYSIS_FORMULA ) == 0 )
            {
                m_analysis_formula_file = element_value;
            }
        else if ( present_element.compare ( m_tag.TAG_OUTPUT_FORMULA ) == 0 )
            {
                m_output_formula_file = element_value;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Master_Formula_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Master_Formula_Parser::endElement ( const std::string& element_name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Master_Formula_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */


        if ( element_name.compare ( m_tag.TAG_FORMULA ) == 0 )
            {
                // Create formula object
                Formula_List flist;
                flist.input = m_input_formula_file;
                flist.analysis = m_analysis_formula_file;
                flist.output = m_output_formula_file;

                std::pair<boost::uint32_t, boost::uint32_t> index = std::make_pair( m_input_type, m_output_type );

                if ( ! ( m_map->insert ( std::make_pair ( index, flist ) ) ).second )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format( "The key(%d:%d) already exists in the master formula map." )
							  % index.first
							  % index.second ) );
                        
                        // throw exception: failed to insert
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                        
                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::INTERNAL_PARSING_ERROR);
                    }


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::INFO,
				     boost::str ( boost::format("Inserted %d:%d into the master formula map:")
						  % index.first
						  % index.second ) );
#endif /* LIBREVERSE_DEBUG */


                m_input_type = 0;
                m_output_type = 0;
                m_input_formula_file = "";
                m_analysis_formula_file = "";
                m_output_formula_file = "";
            }
        else
            {
                // Do nothing
            }

        m_element_list.pop ();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Master_Formula_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
