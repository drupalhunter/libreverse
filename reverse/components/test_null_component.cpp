/*  test_null_component.cpp

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
#include "Null_Component.h"
#include "reverse/data_containers/filename.h"
#include "reverse/infrastructure/data_source/Memory_Data_Source_Config.h"
#include "reverse/infrastructure/data_source/Memory_Data_Transfer.h"
#include "reverse/infrastructure/data_source/Data_Source_T.h"
#include <fstream>
#include "reverse/errors/API_Exception.h"
#include "reverse/include/config.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace reverse;

void test_default_constructor ()
{
    std::cout << "-----------------------------" << std::endl
              << "Test default constructor" << std::endl
              << "-----------------------------" << std::endl;

    component::Null_Component atd_ref;

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(0) );
}

void test_second_constructor ()
{
    std::cout << "-----------------------------" << std::endl
              << "    Test second constructor" << std::endl
              << "-----------------------------" << std::endl;

    component::Null_Component atd_ref ( 20 );

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(20) );
}


meta::meta_object::const_ptr_t
helper_run_test ( infrastructure_types::Component::ptr_t target_ptr,
                  std::string target_file )
{

    // Create data map
    infrastructure_types::Component_Graph::Data_Map_t data_map_ref;

    // Add Data Source with filename added
    data_types::filename::const_ptr_t input_file
        ( new data_container::filename ( target_file.insert (0, PWD_PREFIX) ) );

    infrastructure_types::Memory_Data_Source_Config::ptr_t mem_config
        ( new infrastructure::Memory_Data_Source_Config() );

    infrastructure_types::Memory_Data_Transfer::ptr_t mem_trans
        ( new infrastructure::Memory_Data_Transfer ( mem_config ) );

    infrastructure_types::Data_Source<infrastructure::Memory_Data_Transfer>::ptr_t input_key
        ( new infrastructure::Data_Source<infrastructure::Memory_Data_Transfer>
          ( mem_trans ) );

    infrastructure_types::data_object::ptr_t input_object
        ( new infrastructure::data_object() );
    input_object->set_Data ( input_file );
    input_key->put ( input_object );

    infrastructure_types::Component_Graph::Result_Data_t input_data;
    input_data.first = input_key;
    input_data.second = 1;

    data_map_ref.insert ( std::make_pair ( 0, input_data ) );

    target_ptr->add_Input_Source ( 0 );
    target_ptr->received_Input_Source_Data ( 0 );
    target_ptr->run ( &data_map_ref );

    infrastructure_types::Data_Source_Base::const_ptr_t results =
        target_ptr->results();
    infrastructure_types::data_object::const_ptr_t results_data_obj = results->get();
    meta::meta_object::const_ptr_t meta_results = results_data_obj->get_meta();

    return meta_results;
}

void test_get_name ()
{
    std::cout << "-----------------------------" << std::endl
              << "       Test get name" << std::endl
              << "-----------------------------" << std::endl;

    component::Null_Component atd_ref ( 20 );

    BOOST_CHECK_EQUAL ( atd_ref.get_Name(), "Null_Component" );
}

void test_empty_sources ()
{
    std::cout << "-----------------------------" << std::endl
              << "      Test empty sources" << std::endl
              << "-----------------------------" << std::endl;

    // Create data map
    infrastructure_types::Component_Graph::Data_Map_t data_map_ref;

    boost::shared_ptr<component::Null_Component> null_ptr
        ( new component::Null_Component ( 20 ) );

    null_ptr->run ( &data_map_ref );
}

test_suite*
init_unit_test_suite ( int, char**)
{
    test_suite* test = BOOST_TEST_SUITE ("Architecture Type Detector suite");

    test->add ( BOOST_TEST_CASE ( &test_default_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_second_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_get_name ) );
    test->add ( BOOST_TEST_CASE ( &test_empty_sources ) );

    return test;
}
