/*  Statistical_Test.cpp

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
#include "Statistical_Test.h"
#include "Statistical.h"
#include "Windows_Training_Data.h"

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#ifdef LIBREVERSE_DEBUG
#include <Reverse.h>
#include <Trace.h>
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

namespace libreverse
{
  namespace classifier
  {

    void
    Statistical_Test::test_Constructor ( void )
    {
      classifier_types::Training_Set<Windows_Training_Data>::Data_List_t training;
      classifier_types::Configuration<Windows_Training_Data>::ptr_t config;
      BOOST_CHECK_THROW ( Statistical<Windows_Training_Data> s_ref ( 0.5, training, config ),
			  std::exception );

      config.reset ( new classifier::Configuration<Windows_Training_Data>() );
      BOOST_CHECK_THROW ( Statistical<Windows_Training_Data> t_ref ( 0.5, training, config ),
			  std::exception );

      classifier_types::Training_Data<Windows_Training_Data>::ptr_t tmp_ptr ( new classifier::Training_Data<Windows_Training_Data>() );
      training.push_back ( tmp_ptr );

      Statistical<Windows_Training_Data> u_ref ( 0.5, training, config );
      BOOST_REQUIRE( u_ref.m_sigma == 0.5 );
      BOOST_REQUIRE( u_ref.m_mean_distance_squared == 0.0 );
      BOOST_REQUIRE( u_ref.m_column_sum.size() == 0 );
      BOOST_REQUIRE( u_ref.m_column_avg.size() == 0 );
      BOOST_REQUIRE( u_ref.m_column_var.size() == 0 );
      BOOST_REQUIRE( u_ref.m_column_stdev.size() == 0 );
      BOOST_REQUIRE( u_ref.m_column_lb.size() == 0 );
      BOOST_REQUIRE( u_ref.m_column_ub.size() == 0 );
      BOOST_REQUIRE( u_ref.m_training.size() == 1 );
    }

    void
    Statistical_Test::test_Column_Totals ( void )
    {
      this->populate_PE_Training();

      classifier_types::Configuration<Windows_Training_Data>::ptr_t config ( new classifier::Configuration<Windows_Training_Data>() );
      Statistical<Windows_Training_Data> s_ref ( 0.5, m_pe_training, config );

#ifdef LIBREVERSE_DEBUG
      Trace_State::Instance().set_Trace_File_Name ( "test_Column_Totals.txt" );
      Trace_State::Instance().set_Trace_Level ( TraceLevel::DATA );
      Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::GRNN );
      Trace_State::Instance().open_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

      s_ref.calculate_Column_Totals();

#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().close_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

      // Check totals for compiler #0
      Statistical<Windows_Training_Data>::Compiler_Map_t::const_iterator cpos = s_ref.m_column_sum.find ( 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] == 1765376 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == 768 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 30 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] == 1677824 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] == 1716224 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] == 24576 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] == 1961984 );

      // Check totals for compiler #1
      cpos = s_ref.m_column_sum.find ( 1 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] == 76800 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == 1336 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 18 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] == 38912 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] == 73728 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] == 55559 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] == 139264 );

      // Check totals for compiler #2
      cpos = s_ref.m_column_sum.find ( 2 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] == 252416 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == 1400 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 26 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] == 148480 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] == 184320 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] == 109424 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] == 323584 );
    }

    void
    Statistical_Test::test_Column_Averages ( void )
    {
      classifier_types::Configuration<Windows_Training_Data>::ptr_t config ( new classifier::Configuration<Windows_Training_Data>() );
      Statistical<Windows_Training_Data> s_ref ( 0.5, m_pe_training, config );

      s_ref.calculate_Column_Totals();

#ifdef LIBREVERSE_DEBUG
      Trace_State::Instance().set_Trace_File_Name ( "test_Column_Averages.txt" );
      Trace_State::Instance().set_Trace_Level ( TraceLevel::DATA );
      Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::GRNN );
      Trace_State::Instance().open_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

      s_ref.calculate_Column_Averages();

      double filesize_average = static_cast<double>(1765376) / static_cast<double>(6);

      // Check totals for compiler #0
      Statistical<Windows_Training_Data>::Compiler_Map_t::const_iterator cpos = s_ref.m_column_avg.find ( 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Calculated filesize average: %1$1.15f" ) % filesize_average ) );
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Actual filesize variance: %1$1.15f" )
					% ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] ) );
#endif /* LIBREVERSE_DEBUG */
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] == filesize_average );

      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == 128 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 5 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] ==
		      ( static_cast<double>(1677824) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] ==
		      ( static_cast<double>(1716224) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] ==
		      ( static_cast<double>(24576) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] ==
		      ( static_cast<double>(1961984) / static_cast<double>(6) ) );

      // Check totals for compiler #1
      cpos = s_ref.m_column_avg.find ( 1 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] ==
		      ( static_cast<double>(76800) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] ==
		      ( static_cast<double>(1336) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 3 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] ==
		      ( static_cast<double>(38912) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] ==
		      ( static_cast<double>(73728) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] ==
		      ( static_cast<double>(55559) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] ==
		      ( static_cast<double>(139264) / static_cast<double>(6) ) );

      // Check totals for compiler #2
      cpos = s_ref.m_column_avg.find ( 2 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] ==
		      ( static_cast<double>(252416) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] ==
		      ( static_cast<double>(1400) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] ==
		      ( static_cast<double>(26) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] ==
		      ( static_cast<double>(148480) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] ==
		      ( static_cast<double>(184320) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] ==
		      ( static_cast<double>(109424) / static_cast<double>(6) ) );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] ==
		      ( static_cast<double>(323584) / static_cast<double>(6) ) );

#ifdef LIBREVERSE_DEBUG
      Trace_State::Instance().close_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Statistical_Test::test_Column_Standard_Deviations ( void )
    {
      classifier_types::Configuration<Windows_Training_Data>::ptr_t config ( new classifier::Configuration<Windows_Training_Data>() );
      Statistical<Windows_Training_Data> s_ref ( 0.5, m_pe_training, config );

      s_ref.calculate_Column_Totals();
      s_ref.calculate_Column_Averages();

#ifdef LIBREVERSE_DEBUG
      Trace_State::Instance().set_Trace_File_Name ( "test_Column_Standard_Deviations.txt" );
      Trace_State::Instance().set_Trace_Level ( TraceLevel::DATA );
      Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::GRNN );
      Trace_State::Instance().open_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

      s_ref.calculate_Column_Variances();
      s_ref.calculate_Column_Standard_Deviations();

      this->test_Column_Standard_Deviations_Compiler_Zero ( s_ref );
      this->test_Column_Standard_Deviations_Compiler_One ( s_ref );
      this->test_Column_Standard_Deviations_Compiler_Two ( s_ref );

#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().close_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Statistical_Test::test_Column_Standard_Deviations_Compiler_Zero ( Statistical<Windows_Training_Data> const& s_ref )
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DETAIL,
			   "Entering Statistical_Test::test_Column_Standard_Deviations_Compiler_Zero" );
#endif /* LIBREVERSE_DEBUG */

      double count = 6.0;
      double average_filesize = static_cast<double>(1765376) / count;

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Test average filesize: %1$1.15f" ) % average_filesize ) );
#endif /* LIBREVERSE_DEBUG */


      double average_pe_opt_code_size = static_cast<double>(1677824) / count;
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Test average pe opt code size: %1$1.15f" ) % average_pe_opt_code_size ) );
#endif /* LIBREVERSE_DEBUG */

      double average_pe_opt_base_of_data = static_cast<double>(1716224) / count;
      double average_pe_opt_image_size = static_cast<double>(1961984) / count;

      double filesize_numerator
	(
	 pow ( static_cast<double>(277504) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(278528) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(311808) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(297984) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(300032) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(299520) - average_filesize, static_cast<double>(2.0) ) );
      double filesize_variance = filesize_numerator / count;

      double pe_opt_code_size_variance = 
	(
	 pow ( static_cast<double>(263168) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(264704) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(296448) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(283648) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(285184) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(284672) - average_pe_opt_code_size, static_cast<double>(2.0) ) ) / count;

      double pe_opt_base_of_data_variance =
	(
	 pow ( static_cast<double>(270336) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(270336) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(303104) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(290816) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(290816) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(290816) - average_pe_opt_base_of_data, static_cast<double>(2.0) )
	 ) / count;

      double pe_opt_image_size_variance =
	(
	 pow ( static_cast<double>(311296) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(311296) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(344064) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(331776) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(331776) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(331776) - average_pe_opt_image_size, static_cast<double>(2.0) )
	 ) / count;

      // Check totals for compiler #0
      Statistical<Windows_Training_Data>::Compiler_Map_t::const_iterator cpos = s_ref.m_column_var.find ( 0 );
      Statistical<Windows_Training_Data>::Compiler_Map_t::const_iterator stdev_pos = s_ref.m_column_stdev.find ( 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );

      BOOST_CHECK_CLOSE ( filesize_variance,
			  ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE],
			  0.00000001 );
      BOOST_CHECK_CLOSE ( sqrt(filesize_variance),
			  ((*stdev_pos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE],
			  0.00000001 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == 0.0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 0.0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] == pe_opt_code_size_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] == pe_opt_base_of_data_variance );
      BOOST_REQUIRE ( sqrt(pe_opt_base_of_data_variance) == ((*stdev_pos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] == 0.0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] == pe_opt_image_size_variance );
      BOOST_REQUIRE ( sqrt(pe_opt_image_size_variance) == ((*stdev_pos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DETAIL,
			   "Exiting Statistical_Test::test_Column_Standard_Deviations_Compiler_Zero" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Statistical_Test::test_Column_Standard_Deviations_Compiler_One ( Statistical<Windows_Training_Data> const& s_ref )
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DETAIL,
			   "Entering Statistical_Test::test_Column_Standard_Deviations_Compiler_One" );
#endif /* LIBREVERSE_DEBUG */

      double count = 6.0;
      double average_filesize = static_cast<double>(76800) / count;
      double average_exe_header_address = static_cast<double>(1336) / count;
      double average_pe_opt_code_size = static_cast<double>(38912) / count;
      double average_pe_opt_base_of_data = static_cast<double>(73728) / count;
      double average_pe_opt_entry_point = static_cast<double>(55559) / count;
      double average_pe_opt_image_size = static_cast<double>(139264) / count;

      double filesize_variance =
	(
	 pow ( static_cast<double>(5120) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(6144) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(22016) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(13824) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(14848) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(14848) - average_filesize, static_cast<double>(2.0) ) ) / count;

      double exe_header_address_variance =
	(
	 pow ( static_cast<double>(232) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(224) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(224) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(216) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(224) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(216) - average_exe_header_address, static_cast<double>(2.0) ) ) / count;

      double pe_opt_code_size_variance = 
	(
	 pow ( static_cast<double>(1536) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(2560) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(13312) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(7168) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(7168) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(7168) - average_pe_opt_code_size, static_cast<double>(2.0) )
	 ) / count;

      double pe_opt_base_of_data_variance =
	(
	 pow ( static_cast<double>(8192) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(8192) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(20480) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(12288) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(12288) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(12288) - average_pe_opt_base_of_data, static_cast<double>(2.0) )
	 ) / count;

      double pe_opt_entry_point_variance = 
	(
	 pow ( static_cast<double>(4355) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(5792) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(16029) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(9805) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(9773) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(9805) - average_pe_opt_entry_point, static_cast<double>(2.0) )
	 ) / count;

      double pe_opt_image_size_variance =
	(
	 pow ( static_cast<double>(16384) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(16384) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(32768) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(24576) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(24576) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(24576) - average_pe_opt_image_size, static_cast<double>(2.0) )
	 ) / count;

      // Check totals for compiler #1
      Statistical<Windows_Training_Data>::Compiler_Map_t::const_iterator cpos = s_ref.m_column_var.find ( 1 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE] == filesize_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == exe_header_address_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == 0.0 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] == pe_opt_code_size_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] == pe_opt_base_of_data_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] == pe_opt_entry_point_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] == pe_opt_image_size_variance );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DETAIL,
			   "Exiting Statistical_Test::test_Column_Standard_Deviations_Compiler_One" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Statistical_Test::test_Column_Standard_Deviations_Compiler_Two ( Statistical<Windows_Training_Data> const& s_ref )
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DETAIL,
			   "Entering Statistical_Test::test_Column_Standard_Deviations_Compiler_Two" );
#endif /* LIBREVERSE_DEBUG */

      double count = 6.0;
      double average_filesize = static_cast<double>(252416) / count;

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Test average filesize: %1$1.15f" ) % average_filesize ) );
#endif /* LIBREVERSE_DEBUG */


      double average_exe_header_address = static_cast<double>(1400) / count;
      double average_coff_section_count = static_cast<double>(26) / count;
      double average_pe_opt_code_size = static_cast<double>(148480) / count;
      double average_pe_opt_base_of_data = static_cast<double>(184320) / count;
      double average_pe_opt_entry_point = static_cast<double>(109424) / count;
      double average_pe_opt_image_size = static_cast<double>(323584) / count;

      double filesize_numerator =
	(
	 pow ( static_cast<double>(18432) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(40960) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(40448) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(81920) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(41984) - average_filesize, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(28672) - average_filesize, static_cast<double>(2.0) ) );
      double filesize_variance = filesize_numerator / count;

      double exe_header_address_variance =
	(
	 pow ( static_cast<double>(216) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(232) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(240) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(232) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(248) - average_exe_header_address, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(232) - average_exe_header_address, static_cast<double>(2.0) ) ) / count;

      double coff_section_count_variance =
	(
	 pow ( static_cast<double>(4) - average_coff_section_count, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(5) - average_coff_section_count, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(4) - average_coff_section_count, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(5) - average_coff_section_count, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(4) - average_coff_section_count, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(4) - average_coff_section_count, static_cast<double>(2.0) ) ) / count;

      double pe_opt_code_size_variance = 
	(
	 pow ( static_cast<double>(9216) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(23040) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(27648) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(45056) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(26624) - average_pe_opt_code_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(16896) - average_pe_opt_code_size, static_cast<double>(2.0) )
	 ) / count;

      double pe_opt_base_of_data_variance =
	(
	 pow ( static_cast<double>(16384) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(28672) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(32768) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(49152) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(32768) - average_pe_opt_base_of_data, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(24576) - average_pe_opt_base_of_data, static_cast<double>(2.0) )
	 ) / count;

      double pe_opt_entry_point_numerator = 
	(
	 pow ( static_cast<double>(6976) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(12864) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(26096) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(27360) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(22560) - average_pe_opt_entry_point, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(13568) - average_pe_opt_entry_point, static_cast<double>(2.0) ) );

      double pe_opt_entry_point_variance = pe_opt_entry_point_numerator / count;

      double pe_opt_image_size_variance =
	(
	 pow ( static_cast<double>(32768) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(53248) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(53248) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(81920) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(57344) - average_pe_opt_image_size, static_cast<double>(2.0) ) +
	 pow ( static_cast<double>(45056) - average_pe_opt_image_size, static_cast<double>(2.0) )
	 ) / count;

      // Check totals for compiler #1
      Statistical<Windows_Training_Data>::Compiler_Map_t::const_iterator cpos = s_ref.m_column_var.find ( 2 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COMPILER_ID] == 0 );

      BOOST_CHECK_CLOSE ( filesize_variance,
			  ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_FILESIZE],
			  0.00000001 );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS] == exe_header_address_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT] == coff_section_count_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE] == pe_opt_code_size_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA] == pe_opt_base_of_data_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT] == pe_opt_entry_point_variance );
      BOOST_REQUIRE ( ((*cpos).second)[Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE] == pe_opt_image_size_variance );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN,
			   TraceLevel::DETAIL,
			   "Exiting Statistical_Test::test_Column_Standard_Deviations_Compiler_Two" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Statistical_Test::populate_PE_Training ( void )
    {
      /*-------------------------*/
      /*     CYGWIN EXAMPLE      */
      /*-------------------------*/

      // garrjon1.exe
      classifier_types::Training_Data<Windows_Training_Data>::ptr_t tmp_ptr ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 0 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 277504 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 128 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 263168 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 270336 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 4096 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 311296 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon2.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 0 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 278528 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 128 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 264704 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 270336 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 4096 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 311296 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon3.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 0 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 311808 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 128 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 296448 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 303104 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 4096 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 344064 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon4.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 0 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 297984 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 128 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 283648 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 290816 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 4096 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 331776 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon5.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 0 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 300032 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 128 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 285184 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 290816 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 4096 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 331776 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon6.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 0 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 299520 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 128 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 284672 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 290816 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 4096 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 331776 );
      m_pe_training.push_back ( tmp_ptr );

      /*-------------------------*/
      /*     VS2003 EXAMPLE      */
      /*-------------------------*/

      // garrjon1.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 1 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 5120 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x3 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x600 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x2000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x1103 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x4000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon2.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 1 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 6144 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x3 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0xA00 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x2000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x16A0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x4000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon3.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 1 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 22016 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x3 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x3400 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x5000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x3E9D );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x8000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon4.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 1 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 13824 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xD8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x3 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x1C00 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x3000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x264D );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x6000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon5.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 1 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 14848 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x3 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x1C00 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x3000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x262D );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x6000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon6.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 1 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 14848 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xD8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x3 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x1C00 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x3000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x264D );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x6000 );
      m_pe_training.push_back ( tmp_ptr );

      /*-------------------------*/
      /*     VS2005 EXAMPLE      */
      /*-------------------------*/

      // garrjon1.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 2 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 18432 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xD8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x4 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x2400 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x4000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x1B40 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x8000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon2.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 2 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 40960 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x5A00 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x7000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x3240 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0xD000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon3.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 2 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 40448 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xF0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x4 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x6C00 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x8000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x65F0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0xD000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon4.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 2 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 81920 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x5 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0xB000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0xC000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x6AE0 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0x14000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon5.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 2 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 41984 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xF8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x4 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x6800 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x8000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x5820 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0xE000 );
      m_pe_training.push_back ( tmp_ptr );

      // garrjon6.exe
      tmp_ptr.reset ( new classifier::Training_Data<Windows_Training_Data>() );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COMPILER_ID, 2 ); 
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_FILESIZE, 28672 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_EXE_HEADER_ADDRESS, 0xE8 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_COFF_SECTION_COUNT, 0x4 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_CODE_SIZE, 0x4200 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_BASE_OF_DATA, 0x6000 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_ENTRY_POINT, 0x3500 );
      tmp_ptr->set_Attribute ( Windows_Training_Data::ATTRIBUTE_PE_OPT_IMAGE_SIZE, 0xB000 );
      m_pe_training.push_back ( tmp_ptr );
    }

  } /* namespace classifier */
} /* namespace libreverse */
