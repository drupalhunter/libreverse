/* Elf_Compiler_Dump_Algorithm.cpp

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
#include "Elf_Compiler_Dump_Algorithm.h"

#include "reverse/data_containers/Data_Types.h"
#include "reverse/io/IO_Types.h"
#include "reverse/io/File_ID.h"

#include "reverse/io/input/File_Readers/Elf/Elf_File.h"
#include "reverse/io/input/File_Readers/Elf/Elf_Header_32.h"
#include "reverse/io/input/File_Readers/Elf/Elf_Header_64.h"
#include "reverse/components/input/grnn/Elf_Input_Tag_Names.h"
#include "reverse/io/input/File_Readers/Elf/Elf_Reader_32.h"
#include "reverse/io/input/File_Readers/Elf/Elf_Reader_64.h"

#include <sstream>
#include <iostream>
#include <boost/format.hpp>

namespace reverse {
  namespace optimizer {

    std::string
    Elf_Compiler_Dump_Algorithm::process ( boost::uint32_t compiler_id,
					  std::string filename )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Elf_Compiler_Dump_Algorithm::process" );
#endif /* LIBREVERSE_DEBUG */

      std::stringstream output;

      try
	{
	  reverse::io_types::File_ID::ptr_t file_obj ( new reverse::io::File_ID ( filename ) );
	    
	  reverse::elf_module::Elf_Reader_32 reader32_obj ( file_obj );

	  if ( reader32_obj.support_File_Type() )
	    {
	      output << process_File ( compiler_id, reader32_obj );
	    }
	  else
	    {
	      reverse::elf_module::Elf_Reader_64 reader64_obj ( file_obj );

	      if ( reader64_obj.support_File_Type() )
		{
		  output << process_File ( compiler_id, reader64_obj );
		}
	    }
	}
      catch ( std::exception &e )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::ERROR,
			       boost::str ( boost::format("Cannot read %1%. Skipping the file. ") % filename ) );

	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::ERROR,
			       e.what() );
#endif /* LIBREVERSE_DEBUG */

	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Compiler_Dump_Algorithm::process" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Compiler_Dump_Algorithm::process_File ( boost::uint32_t compiler_id, 
					       reverse::elf_module::Elf_Reader_32& reader32_obj )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Elf_Compiler_Dump_Algorithm::process_File (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      reader32_obj.read_Headers();

      reverse::elf_types::Elf_File::const_ptr_t file_ptr = reader32_obj.get_File();
      reverse::elf_types::Elf_Header_32::ptr_t hdr_ptr = reader32_obj.get_Header();
      reverse::elf_types::Elf_File_Header_32::const_ptr_t file_hdr_ptr = hdr_ptr->get_File_Header();

      output << boost::format ( "  <%1%>" )
	% classifier::Elf_Input_Tag_Names::TAG_FILE << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Elf_Input_Tag_Names::TAG_TARGET_ID
	% compiler_id
	% classifier::Elf_Input_Tag_Names::TAG_TARGET_ID << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_FILESIZE
	% file_ptr->size()
	% classifier::Elf_Input_Tag_Names::TAG_FILESIZE << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Elf_Input_Tag_Names::TAG_ENTRY_POINT_ADDRESS
	% file_hdr_ptr->get_Entry()
	% classifier::Elf_Input_Tag_Names::TAG_ENTRY_POINT_ADDRESS << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADERS_START
	% file_hdr_ptr->get_Section_Header_Offset()
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADERS_START << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_PROGRAM_HEADER_COUNT
	% file_hdr_ptr->get_Program_Header_Count()
	% classifier::Elf_Input_Tag_Names::TAG_PROGRAM_HEADER_COUNT << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_COUNT
	% file_hdr_ptr->get_Section_Header_Count()
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_COUNT << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_STRING_TABLE_INDEX
	% file_hdr_ptr->get_String_Token_Index()
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_STRING_TABLE_INDEX << std::endl;

      elf_types::Elf_Section_Header_32::const_ptr_t sec_ptr = hdr_ptr->get_Section_Header ( ".text" );

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_TEXT_SECTION_SIZE
	% sec_ptr->get_Section_Size()
	% classifier::Elf_Input_Tag_Names::TAG_TEXT_SECTION_SIZE << std::endl;

      output << boost::format ( "  </%1%>" )
	% classifier::Elf_Input_Tag_Names::TAG_FILE << std::endl;

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Compiler_Dump_Algorithm::process_File (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Compiler_Dump_Algorithm::process_File ( boost::uint32_t compiler_id, 
					       reverse::elf_module::Elf_Reader_64& reader64_obj )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Elf_Compiler_Dump_Algorithm::process_File (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;
    
      reader64_obj.read_Headers();

      reverse::data_types::memory_map::ptr_t memory_ptr = reader64_obj.get_memory_map();
      reverse::elf_types::Elf_Header_64::ptr_t hdr_ptr = reader64_obj.get_Header();
      reverse::elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = hdr_ptr->get_File_Header();

      output << boost::format ( "  <%1%>" )
	% classifier::Elf_Input_Tag_Names::TAG_FILE << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Elf_Input_Tag_Names::TAG_TARGET_ID
	% compiler_id
	% classifier::Elf_Input_Tag_Names::TAG_TARGET_ID << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_FILESIZE
	% memory_ptr->size()
	% classifier::Elf_Input_Tag_Names::TAG_FILESIZE << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Elf_Input_Tag_Names::TAG_ENTRY_POINT_ADDRESS
	% file_hdr_ptr->get_Entry()
	% classifier::Elf_Input_Tag_Names::TAG_ENTRY_POINT_ADDRESS << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADERS_START
	% file_hdr_ptr->get_Section_Header_Offset()
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADERS_START << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_PROGRAM_HEADER_COUNT
	% file_hdr_ptr->get_Program_Header_Count()
	% classifier::Elf_Input_Tag_Names::TAG_PROGRAM_HEADER_COUNT << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_COUNT
	% file_hdr_ptr->get_Section_Header_Count()
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_COUNT << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_STRING_TABLE_INDEX
	% file_hdr_ptr->get_String_Token_Index()
	% classifier::Elf_Input_Tag_Names::TAG_SECTION_HEADER_STRING_TABLE_INDEX << std::endl;

      elf_types::Elf_Section_Header_64::const_ptr_t sec_ptr = hdr_ptr->get_Section_Header ( ".text" );

      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Elf_Input_Tag_Names::TAG_TEXT_SECTION_SIZE
	% sec_ptr->get_Section_Size()
	% classifier::Elf_Input_Tag_Names::TAG_TEXT_SECTION_SIZE << std::endl;

      output << boost::format ( "  </%1%>" )
	% classifier::Elf_Input_Tag_Names::TAG_FILE << std::endl;

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Compiler_Dump_Algorithm::process_File (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    void
    Elf_Compiler_Dump_Algorithm::find_Files ( const boost::filesystem::path& dirpath,
					     std::vector<std::string>& output_files )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Elf_Compiler_Dump_Algorithm::find_Files" );
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

		  output_files.push_back ( itr->string() );
		}
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Compiler_Dump_Algorithm::find_Files" );
#endif /* LIBREVERSE_DEBUG */

    }

  } /* namespace optimizer */
} /* namespace reverse */
