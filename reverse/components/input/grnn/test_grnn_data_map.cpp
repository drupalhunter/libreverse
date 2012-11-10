/*  test_grnn_data_map.cpp

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
#define BOOST_TEST_MODULE GRNN Data Map test suite

// Boost Test declaration and Checking macro
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include "Classifier_Types.h"
#include "GRNN_Data_Entry.h"
#include "GRNN_Data_Map.h"

using namespace libreverse;

BOOST_AUTO_TEST_SUITE(grnn)

BOOST_AUTO_TEST_CASE(test_bad_key)
{
  classifier::GRNN_Data_Types::Value_Type key = classifier::GRNN_Data_Types::UNKNOWN;
  double sigma = 1.0;
  std::string file = "Funky";
  classifier_types::GRNN_Data_Entry::ptr_t entry_ptr ( new classifier::GRNN_Data_Entry ( sigma, file ) );
 
  classifier::GRNN_Data_Map a_ref;

  BOOST_CHECK_THROW ( a_ref.insert ( key, entry_ptr ), std::exception );
  BOOST_CHECK_THROW ( a_ref.get_Entry ( key ), std::exception );

  key = classifier::GRNN_Data_Types::WINDOWS_PE;
  BOOST_CHECK_THROW ( a_ref.get_Entry ( key ), std::exception );
}

BOOST_AUTO_TEST_CASE(test_duplicate_entry)
{
  classifier::GRNN_Data_Types::Value_Type key = classifier::GRNN_Data_Types::JAVA_CLASS;
  double sigma = 1.0;
  std::string file = "Funky";
  classifier_types::GRNN_Data_Entry::ptr_t entry_ptr ( new classifier::GRNN_Data_Entry ( sigma, file ) );
 
  classifier::GRNN_Data_Map a_ref;
  BOOST_CHECK_EQUAL ( a_ref.insert ( key, entry_ptr ), true );
  BOOST_CHECK_EQUAL ( a_ref.insert ( key, entry_ptr ), false );
}

BOOST_AUTO_TEST_CASE(test_valid_key)
{
  classifier::GRNN_Data_Types::Value_Type key = classifier::GRNN_Data_Types::JAVA_CLASS;
  double sigma = 1.0;
  std::string file = "Funky";
  classifier_types::GRNN_Data_Entry::ptr_t entry_ptr ( new classifier::GRNN_Data_Entry ( sigma, file ) );
 
  classifier::GRNN_Data_Map a_ref;

  BOOST_CHECK_EQUAL ( a_ref.insert ( key, entry_ptr ), true );
}

BOOST_AUTO_TEST_CASE(test_get_entry)
{
  classifier::GRNN_Data_Types::Value_Type key = classifier::GRNN_Data_Types::JAVA_CLASS;
  double sigma = 1.0;
  std::string file = "Funky";
  classifier_types::GRNN_Data_Entry::ptr_t entry_ptr ( new classifier::GRNN_Data_Entry ( sigma, file ) );
 
  classifier::GRNN_Data_Map a_ref;
  BOOST_CHECK_EQUAL ( a_ref.insert ( key, entry_ptr ), true );

  classifier_types::GRNN_Data_Entry::const_ptr_t retrieved_obj = a_ref.get_Entry ( key );
  BOOST_CHECK_EQUAL ( entry_ptr->get_Sigma(), retrieved_obj->get_Sigma() );
  BOOST_CHECK_EQUAL ( entry_ptr->get_Filename(), retrieved_obj->get_Filename() );
}

BOOST_AUTO_TEST_CASE(test_null_object)
{
  classifier::GRNN_Data_Types::Value_Type key = classifier::GRNN_Data_Types::UNKNOWN;
  classifier_types::GRNN_Data_Entry::ptr_t entry_ptr;
 
  classifier::GRNN_Data_Map a_ref;

  BOOST_CHECK_THROW ( a_ref.insert ( key, entry_ptr ), std::exception );
}

BOOST_AUTO_TEST_SUITE_END()
