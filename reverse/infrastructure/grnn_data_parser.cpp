/*  GRNN_Data_Parser.cpp

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

#include "GRNN_Data_Parser.h"

#include "infrastructure/Component.h"
#include "infrastructure/Component_Graph.h"
#include "infrastructure/Component_State.h"
#include "components/Component_Factory.h"
#include "errors/Parsing_Exception.h"
#include "data_containers/Memory_Map.h"
#include "components/input/grnn/GRNN_Data_Entry.h"
#include "components/input/grnn/GRNN_Data_Map.h"
#include "components/input/grnn/GRNN_Data_Types.h"

#include <iostream>
#include <boost/format.hpp>
#include <sstream>
#include <fstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    const int GRNN_Data_Parser::MATCH = 0;

    GRNN_Data_Parser::GRNN_Data_Parser ()
        : m_type ( "" ),
          m_sigma ( 0.0 ),
          m_file ( "" )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside GRNN_Data_Parser constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    classifier_types::GRNN_Data_Map::ptr_t
    GRNN_Data_Parser::get_Data_Map ( std::string filename )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering GRNN_Data_Parser::get_Data_Map" );
#endif /* LIBREVERSE_DEBUG */

        m_data_map.reset ( new classifier::GRNN_Data_Map() );

        // Parse file and generate graph

        std::ifstream input ( filename.c_str() );
        data_container::Memory_Map input_data ( input );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::INFO,
                             boost::str ( boost::format ( "Parsing %s" ) % filename ) );
#endif /* LIBREVERSE_DEBUG */

        // Create parser
        if ( ! this->createParser() )
            {

#ifdef LIBREVERSE_DEBUG
	      // Error creating
	      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				   TraceLevel::ERROR,
				   "GRNN_Data_Parser::parse_Data - error creating parser" );
#endif /* LIBREVERSE_DEBUG */


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
                             "Exiting GRNN_Data_Parser::get_Data_Map" );
#endif /* LIBREVERSE_DEBUG */

        return m_data_map;
    }

    void
    GRNN_Data_Parser::startElement ( const std::string& element_name,
				     const Attribute_Map_t& attributes )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering GRNN_Data_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */


        m_element_list.push ( element_name );

        if ( element_name.compare ( m_tag.TAG_ENTRY ) == 0 )
            {
                
                Attribute_Map_t::const_iterator cpos = attributes.find ( m_tag.ATTRIBUTE_TYPE );

                if ( cpos == attributes.end() )
                    {


#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     "GRNN_Data_Parser::handle_Elements - missing type atrribute in <entry> element." );

                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::INVALID_FORMAT);
                    }

		this->m_type = (*cpos).second;

		cpos = attributes.find ( m_tag.ATTRIBUTE_SIGMA );

                if ( cpos == attributes.end() )
                    {


#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     "GRNN_Data_Parser::handle_Elements - missing sigma atrribute in <entry> element." );

                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::ERROR,
					     boost::str ( boost::format("Exception throw in %s at line %d")
							  % __FILE__
							  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::Parsing_Exception
                            (errors::Parsing_Exception::INVALID_FORMAT);
                    }

		std::stringstream double_string;
		double_string << (*cpos).second;
		double_string >> m_sigma;


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "Stored sigma: %1%" ) % m_sigma ) );
#endif /* LIBREVERSE_DEBUG */

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting GRNN_Data_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */

    }

    void GRNN_Data_Parser::charData ( const std::string& element_value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering GRNN_Data_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */


        std::string present_element = m_element_list.top();

        if ( present_element.compare ( m_tag.TAG_ENTRY ) == 0 )
            {
                m_file = element_value;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting GRNN_Data_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    GRNN_Data_Parser::endElement ( const std::string& element_name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering GRNN_Data_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */


        if ( element_name.compare ( m_tag.TAG_ENTRY ) == 0 )
            {
	      // Add entry to GRNN_Data_Map
	      classifier_types::GRNN_Data_Entry::ptr_t entry_obj ( new classifier::GRNN_Data_Entry ( m_sigma, m_file ) );
	      m_sigma = 0.0;
	      m_file = "";

	      m_data_map->insert ( classifier::GRNN_Data_Types::get_Type ( m_type ), entry_obj );
            }

        m_element_list.pop();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting GRNN_Data_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
