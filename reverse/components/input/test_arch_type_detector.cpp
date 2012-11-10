/*  test_arch_type_detector.cpp

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
#include "Arch_Type_Detector.h"
#include "libreverse/data_containers/Filename.h"
#include "libreverse/infrastructure/data_source/Memory_Data_Source_Config.h"
#include "libreverse/infrastructure/data_source/Memory_Data_Transfer.h"
#include "libreverse/infrastructure/data_source/Data_Source_T.h"
#include <fstream>
#include "libreverse/errors/API_Exception.h"
#include "libreverse/infrastructure/Component_State.h"
#include "libreverse/infrastructure/Component_Types.h"
#include "libreverse/include/config.h"
#include "libreverse/data_containers/Data_Types.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace libreverse;
using namespace libreverse::meta;

void test_default_constructor ()
{
    std::cout << "-----------------------------" << std::endl
              << "Test default constructor" << std::endl
              << "-----------------------------" << std::endl;

    component::Arch_Type_Detector atd_ref;

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(0) );
}

void test_second_constructor ()
{
    std::cout << "-----------------------------" << std::endl
              << "    Test second constructor" << std::endl
              << "-----------------------------" << std::endl;

    infrastructure_types::Component_State::ptr_t state_ptr ( new infrastructure::Component_State ( 20 ) );

    component::Arch_Type_Detector atd_ref ( state_ptr );

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(20) );
}

meta::Meta_Object::const_ptr_t
helper_run_test ( infrastructure_types::Component::ptr_t target_ptr,
                  std::string target_file )
{

    // Create data map
    infrastructure_types::Component_Graph::Data_Map_t data_map_ref;

    // Add Data Source with filename added
    data_types::Filename::const_ptr_t input_file
        ( new data_container::Filename
          ( target_file.insert ( 0, PWD_PREFIX ) ) );

    infrastructure_types::Memory_Data_Source_Config::ptr_t
        mem_config ( new infrastructure::Memory_Data_Source_Config() );

    infrastructure_types::Memory_Data_Transfer::ptr_t
        mem_trans ( new infrastructure::Memory_Data_Transfer
                    ( mem_config ) );

    infrastructure_types::Data_Source<infrastructure::Memory_Data_Transfer>::ptr_t
        input_key ( new infrastructure::Data_Source<infrastructure::Memory_Data_Transfer>
                    ( mem_trans ) );

    infrastructure_types::Data_Object::ptr_t
        input_object ( new infrastructure::Data_Object() );

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
    infrastructure_types::Data_Object::const_ptr_t
        results_data_obj = results->get();

    meta::Meta_Object::const_ptr_t meta_results =
        results_data_obj->getMeta();

    return meta_results;
}

void test_intel_winpe_process ()
{
    trace::Trace_State::Instance().set_Trace_Level ( TraceLevel::DETAIL );
    trace::Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::COMPONENTS );
    trace::Trace_State::Instance().set_Trace_File_Prefix ( "Test_arch_type_detector_WINPE");
    trace::Trace_State::Instance().open_Trace_File ();

    std::cout << "-----------------------------" << std::endl
              << "  Test intel winpe process" << std::endl
              << "-----------------------------" << std::endl;

    infrastructure_types::Component_State::ptr_t state_ptr ( new infrastructure::Component_State ( 20 ) );

    boost::shared_ptr<component::Arch_Type_Detector> atd_ptr
        ( new component::Arch_Type_Detector ( state_ptr ) );

    meta::Meta_Object::const_ptr_t meta_results =
        helper_run_test ( atd_ptr, "/test_targets/cokegift.exe" );

    Meta_Object::Data_Pair_t arch_meta_value =
        meta_results->get_Value ( "arch_type" );

    assert ( arch_meta_value.second == Meta_Object::STRING );
    std::string arch_str_val = arch_meta_value.first;

    BOOST_CHECK_EQUAL ( arch_str_val, "intel:i386" );

    trace::Trace_State::Instance().close_Trace_File ();
}

void test_intel_elf_process ()
{
    trace::Trace_State::Instance().set_Trace_Level ( TraceLevel::DETAIL );
    trace::Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::COMPONENTS );
    trace::Trace_State::Instance().set_Trace_File_Prefix ( "Test_arch_type_detector_ELF");
    trace::Trace_State::Instance().open_Trace_File ();

    std::cout << "-----------------------------" << std::endl
              << "   Test intel elf process" << std::endl
              << "-----------------------------" << std::endl;

    infrastructure_types::Component_State::ptr_t state_ptr ( new infrastructure::Component_State ( 20 ) );
                                                                     
    boost::shared_ptr<component::Arch_Type_Detector> atd_ptr
        ( new component::Arch_Type_Detector( state_ptr ) );

    meta::Meta_Object::const_ptr_t meta_results =
        helper_run_test ( atd_ptr, "/test_targets/echo" );

    Meta_Object::Data_Pair_t arch_meta_value =
        meta_results->get_Value ( "arch_type" );

    assert ( arch_meta_value.second == Meta_Object::STRING );
    std::string arch_str_val = arch_meta_value.first;

    BOOST_CHECK_EQUAL ( arch_str_val, "intel:i386" );

    trace::Trace_State::Instance().close_Trace_File ();
}

void test_get_name ()
{
    std::cout << "-----------------------------" << std::endl
              << "       Test get name" << std::endl
              << "-----------------------------" << std::endl;

    infrastructure_types::Component_State::ptr_t state_ptr ( new infrastructure::Component_State ( 20 ) );

    component::Arch_Type_Detector atd_ref ( state_ptr );

    BOOST_CHECK_EQUAL ( atd_ref.get_Name(), "Arch_Type_Detector" );
}

void test_empty_sources ()
{
    std::cout << "-----------------------------" << std::endl
              << "      Test empty sources" << std::endl
              << "-----------------------------" << std::endl;

    // Create data map
    infrastructure_types::Component_Graph::Data_Map_t data_map_ref;

    infrastructure_types::Component_State::ptr_t state_ptr ( new infrastructure::Component_State ( 20 ) );

    boost::shared_ptr<component::Arch_Type_Detector> atd_ptr
        ( new component::Arch_Type_Detector ( state_ptr ) );

    BOOST_CHECK_THROW ( atd_ptr->run ( &data_map_ref ),
                        errors::API_Exception );
}

void test_wrong_sources ()
{
    trace::Trace_State::Instance().set_Trace_Level ( TraceLevel::DETAIL );
    trace::Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::COMPONENTS );
    trace::Trace_State::Instance().set_Trace_File_Prefix ( "Test_arch_type_detector_WRONG_SOURCES");
    trace::Trace_State::Instance().open_Trace_File ();

    std::cout << "-----------------------------" << std::endl
              << "     Test wrong sources" << std::endl
              << "-----------------------------" << std::endl;

    // Create data map
    infrastructure_types::Component_Graph::Data_Map_t data_map_ref;

    infrastructure_types::Component_State::ptr_t state_ptr ( new infrastructure::Component_State ( 20 ) );

    boost::shared_ptr<component::Arch_Type_Detector> atd_ptr
        ( new component::Arch_Type_Detector ( state_ptr ) );

    // Add Data Source with filename added
    data_types::Control_Flow_Graph::const_ptr_t input_cfg ( new data_container::Control_Flow_Graph() );

    infrastructure_types::Memory_Data_Source_Config::ptr_t mem_config
        ( new infrastructure::Memory_Data_Source_Config() );

    infrastructure_types::Memory_Data_Transfer::ptr_t mem_trans
        ( new infrastructure::Memory_Data_Transfer ( mem_config ) );

    infrastructure_types::Data_Source<infrastructure::Memory_Data_Transfer>::ptr_t input_key
        ( new infrastructure::Data_Source<infrastructure::Memory_Data_Transfer>( mem_trans ) );

    infrastructure_types::Data_Object::ptr_t input_object
        ( new infrastructure::Data_Object() );

    input_object->set_Data ( input_cfg );

    input_key->put ( input_object );

    infrastructure_types::Component_Graph::Result_Data_t input_data;
    input_data.first = input_key;
    input_data.second = 1;

    data_map_ref.insert ( std::make_pair ( 0, input_data ) );

    atd_ptr->add_Input_Source ( 0 );
    atd_ptr->received_Input_Source_Data ( 0 );
    BOOST_CHECK_THROW ( atd_ptr->run ( &data_map_ref ),
                        errors::API_Exception );

    trace::Trace_State::Instance().close_Trace_File ();
}

test_suite*
init_unit_test_suite ( int, char**)
{
    test_suite* test = BOOST_TEST_SUITE ("Architecture Type Detector suite");

    test->add ( BOOST_TEST_CASE ( &test_default_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_second_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_intel_winpe_process ) );
    test->add ( BOOST_TEST_CASE ( &test_intel_elf_process ) );
    test->add ( BOOST_TEST_CASE ( &test_get_name ) );
    test->add ( BOOST_TEST_CASE ( &test_empty_sources ) );
    test->add ( BOOST_TEST_CASE ( &test_wrong_sources ) );

    return test;
}
