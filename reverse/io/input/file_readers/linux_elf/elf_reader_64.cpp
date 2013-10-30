/*  Elf_Reader_64.cpp

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

/*
  Code for most of this file was obtained from the GNU Binutils
  readelf.c file. Below is the copyright for the original code. The
  original code was used as a inspiration on how to design an Elf
  file reader. I give full credit of this excellent set of code to
  the original developers. Thanks for the hard work.

  Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

  Originally developed by Eric Youngdale <eric@andante.jic.com>
  Modifications by Nick Clifton <nickc@redhat.com>

  This file is part of GNU Binutils.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
*/

#include <reverse/io/input/file_readers/linux_elf/elf_reader_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_file_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_parser.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_file_header_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_section_header_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_symbol_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_meta_info.hpp>
#include <reverse/io/file_id.hpp>

#include <reverse/data_containers/memory_map.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/errors/parsing_exception.hpp>

#include <reverse/trace.hpp>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/make_shared.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  elf_reader_64::elf_reader_64 ( boost::shared_ptr < const io::file_id > target_file )
	    : m_filename ( target_file ),
	      m_supported ( false )
	  {
	    trace::io_detail ( "Inside Elf_Reader constructor" );
	  }

	  elf_reader_64::~elf_reader_64 ( void )
	  {
	    trace::io_detail ( "Inside Elf_Reader destructor" );
	  }

	  bool
	  elf_reader_64::support_file_type ( void )
	  {
	    trace::io_detail ( "inside elf_reader_64::support_file_type" );

	    return m_supported;
	  }

	  void elf_reader_64::read_headers ( void )
	  {
	    trace::io_detail ( "Entering elf_reader_64::read_headers" );

	    // Create the file mapping
	    boost::interprocess::file_mapping fm ( m_filename->get_full_name().c_str(), boost::interprocess::read_only );
    
	    // Map the file in memory
	    boost::interprocess::mapped_region region ( fm, boost::interprocess::read_only );
    
	    // Get the start address of the file in memory
	    char const* iter = reinterpret_cast<const char*> ( region.get_address() );
	    char const* end = iter + region.get_size();
    
	    // Parse the file_hdr
	    elf_parser parser;

	    m_supported = parser.read ( iter, end, m_elf_file );

	    if ( ! m_supported )
	      {
		throw errors::parsing_exception ( errors::parsing_exception::unknown_parsing_error );
	      }
    
	    // \todo Dump elf header
	    //trace::io_data ( "Elf Header dump: \n%1%", new_file_hdr->to_string() );

	    trace::io_detail ( "Exiting elf_reader_64::read_file_header" );
	  }


	  std::string
	  elf_reader_64::get_file_type ( void )
	  {
	    trace::io_detail ( "entering elf_reader_64::get_file_type" );

	    std::string result = elf_meta_info::file_type_64bit;

	    return result;
	  }


	  boost::shared_ptr < data_containers::memory_map > 
	  elf_reader_64::get_memory_map ( void )
	  {
	    trace::io_detail ( "entering elf_reader_64::get_memory_map" );

	    // Get base address of the image
	    Elf64_Addr base_address = m_elf_file.program_headers[0].p_vaddr;
	    Elf64_Addr highest_memory_address = 0 ;
	    Elf64_Word highest_memory_size = 0;
	    
	    for ( std::vector < elf_program_header_64 >::const_iterator cpos = m_elf_file.program_headers.begin();
		  cpos != m_elf_file.program_headers.end();
		  cpos++ )
	      {
		if ( (*cpos).p_type == elf_common::PT_LOAD )
		  {
		    highest_memory_address = (*cpos).p_vaddr;
		    highest_memory_size = (*cpos).p_memsz;
		  }
		else if ( ( (*cpos).p_vaddr < base_address ) && ( (*cpos).p_vaddr != 0 ) )
		  {
		    base_address = (*cpos).p_vaddr;
		  }
		else if ( ( (*cpos).p_vaddr > highest_memory_address ) &&
			  ( (*cpos).p_vaddr != 0 ) &&
			  ( (*cpos).p_type == elf_common::PT_LOAD ) )
		  {
		    highest_memory_address = (*cpos).p_vaddr;
		    highest_memory_size = (*cpos).p_memsz;
		  }
		else
		  {
		    // Do nothing
		  }
	      }

	    boost::uint32_t size = ( highest_memory_address + highest_memory_size ) - base_address;

	    trace::io_data ( "elf_reader_64::get_memory_map - base_address = 0x%1$-08x (0x%2$-08x)",
			     base_address,
			     size );

	    boost::shared_ptr < data_containers::memory_map > result =
	      boost::make_shared < data_containers::memory_map > ( size, base_address );

	    // Steps to load elf
	    /* 1. Build process image by loading all the sections.

	       The program header table tells the system how to create a
	       process image. Files used to build a process image (execute
	       a program) must have a program header table. A section
	       header table contains information describing the file's
	       sections. Every section has an entry in the table; each
	       entry gives information such as the section name, the
	       section size, etc. Files used during linking must have a
	       section header table.

	       A process image has segments that hold its text, data,
	       stack, and so on. The major sections in this part discuss
	       the following:

	       - Program header. This section complements Part 1,
	       describing object file structures that relate directly to
	       program execution. The primary data structure, a program
	       header table, locates segment images within the file and
	       contains other information necessary to create the memory
	       image for the program.

	       - Program loading. Given an object file, the system must
	       load it into memory for the program to run.

	       - Dynamic linking. After the system loads the program, it
	       must complete the process image by resolving symbolic
	       references among the object files that compose the process.

	       NOTE: We ignore using the dynamic section since we are
	       always loaded the image at its desired location in a
	       Memory Map.

	       ALGORITHM:

	       FOR all x:Elf_Program_Headers
	       IF x.p_type != LOAD THEN skip
	    */
	    Elf64_Half const elf_type = m_elf_file.elf_file_header.e_type;

	    if ( elf_type != elf_common::ET_EXEC ) {
	      // ERROR
	    }
	    /* 2. Perform relocations */

	    /* (QUESTION?)3. Perform dynamic linking */

	    trace::io_detail ( "exiting elf_reader_64::get_memory_map" );

	    return result;
	  }



	  std::string
	  elf_reader_64::get_section_string ( std::string name ) const
	  {

	    std::string output;

// #ifdef LIBREVERSE_DEBUG
// 	    Trace::write_Trace ( TraceArea::IO,
// 				 TraceLevel::DETAIL,
// 				 "Entering Elf_Reader_64::get_Section_String" );
// #endif /* LIBREVERSE_DEBUG */


// 	    std::string output = name;

// 	    if ( name.compare ( ".code" ) == 0 ) {
// 	      output = ".text";
// 	    }


// #ifdef LIBREVERSE_DEBUG
// 	    Trace::write_Trace ( TraceArea::IO,
// 				 TraceLevel::DETAIL,
// 				 "Exiting Elf_Reader_64::get_Section_String" );
// #endif /* LIBREVERSE_DEBUG */


	    return output;
	  }

	  std::string
	  elf_reader_64::to_string ( void )
	  {
	    trace::io_detail ( "entering elf_reader_64::to_string" );

	    std::string output;

	    // \todo Add Karma generator to turn elf_file_32 into text output
// 	    std::string result = m_elf_data->to_String();

	    trace::io_detail ( "exiting elf_reader_64::to_string" );

	    return output;
	  }

	  std::vector < std::string > 
	  elf_reader_64::get_text_strings ( void )
	  {

	    trace::io_detail ( "entering elf_reader_64::get_text_string" );

	    std::vector < std::string >  output;

	    // this->read_Headers();

	    // m_elf_data->get_Text_String ( &output );

	    trace::io_detail ( "exiting elf_reader_64::get_text_string" );

	    return output;
	  }

	  std::vector < std::string >
	  elf_reader_64::get_utf16_strings ( void )
	  {
	    trace::io_detail ( "entering elf_reader_64::get_utf16_string" );

	    std::vector < std::string > output;

	    // For each section
	    //  - Read UTF-16 Strings

	    trace::io_detail ( "exiting elf_reader_64::get_utf16_string" );

	    return output;
	  }

	  std::string
	  elf_reader_64::get_string_name ( boost::uint64_t index ) const
	  {
	    trace::io_detail ( "entering elf_reader_64::get_string_name" );

	    data_containers::memory_map::const_iterator pos = m_string_table_ptr->begin();

	    const char* name = reinterpret_cast<const char*> ( & ( *pos ) + index );

	    trace::io_detail ( "exiting elf_reader_64::get_string_name" );

	    return std::string ( name );
	  }

// 	  void
// 	  Elf_Reader_64::set_Symbol_Name ( elf_types::Elf_Symbol_64::ptr_t symbol_ptr )
// 	  {

// #ifdef LIBREVERSE_DEBUG
// 	    Trace::write_Trace ( TraceArea::IO,
// 				 TraceLevel::DETAIL,
// 				 "Entering Elf_Reader_64::set_Symbol_Name" );
// #endif /* LIBREVERSE_DEBUG */


// 	    std::string name = "";

// 	    // Does the symbol table entry have a string name index?
// 	    if ( symbol_ptr->get_String_Token_Index() == 0 ) {
// 	      name = "<null>";

// 	      // If not, is the symbol table entry associated with a section?
// 	      // If the answer is NO then the sec_name we defined will be used
// 	      // to say that name of the entry is "<null>".
// 	      if ( symbol_ptr->get_Symbol_Type_Value() == Elf_Common::STT_SECTION ) {
// 		// Find section index assocaited with this symbol table entry
// 		boost::uint16_t sec_index = 0;

// 		if ( symbol_ptr->get_Index() < Elf_Common::SHN_LORESERVE ) {
// 		  // Index is less then the lower bound of the
// 		  // the range of reserved indexes. The default
// 		  // is st_shndx.
// 		  sec_index = symbol_ptr->get_Index();
// 		} else if ( symbol_ptr->get_Index() > Elf_Common::SHN_LORESERVE ) {
// 		  // If a symbol's value refers to a specific location
// 		  // within a section, its section index member,
// 		  // st_shndx, holds an index into the section header
// 		  // table. (Elf)
// 		  sec_index = symbol_ptr->get_Index() -
// 		    ( Elf_Common::SHN_HIRESERVE + 1 - Elf_Common::SHN_LORESERVE );
// 		}

// 		// If sec_index is set, Grab the section name
// 		if ( sec_index != 0 ) {
// 		  // Grab section header
// 		  elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr = m_elf_data->get_Section_Header ( sec_index );

// 		  name = sec_hdr->get_Section_String_Name();
// 		} else if ( symbol_ptr->get_Index() == Elf_Common::SHN_ABS ) {
// 		  // The symbol has an absolute value that will not
// 		  // change because of relocation. (Elf)
// 		  name = "ABS";
// 		} else if ( symbol_ptr->get_Index() == Elf_Common::SHN_COMMON ) {
// 		  // The symbol labels a common block that has not yet
// 		  // been allocated. The symbol's value gives alignment
// 		  // constraints, similar to a section's sh_addralign
// 		  // member. That is, the link editor will allocate the
// 		  // storage for the symbol at an address that is a
// 		  // multiple of st_value. The symbol's size tells how
// 		  // many bytes are required. (Elf)
// 		  name = "COMMON";
// 		} else {
// 		  std::stringstream default_str;
// 		  default_str << boost::format ( "<section 0x%1%>" ) %
// 		    boost::io::group ( std::setfill ( '0' ),
// 				       std::hex, std::setw ( 4 ),
// 				       symbol_ptr->get_Index() );
// 		  name = default_str.str();
// 		}
// 	      }
// 	    }
// 	    // Is the string table defined?
// 	    else if ( m_string_table_ptr.get() == 0 ) {
// 	      std::stringstream data;
// 	      data << "<string table index "
// 		   << symbol_ptr->get_String_Token_Index()
// 		   << ">";

// 	      name = data.str();
// 	    }
// 	    // Our symbol has a string name index and the string table is
// 	    // defined.  Grab the symbol name from the string table.
// 	    else {
// 	      name = this->get_String_Name ( symbol_ptr->get_String_Token_Index() );
// 	    }

// 	    symbol_ptr->set_Symbol_Name ( name );


// #ifdef LIBREVERSE_DEBUG
// 	    Trace::write_Trace ( TraceArea::IO,
// 				 TraceLevel::DETAIL,
// 				 "Entering Elf_Reader_64::set_Symbol_Name" );
// #endif /* LIBREVERSE_DEBUG */

// 	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse
