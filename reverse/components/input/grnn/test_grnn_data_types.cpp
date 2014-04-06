/*  test_grnn_data_types.cpp

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

#include <boost/format.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN Data Types test suite

// Boost Test declaration and Checking macro
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include "GRNN_Data_Types.h"

using namespace reverse;

BOOST_AUTO_TEST_SUITE(grnn)

BOOST_AUTO_TEST_CASE(test_empty_string)
{
  BOOST_CHECK_THROW ( classifier::GRNN_Data_Types::get_Type ("" ), std::exception );
}

BOOST_AUTO_TEST_CASE(test_invalid_type_string)
{
  BOOST_CHECK_THROW ( classifier::GRNN_Data_Types::get_Type ("junk" ), std::exception );
}

BOOST_AUTO_TEST_CASE(test_valid_type_string)
{
  BOOST_CHECK_EQUAL ( classifier::GRNN_Data_Types::get_Type ("java_class" ),
		      classifier::GRNN_Data_Types::JAVA_CLASS );
}

BOOST_AUTO_TEST_SUITE_END()
