/*  test_memory_map.cpp

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
#include <boost/format.hpp>
#include "memory_map.h"
#include <fstream>
#include "libreverse/Reverse.h"
#include "libreverse/Trace.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace libreverse;

void test_seek_PASS_LOW_SEEK ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size );

    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(0) );

    a_ref.index_Seek( static_cast<boost::uint8_t>(0) );
    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(0) );
}

void test_seek_PASS_HIGH_SEEK ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size );
    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(0));

    a_ref.index_Seek( static_cast<boost::uint32_t>(4) );

    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(4) );
}

void test_seek_FAIL_HIGH_SEEK ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size );
    BOOST_CHECK_EQUAL ( a_ref.index_Seek( static_cast<boost::uint32_t>(6) ),
                        data_types::memory_map::OUT_OF_RANGE );
}

void test_copy ()
{
    trace::Trace_State::Instance().set_Trace_Level ( api::TraceLevel::DATA );
    trace::Trace_State::Instance().set_Trace_Area_Mask ( api::TraceArea::DATA_CONTAINERS );
    trace::Trace_State::Instance().open_Trace_File ();

    std::ifstream input ( "data_int.hex",
                          std::ios_base::in |
                          std::ios_base::binary );
    data_types::memory_map::ptr_t src_ptr ( new data_container::memory_map ( input ) );
	data_container::memory_map dest_ref ( src_ptr->size() );

	dest_ref.copy ( src_ptr, src_ptr->size() );
    BOOST_CHECK ( dest_ref == *src_ptr );

    trace::Trace_State::Instance().close_Trace_File ();

}

void test_uint8_read ()
{
    std::ifstream input ( "data_int.hex",
                          std::ios_base::in |
                          std::ios_base::binary );

	data_container::memory_map src_ref ( input );

    boost::uint8_t val;

    src_ref.read ( &val, sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x20 );

    src_ref.read ( &val, sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x15 );

    src_ref.read ( &val, sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x10 );

    src_ref.read ( &val, sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x05 );

}

void test_uint16_read ()
{
    std::ifstream input ( "data_int.hex",
                          std::ios_base::in |
                          std::ios_base::binary );

	data_container::memory_map src_ref ( input );

    boost::uint16_t val;

    src_ref.read ( reinterpret_cast<boost::uint8_t*>(&val), sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x1520 );

    src_ref.read ( reinterpret_cast<boost::uint8_t*>(&val), sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x0510 );
}

void test_uint32_read ()
{
    std::ifstream input ( "data_int.hex",
                          std::ios_base::in |
                          std::ios_base::binary );

	data_container::memory_map src_ref ( input );

    boost::uint32_t val;

    src_ref.read ( reinterpret_cast<boost::uint8_t*>(&val), sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val,
                        static_cast<boost::uint32_t>(0x05101520) );
}

void test_uint64_read ()
{
    std::ifstream input ( "data_int.hex",
                          std::ios_base::in |
                          std::ios_base::binary );

	data_container::memory_map src_ref ( input );

    boost::uint64_t val;

    src_ref.read ( reinterpret_cast<boost::uint8_t*>(&val), sizeof ( val ) );
    BOOST_CHECK_EQUAL ( val, 0x2530354005101520ULL );
}

void test_seek_ADDRESS_PASS_LOW ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size, 0x400 );

    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(0) );

    a_ref.address_Seek(0x400);

    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(0) );
}

void test_seek_ADDRESS_PASS_HIGH ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size, 0x400 );

    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(0) );

    a_ref.address_Seek(0x404);

    BOOST_CHECK_EQUAL ( a_ref.get_Present_Position_Value (),
                        static_cast<boost::uint32_t>(4) );
}

void test_seek_ADDRESS_FAIL_LOW ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size, 0x400 );
    BOOST_CHECK_EQUAL ( a_ref.address_Seek(0x300),
                        data_types::memory_map::OUT_OF_RANGE );
}

void test_seek_ADDRESS_FAIL_HIGH ()
{
    boost::uint32_t size = 5;
    data_container::memory_map a_ref ( size, 0x400 );
    BOOST_CHECK_EQUAL ( a_ref.address_Seek(0x500),
                        data_types::memory_map::OUT_OF_RANGE );
}

void test_subset ()
{
    std::ifstream input ( "data_int.hex",
                          std::ios_base::binary );

    data_types::memory_map::ptr_t src_ref
        ( new data_container::memory_map ( input ) );

    std::cout << src_ref->to_String() << std::endl;

    src_ref->index_Seek ( static_cast<boost::uint8_t>(4) );

    std::pair<data_types::memory_map::ptr_t,boost::int8_t> sub_ptr =
        src_ref->subset ( 4 );

    BOOST_CHECK_EQUAL ( sub_ptr.second, data_types::memory_map::SUCCESS );

    boost::uint16_t val;

    std::cout << sub_ptr.first->to_String() << std::endl;

    sub_ptr.first->read
        ( reinterpret_cast<boost::uint8_t*>(&val), sizeof ( val ) );

    std::cout << boost::format ("val = %X") % val << std::endl;

    BOOST_CHECK_EQUAL ( val, 0x3540 );

}


test_suite*
init_unit_test_suite ( int, char** )
{
    test_suite* test = BOOST_TEST_SUITE ("Memory Map suite");

    // Allow memory_map to allocate our memory at any location
    test->add ( BOOST_TEST_CASE ( &test_seek_PASS_LOW_SEEK ) );
    test->add ( BOOST_TEST_CASE ( &test_seek_PASS_HIGH_SEEK ) );
    test->add ( BOOST_TEST_CASE ( &test_seek_FAIL_HIGH_SEEK ) );
    test->add ( BOOST_TEST_CASE ( &test_copy ) );
    test->add ( BOOST_TEST_CASE ( &test_uint8_read ) );
    test->add ( BOOST_TEST_CASE ( &test_uint16_read ) );
    test->add ( BOOST_TEST_CASE ( &test_uint32_read ) );
    test->add ( BOOST_TEST_CASE ( &test_uint64_read ) );
    test->add ( BOOST_TEST_CASE ( &test_seek_ADDRESS_PASS_LOW ) );
    test->add ( BOOST_TEST_CASE ( &test_seek_ADDRESS_PASS_HIGH ) );
    test->add ( BOOST_TEST_CASE ( &test_seek_ADDRESS_FAIL_LOW ) );
    test->add ( BOOST_TEST_CASE ( &test_seek_ADDRESS_FAIL_HIGH ) );
    test->add ( BOOST_TEST_CASE ( &test_subset ) );

    return test;
}
