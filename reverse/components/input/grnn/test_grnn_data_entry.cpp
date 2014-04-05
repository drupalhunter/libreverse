/*  test_grnn_data_entry.cpp

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
#define BOOST_TEST_MODULE GRNN Data Entry test suite

// Boost Test declaration and Checking macro
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include "GRNN_Data_Entry.h"

using namespace libreverse::classifier;

BOOST_AUTO_TEST_SUITE(grnn)

BOOST_AUTO_TEST_CASE(test_empty_filename)
{
  double sigma = 1.0;
  std::string filename = "";

  BOOST_CHECK_THROW ( GRNN_Data_Entry a_ref ( sigma, filename ), std::exception );
}

BOOST_AUTO_TEST_CASE(test_zero_sigma)
{
  double sigma = 0.0;
  std::string filename = "Funky";

  BOOST_CHECK_THROW ( GRNN_Data_Entry a_ref ( sigma, filename ), std::exception );
}

BOOST_AUTO_TEST_CASE(test_returns)
{
  double sigma = 1.0;
  std::string filename = "Funky";

  GRNN_Data_Entry a_ref ( sigma, filename );

  BOOST_CHECK_EQUAL ( a_ref.get_Sigma(), sigma );
  BOOST_CHECK_EQUAL ( a_ref.get_filename(), filename );
}

BOOST_AUTO_TEST_SUITE_END()
