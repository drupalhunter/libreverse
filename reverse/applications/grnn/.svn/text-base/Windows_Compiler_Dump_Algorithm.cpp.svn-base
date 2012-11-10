/* Windows_Compiler_Dump_Algorithm.cpp

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
#include "Windows_Compiler_Dump_Algorithm.h"

#include "libreverse/data_containers/Data_Types.h"
#include "libreverse/io/IO_Types.h"
#include "libreverse/io/File_ID.h"
#include "libreverse/io/input/File_Readers/Windows_PE/PE_File.h"
#include "libreverse/io/input/File_Readers/Windows_PE/DOS_Header.h"
#include "libreverse/io/input/File_Readers/Windows_PE/Coff_Header.h"
#include "libreverse/io/input/File_Readers/Windows_PE/Header_32.h"
#include "libreverse/io/input/File_Readers/Windows_PE/PE_Optional_Header_32.h"
#include "libreverse/io/input/File_Readers/Windows_PE/PE_Header_32.h"
#include "libreverse/io/input/File_Readers/Windows_PE/Header_64.h"
#include "libreverse/io/input/File_Readers/Windows_PE/PE_Optional_Header_64.h"
#include "libreverse/io/input/File_Readers/Windows_PE/PE_Header_64.h"
#include "libreverse/components/input/grnn/Windows_Training_Data_Parser.h"

#include <sstream>
#include <iostream>
#include <boost/format.hpp>

namespace libreverse {
  namespace optimizer {

    std::string
    Windows_Compiler_Dump_Algorithm::process ( boost::uint32_t compiler_id,
					      std::string filename )
    {
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Compiler_Dump_Algorithm::process" );

      std::stringstream output;

      try
	{
	  libreverse::io_types::File_ID::ptr_t file_obj ( new libreverse::io::File_ID ( filename ) );
	    
	  libreverse::wpef_module::Reader_32 reader32_obj ( file_obj );

	  if ( reader32_obj.support_File_Type() )
	    {
	      output << process_File ( compiler_id, reader32_obj );
	    }
	  else
	    {
	      libreverse::wpef_module::Reader_64 reader64_obj ( file_obj );

	      if ( reader64_obj.support_File_Type() )
		{
		  output << process_File ( compiler_id, reader64_obj );
		}
	    }
	}
      catch ( std::exception &e )
	{
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::ERROR,
			       boost::str ( boost::format("Cannot read %1%. Skipping the file. ") % filename ) );

	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::ERROR,
			       e.what() );
	}

      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Compiler_Dump_Algorithm::process" );

      return output.str();
    }

    std::string
    Windows_Compiler_Dump_Algorithm::process_File ( boost::uint32_t compiler_id, 
						   libreverse::wpef_module::Reader_32& reader32_obj )
    {
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Compiler_Dump_Algorithm::process_File (32-bit)" );

      std::stringstream output;

      reader32_obj.read_Headers();

      libreverse::wpef_types::PE_File::ptr_t file_ptr = reader32_obj.get_File();

      output << boost::format ( "  <%1%>" )
	% classifier::Windows_Input_Tag_Names::TAG_FILE << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_TARGET_ID
	% compiler_id
	% classifier::Windows_Input_Tag_Names::TAG_TARGET_ID << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_FILE_SIZE
	% file_ptr->get_File_Size()
	% classifier::Windows_Input_Tag_Names::TAG_FILE_SIZE << std::endl;

      libreverse::wpef_types::Header_32::ptr_t hdr_ptr = reader32_obj.get_Header();

      // get stats
      //   - DOS (1 items)
      libreverse::wpef_types::DOS_Header::ptr_t dos_ptr = hdr_ptr->get_DOS_Header();

      //     - file address of new exe header (e_lfanew)
      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Windows_Input_Tag_Names::TAG_EXE_HEADER_ADDRESS
	% dos_ptr->get_EXE_Header_Address()
	% classifier::Windows_Input_Tag_Names::TAG_EXE_HEADER_ADDRESS << std::endl;

      //   - PE (23 items)
      libreverse::wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = hdr_ptr->get_PE_Header();

      //     - COFF header
      libreverse::wpef_types::COFF_Header::ptr_t coff_hdr_ptr = pe_hdr_ptr->get_COFF_Header();

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_COFF_SECTION_COUNT
	% coff_hdr_ptr->get_Section_Header_Count ()
	% classifier::Windows_Input_Tag_Names::TAG_COFF_SECTION_COUNT
	     << std::endl;

      //     - Optional header (15)
      libreverse::wpef_types::PE_Optional_Header_32::ptr_t pe_opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      /*
      //       - m_major_linker_version
      //       - m_minor_linker_version
      output << boost::format ( "    <%1%>%2%.%3%</%4%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_LINKER_VERSION
	% static_cast<boost::uint16_t> ( pe_opt_hdr_ptr->get_Major_Linker_Version() )
	% static_cast<boost::uint16_t> ( pe_opt_hdr_ptr->get_Minor_Linker_Version() )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_LINKER_VERSION << std::endl;
      */

      //       - m_size_of_code
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_CODE_SIZE
	% pe_opt_hdr_ptr->get_Size_Of_Code()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_CODE_SIZE << std::endl;

      //       - m_base_of_data
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_BASE_OF_DATA
	% pe_opt_hdr_ptr->get_Base_Of_Data()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_BASE_OF_DATA << std::endl;

      //       - m_addr_of_entry_point
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_ENTRY_POINT
	% pe_opt_hdr_ptr->get_Entry_Point()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_ENTRY_POINT << std::endl;

      //       - m_size_of_image
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_IMAGE_SIZE
	% pe_opt_hdr_ptr->get_Size_Of_Image()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_IMAGE_SIZE << std::endl;

      output << boost::format ( "</%1$s>" ) % classifier::Windows_Input_Tag_Names::TAG_FILE << std::endl;

      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Compiler_Dump_Algorithm::process_File (32-bit)" );

      return output.str();
    }

    std::string
    Windows_Compiler_Dump_Algorithm::process_File ( boost::uint32_t compiler_id, 
						   libreverse::wpef_module::Reader_64& reader64_obj )
    {
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Compiler_Dump_Algorithm::process_File (64-bit)" );

      std::stringstream output;
    
      reader64_obj.read_Headers();

      libreverse::wpef_types::PE_File::ptr_t file_ptr = reader64_obj.get_File();

      output << boost::format ( "  <%1%>" )
	% classifier::Windows_Input_Tag_Names::TAG_FILE
	     << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_TARGET_ID
	% compiler_id
	% classifier::Windows_Input_Tag_Names::TAG_TARGET_ID << std::endl;

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_FILE_SIZE
	% file_ptr->get_File_Size()
	% classifier::Windows_Input_Tag_Names::TAG_FILE_SIZE << std::endl;


      libreverse::wpef_types::Header_64::ptr_t hdr_ptr = reader64_obj.get_Header();

      // get stats
      //   - DOS (2 items)
      libreverse::wpef_types::DOS_Header::ptr_t dos_ptr = hdr_ptr->get_DOS_Header();

      //     - file address of new exe header (e_lfanew)
      output << boost::format ( "    <%1%>%2%</%3%>" ) 
	% classifier::Windows_Input_Tag_Names::TAG_EXE_HEADER_ADDRESS
	% dos_ptr->get_EXE_Header_Address()
	% classifier::Windows_Input_Tag_Names::TAG_EXE_HEADER_ADDRESS << std::endl;

      //   - PE (23 items)
      libreverse::wpef_types::PE_Header_64::const_ptr_t pe_hdr_ptr = hdr_ptr->get_PE_Header();

      //     - entire C
      libreverse::wpef_types::COFF_Header::ptr_t coff_hdr_ptr = pe_hdr_ptr->get_COFF_Header();

      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_COFF_SECTION_COUNT
	% coff_hdr_ptr->get_Section_Header_Count ()
	% classifier::Windows_Input_Tag_Names::TAG_COFF_SECTION_COUNT
	     << std::endl;

      //     - Optional header (15)
      libreverse::wpef_types::PE_Optional_Header_64::ptr_t pe_opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      //       - m_major_linker_version
      //       - m_minor_linker_version
      output << boost::format ( "    <%1%>%2%.%3%</%4%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_LINKER_VERSION
	% static_cast<boost::uint16_t> ( pe_opt_hdr_ptr->get_Major_Linker_Version() )
	% static_cast<boost::uint16_t> ( pe_opt_hdr_ptr->get_Minor_Linker_Version() )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_LINKER_VERSION << std::endl;

      //       - m_size_of_code
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_CODE_SIZE
	% pe_opt_hdr_ptr->get_Size_Of_Code()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_CODE_SIZE << std::endl;

      //       - m_addr_of_entry_point
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_ENTRY_POINT
	% pe_opt_hdr_ptr->get_Entry_Point()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_ENTRY_POINT << std::endl;

      //       - m_size_of_image
      output << boost::format ( "    <%1%>%2%</%3%>" )
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_IMAGE_SIZE
	% pe_opt_hdr_ptr->get_Size_Of_Image()
	% classifier::Windows_Input_Tag_Names::TAG_PE_OPT_IMAGE_SIZE << std::endl;

      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Compiler_Dump_Algorithm::process_File (64-bit)" );

      return output.str();
    }

    void
    Windows_Compiler_Dump_Algorithm::find_Files ( const boost::filesystem::path& dirpath,
						 std::vector<std::string>& output_files )
    {
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Entering Windows_Compiler_Dump_Algorithm::fine_Files" );

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
	      
		  if ( name.find ( ".exe" ) != std::string::npos )
		    {
		      output_files.push_back ( itr->string() );
		    }
		  else if ( name.find ( ".dll" ) != std::string::npos )
		    {
		      output_files.push_back ( itr->string() );
		    }
		}
	    }
	}

      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DETAIL,
			   "Exiting Windows_Compiler_Dump_Algorithm::fine_Files" );
    }

  } /* namespace optimizer */
} /* namespace libreverse */
