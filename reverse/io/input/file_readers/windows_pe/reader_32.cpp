
/*  Reader_32.cpp

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

#include "Reader_32.h"
#include "Header_32.h"
#include "Coff_Header.h"
#include "DOS_Header.h"
#include "PE_Header_32.h"
#include "PE_Debug_Directory.h"
#include "PE_Export_Directory.h"
#include "PE_File.h"
#include "PE_Import_Directory.h"
#include "PE_Optional_Header_32.h"
#include "PE_Resource_Directory.h"
#include "PE_Resource_Directory_String.h"
#include "PE_Resource_Directory_Entry.h"
#include "PE_Resource_Data_Entry.h"
#include "PE_Section_Header.h"
#include "PE_Machine_Types.h"
#include "PE_Exception_Table_Constants.h"
#include "PE_Exception_Table_Entry.h"
#include "AMD_IA_64_Exception_Table_Entry.h"
#include "ARM_POWERPC_SH_Exception_Table_Entry_32.h"

#include "io/File_ID.h"
#include "io/String_Converter.h"
#include "io/Preconditions.h"
#include "data_containers/Memory_Map.h"
#include "errors/IO_Exception.h"
#include "errors/Internal_Exception.h"

#include <sstream>
#include <list>

using namespace libreverse::io;

namespace libreverse { namespace wpef_module {

    Reader_32::Reader_32 ( io_types::File_ID::const_ptr_t target_file )
      : m_file ( new PE_File ( target_file ) ),
	m_convert ( false ),
	m_data ( new Header_32() )
    {}

    Reader_32::~Reader_32 (void){}

    void
    Reader_32::read_DOS_Header (void)
    {
      if ( ! m_file->init() )
	{
	  std::cout << "Error initializing file. Checking standard output for error message."
		    << std::endl;
	  return;
	}

      wpef_types::DOS_Header::ptr_t dos_hdr_ptr = m_data->get_DOS_Header();

      if (dos_hdr_ptr.get() == 0)
	{
	  wpef_types::DOS_Header::ptr_t new_dos_hdr_ptr ( new DOS_Header());
	    
	  m_file->read_DOS_Header (new_dos_hdr_ptr);

	  if ( new_dos_hdr_ptr->needs_Convert () )
	    {
	      new_dos_hdr_ptr->convert ();
	    }

	  m_data->set_DOS_Header( new_dos_hdr_ptr );

	  dos_hdr_ptr = m_data->get_DOS_Header();
	}

      return;
    }

    void Reader_32::read_PE_Header (void)
    {
      read_DOS_Header ();

      wpef_types::DOS_Header::const_ptr_t dos_hdr = m_data->get_DOS_Header();

      wpef_types::PE_Header_32::const_ptr_t pe_hdr = m_data->get_PE_Header();

      if ( dos_hdr->has_PE_Header() && (!pe_hdr) )
	{
	  m_file->seek ( dos_hdr->get_PE_Offset() );

	  wpef_types::PE_Header_32::ptr_t new_pe_hdr ( new PE_Header_32() );

	  m_file->read_PE_Header ( new_pe_hdr );

	  if ( new_pe_hdr->needs_Convert() )
	    {
	      new_pe_hdr->convert();
	      m_convert = true;
	    }

	  m_data->set_PE_Header ( new_pe_hdr );
	}
    }

    void Reader_32::read_Section_Headers (void)
    {
      // Read sections headers by reading the PE Section header count
      if ( m_data->get_PE_Section_Header_Count () == 0 )
	{
	  read_PE_Header ();

	  wpef_types::PE_Header_32::const_ptr_t file_hdr = m_data->get_PE_Header();

	  io::Preconditions::is_set ( file_hdr );
	  wpef_types::COFF_Header::ptr_t coff_hdr_ptr = file_hdr->get_COFF_Header();

	  boost::uint16_t limit = coff_hdr_ptr->get_Section_Header_Count();

	  for ( boost::uint16_t i = 0; i < limit; i++ )
	    {
	      wpef_types::PE_Section_Header::ptr_t new_sec_hdr ( new PE_Section_Header());

	      m_file->read_PE_Section_Header (new_sec_hdr);

	      if ( m_convert )
		{
		  new_sec_hdr->convert();
		}

	      m_data->set_PE_Section_Header ( new_sec_hdr );
	    }
	}
    }

    std::string
    Reader_32::get_File_Type (void)
    {
      read_DOS_Header();

      wpef_types::DOS_Header::ptr_t dos_hdr = m_data->get_DOS_Header();

      std::string result = dos_hdr->get_File_Type();

      if (dos_hdr->has_PE_Header())
	{
	  read_PE_Header ();

	  wpef_types::PE_Header_32::const_ptr_t pe_hdr = m_data->get_PE_Header();

	  result = pe_hdr->get_File_Type();
	}

      return result;
    }

    std::string
    Reader_32::get_Arch_Type (void)
    {
      read_DOS_Header();

      wpef_types::DOS_Header::ptr_t dos_hdr_ptr = m_data->get_DOS_Header();

      std::string result = dos_hdr_ptr->get_Arch_Type();

      if (dos_hdr_ptr->has_PE_Header())
	{
	  read_PE_Header ();

	  wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
	  result = pe_hdr_ptr->get_Arch_Type();
	}

      return result;
    }

    std::string
    Reader_32::get_Section_Offset ( std::string name )
    {
      read_PE_Header();

      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      wpef_types::COFF_Header::ptr_t coff_hdr_ptr = pe_hdr_ptr->get_COFF_Header();

      if ( coff_hdr_ptr->get_Section_Header_Count() > 0)
	{
	  read_Section_Headers();
	}

      std::stringstream output;
      if ( name.compare(".code") == 0 )
	{
	  output << opt_hdr_ptr->get_Base_Of_Code();
	}
      else if ( name.compare(".data") == 0 )
	{
	  output << opt_hdr_ptr->get_Base_Of_Data();
	}

      return output.str();
    }

    std::string
    Reader_32::get_Section_Length ( std::string name )
    {
      read_PE_Header();

      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      wpef_types::COFF_Header::ptr_t coff_hdr_ptr = pe_hdr_ptr->get_COFF_Header();

      if ( coff_hdr_ptr->get_Section_Header_Count() > 0)
	{
	  read_Section_Headers();
	}

      std::stringstream output;
      if ( name.compare(".code") == 0 )
	{
	  output << opt_hdr_ptr->get_Size_Of_Code();
	}
      else if ( name.compare(".data") == 0 )
	{
	  output << opt_hdr_ptr->get_Size_Of_Init_Data();
	}

      return output.str();
    }

    bool
    Reader_32::support_File_Type ( void )
    {
      if ( ! m_file->init() )
	{
	  std::cout << "Error initializing file. Checking standard output for error message."
		    << std::endl;
	  return false;
	}

      bool dos_support = false;
      bool pe_support = false;

      wpef_types::DOS_Header::ptr_t dos_hdr_ptr =
	m_data->get_DOS_Header();

      if ( dos_hdr_ptr.get() == 0 )
	{
	  read_DOS_Header();

	  dos_hdr_ptr = m_data->get_DOS_Header();
	}

      if ( dos_hdr_ptr->is_DOS_File() )
	{
	  dos_support = true;
	}

      if ( ( dos_support ) && ( dos_hdr_ptr->has_PE_Header() ) )
	{
	  read_PE_Header();

	  wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

	  if ( pe_hdr_ptr->is_PE_File() )
	    {
	      pe_support = true;
	    }
	}

      return (dos_support || pe_support );
    }

    std::string
    Reader_32::get_Entry_Point (void)
    {
      read_PE_Header();

      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      std::stringstream output;
      output << opt_hdr_ptr->get_Entry_Point();
      return output.str();
    }

    std::string
    Reader_32::get_Base_Address (void)
    {
      read_PE_Header();

      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      std::stringstream output;
      output << opt_hdr_ptr->get_Image_Base();
      return output.str();
    }

    void
    Reader_32::read_Headers ( void )
    {
      // Reading information from unloaded file image
      this->read_DOS_Header();
      this->read_PE_Header();
      this->read_Section_Headers();

      // Reading information from loaded image in memory
      if ( ! this->m_loaded_file )
	{
	  this->preload_Image ();
	}

      read_Export_Table ();
      read_Import_Table ();
      read_Resource_Table ();

      /*
	read_Exception_Table();
	read_Certificate_Table();
	read_Base_Relocation_Table();
      */
      read_Debug_Table ();
      read_Load_Config_Table ();

      /*
	read_TLS_Table();
	read_Bound_Import_Table();
	read_IAT();
	read_Delay_Import_Descriptor();
	read_CLR_Runtime_Header();
      */
    }

    data_types::Memory_Map::ptr_t
    Reader_32::get_Memory_Map ( void )
    {
      this->read_Headers();
      
      return m_loaded_file->get_Memory_Map();
    }

    void
    Reader_32::preload_Image ( void )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Reader_32::preload_Image" );

      if ( ! this->m_loaded_file )
	{
	  /*
	    IF not already done THEN
                  
	    2. Try to allocate a memory block of
	    PEHeader.OptionalHeader.SizeOfImage bytes at position
	    PEHeader.OptionalHeader.ImageBase.

	    NOTE: I am not going to try and allocate memory at the
	    location of image base for now. We will need to deal with
	    relocations.
	  */
       
	  wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

	  wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

	  // Calculate base address of map
	  boost::uint32_t base_address = opt_hdr_ptr->get_Base_Of_Code() + opt_hdr_ptr->get_Image_Base();

	  data_types::Memory_Map::ptr_t loaded_image ( new data_container::Memory_Map ( opt_hdr_ptr->get_Size_Of_Image(),
											base_address ) );

	  /*
	    3. Parse section headers and copy sections to their
	    addresses.  The destination address for each section,
	    relative to the base of the allocated memory block, is
	    stored in the VirtualAddress attribute of the
	    IMAGE_SECTION_HEADER structure.
	  */
	  for ( wpef_types::Header_32::Section_Header_Map_t::const_iterator cpos = m_data->get_PE_Section_Header_List_Begin();
		cpos != m_data->get_PE_Section_Header_List_End();
		cpos++ )
	    {
	      wpef_types::PE_Section_Header::const_ptr_t sec_ptr = (*cpos).second;
                        
	      // Grab source memory location of raw data in file (PointerToRawData)
	      boost::uint32_t const src_offset = sec_ptr->get_Pointer_To_Raw_Data();
                        
	      // Grab source memory size of raw data in file (SizeOfRawData)
	      boost::uint32_t src_size = sec_ptr->get_Size_Of_Raw_Data();
                        
	      // If src_size == 0 then we use either
	      //   SizeOfInitializedData or SizeOfUnitializedData
	      if ( src_size == 0 )
		{
		  if ( sec_ptr->has_Uninitialized_Data() )
		    {
		      src_size = opt_hdr_ptr->get_Size_Of_Uninitialized_Data();
		    }
		  // QUESTION: If we have a size of zero but the
		  // code is not uninitialized data then is
		  // there a problem?

		  // Do nothing for this space
		}
	      else if ( ( src_size != 0 ) &&
			( sec_ptr->has_Initialized_Data() ||
			  sec_ptr->has_Code() ) )
		{
		  // Grab destination memory location on loaded
		  // data in memory (VirtualAddress)
		  boost::uint32_t const dest_address = sec_ptr->get_Virtual_Address() + opt_hdr_ptr->get_Image_Base();

		  // - Set write position to where writing data will be start.
		 loaded_image->address_Seek ( dest_address );

		  // - Set read position to where reading data will be start
		  m_file->address_Seek ( src_offset );

		  // - Copy Data
		  m_file->copy ( loaded_image,
				 src_size );
		}
	    }

	  this->m_loaded_file.reset ( new PE_File ( loaded_image, m_file->get_ID() ) );
	}

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Reader_32::preload" );

    }

    std::string
    Reader_32::get_Section_String ( std::string name ) const
    {
      return name;
    }

    std::string
    Reader_32::to_String ( void )
    {
      this->read_Headers();

      return m_data->to_String();
    }

    io_types::Text_Data::data_type
    Reader_32::get_Text_Strings ( void )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Reader::get_Text_String" );

      io_types::Text_Data::data_type output;

      this->read_Headers();
        
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      boost::uint32_t dest_address = 0;
      boost::uint32_t dest_size = 0;
      boost::uint8_t byte = 0;
      std::string found_string = "";

      for ( wpef_types::Header_32::Section_Header_Map_t::const_iterator pos = m_data->get_PE_Section_Header_List_Begin();
	    pos != m_data->get_PE_Section_Header_List_End();
	    ++pos)
	{
	  // SEARCH:
	  // IF section type has data
	  if ( ((*pos).second)->has_Initialized_Data() || ((*pos).second)->has_Uninitialized_Data() )
	    {
	      dest_address = ((*pos).second)->get_Virtual_Address() + opt_hdr_ptr->get_Image_Base();
	      dest_size = ((*pos).second)->get_Virtual_Size();

	      // Reset the memory map to the start of the section
	      this->m_loaded_file->address_Seek ( dest_address );

	      //   For all bytes in the section
	      for ( boost::uint32_t index = 0; index < dest_size; ++index )
		{
		  this->m_loaded_file->read ( &byte );

		  //   Find ASCII non-graphic character strings
		  if ( ( byte != '\t' ) &&
		       isprint ( byte ) &&
		       ( byte <= 127 ) )
		    {
		      //   Add string to output
		      found_string.push_back ( byte );
		    }
		  else
		    {
		      // character is a graphic character

		      // IF found_string is greater than or equal minimum THEN save found_string
		      // ELSE reset found_string
		      if ( found_string.size() >= 4 )
			{
			  output.push_back ( found_string );
			}

		      found_string.clear();
		    }
		}
	    }
	}

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Reader::get_Text_String" );

      return output;
    }

    io_types::Text_Data::data_type
    Reader_32::get_UTF16_Strings ( void )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Reader::get_UTF16_String" );

      io_types::Text_Data::data_type output;

      this->read_Headers ();
        
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      boost::uint32_t dest_address = 0;
      boost::uint32_t dest_size = 0;
      boost::uint16_t letter = 0;
      std::vector<UChar> found_string;

      for ( wpef_types::Header_32::Section_Header_Map_t::const_iterator pos = m_data->get_PE_Section_Header_List_Begin();
	    pos != m_data->get_PE_Section_Header_List_End();
	    ++pos)
	{
	  // SEARCH:
	  // IF section type has data
	  if ( ((*pos).second)->has_Initialized_Data() || ((*pos).second)->has_Uninitialized_Data() )
	    {
	      dest_address = ((*pos).second)->get_Virtual_Address() + opt_hdr_ptr->get_Image_Base();
	      dest_size = ((*pos).second)->get_Virtual_Size();

	      // Reset the memory map to the start of the section
	      this->m_loaded_file->address_Seek ( dest_address );

	      //   For all bytes in the section
	      for ( boost::uint32_t index = 0; index < dest_size; ++index )
		{
		  this->m_loaded_file->read ( &letter );

		  //   Find ASCII non-graphic character strings
		  if ( ( letter != 0x2029 ) &&
		       ( letter != 0x2028 ) &&
		       ( letter != 0x000D ) &&
		       ( letter != 0x000A ) &&
		       ( letter != 0x0085 ) &&
		       ( ( letter >= 0x0020 ) &&
			 ( letter <= 0x007F ) ) )
		    {
		      //   Add string to output
		      found_string.push_back ( letter );
		    }
		  else
		    {
		      // character is a graphic character

		      // IF found_string is greater than or equal minimum THEN save found_string
		      // ELSE reset found_string
		      if ( found_string.size() >= 4 )
			{
			  std::string converted_string = String_Converter::convert_From_UTF16_String ( found_string );
			  output.push_back ( converted_string );
			}

		      found_string.clear();
		    }
		}
	    }
	}

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Reader::get_UTF16_String" );

      return output;
    }

    void
    Reader_32::read_Export_Table ()
    {
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();

      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      // IF we have an export table AND
      // IF we have not read the export table THEN
      if ( ( opt_hdr_ptr->get_Export_Table_Address() != 0 ) &&
	   ( ! m_data->get_Export_Directory() ) )
	{
	  boost::uint32_t const export_address = opt_hdr_ptr->get_Export_Table_Address() +
	    opt_hdr_ptr->get_Image_Base();

	  std::vector<boost::uint32_t> export_list;
	  std::vector<boost::uint32_t> name_pointer_list;
	  std::vector<boost::uint16_t> ordinal_list;

	  m_loaded_file->address_Seek ( export_address );

	  //-----------------------------
	  // Read export directory table
	  //-----------------------------
	  wpef_types::PE_Export_Directory::ptr_t export_dir_ptr ( new PE_Export_Directory() );

	  m_loaded_file->read_PE_Export_Directory ( export_dir_ptr );

	  m_data->set_Export_Directory ( export_dir_ptr );

	  //-----------------------------
	  // Read export address table entries
	  //-----------------------------
	  boost::uint32_t count = export_dir_ptr->get_Address_Table_Entries();

	  boost::uint32_t value = 0;

	  boost::uint32_t export_addr_table_offset = export_dir_ptr->get_Export_Address_Table_RVA () +
	    opt_hdr_ptr->get_Image_Base();

	  m_loaded_file->address_Seek ( export_addr_table_offset );
	  
	  for ( boost::uint32_t i = 0;
		i < count;
		i++ )
	    {
	      m_loaded_file->read ( &value );
	      export_list.push_back ( value );
	    }

	  //-----------------------------
	  // Read name pointer table entries
	  //-----------------------------
	  count = export_dir_ptr->get_Number_Of_Name_Pointers();
	  value = 0;

	  boost::uint32_t name_offset = export_dir_ptr->get_Name_Pointer_RVA() +
	    opt_hdr_ptr->get_Image_Base();
	  
	  m_loaded_file->address_Seek ( name_offset );

	  for ( boost::uint32_t i = 0;
		i < count;
		i++ )
	    {
	      m_loaded_file->read ( &value );
	      name_pointer_list.push_back ( value );
	    }

	  //-----------------------------
	  // Read ordinal table entries
	  //-----------------------------
	  boost::uint32_t ordinal_offset =
	    export_dir_ptr->get_Ordinal_Table_RVA () +
	    opt_hdr_ptr->get_Image_Base();

	  m_loaded_file->address_Seek ( ordinal_offset );

	  boost::uint16_t ord_value = 0;

	  for ( boost::uint32_t i = 0;
		i < count;
		i++ )
	    {
	      m_loaded_file->read ( &ord_value );
	      ordinal_list.push_back ( ord_value );
	    }

	  //-----------------------------
	  //    Create data structures
	  //
	  //    (A) Table: string, ordinal_index
	  //
	  //    (B) List: ordinal values
	  //
	  //    (C) Table: ordinal value - ordinal base, RVA pointer
	  //    to symbol address
	  //
	  //-----------------------------

	  // ALGORITHM:
	  //
	  //   Since each data structure above has the same length. We
	  //   will step from 0 to length - 1 to do:
	  //
	  //   Step 1: Create an entry in table C from the
	  //   present position in m_ordinal_list and
	  //   m_export_list.
	  //
	  //   Step 2: Skip making an entry in Ordinal list
	  //   since its already made and stored in the
	  //   PE_Export_Directory object.
	  //
	  //   Step 3: Given the present location in the
	  //   m_export_list find the string name for the
	  //   symbol. Add the string name and the ordinal index
	  //   to Table A.

	  boost::uint32_t entry_limit = ordinal_list.size();
	  std::string symbol_name = "";

	  for ( boost::uint32_t i = 0;
		i < entry_limit;
		i++ )
	    {
	      m_loaded_file->address_Seek ( name_pointer_list[i] +
					     opt_hdr_ptr->get_Image_Base() );

	      m_loaded_file->read_Null_Terminated_String ( symbol_name );
	      export_dir_ptr->add_Export_Entry ( export_list[i],
						 ordinal_list[i],
						 symbol_name );
	    }
	}
    }

    void
    Reader_32::read_Import_Table ()
    {
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();
       
      // IF we have an import table AND
      // IF we have not read the import table THEN
      if ( ( opt_hdr_ptr->get_Import_Table_Address() != 0 ) &&
	   ( m_data->get_PE_Import_Directory_Count() == 0 ) )
	{
	  boost::uint32_t const address = opt_hdr_ptr->get_Import_Table_Address() +
	    opt_hdr_ptr->get_Image_Base();

	  m_loaded_file->address_Seek ( address );

	  //--------------------------------------
	  // Step 1: Read all the Import_Directory objects until one
	  //         is null.
	  //--------------------------------------
	  // BEGIN WHILE import_dir->is_Null ()

	  bool not_done = true;
	  do
	    {
	      wpef_types::PE_Import_Directory::ptr_t import_dir_ptr ( new PE_Import_Directory() );

	      m_loaded_file->read_PE_Import_Directory ( import_dir_ptr );

	      if ( ! import_dir_ptr->is_Null() )
		{
		  m_data->add_Import_Directory ( import_dir_ptr );
		}
	      else
		{
		  not_done = false;
		}

	    }
	  while ( not_done );

	  // END WHILE import_dir->is_Null()


	  //--------------------------------------
	  // Step 2: For each Import_Directory object found read all
	  //         its Import Lookup tables
	  //--------------------------------------

	  for ( wpef_types::Header_32::Import_Directory_List_t::iterator pos = m_data->get_PE_Import_Directory_List_Begin();
		pos != m_data->get_PE_Import_Directory_List_End();
		pos++ )
	    {
	      this->read_Import_Lookup_Table ( *pos );
	    }
	}
    }

    void
    Reader_32::read_Import_Lookup_Table ( wpef_types::PE_Import_Directory::ptr_t& import_dir_ptr )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Reader_32::read_Import_Lookup_Table" );

      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      // Read string for this DLL
      boost::uint32_t const name_offset = import_dir_ptr->get_Name_RVA () + opt_hdr_ptr->get_Image_Base();

      m_loaded_file->address_Seek ( name_offset );

      std::string dll_name = "";
      m_loaded_file->read_Null_Terminated_String ( dll_name );
      import_dir_ptr->set_DLL_Name ( dll_name);

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DATA,
			   boost::str ( boost::format ("  dll name: %s") % dll_name ) );

      // Read Import Lookup tables for this DLL
      boost::uint32_t il_table_val = 0;

      boost::uint32_t table_offset = import_dir_ptr->get_Import_Lookup_Table ();

      if ( table_offset == 0 )
	{
	  // Since the Import lookup table and the Import Address
	  // Table are the same until the application is binded
	  // we can search for the import information in either
	  // the lookup first then followed by the Import Address Table
	  table_offset = import_dir_ptr->get_Import_Address_Table ();
	}

      m_loaded_file->address_Seek ( table_offset + opt_hdr_ptr->get_Image_Base() );
      m_loaded_file->read ( &il_table_val );

      bool is_bit_31_set = false;

      do
	{
	  //                is_bit_31_set = ( ( ( il_table_val >> 30 ) & 0x1 ) == 1 );
	  is_bit_31_set = ( ( il_table_val >> 31 ) == 1 );

	  // Is bit 31 set?
	  //if ( il_table_val & 0x80000000 )
	  if ( is_bit_31_set )
	    {
	      boost::uint32_t val = il_table_val & 0x0000FFFF;
	      import_dir_ptr->add_Ordinal ( val );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str ( boost::format ("  ordinal: %d") % val ) );
	    }
	  else
	    {
	      // - No, import by name
	      // Get offset to string
	      boost::uint32_t target_offset = il_table_val & 0x7FFFFFFF;

	      target_offset += opt_hdr_ptr->get_Image_Base();

	      // Save present offset
	      boost::uint32_t const prev_offset = m_loaded_file->get_Present_Position_Value();

	      // Read null terminated string
	      m_loaded_file->address_Seek ( target_offset );

	      boost::uint16_t hint = 0;
	      m_loaded_file->read ( &hint );

	      std::string str_name = "";
	      m_loaded_file->read_Null_Terminated_String ( str_name );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str ( boost::format ("  hint: %d function: %s") % hint % str_name ) );

	      // reset offset to previous location
	      m_loaded_file->index_Seek ( prev_offset );

	      // Add string to import_dir_ptr->add_Function_Name (string)
	      import_dir_ptr->add_Function_Name ( hint, str_name );
	    }

	  m_loaded_file->read ( &il_table_val );
	}
      while ( il_table_val != 0 );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Reader_32::read_Import_Lookup_Table" );
    }

    void
    Reader_32::read_Resource_Table ()
    {
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      // Get address for resource table

      if ( ( opt_hdr_ptr->get_Resource_Table_Address() != 0 ) &&
	   ( ! m_data->get_PE_Resource_Directory() ) )
	{
	  //--------------------------------------
	  //   Handle Resource Type entries
	  //--------------------------------------

	  boost::uint32_t const address = opt_hdr_ptr->get_Resource_Table_Address() +
	    opt_hdr_ptr->get_Image_Base();

	  m_loaded_file->address_Seek ( address );

	  wpef_types::PE_Resource_Directory::ptr_t new_res_ptr ( new PE_Resource_Directory() );

	  m_loaded_file->read_PE_Resource_Directory ( new_res_ptr);

	  boost::uint16_t num_entry = new_res_ptr->get_Number_Of_Name_Entries();

	  std::list<wpef_types::PE_Resource_Directory_Entry::ptr_t> entry_list;

	  for ( boost::uint16_t i = 0; i < num_entry; i++ )
	    {
	      wpef_types::PE_Resource_Directory_Entry::ptr_t new_res_ent_ptr ( new PE_Resource_Directory_Entry
									       ( PE_Resource_Directory_Entry::NAME ) );

	      m_loaded_file->read_PE_Resource_Directory_Entry ( new_res_ent_ptr );
	      entry_list.push_back ( new_res_ent_ptr );
	    }

	  num_entry = new_res_ptr->get_Number_Of_Id_Entries();

	  for ( boost::uint16_t i = 0; i < num_entry; i++ )
	    {
	      wpef_types::PE_Resource_Directory_Entry::ptr_t new_res_ent_ptr ( new PE_Resource_Directory_Entry
									       ( PE_Resource_Directory_Entry::ID ));

	      m_loaded_file->read_PE_Resource_Directory_Entry ( new_res_ent_ptr );
	      entry_list.push_back ( new_res_ent_ptr );

	    }

	  for ( std::list<wpef_types::PE_Resource_Directory_Entry::ptr_t>::iterator pos = entry_list.begin();
		pos != entry_list.end();
		pos++ )
	    {
	      this->handle_Resource_Directory_Entries ( new_res_ptr,
							(*pos),
							address );
	    }

	  m_data->set_Resource_Directory ( new_res_ptr );
	}
    }

    void
    Reader_32::handle_Resource_Directory_Entries ( wpef_types::PE_Resource_Directory::ptr_t& parent_ptr,
						   wpef_types::PE_Resource_Directory_Entry::ptr_t& parent_entry_ptr,
						   boost::uint32_t base_address )
    {
      std::string name = "";

      // Save present offset
      if ( parent_entry_ptr->get_Type() == PE_Resource_Directory_Entry::NAME )
	{
	  boost::uint32_t const prev_offset = m_loaded_file->get_Present_Position_Value();

	  // Seek to address of m_name
	  boost::uint32_t const name_offset = parent_entry_ptr->get_Name_Offset() & 0x7FFFFFFF;

	  m_loaded_file->address_Seek ( name_offset + base_address );

	  // Read resource directory string
	  wpef_types::PE_Resource_Directory_String::ptr_t new_string_ptr ( new PE_Resource_Directory_String () );

	  m_loaded_file->read_PE_Resource_Directory_String ( new_string_ptr );

	  name = new_string_ptr->get_String();

	  // Restore old address
	  m_loaded_file->index_Seek ( prev_offset );
	}

      // IF our offset is a subDirectory we are only concerned about
      // the lower 31 bits.  ELSE the lower 31 bits point to an
      // IMAGE_RESOURCE_DATA_ENTRY
      boost::uint32_t offset = parent_entry_ptr->get_Offset() & 0x7FFFFFFF;
      m_loaded_file->address_Seek ( offset + base_address );

      // Grab level from parent and increment it
      boost::uint8_t level = parent_ptr->get_Level() + 1;

      //if ( parent_entry_ptr->get_Offset() & 0x80000000 )
      if ( parent_entry_ptr->is_Directory_Bit_Set() )
	{
	  wpef_types::PE_Resource_Directory::ptr_t child_ptr
	    ( new PE_Resource_Directory(level));

	  if ( parent_entry_ptr->get_Type() == PE_Resource_Directory_Entry::NAME )
	    {
	      child_ptr->set_Name ( name );
	    }
	  else
	    {
	      child_ptr->set_ID
		( parent_entry_ptr->get_Name_Offset() );
	    }
	  
	  m_loaded_file->read_PE_Resource_Directory ( child_ptr );

	  boost::uint16_t num_entry = child_ptr->get_Number_Of_Name_Entries();

	  std::list<wpef_types::PE_Resource_Directory_Entry::ptr_t> entry_list;

	  for ( boost::uint16_t i = 0; i < num_entry; i++ )
	    {
	      wpef_types::PE_Resource_Directory_Entry::ptr_t new_res_ent_ptr
		( new PE_Resource_Directory_Entry
		  ( PE_Resource_Directory_Entry::NAME ));
	      
	      m_loaded_file->read_PE_Resource_Directory_Entry ( new_res_ent_ptr );
	      entry_list.push_back ( new_res_ent_ptr );
	    }

	  num_entry = child_ptr->get_Number_Of_Id_Entries();

	  for ( boost::uint16_t i = 0; i < num_entry; i++ )
	    {
	      wpef_types::PE_Resource_Directory_Entry::ptr_t new_res_ent_ptr
		( new PE_Resource_Directory_Entry
		  ( PE_Resource_Directory_Entry::ID ));

	      m_loaded_file->read_PE_Resource_Directory_Entry ( new_res_ent_ptr );
	      entry_list.push_back ( new_res_ent_ptr );
	    }

	  for ( std::list<wpef_types::PE_Resource_Directory_Entry::ptr_t>::iterator pos =
		  entry_list.begin();
		pos != entry_list.end();
		pos++ )
	    {
	      handle_Resource_Directory_Entries ( child_ptr,
						  (*pos),
						  base_address );
	    }

	  parent_ptr->add_Directory ( child_ptr );
	}
      else
	{

	  wpef_types::PE_Resource_Data_Entry::ptr_t new_res_data_ptr ( new PE_Resource_Data_Entry(level));

	  wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
	  wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

	  m_loaded_file->read_PE_Resource_Data_Entry ( new_res_data_ptr,
							opt_hdr_ptr->get_Image_Base() );

	  parent_ptr->add_Data ( new_res_data_ptr );
	}
    }

    void
    Reader_32::read_Debug_Table ()
    {
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      // Get address for resource table

      if ( ( opt_hdr_ptr->get_Debug_Table_Address() != 0 ) &&
	   ( ! m_data->get_Debug_Directory() ) )
	{
	  //--------------------------------------
	  //   Debug entries
	  //--------------------------------------
	  boost::uint32_t const address =
	    opt_hdr_ptr->get_Debug_Table_Address() +
	    opt_hdr_ptr->get_Image_Base();

	  m_loaded_file->address_Seek ( address );

	  wpef_types::PE_Debug_Directory::ptr_t new_debug_ptr ( new PE_Debug_Directory());

	  m_loaded_file->read_PE_Debug_Directory ( new_debug_ptr);

	  if ( m_convert )
	    {
	      new_debug_ptr->convert ();
	    }

	  m_data->set_Debug_Directory ( new_debug_ptr );
	}
    }

    void
    Reader_32::read_Load_Config_Table ()
    {
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      // Get address for resource table

      /*
	if ( opt_hdr_ptr->get_Load_Config_Table_Address() != 0 )
	{
	//--------------------------------------
	//   Debug entries
	//--------------------------------------
	data_types::Memory_Map::ptr_t map_ptr =
	m_loaded_file->get_Map_Ptr();

	boost::uint32_t const address =
	opt_hdr_ptr->get_Load_Config_Table_Address() +
	opt_hdr_ptr->get_Image_Base();

	map_ptr->address_Seek ( address );

	wpef_types::PE_Load_Config_Directory::ptr_t new_lc_ptr
	( new PE_Load_Config_Directory());

	m_loaded_file->read_PE_Load_Config_Directory ( new_lc_ptr);

	m_data->set_Load_Config_Directory ( new_lc_ptr );

	}
      */
    }

    wpef_types::Header_32::ptr_t
    Reader_32::get_Header (void)
    {
      return m_data;
    }

    wpef_types::PE_File::ptr_t
    Reader_32::get_File (void) const
    {
      return m_file;
    }

    void
    Reader_32::read_Exception_Table ()
    {
      wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
      wpef_types::PE_Optional_Header_32::ptr_t opt_hdr_ptr = pe_hdr_ptr->get_Optional_Header();

      // IF we have an exception table AND its not read
      if ( ( opt_hdr_ptr->get_Exception_Table_Address() != 0 ) &&
	   ( m_data->get_PE_Exception_Table_Entry_Count() == 0 ) )
	{
	  boost::uint32_t const address = opt_hdr_ptr->get_Exception_Table_Address() +
	    opt_hdr_ptr->get_Image_Base();

	  m_loaded_file->address_Seek ( address );

	  //--------------------------------------
	  // Step 1: Get type of CPU
	  //         IF type is supported, continue. ELSE skip reading exception table (ERROR?)
	  //
	  // NOTE: A type of CPU which does not need an
	  // exception table but has one present in the file
	  // could have a security problem. Can we consider it
	  // an error if we have bytes in the .pdata section for
	  // CPU which does not need the .pdata info? Is it a
	  // virus?
	  //
	  // ACTION: IF valid, process. Otherwise dump memory
	  //         map for the section to the cerr output.
	  //--------------------------------------
	  wpef_types::PE_Header_32::const_ptr_t pe_hdr_ptr = m_data->get_PE_Header();
	  wpef_types::COFF_Header::ptr_t coff_hdr_ptr = pe_hdr_ptr->get_COFF_Header();
	  boost::uint16_t machine_number = coff_hdr_ptr->get_Machine_Number();
	  boost::uint32_t exception_table_entry_size;

	  switch ( machine_number )
	    {
	      // We are suppose to support MIPS 32-bit but
	      // the specification does not dictate which
	      // IMAGE_FILE_MACHINE constant represents
	      // them.
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_IA64:
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_AMD64:
	      exception_table_entry_size = PE_Exception_Table_Constants::X86_SIZE;
	      break;
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_POWERPC:
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_POWERPCFP:
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_SH3:
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_SH3DSP:
	    case PE_Machine_Types::IMAGE_FILE_MACHINE_SH4:
	      exception_table_entry_size = PE_Exception_Table_Constants::ARM_POWERPC_SH_SIZE;
	      break;
	    default:
	      // Write error report
                        
	      return;
	    }

	  //--------------------------------------
	  // Step 2: Count the number of entry
	  //
	  // Sizes:
	  // - MIPS (20 bytes)
	  // - ARM, PowerpC, SH3 and SH4 (8 bytes)
	  // - x86 and Itanium (12 bytes)
	  //--------------------------------------
	  boost::uint32_t entry_count = opt_hdr_ptr->get_Exception_Table_Size() / exception_table_entry_size;
                
	  //--------------------------------------
	  // Step 3: For i = 0 to Count
	  //           Read Entry
	  //           Save exception data
	  //--------------------------------------
	  for ( boost::uint32_t index = 0; index < entry_count; ++index )
	    {
	      // Create Exception table entry based on CPU
	      wpef_types::PE_Exception_Table_Entry::ptr_t except_ptr =
		this->create_Exception_Table_Entry ( machine_number );

	      // Call read on exception table entry passing the file reference
	      except_ptr->read_Entry ( m_loaded_file );

	      // Add Exception table entry into the list
	      m_data->add_Exception_Table_Entry ( except_ptr );
	    }
	}
    }

    wpef_types::PE_Exception_Table_Entry::ptr_t
    Reader_32::create_Exception_Table_Entry ( boost::uint16_t type )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Reader_32::create_Exception_Table_Entry" );

      switch ( type )
	{
	case PE_Machine_Types::IMAGE_FILE_MACHINE_IA64:
	case PE_Machine_Types::IMAGE_FILE_MACHINE_AMD64:
	  {
	    wpef_types::PE_Exception_Table_Entry::ptr_t output ( new AMD_IA_64_Exception_Table_Entry() );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Reader_32::create_Exception_Table_Entry" );
                    
	    return output;
	  }
	case PE_Machine_Types::IMAGE_FILE_MACHINE_POWERPC:
	case PE_Machine_Types::IMAGE_FILE_MACHINE_POWERPCFP:
	case PE_Machine_Types::IMAGE_FILE_MACHINE_SH3:
	case PE_Machine_Types::IMAGE_FILE_MACHINE_SH3DSP:
	case PE_Machine_Types::IMAGE_FILE_MACHINE_SH4:
	  {
	    wpef_types::PE_Exception_Table_Entry::ptr_t output ( new ARM_POWERPC_SH_Exception_Table_Entry_32() );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting Reader_32::create_Exception_Table_Entry" );

	    return output;
	  }

	default:
	  {
	    // Write error report
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::ERROR,
				 boost::str ( boost::format("Exception throw in %s at line %d")
					      % __FILE__
					      % __LINE__ ) );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::ERROR,
				 boost::str ( boost::format("Unsupported Exception type: %1%") % type ) );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::ERROR,
				 "Contact the developers of libreverse if you feel that this type should be supported.");

	    throw errors::Internal_Exception
	      (errors::Internal_Exception::UNSUPPORTED_FEATURE);

	  }
	}
    }
  } /* namespace wpef_module */
} /* namespace libreverse */
