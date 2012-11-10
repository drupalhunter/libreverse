/*  Configuration_Parser.cpp

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

#include "Configuration_Parser.h"
#include "infrastructure/data_source/Database_Data_Source_Config.h"
#include "infrastructure/data_source/File_Data_Source_Config.h"
#include "infrastructure/data_source/Memory_Data_Source_Config.h"
#include "infrastructure/Configuration_Data.h"
#include "include/config.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <fstream>
#include "data_containers/Memory_Map.h"
#include "errors/Parsing_Exception.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Configuration_Parser::Configuration_Parser ( std::string file )
        : m_file (""),
	  m_host (""),
	  m_user (""),
	  m_password (""),
          m_data_ptr (new Configuration_Data())
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Parser Constructor" );
#endif /* LIBREVERSE_DEBUG */


        if ( ! file.empty() )
            {
                m_file = file;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Parser Constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Configuration_Parser::~Configuration_Parser ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Parser destructor" );
#endif /* LIBREVERSE_DEBUG */


        if ( ! m_element_list.empty() )
            {
                

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				   TraceLevel::WARN,
				   boost::str ( boost::format("(WW) Found %d items still on the stack.")
						% m_element_list.size() ) );
#endif /* LIBREVERSE_DEBUG */

	      
                while ( ! m_element_list.empty() )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
					     TraceLevel::WARN,
					     boost::str ( boost::format("  %s")
							  % m_element_list.top() ) ) ;
#endif /* LIBREVERSE_DEBUG */

                        
                        m_element_list.pop();
                    }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Parser destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    // Parser
    infrastructure_types::Configuration_Data::ptr_t
    Configuration_Parser::parse_Data (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Parser::parse_Data" );
#endif /* LIBREVERSE_DEBUG */


        if ( ! boost::filesystem::exists ( m_file ) )
            {


#ifdef LIBREVERSE_DEBUG
                // Error creating
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str(boost::format
						("Configuration_Parser::parse_Data - cannot find %s")
						% m_file) );
#endif /* LIBREVERSE_DEBUG */

                // Throw exception
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::MISSING_FILE );
            }

        std::ifstream input ( m_file.c_str() );

        data_container::Memory_Map input_data ( input );

        // Create parser
        if ( ! this->createParser() )
            {

#ifdef LIBREVERSE_DEBUG
                // Error creating
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     "Configuration_Parser::parse_Data - error creating parser");
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
				     boost::str(boost::format
						("%s at line %d in %s")
						% getErrorString ( getErrorCode() )
						% getCurrentLineNumber()
						% m_file ) );
#endif /* LIBREVERSE_DEBUG */


                // Throw exception
                throw errors::Parsing_Exception
                    ( errors::Parsing_Exception::INVALID_FORMAT );
            }
                           
        this->destroyParser();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Parser::parse_Data" );
#endif /* LIBREVERSE_DEBUG */

        return m_data_ptr;
    }

    void
    Configuration_Parser::startElement ( const std::string& element_name,
                                         const Attribute_Map_t& )//attributes )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Configuration_Parser::startElement" );
#endif /* LIBREVERSE_DEBUG */

        m_element_list.push ( element_name );
    }

    void Configuration_Parser::charData ( const std::string& element_value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */

        std::string present_element = m_element_list.top();

        if ( present_element.compare ( m_tag.TAG_FORMULA_DIRECTORY ) == 0 )
            {
                m_data_ptr->set_Formula_Directory ( element_value );
            }
        else if ( present_element.compare ( m_tag.TAG_FILE_PREFIX ) == 0 )
            {
                infrastructure_types::File_Data_Source_Config::ptr_t file_ptr ( new File_Data_Source_Config ( element_value ) );

                m_data_ptr->set_Transfer_Config ( file_ptr );
            }
        else if ( present_element.compare ( m_tag.TAG_MEMORY ) == 0 )
            {
                infrastructure_types::Memory_Data_Source_Config::ptr_t mem_ptr ( new Memory_Data_Source_Config () );

                m_data_ptr->set_Transfer_Config ( mem_ptr );
            }
        else if ( present_element.compare ( m_tag.TAG_HOST ) == 0 )
            {
                this->m_host = element_value;
            }
        else if ( present_element.compare ( m_tag.TAG_USER ) == 0 )
            {
                this->m_user = element_value;
            }
        else if ( present_element.compare ( m_tag.TAG_PASSWORD ) == 0 )
            {
                this->m_password = element_value;
            }
        else if ( present_element.compare ( m_tag.TAG_GRNN_DATA_FILE ) == 0 )
            {
                std::string grnn_file = element_value;

                m_data_ptr->set_GRNN_Data_File ( grnn_file );
            }
        else
            {
                // Do nothing
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Parser::charData" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Configuration_Parser::endElement ( const std::string& element_name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */


        if ( element_name.compare ( m_tag.TAG_DATABASE ) == 0 )
            {
                infrastructure_types::Database_Data_Source_Config::ptr_t db_ptr ( new Database_Data_Source_Config ( this->m_host,
														    this->m_user,
														    this->m_password ) );
                
                m_data_ptr->set_Transfer_Config ( db_ptr );
            }

        m_element_list.pop();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Parser::endElement" );
#endif /* LIBREVERSE_DEBUG */

    }

    /*
    void
    Configuration_Parser::parse_DLL_Directory ( void )
        throw ( errors::Configuration_Exception )
    {
        boost::filesystem::path dir_path ( m_data_ptr->get_DLL_Directory() );

        if ( ! boost::filesystem::exists ( dir_path ) )
            {
                std::cerr << std::endl << "Could not find: "
                          << dir_path.native_file_string() << std::endl;

                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::Configuration_Exception
                    ( errors::Configuration_Exception::DLL_PATH_ERROR );
            }

        if ( ! boost::filesystem::is_directory ( dir_path ) )
            {
                std::cerr << std::endl << "Given dll directory name is not a file system directory: "
                          << dir_path.native_file_string() << std::endl;

                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::Configuration_Exception
                    ( errors::Configuration_Exception::DLL_PATH_ERROR );
            }

        boost::filesystem::directory_iterator end_itr;
        for ( boost::filesystem::directory_iterator dir_itr ( dir_path );
              dir_itr != end_itr;
              ++dir_itr )
            {
                if ( ! boost::filesystem::is_directory ( *dir_itr ) )
                    {
                        // See if the file ends with '.dll'
                        std::string name = (*dir_itr).string();
                        if ( this->endsWith ( name, ".dll" ) )
                            {
//                                 m_data_ptr->add_DLL_Path ( (*dir_itr).leaf(),
//                                                        (*dir_itr) );
                            }
                    }
            }
    }

    bool
    Configuration_Parser::endsWith( std::string& line, std::string target ) const
    {
        bool result = true;

        unsigned int i = line.length();
        unsigned int j = target.length();

        if ( i >= j )
            {
                while ( j > 0 )
                    {
                        if ( line[i-1] != target[j-1] )
                            {
                                result = false;
                j = 0;
                            }
                        else
                            {
                                --i;
                                --j;
                            }
                    }
            }
        else // i < j is always false since the input line is less
             // than the target. The line can never end with the
             // target characters.
            {
                result = false;
            }

        return result;
    }
*/

    std::string
    Configuration_Parser::get_Configuration_File (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Configuration_Parser::get_Configuration_File" );
#endif /* LIBREVERSE_DEBUG */

        return m_file;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
