/*  test_configuration_parser.cpp

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

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "libreverse/include/config.h"
#include "Configuration_Parser.h"
#include "Configuration_Data.h"
#include "data_source/Database_Data_Source_Config.h"
#include "data_source/Memory_Data_Source_Config.h"
#include "data_source/File_Data_Source_Config.h"
#include "libreverse/Reverse.h"
#include "Component_Types.h"

using namespace libreverse;
using namespace libreverse::infrastructure;
using namespace libreverse::api;
using namespace boost::unit_test;
using namespace boost::unit_test_framework;

void test_constructor ()
{
    Configuration_Parser a;

    BOOST_CHECK_EQUAL ( a.get_Configuration_File(),
                        CONF_PREFIX
                        "libreverse/config.xml" );

    Configuration_Parser b ("local_config.xml");
    BOOST_CHECK_EQUAL ( b.get_Configuration_File(),
                        "local_config.xml" );
}

void test_parse_database_config ()
{
    Configuration_Parser a ("db_config.xml");
    Configuration_Data::ptr_t config_data_ptr = a.parse_Data();

    // Is the transfer config a Memory_Transfer?
    infrastructure_types::Database_Data_Source_Config::ptr_t source_ptr =
        boost::dynamic_pointer_cast<Database_Data_Source_Config> ( config_data_ptr->get_Transfer_Config() );

    BOOST_CHECK_EQUAL ( source_ptr->get_Type(),
                        Transfer_Types::DATABASE );

    // Get Formula Directory
    std::string form_dir_string = config_data_ptr->get_Formula_Directory();
    BOOST_CHECK_EQUAL ( form_dir_string,
                        "/home/storri/src/libreverse" );

    // Get DLL Directory
    std::string dll_dir_string = config_data_ptr->get_DLL_Directory();
    BOOST_CHECK_EQUAL ( dll_dir_string,
                        "" );

    // Get Host
    BOOST_CHECK_EQUAL ( source_ptr->get_Host(),
                        "localhost" );

    // Get User
    BOOST_CHECK_EQUAL ( source_ptr->get_User(),
                        "password" );

    // Get Password
    BOOST_CHECK_EQUAL ( source_ptr->get_Password(),
                        "fuzzybunnyslippers" );
}

void test_parse_memory_config ()
{
    Configuration_Parser a ("memory_config.xml");
    Configuration_Data::ptr_t config_data_ptr = a.parse_Data();

    // Is the transfer config a Memory_Transfer?
    infrastructure_types::Memory_Data_Source_Config::ptr_t source_ptr =
        boost::dynamic_pointer_cast<Memory_Data_Source_Config> ( config_data_ptr->get_Transfer_Config() );

    BOOST_CHECK_EQUAL ( source_ptr->get_Type(),
                        Transfer_Types::MEMORY );

    // Get Formula Directory
    std::string form_dir_string = config_data_ptr->get_Formula_Directory();
    BOOST_CHECK_EQUAL ( form_dir_string,
                        "/home/storri/src/libreverse" );

}

void test_parse_file_config ()
{
    Configuration_Parser a ("file_config.xml");
    Configuration_Data::ptr_t config_data_ptr = a.parse_Data();

    // Is the transfer config a File_Transfer?
    infrastructure_types::File_Data_Source_Config::ptr_t source_ptr =
        boost::dynamic_pointer_cast<File_Data_Source_Config> ( config_data_ptr->get_Transfer_Config() );

    BOOST_CHECK_EQUAL ( source_ptr->get_Type(),
                        Transfer_Types::FILE );

    BOOST_CHECK_EQUAL ( source_ptr->get_Filename(),
                        "GummyBears_0.dat" );

    // Get Formula Directory
    std::string form_dir_string = config_data_ptr->get_Formula_Directory();
    BOOST_CHECK_EQUAL ( form_dir_string,
                        "/home/storri/src/libreverse" );
}

test_suite*
init_unit_test_suite ( int , char** )
{
  test_suite* test = BOOST_TEST_SUITE ( "Configuration Parser test suite" );

  test->add ( BOOST_TEST_CASE ( &test_constructor ) );
  test->add ( BOOST_TEST_CASE ( &test_parse_database_config ) );
  test->add ( BOOST_TEST_CASE ( &test_parse_memory_config ) );
  test->add ( BOOST_TEST_CASE ( &test_parse_file_config ) );

  return test;
}
