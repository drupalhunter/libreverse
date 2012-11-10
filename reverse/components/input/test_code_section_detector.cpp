/*  test_code_section_detector.cpp

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
#include "Code_Section_Detector.h"
#include "data_types/Filename.h"
#include "infrastructure/data_source/Memory_Data_Source_Config.h"
#include "infrastructure/data_source/Memory_Data_Transfer.h"
#include "infrastructure/data_source/Data_Source_T.h"
#include <fstream>

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace libreverse::data_types;
using namespace libreverse::component;
using namespace libreverse::meta;
using namespace libreverse::infrastructure;

void test_default_constructor ()
{
    Code_Section_Detector atd_ref;
    Filename::ptr_t const file = atd_ref.get_Filename();
    BOOST_CHECK_EQUAL ( file->to_String(), "" );

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(0) );
}

void test_second_constructor ()
{
    Code_Section_Detector atd_ref ( 20 );
    Filename::ptr_t const file = atd_ref.get_Filename();
    BOOST_CHECK_EQUAL ( file->to_String(), "" );

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(20) );
}

void test_visit ()
{
    Code_Section_Detector atd_ref ( 20 );

    Filename::ptr_t input_file ( new Filename ( "arch_test1.exe" ) );

    atd_ref.visit ( input_file );

    Filename::ptr_t const file = atd_ref.get_Filename();

    BOOST_CHECK_EQUAL ( file->to_String(), "arch_test1.exe" );

    BOOST_CHECK_EQUAL ( atd_ref.get_ID(), static_cast<boost::uint32_t>(20) );
}

Meta_Object::ptr_t
helper_run_test ( Component::ptr_t target_ptr,
                  std::string target_file )
{
    // Create data map
    Graph_Base::Data_Map_t data_map_ref;

    // Add Data Source with filename added
    Filename::ptr_t input_file ( new Filename ( target_file.insert (0, PWD_PREFIX) ) );

    Memory_Data_Source_Config::ptr_t mem_config ( new Memory_Data_Source_Config() );
    Memory_Data_Transfer::ptr_t mem_trans ( new Memory_Data_Transfer ( mem_config ) );
    Data_Source<Memory_Data_Transfer>::ptr_t input_key
        ( new Data_Source<Memory_Data_Transfer>( mem_trans ) );

    Data_Object::ptr_t input_object ( new Data_Object() );
    input_object->setData ( input_file );
    input_key->put ( input_object );

    Graph_Base::Result_Data_t input_data;
    input_data.first = input_key;
    input_data.second = 1;

    data_map_ref.insert ( std::make_pair ( 0, input_data ) );

    target_ptr->set_Data_Source ( 0 );
    target_ptr->init ( 0 );
    target_ptr->run ( data_map_ref );

    Data_Source_Base::ptr_t results = target_ptr->results();
    Data_Object::ptr_t results_data_obj = results->get();
    Meta_Object::ptr_t meta_results = results_data_obj->getMeta();

    return meta_results;
}

void test_intel_winpe_process ()
{
    Code_Section_Detector::ptr_t atd_ptr ( new Code_Section_Detector ( 20 ) );

    Meta_Object::ptr_t meta_results =
        helper_run_test ( atd_ptr, "/test_targets/cokegift.exe" );

    std::string text = meta_results->get_Value ( "code_section_address" );
    boost::uint32_t value = meta_results->convert_To_UInt32 ( text );
    BOOST_CHECK_EQUAL ( value, 0x1000 );

    text = meta_results->get_Value ( "code_section_size" );
    value = meta_results->convert_To_UInt32 ( text );
    BOOST_CHECK_EQUAL ( value, 0x8014C );
}

void test_intel_elf_process ()
{
    Code_Section_Detector::ptr_t atd_ptr ( new Code_Section_Detector( 20 ) );

    Meta_Object::ptr_t meta_results =
        helper_run_test ( atd_ptr, "/test_targets/echo" );

    std::string text = meta_results->get_Value ( "code_section" );

    BOOST_CHECK_EQUAL ( text, "intel:i386" );
}

void test_get_name ()
{
    Code_Section_Detector atd_ref ( 20 );

    BOOST_CHECK_EQUAL ( atd_ref.get_Name(), "Code_Section_Detector" );
}

test_suite*
init_unit_test_suite ( int, char**)
{
    test_suite* test = BOOST_TEST_SUITE ("Code Section Detector suite");

    test->add ( BOOST_TEST_CASE ( &test_default_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_second_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_visit ) );
    test->add ( BOOST_TEST_CASE ( &test_intel_winpe_process ) );
    test->add ( BOOST_TEST_CASE ( &test_intel_elf_process ) );
    test->add ( BOOST_TEST_CASE ( &test_get_name ) );

    return test;
}
