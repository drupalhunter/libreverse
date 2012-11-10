/*  test_configurator.cpp

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
#include "Configurator.h"
#include "libreverse/errors/Parsing_Exception.h"

using namespace libreverse;
using namespace boost::unit_test;
using namespace boost::unit_test_framework;

void test_instance ()
{
    infrastructure_types::Configurator::ptr_t a_ptr =
        infrastructure::Configurator::Instance("memory_config.xml");

    BOOST_CHECK ( a_ptr.get() != 0 );
}

test_suite*
init_unit_test_suite ( int , char** )
{
  test_suite* test = BOOST_TEST_SUITE ( "Configurator test suite" );

  test->add ( BOOST_TEST_CASE ( &test_instance ) );

  return test;
}
