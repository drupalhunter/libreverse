/* Java_Compiler_Dump_Algorithm.h

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
#include "Java_Compiler_Dump_Algorithm.h"

#include "libreverse/components/input/grnn/Java_Training_Data_Parser.h"
#include "libreverse/io/IO_Types.h"
#include "libreverse/io/File_ID.h"
#include "libreverse/io/input/File_Readers/Java_Class/Reader.h"
#include "libreverse/io/input/File_Readers/Java_Class/Class_Header.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Pool_Info.h"
#include "libreverse/data_containers/memory_map.h"

#include <boost/format.hpp>
#include <sstream>
#include <iostream>

#include <libreverse/Reverse.h>

#ifdef LIBREVERSE_DEBUG
#include <libreverse/Trace.h>
using namespace libreverse::trace;
using namespace libreverse::api;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse {
  namespace optimizer {

    std::string
    Java_Compiler_Dump_Algorithm::process ( boost::uint32_t compiler_id,
					   std::string filename )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Java_Compiler_Dump_Algorithm::process" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      try
	{
	  libreverse::io_types::File_ID::ptr_t file_obj ( new libreverse::io::File_ID ( filename ) );
	    
	  libreverse::java_module::Reader r_obj ( file_obj );
	    
	  r_obj.read_Class_Header();

	  libreverse::data_types::memory_map::ptr_t mem_ptr = r_obj.get_memory_map();

	  output << boost::format("  <%1%>") % classifier::Java_Input_Tag_Names::TAG_FILE << std::endl;

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_TARGET_ID
	    % compiler_id
	    % classifier::Java_Input_Tag_Names::TAG_TARGET_ID << std::endl;

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_FILESIZE
	    % ( mem_ptr->size() )
	    % classifier::Java_Input_Tag_Names::TAG_FILESIZE << std::endl;

	  //   Get class header
	  libreverse::java_types::Class_Header::ptr_t hdr_ptr = r_obj.get_Header();

	  //   Grab data
	  std::vector<float> stats(12,0);
	  collect_Constant_Pool_Stats ( stats, hdr_ptr->get_Constant_Pool_Begin(), hdr_ptr->get_Constant_Pool_End() );

	  //   Add entry to output file
	  output << boost::format ( "    <%1%>%2%.%3%</%4%>" )
	    % classifier::Java_Input_Tag_Names::TAG_VERSION
	    % hdr_ptr->get_Major_Version()
	    % hdr_ptr->get_Minor_Version()
	    % classifier::Java_Input_Tag_Names::TAG_VERSION << std::endl;

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_THIS_INDEX
	    % hdr_ptr->get_This_Class()
	    % classifier::Java_Input_Tag_Names::TAG_THIS_INDEX << std::endl;

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_SUPER_INDEX
	    % hdr_ptr->get_Super_Class()
	    % classifier::Java_Input_Tag_Names::TAG_SUPER_INDEX << std::endl;

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_CONSTANT_POOL_COUNT
	    % hdr_ptr->get_Constant_Pool_Count()
	    % classifier::Java_Input_Tag_Names::TAG_CONSTANT_POOL_COUNT << std::endl;

	  float constant_pool_total = hdr_ptr->get_Constant_Pool_Count();
	  print_Constant_Pool_Stats ( output, stats, constant_pool_total );

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_FIELD_COUNT
            % hdr_ptr->get_Field_Count()
	    % classifier::Java_Input_Tag_Names::TAG_FIELD_COUNT << std::endl;

	  output << boost::format ( "    <%1%>%2%</%3%>" )
	    % classifier::Java_Input_Tag_Names::TAG_METHOD_COUNT
            % hdr_ptr->get_Method_Count()
	    % classifier::Java_Input_Tag_Names::TAG_METHOD_COUNT << std::endl;

	  output << boost::format("  </%1%>" ) % classifier::Java_Input_Tag_Names::TAG_FILE << std::endl;
	}
      catch ( std::exception &e )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::ERROR,
			       boost::str ( boost::format("(ERROR) Cannot read %1%. Skipping the file. ") % filename ) );

	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::ERROR,
			       e.what() );
#endif /* LIBREVERSE_DEBUG */

	}

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Compiler_Dump_Algorithm::process" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    void
    Java_Compiler_Dump_Algorithm::collect_Constant_Pool_Stats
    ( std::vector<float>& stats,
      libreverse::java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pool_start,
      libreverse::java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pool_end )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Java_Compiler_Dump_Algorithm::collect_Constant_Pool_Stats" );
#endif /* LIBREVERSE_DEBUG */


      for ( libreverse::java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pos = pool_start;
	    pos != pool_end;
	    ++pos )
	{
	  boost::uint16_t index = (*pos).second->get_Tag();
	  ( stats.at(index-1) )++;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Compiler_Dump_Algorithm::collect_Constant_Pool_Stats" );
#endif /* LIBREVERSE_DEBUG */

    }
    
    void
    Java_Compiler_Dump_Algorithm::print_Constant_Pool_Stats ( std::stringstream& output,
							     std::vector<float>& stats,
							     float constant_pool_total )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Java_Compiler_Dump_Algorithm::print_Constant_Pool_Stats" );
#endif /* LIBREVERSE_DEBUG */


      for ( std::vector<float>::const_iterator pos = stats.begin();
	    pos != stats.end();
	    ++pos )
	{
	  output << boost::format ("    <%1$s tag=\"%2$d\" count=\"%3$d\" ratio=\"%4$3.2f\"/>")
	    % classifier::Java_Input_Tag_Names::TAG_CONSTANT_POOL_INFO
	    % ( pos - stats.begin() + 1)
	    % (*pos)
	    % ( (*pos) / constant_pool_total * 100 ) << std::endl;
	}

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Compiler_Dump_Algorithm::print_Constant_Pool_Stats" );
#endif /* LIBREVERSE_DEBUG */

    }


    void
    Java_Compiler_Dump_Algorithm::find_Files ( const boost::filesystem::path& dirpath,
					      std::vector<std::string>& output_files )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Java_Compiler_Dump_Algorithm::find_Files" );
#endif /* LIBREVERSE_DEBUG */


      if ( exists ( dirpath ) )
	{
	  boost::filesystem::directory_iterator end_itr; // default construction yields past the end

	  for ( boost::filesystem::directory_iterator itr ( dirpath );
		itr != end_itr;
		++itr )
	    {
	      if ( is_directory ( *itr ) )
		{
		  find_Files ( *itr, output_files );
		}
	      else
		{
		  std::string name = itr->leaf();
	      
		  if ( name.find ( ".class" ) != std::string::npos )
		    {
		      output_files.push_back ( itr->string() );
		    }
		}
	    }
	}

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Compiler_Dump_Algorithm::find_Files" );
#endif /* LIBREVERSE_DEBUG */

    }

  } /* namespace optimizer */
} /* namespace libreverse */
