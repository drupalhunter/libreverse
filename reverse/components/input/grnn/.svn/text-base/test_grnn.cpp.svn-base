

/*  test_grnn.cpp

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
#define BOOST_TEST_MODULE GRNN test suite

// Boost Test declaration and Checking macro
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include "Java_Training_Data.h"
#include "GRNN.h"

#include "libreverse/Reverse.h"
#include "libreverse/Trace.h"
#include <iostream>

using namespace libreverse::trace;
using namespace libreverse;

BOOST_AUTO_TEST_SUITE(grnn)

BOOST_AUTO_TEST_CASE(test_distance_squared_zero_sigma)
{
  double sigma = 0.0;

  classifier_types::Training_Set<classifier::Java_Training_Data>::Candidate_Data_Map_t training_set;
  classifier_types::Training_Set<classifier::Java_Training_Data>::Candidate_Data_Map_t verification_set;

  classifier::GRNN<classifier::Java_Training_Data> src_ref ( sigma,
							     training_set,
							     verification_set );

  BOOST_CHECK_THROW ( src_ref.execute(), std::exception );
  BOOST_CHECK_THROW ( src_ref.classify(), std::exception );
}

BOOST_AUTO_TEST_CASE(test_distance_squared_empty_sets)
{
  double sigma = 0.002;

  classifier_types::Training_Set<classifier::Java_Training_Data>::Candidate_Data_Map_t training_set;
  classifier_types::Training_Set<classifier::Java_Training_Data>::Candidate_Data_Map_t verification_set;

  classifier::GRNN<classifier::Java_Training_Data> src_ref ( sigma,
							     training_set,
							     verification_set );

  BOOST_CHECK_THROW ( src_ref.execute(), std::exception );
  BOOST_CHECK_THROW ( src_ref.classify(), std::exception );
}


BOOST_AUTO_TEST_CASE(test_distance_squared)
{
  double sigma = 0.002;

  classifier_types::Variable_Map::map_type training_map;
  training_map.insert ( std::make_pair ( 0, 0.0 ) );
  training_map.insert ( std::make_pair ( 1, 0.0 ) );
  training_map.insert ( std::make_pair ( 2, 0.0 ) );
  training_map.insert ( std::make_pair ( 3, 0.0 ) );
  training_map.insert ( std::make_pair ( 4, 0.0 ) );
  training_map.insert ( std::make_pair ( 5, 0.0 ) );

  classifier_types::Training_Set<classifier::Java_Training_Data>::Candidate_Data_Map_t training_set;
  training_set.push_back ( training_map );
  
  classifier_types::Variable_Map::map_type verification_map;
  verification_map.insert ( std::make_pair ( 0, 1.0 ) );
  verification_map.insert ( std::make_pair ( 1, 1.0 ) );
  verification_map.insert ( std::make_pair ( 2, 1.0 ) );
  verification_map.insert ( std::make_pair ( 3, 1.0 ) );
  verification_map.insert ( std::make_pair ( 4, 1.0 ) );
  verification_map.insert ( std::make_pair ( 5, 1.0 ) );

  classifier_types::Training_Set<classifier::Java_Training_Data>::Candidate_Data_Map_t verification_set;
  verification_set.push_back ( verification_map );


  classifier::GRNN<classifier::Java_Training_Data> src_ref ( sigma,
							     training_set,
							     verification_set );

  src_ref.execute();

  /*
  double distance_squared = src_ref.distance_squared ( verification_set.begin(), training_set.begin() );
  std::cout << boost::format ( "Distance squared: %1$1.10f" ) % distance_squared << std::endl;

  BOOST_CHECK_EQUAL ( distance_squared, 5.0 );
  */
}

BOOST_AUTO_TEST_SUITE_END()
