/*  test_reverse.cpp

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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Reverse test suite

#include <boost/test/unit_test.hpp>
#include "libreverse/Reverse.h"
#include "libreverse/errors/Reverse_Exception.h"
#include <iostream>

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace libreverse::api;
using namespace libreverse;

void test_input_types ()
{
    Reverse m_api;

    // PASS: valid Input type given
    // A non-empty string will make the check pass but should fail
    // since we are not giving a valid file name
    BOOST_CHECK_EQUAL ( m_api.execute ( "fake_formula_file",
                                        Input_Types::BINARY,
                                        Output_Types::C ),
                        Results::FAILURE );

}

void test_output_types ()
{
    Reverse m_api;

    // PASS: valid Input type given
    // A non-empty string will make the check pass but should fail
    // since we are not giving a valid file name
    BOOST_CHECK_EQUAL ( m_api.execute ( "fake_formula_file",
                                        Input_Types::BINARY,
                                        Output_Types::UML ),
                        Results::FAILURE );

}

void test_filename ()
{
    Reverse m_api;

    // Empty string will cause a Reverse_Exception since we are expecting
    // a non-empty string as input for the file name.
    BOOST_CHECK_EQUAL ( m_api.execute ( "",
                                        Input_Types::BINARY,
                                        Output_Types::C ),
                        Results::FAILURE );

    // A non-empty string will make the check pass but should fail
    // since we are not giving a valid file name
    BOOST_CHECK_EQUAL ( m_api.execute ( "fake_formula_file",
                                        Input_Types::BINARY,
                                        Output_Types::CPLUSPLUS ),
                        Results::FAILURE );

}

test_suite*
init_unit_test_suite ( int , char** )
{
  test_suite* test = BOOST_TEST_SUITE ( "Reverse test suite" );

  test->add ( BOOST_TEST_CASE ( &test_filename ) );
  test->add ( BOOST_TEST_CASE ( &test_input_types ) );
  test->add ( BOOST_TEST_CASE ( &test_output_types ) );

  return test;
}
