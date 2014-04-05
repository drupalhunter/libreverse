/*  test_byte_converter.cpp

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
#include "Byte_Converter.h"
#include "reverse/include/config.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace reverse::io;

void test_16bit()
{
    boost::uint16_t input = 0x1234;
    boost::uint16_t const output = 0x3412;

    Byte_Converter::convert ( input );

    BOOST_CHECK_EQUAL ( input, output );
}

void test_32bit()
{
    boost::uint32_t input = 0x12345678;
    boost::uint32_t const output = 0x78563412;

    Byte_Converter::convert ( input );

    BOOST_CHECK_EQUAL ( input, output );
}

void test_64bit()
{
    boost::uint64_t input = 0x1122334455667788ULL;
    boost::uint64_t const output = 0x8877665544332211ULL;

    Byte_Converter::convert ( input );

    BOOST_CHECK_EQUAL ( input, output );
}

test_suite*
init_unit_test_suite ( int, char**)
{
    test_suite* test = BOOST_TEST_SUITE ("Byte Converter test suite");

    test->add ( BOOST_TEST_CASE ( &test_16bit ) );
    test->add ( BOOST_TEST_CASE ( &test_32bit ) );
    test->add ( BOOST_TEST_CASE ( &test_64bit ) );

    return test;
}
