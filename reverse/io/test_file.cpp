/*  test_file.cpp

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
#include "File.h"
#include "File_ID.h"
#include "reverse/data_containers/memory_map.h"
#include "reverse/include/config.h"
#include "reverse/errors/IO_Exception.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace reverse;
using namespace reverse::data_types;

void test_file_id_constructor()
{
    io_types::File_ID::ptr_t id_ptr ( new io::File_ID ( PWD_PREFIX
                                          "/test_targets/echo" ) );

    // File() - test #1 - good file name
    io::File file_ref ( id_ptr );

    // File() - test #2 - null file name
    io_types::File_ID::ptr_t null_file_ptr;

    BOOST_CHECK_THROW ( io::File null_file_ref ( null_file_ptr ),
                        reverse::errors::IO_Exception );

    // File (memory_map,File_ID) - test #1 - null map and file
    data_types::memory_map::ptr_t null_map_ptr;
    BOOST_CHECK_THROW ( io::File null_file_ref1 ( null_map_ptr, null_file_ptr ),
                        reverse::errors::IO_Exception );

    // File (memory_map,File_ID) - test #2 - null map
    BOOST_CHECK_THROW ( io::File null_file_ref2 ( null_map_ptr, id_ptr ),
                        reverse::errors::IO_Exception );

    // File (memory_map,File_ID) - test #3 - null file
    data_types::memory_map::ptr_t map_ptr ( new data_container::memory_map(1) );
    BOOST_CHECK_THROW ( io::File null_file_ref3 ( map_ptr, null_file_ptr ),
                        reverse::errors::IO_Exception );

    // File (memory_map,File_ID) - test #4 - good map and file pointer
    io::File good_ref ( map_ptr, id_ptr );
}

void test_get_id ()
{
    io_types::File_ID::ptr_t id_ptr ( new io::File_ID ( PWD_PREFIX
                                          "/test_targets/echo" ) );

    // File() - test #1 - good file name
    io::File file_ref ( id_ptr );

    io_types::File_ID::const_ptr_t returned_id_ptr = file_ref.get_ID();

    BOOST_CHECK_EQUAL ( returned_id_ptr->get_Full_Name(),
                        PWD_PREFIX
                        "/test_targets/echo" );
}

void test_open()
{
    io_types::File_ID::ptr_t empty_name_ptr ( new io::File_ID ( "" ) );

    io_types::File_ID::ptr_t name_set_ptr ( new io::File_ID ( PWD_PREFIX
                                                              "/test_targets/echo" ) );

    // test 1a - name empty
    io::File file_ref ( empty_name_ptr );
    BOOST_CHECK_EQUAL ( file_ref.init (), false );

    // test 1b - name is set
    io::File good_file_ref ( name_set_ptr );
    BOOST_CHECK_EQUAL ( good_file_ref.init (), true );

    // test 2a - file handle is already open
    BOOST_CHECK_EQUAL ( good_file_ref.init (), true );
}

void test_begin()
{
    io_types::File_ID::ptr_t name_set_ptr ( new io::File_ID ( PWD_PREFIX
                                                              "/test_targets/echo" ) );

    io::File good_file_ref ( name_set_ptr );

    BOOST_CHECK_THROW ( good_file_ref.begin(), reverse::errors::IO_Exception );

    BOOST_CHECK_EQUAL ( good_file_ref.init(), true );
}

void test_end()
{
    io_types::File_ID::ptr_t name_set_ptr ( new io::File_ID ( PWD_PREFIX
                                                              "/test_targets/echo" ) );

    io::File good_file_ref ( name_set_ptr );

    BOOST_CHECK_THROW ( good_file_ref.end(), reverse::errors::IO_Exception );

    BOOST_CHECK_EQUAL ( good_file_ref.init(), true );
}

void test_get_map_ptr ()
{
    io_types::File_ID::ptr_t name_set_ptr ( new io::File_ID ( PWD_PREFIX
                                                              "/test_targets/echo" ) );

    io::File good_file_ref ( name_set_ptr );

    data_types::memory_map::ptr_t result_ptr = good_file_ref.get_Map_Ptr();
    BOOST_CHECK ( result_ptr.get() == 0 );

    good_file_ref.init();
    result_ptr = good_file_ref.get_Map_Ptr();

    BOOST_CHECK ( result_ptr.get() != 0 );
}

void test_size ()
{
    io_types::File_ID::ptr_t name_set_ptr ( new io::File_ID ( PWD_PREFIX
                                                              "/test_targets/echo" ) );

    io::File good_file_ref ( name_set_ptr );

    BOOST_CHECK_THROW ( good_file_ref.size(), reverse::errors::IO_Exception );

    good_file_ref.init();

    BOOST_CHECK ( good_file_ref.size() == 0 );
}

test_suite*
init_unit_test_suite ( int, char**)
{
    test_suite* test = BOOST_TEST_SUITE ("File test suite");

    test->add ( BOOST_TEST_CASE ( &test_file_id_constructor ) );
    test->add ( BOOST_TEST_CASE ( &test_get_id ) );
    test->add ( BOOST_TEST_CASE ( &test_open ) );
    test->add ( BOOST_TEST_CASE ( &test_begin ) );
    test->add ( BOOST_TEST_CASE ( &test_end ) );
    test->add ( BOOST_TEST_CASE ( &test_get_map_ptr ) );

    return test;
}
