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

#include <reverse/trace.hpp>
#include <reverse/data_containers/memory_map.hpp>
#include <reverse/errors/parsing_exception.hpp>
#include <reverse/infrastructure/configuration_parser.hpp>
#include <reverse/infrastructure/data_source/database_data_source_config.hpp>
#include <reverse/infrastructure/data_source/file_data_source_config.hpp>
#include <reverse/infrastructure/data_source/memory_data_source_config.hpp>
#include <reverse/infrastructure/configuration_data.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>

#include <iostream>
#include <fstream>

namespace reverse {
  namespace infrastructure {

    configuration_parser::configuration_parser ( std::string file )
        : m_file (""),
	  m_host (""),
	  m_user (""),
	  m_password (""),
          m_data_ptr (new configuration_data()),
	  expatpp ()
    {
#warning Todo: Implement JSON Spirit
      trace::infrastructure_detail ( "Entering Configuration_Parser Constructor" );

      // if ( ! file.empty() )
      // 	{
      // 	  m_file = file;
      // 	}

      trace::infrastructure_detail ( "Exiting Configuration_Parser Constructor" );
    }

    configuration_parser::~configuration_parser ()
    {
        trace::infrastructure_detail ( "Entering Configuration_Parser destructor" );

        // if ( ! m_element_list.empty() )
        //     {
	//       trace::infrastructure_error ( "(WW) Found %d items still on the stack.", m_element_list.size() );
	      
	//       while ( ! m_element_list.empty() )
	// 	{
	// 	  trace::infrastructure_error ( "  %s", m_element_list.top() );
                        
	// 	  m_element_list.pop();
	// 	}
        //     }

        trace::infrastructure_detail ( "Exiting Configuration_Parser destructor" );
    }

    // Parser
    boost::shared_ptr < infrastructure::configuration_data >
    configuration_parser::parse_data (void)
    {
      trace::infrastructure_detail ( "Entering Configuration_Parser::parse_Data" );

      // if ( ! boost::filesystem::exists ( m_file ) )
      // 	{
      // 	  // Error creating
      // 	  trace::infrastructure_error ( "Configuration_Parser::parse_Data - cannot find %s", m_file );

      // 	  // Throw exception
      // 	  throw errors::parsing_exception ( errors::parsing_exception::missing_file );
      // 	}

      // std::ifstream input ( m_file.c_str() );
      
      // data_containers::memory_map input_data ( input, input.tellg() );
      
      //   // Parse file
      // XML_Status result = this->XML_Parse ( reinterpret_cast<const char*>(&(*input_data.begin())),
      // 					    input_data.size(),

      // 	  {
      // 	    trace::infrastructure_error ( "%s at line %d in %s",
      // 					  getErrorString ( getErrorCode() ),
      // 					  getCurrentLineNumber(),
      // 					  m_file );

      // 	    // Throw exception
      // 	    throw errors::parsing_exception ( errors::parsing_exception::invalid_format );
      // 	  }
                           
      //   this->destroyParser();

      //   trace::infrastructure_detail ( "Exiting Configuration_Parser::parse_Data" );

        return m_data_ptr;
    }

    void
    configuration_parser::startElement ( const XML_Char* element_name,
                                         const XML_Char** )//attributes )
    {
      trace::infrastructure_detail ( "Inside Configuration_Parser::startElement" );

      //      m_element_list.push ( element_name );
    }

    void configuration_parser::charData ( const std::string& element_value )
    {
        trace::infrastructure_detail ( "Entering Configuration_Parser::charData" );

        // std::string present_element = m_element_list.top();

        // if ( present_element.compare ( m_tag.TAG_FORMULA_DIRECTORY ) == 0 )
        //     {
        //         m_data_ptr->set_formula_directory ( element_value );
        //     }
        // else if ( present_element.compare ( m_tag.TAG_FILE_PREFIX ) == 0 )
	//   {
	//     boost::shared_ptr < infrastructure::file_data_source_config > file_ptr = boost::make_shared < infrastructure::file_data_source_config > ( element_value );
	//     m_data_ptr->set_transfer_config ( file_ptr );
	//   }
        // else if ( present_element.compare ( m_tag.TAG_MEMORY ) == 0 )
	//   {
	//     boost::shared_ptr < infrastructure::memory_data_source_config > mem_ptr = boost::make_shared < infrastructure::memory_data_source_config> ();
	//     m_data_ptr->set_transfer_config ( mem_ptr );
	//   }
        // else if ( present_element.compare ( m_tag.TAG_HOST ) == 0 )
	//   {
	//     this->m_host = element_value;
	//   }
        // else if ( present_element.compare ( m_tag.TAG_USER ) == 0 )
	//   {
	//     this->m_user = element_value;
	//   }
        // else if ( present_element.compare ( m_tag.TAG_PASSWORD ) == 0 )
	//   {
	//     this->m_password = element_value;
	//   }
        // else if ( present_element.compare ( m_tag.TAG_GRNN_DATA_FILE ) == 0 )
	//   {
	//     std::string grnn_file = element_value;
	//     m_data_ptr->set_grnn_data_file ( grnn_file );
	//   }
        // else
	//   {
	//     // Do nothing
	//   }
	
        trace::infrastructure_detail ( "Exiting Configuration_Parser::charData" );
    }

    void
    configuration_parser::endElement ( const std::string& element_name )
    {
      trace::infrastructure_detail ( "Entering Configuration_Parser::end_element" );
      
      // if ( element_name.compare ( m_tag.TAG_DATABASE ) == 0 )
      // 	{
      // 	  boost::shared_ptr < infrastructure::data_source::database_data_source_config > db_ptr =
      // 	    boost::make_shared < infrastructure::data_source::database_data_source_config > ( this->m_host,
      // 											      this->m_user,
      // 											      this->m_password );
      
      // 	  m_data_ptr->set_transfer_config ( db_ptr );
      // 	}
      
      // m_element_list.pop();
      
      trace::infrastructure_detail ( "Exiting configuration_parser::end_element" );
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
    configuration_parser::get_configuration_file (void) const
    {
      trace::infrastructure_detail ( "Inside Configuration_Parser::get_Configuration_File" );

      return m_file;
    }

  } /* namespace infrastructure */
} /* namespace reverse */
