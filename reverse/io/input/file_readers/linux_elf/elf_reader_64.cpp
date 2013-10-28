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

#include <reverse/io/input/file_readers/linux_elf/data_containers/memory_map.hpp>
#include <reverse/io/input/file_readers/linux_elf/io/file_id.hpp>
#include <reverse/errors/io_exception.hpp>

#include <reverse/trace.hpp>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  elf_reader_64::elf_reader_64 ( boost::shared_ptr < const io::file_id > target_file )
	    : m_filename ( target_file ),
	      m_convert ( false )
	  {
	    trace::io_detail ( "Inside Elf_Reader constructor" );
	  }

	  elf_reader_64::~elf_reader_64 ( void )
	  {
	    trace::io_detail ( "Inside Elf_Reader destructor" );
	  }

	  void elf_reader_64::read_headers ( void )
	  {
	    trace::io_detail ( "Entering elf_reader_64::read_headers" );

	    // Create the file mapping
	    boost::interprocess::file_mapping fm ( m_filename->get_full_name(), boost::interprocess::read_only );
    
	    // Map the file in memory
	    boost::interprocess::mapped_region region ( fm, boost::interprocess::read_only );
    
	    // Get the start address of the file in memory
	    char const* iter = region.get_address();
	    char const* end = iter + region.get_size();
    
	    // Parse the file_hdr
	    elf_parser parser;
	    if ( parser.read ( iter, end, m_elf_file ) )
	      {
		// \todo Add conversion
		// 	if ( new_file_hdr->needs_convert() ) {
		//                new_file_hdr->convert();
		//                m_convert = true;
		//           }
		// 
		//           m_elf_data->set_file_header ( new_file_hdr );
	      }
	    else
	      {
		throw errors::io_exception ( "Error parsing input file." );
	      }
    
	    if ( ! m_elf_file->init() ) {
	      trace::io_error ( "Error initializing file. Checking standard output for error message." );
	      return;
	    }

	    // \todo Dump elf header
	    //trace::io_data ( "Elf Header dump: \n%1%", new_file_hdr->to_string() );

	    trace::io_detail ( "Exiting elf_reader_64::read_file_header" );
	  }


	  std::string
	  elf_reader_64::get_file_type ( void )
	  {
	    trace::io_detail ( "Entering Elf_Reader_64::get_File_Type" );

	    std::string result = elf_meta_info::FILE_TYPE_64BIT;

	    return result;
	  }

	  std::string
	  elf_reader_64::get_arch_type ( void )
	  {
	    trace::io_detail ( "Entering Elf_Reader_64::get_Arch_Type" );

    
	    read_File_Header();

	    elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

	    std::string result = file_hdr_ptr->get_Arch_Type();

	    trace::io_detail("Exiting Elf_Reader_64::get_Arch_Type" );

	    return result;
	  }

	  std::string
	  Elf_Reader_64::get_Section_Offset ( std::string name )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Section_Offset" );
#endif /* LIBREVERSE_DEBUG */


	    read_File_Header();

	    elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

	    if ( file_hdr_ptr->get_Section_Header_Count() > 0 ) {
	      read_Section_Headers();
	    }

	    elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr_ptr =
	      m_elf_data->get_Section_Header ( this->get_Section_String ( name ) );

	    std::stringstream output;
	    output << sec_hdr_ptr->get_Section_Offset ();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Section_Offset" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }

	  std::string
	  Elf_Reader_64::get_Section_Length ( std::string name )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Section_Length" );
#endif /* LIBREVERSE_DEBUG */


	    read_File_Header();

	    elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

	    if ( file_hdr_ptr->get_Section_Header_Count() > 0 ) {
	      read_Section_Headers();
	    }

	    elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr_ptr =
	      m_elf_data->get_Section_Header ( this->get_Section_String ( name ) );

	    std::stringstream output;
	    output << sec_hdr_ptr->get_Section_Size ();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Section_Length" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }

	  std::string
	  Elf_Reader_64::get_Entry_Point ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Entry_Point" );
#endif /* LIBREVERSE_DEBUG */


	    read_File_Header();

	    elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

	    std::stringstream output;
	    output << file_hdr_ptr->get_Entry ();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Entry_Point" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }

	  std::string
	  Elf_Reader_64::get_Base_Address ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Base_Address" );
#endif /* LIBREVERSE_DEBUG */


	    read_Program_Headers();

	    std::stringstream output;

	    output << m_elf_data->get_Base_Address();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Base_Address" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }

	  void
	  Elf_Reader_64::read_Symbol_Token ()
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::read_Symbol_Token" );
#endif /* LIBREVERSE_DEBUG */


	    /*
	      Elf_File_Header_64::ptr_t file_hdr =
	      m_elf_data->get_File_Header();

	      Elf_Section_Header_64::ptr_t sec_hdr;

	      boost::uint16_t pos = 0;
	      for ( ; pos != file_hdr->get_Section_Header_Count();
	      ++pos)
	      {

	      sec_hdr = m_elf_data->get_Section_Header(pos);

	      if (sec_hdr->get_Section_Type() == Elf_Common::SHT_SYMTAB)
	      {
	      break;
	      }
	      }

	      if (pos == file_hdr->get_Section_Header_Count())
	      {
	      return;
	      }

	      Elf_Section_Header_64::ptr_t symbol_hdr = sec_hdr;

	      Elf_Section_Header_64::ptr_t symbol_string_hdr =
	      m_elf_data->get_Section_Header (symbol_hdr->get_Next_Section_Index());

	      char* string_table =
	      (char*)m_elf_file->read (symbol_string_hdr->get_Section_Offset(),
	      symbol_string_hdr->get_Section_Size());

	      boost::uint64_t num_symbols = symbol_hdr->get_Section_Size() /
	      symbol_hdr->get_Section_Token_Size();

	      m_elf_file->seek (symbol_hdr->get_Section_Offset());

	      for (boost::uint64_t i = 0; i < num_symbols; ++i)
	      {
	      Elf_Symbol_64::ptr_t symbol
	      (new Elf_Symbol_64 (file_hdr->get_Machine_Value()));

	      m_elf_file->read_Elf_Symbol (symbol);
	      m_elf_data->push_Back_Symbol (symbol);
	      }

	      std::cout << std::endl << "Symbol Token:" << std::endl
	      << boost::format("%|8|") % "Num:"
	      << boost::format("%|9|") % "Value"
	      << boost::format("%|6|") % "Size"
	      << boost::format(" %|-9|") % "Type"
	      << boost::format("%|-9|") % "Bind"
	      << boost::format("%|-7|") % "Vis"
	      << boost::format("%|4|") % "Ndx"
	      << boost::format(" %|4|") % "Name" << std::endl;

	      std::cout << m_elf_data->get_Symbol_Token_String (string_table)
	      << std::endl;
	    */


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::read_Symbol_Token" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  void
	  Elf_Reader_64::read_Relocations ()
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::read_Relocations" );
#endif /* LIBREVERSE_DEBUG */


	    read_File_Header();

	    elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

	    if ( file_hdr_ptr->get_Section_Header_Count() > 0 ) {

	      read_Section_Headers();

	      elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr_ptr;

	      for ( boost::uint16_t pos = 0 ;
                    pos != file_hdr_ptr->get_Section_Header_Count();
                    ++pos ) {
		sec_hdr_ptr = m_elf_data->get_Section_Header ( pos );

		switch ( sec_hdr_ptr->get_Section_Type() ) {
		case Elf_Common::SHT_RELA: {
		  // If the Relocation Symbols have not been retrieved
		  // then read the symbols into Elf Header
		  if ( !m_elf_data->has_Symbols() ) {
		    this->read_Relocation_Symbols ( sec_hdr_ptr, file_hdr_ptr );
		  }

		  // Read the Relocation Addend Headers into Elf Header
		  this->read_Relocation_Addend_Headers ( sec_hdr_ptr, file_hdr_ptr );

		  break;
		}
		case Elf_Common::SHT_REL: {
		  // If the Relocation Symbols have not been retrieved
		  // then read the symbols into Elf Header
		  if ( !m_elf_data->has_Symbols() ) {
		    this->read_Relocation_Symbols ( sec_hdr_ptr, file_hdr_ptr );
		  }

		  // Read the Relocation Addend Headers into Elf Header
		  this->read_Relocation_Headers ( sec_hdr_ptr, file_hdr_ptr );

		  break;
		}
		default: {
		  continue;
		}
		}
	      }
	    }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::read_Relocations" );
#endif /* LIBREVERSE_DEBUG */


	  }

	  bool
	  Elf_Reader_64::support_File_Type ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */


	    bool result = true;

	    if ( ! m_elf_file->init() ) {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::ERROR,
				   "Error initializing file. Checking standard output for error message." );
#endif /* LIBREVERSE_DEBUG */


	      result = false;
	    } else {
	      elf_types::Elf_Header_Eident::ptr_t eident_header ( new Elf_Header_Eident() );

	      m_elf_file->read_Elf_Header_Eident ( eident_header );


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DETAIL,
				   "Exiting Elf_Reader_64::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */


	      result = eident_header->is_Elf_File();


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DETAIL,
				   "Exiting Elf_Reader_64::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */

	    }

	    return result;
	  }

	  void
	  Elf_Reader_64::read_Relocation_Headers ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
						   elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::read_Relocation_Headers" );
#endif /* LIBREVERSE_DEBUG */


	    // Setup file for position to reading Relocation headers
	    m_elf_file->seek ( sec_hdr->get_Section_Offset() );
	    boost::uint64_t number_relocs =
	      sec_hdr->get_Section_Size() /
	      sec_hdr->get_Section_Token_Size();



#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 boost::str
				 ( boost::format ( "Relocations section '%s' at offset %d contains %d entries:" )
				   % sec_hdr->get_Section_String_Name()
				   % sec_hdr->get_Section_Offset()
				   % number_relocs ) );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 " Offset     Info       Type            Sym.Value     Sym.Name" );
#endif /* LIBREVERSE_DEBUG */


	    // Read Relocation headers and add to Elf_Header.
	    for ( boost::uint64_t i = 0; i < number_relocs; ++i ) {
	      elf_types::Elf_Relocation_64::ptr_t reloc_hdr_ptr ( new Elf_Relocation_64 ( file_hdr ) );

	      m_elf_file->read_Elf_Relocation ( reloc_hdr_ptr );

	      if ( m_convert ) {
		reloc_hdr_ptr->convert ();
	      }

	      elf_types::Elf_Symbol_64::const_ptr_t reloc_symbol_ptr =
		m_elf_data->get_Symbol ( reloc_hdr_ptr->get_Symbol_Token_Index() );



#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str
				   ( boost::format ( "%s   %s" )
				     % reloc_hdr_ptr->to_String()
				     % reloc_symbol_ptr->to_String() ) );
#endif /* LIBREVERSE_DEBUG */


	      m_elf_data->push_Back_Relocation_Header ( reloc_hdr_ptr );
	    }



#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::read_Relocation_Headers" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  void
	  Elf_Reader_64::read_Relocation_Addend_Headers ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
							  elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::read_Relocation_Addend_Headers" );
#endif /* LIBREVERSE_DEBUG */


	    m_elf_file->seek ( sec_hdr->get_Section_Offset() );

	    boost::uint64_t number_relocs =
	      sec_hdr->get_Section_Size() /
	      sec_hdr->get_Section_Token_Size();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 boost::str
				 ( boost::format ( "Relocations section '%s' at offset %d contains %d entries:" )
				   % sec_hdr->get_Section_String_Name()
				   % sec_hdr->get_Section_Offset()
				   % number_relocs ) );
#endif /* LIBREVERSE_DEBUG */


	    for ( boost::uint64_t i = 0; i < number_relocs; ++i ) {
	      elf_types::Elf_Relocation_Add_64::ptr_t reloc_add_hdr_ptr ( new Elf_Relocation_Add_64 ( file_hdr ) );

	      m_elf_file->read_Elf_Relocation_Add ( reloc_add_hdr_ptr );

	      if ( m_convert ) {
		reloc_add_hdr_ptr->convert ();
	      }

	      elf_types::Elf_Symbol_64::const_ptr_t reloc_symbol_ptr =
		m_elf_data->get_Symbol ( reloc_add_hdr_ptr->get_Symbol_Token_Index() );



#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str
				   ( boost::format ( "%s   %s" )
				     % reloc_add_hdr_ptr->to_String()
				     % reloc_symbol_ptr->to_String() ) );
#endif /* LIBREVERSE_DEBUG */


	      m_elf_data->push_Back_Relocation_Add_Header ( reloc_add_hdr_ptr );
	    }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::read_Relocation_Addend_Headers" );
#endif /* LIBREVERSE_DEBUG */


	  }

	  void
	  Elf_Reader_64::read_Relocation_Symbols ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
						   elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::read_Relocation_Symbols" );
#endif /* LIBREVERSE_DEBUG */


	    // Setup file for position to reading Relocation Symbols
	    elf_types::Elf_Section_Header_64::const_ptr_t sym_hdr =
	      m_elf_data->get_Section_Header ( sec_hdr->get_Next_Section_Index() );

	    elf_types::Elf_Section_Header_64::const_ptr_t sym_string_hdr =
	      m_elf_data->get_Section_Header ( sym_hdr->get_Next_Section_Index() );

	    m_elf_file->seek ( sym_string_hdr->get_Section_Offset() );

	    m_string_table_ptr = m_elf_file->subset ( sym_string_hdr->get_Section_Size() );

	    m_elf_file->seek ( sym_hdr->get_Section_Offset() );

	    boost::uint64_t number_symbols =
	      sym_hdr->get_Section_Size() /
	      sym_hdr->get_Section_Token_Size();

	    // Read Symbols
	    for ( boost::uint64_t i = 0; i < number_symbols; ++i ) {
	      elf_types::Elf_Symbol_64::ptr_t reloc_symbol ( new Elf_Symbol_64 ( file_hdr->get_Machine_Value() ) );

	      m_elf_file->read_Elf_Symbol ( reloc_symbol );

	      if ( m_convert ) {
		reloc_symbol->convert();
	      }

	      this->set_Symbol_Name ( reloc_symbol );

	      m_elf_data->push_Back_Symbol ( reloc_symbol );
	    }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::read_Relocation_Symbols" );
#endif /* LIBREVERSE_DEBUG */


	  }

	  void
	  Elf_Reader_64::read_Headers ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::read_Headers" );
#endif /* LIBREVERSE_DEBUG */


	    this->read_Program_Headers();
	    this->read_Section_Headers();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::read_Headers" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  data_types::Memory_Map::ptr_t
	  Elf_Reader_64::get_Memory_Map ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Memory_Map" );
#endif /* LIBREVERSE_DEBUG */


	    this->read_Headers();

	    // Get base address of the image
	    boost::uint64_t base_address = m_elf_data->get_Base_Address();

	    boost::uint64_t memory_size = m_elf_data->get_Loaded_Memory_Size();

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Elf_Reader_64::get_Memory_Map - base_address = 0x%1$-08X (0x%2$-08X)" )
					      % base_address
					      % memory_size ) );

	    data_types::Memory_Map::ptr_t result ( new data_container::Memory_Map ( memory_size, base_address ) );

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
	    elf_types::Elf_File_Header_64::const_ptr_t elf_file_hdr_ptr = m_elf_data->get_File_Header();

	    boost::uint16_t const elf_type = elf_file_hdr_ptr->get_File_Type_Value();

	    if ( elf_type != Elf_Common::ET_EXEC ) {
	      // ERROR
	    }
	    /* 2. Perform relocations */

	    /* (QUESTION?)3. Perform dynamic linking */


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Memory_Map" );
#endif /* LIBREVERSE_DEBUG */


	    return result;

	  }

	  std::string
	  Elf_Reader_64::get_Section_String ( std::string name ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Section_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::string output = name;

	    if ( name.compare ( ".code" ) == 0 ) {
	      output = ".text";
	    }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Section_String" );
#endif /* LIBREVERSE_DEBUG */


	    return output;
	  }

	  std::string
	  Elf_Reader_64::to_String ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    this->read_Headers();

	    std::string result = m_elf_data->to_String();


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    return result;
	  }

	  io_types::Text_Data::data_type
	  Elf_Reader_64::get_Text_Strings ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


	    io_types::Text_Data::data_type output;

	    this->read_Headers();

	    m_elf_data->get_Text_String ( &output );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


	    return output;
	  }

	  io_types::Text_Data::data_type
	  Elf_Reader_64::get_UTF16_Strings ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */


	    io_types::Text_Data::data_type output;

	    // For each section
	    //  - Read UTF-16 Strings


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */


	    return output;
	  }

	  std::string
	  Elf_Reader_64::get_String_Name ( boost::uint64_t index ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::get_String_Name" );
#endif /* LIBREVERSE_DEBUG */


	    data_types::Memory_Map::const_iterator pos = m_string_table_ptr->begin();

	    const char* name = reinterpret_cast<const char*> ( & ( *pos ) + index );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Elf_Reader_64::get_String_Name" );
#endif /* LIBREVERSE_DEBUG */


	    return std::string ( name );
	  }

	  void
	  Elf_Reader_64::set_Symbol_Name ( elf_types::Elf_Symbol_64::ptr_t symbol_ptr )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::set_Symbol_Name" );
#endif /* LIBREVERSE_DEBUG */


	    std::string name = "";

	    // Does the symbol table entry have a string name index?
	    if ( symbol_ptr->get_String_Token_Index() == 0 ) {
	      name = "<null>";

	      // If not, is the symbol table entry associated with a section?
	      // If the answer is NO then the sec_name we defined will be used
	      // to say that name of the entry is "<null>".
	      if ( symbol_ptr->get_Symbol_Type_Value() == Elf_Common::STT_SECTION ) {
		// Find section index assocaited with this symbol table entry
		boost::uint16_t sec_index = 0;

		if ( symbol_ptr->get_Index() < Elf_Common::SHN_LORESERVE ) {
		  // Index is less then the lower bound of the
		  // the range of reserved indexes. The default
		  // is st_shndx.
		  sec_index = symbol_ptr->get_Index();
		} else if ( symbol_ptr->get_Index() > Elf_Common::SHN_LORESERVE ) {
		  // If a symbol's value refers to a specific location
		  // within a section, its section index member,
		  // st_shndx, holds an index into the section header
		  // table. (Elf)
		  sec_index = symbol_ptr->get_Index() -
		    ( Elf_Common::SHN_HIRESERVE + 1 - Elf_Common::SHN_LORESERVE );
		}

		// If sec_index is set, Grab the section name
		if ( sec_index != 0 ) {
		  // Grab section header
		  elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr = m_elf_data->get_Section_Header ( sec_index );

		  name = sec_hdr->get_Section_String_Name();
		} else if ( symbol_ptr->get_Index() == Elf_Common::SHN_ABS ) {
		  // The symbol has an absolute value that will not
		  // change because of relocation. (Elf)
		  name = "ABS";
		} else if ( symbol_ptr->get_Index() == Elf_Common::SHN_COMMON ) {
		  // The symbol labels a common block that has not yet
		  // been allocated. The symbol's value gives alignment
		  // constraints, similar to a section's sh_addralign
		  // member. That is, the link editor will allocate the
		  // storage for the symbol at an address that is a
		  // multiple of st_value. The symbol's size tells how
		  // many bytes are required. (Elf)
		  name = "COMMON";
		} else {
		  std::stringstream default_str;
		  default_str << boost::format ( "<section 0x%1%>" ) %
		    boost::io::group ( std::setfill ( '0' ),
				       std::hex, std::setw ( 4 ),
				       symbol_ptr->get_Index() );
		  name = default_str.str();
		}
	      }
	    }
	    // Is the string table defined?
	    else if ( m_string_table_ptr.get() == 0 ) {
	      std::stringstream data;
	      data << "<string table index "
		   << symbol_ptr->get_String_Token_Index()
		   << ">";

	      name = data.str();
	    }
	    // Our symbol has a string name index and the string table is
	    // defined.  Grab the symbol name from the string table.
	    else {
	      name = this->get_String_Name ( symbol_ptr->get_String_Token_Index() );
	    }

	    symbol_ptr->set_Symbol_Name ( name );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering Elf_Reader_64::set_Symbol_Name" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  elf_types::Elf_Header_64::ptr_t
	  Elf_Reader_64::get_Header ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside Elf_Reader_64::get_Header" );
#endif /* LIBREVERSE_DEBUG */


	    return m_elf_data;
	  }

	  elf_types::elf_file const&
	  elf_reader_64::get_file ( void ) const
	  {

	    trace::io_detail( "inside elf_reader_64::get_header" );

	    return m_elf_file;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse
