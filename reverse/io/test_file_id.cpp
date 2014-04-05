/*  test_file_id.cpp

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
#include "File_ID.h"
#include "reverse/include/config.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace reverse::io;

void test_file_id_constructor()
{
    File_ID id_ref ( PWD_PREFIX
                     "/test_targets/echo" );

    // test #1 - good file name
    BOOST_CHECK_EQUAL ( id_ref.get_Full_Name(),
                        PWD_PREFIX
                        "/test_targets/echo" );

    // File() - test #2 - null file name
    File_ID null_ref ( "" );
    BOOST_CHECK_EQUAL ( null_ref.get_Full_Name(), "" );
}

test_suite*
init_unit_test_suite ( int, char**)
{
    test_suite* test = BOOST_TEST_SUITE ("File ID test suite");

    test->add ( BOOST_TEST_CASE ( &test_file_id_constructor ) );

    return test;
}
