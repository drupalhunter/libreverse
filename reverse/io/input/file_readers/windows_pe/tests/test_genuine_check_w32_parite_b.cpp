/*  test_genuine_check_w32_parite_b.cpp

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

#include <boost/test/unit_test.hpp>
#include "libreverse/io/input/File_Readers/Windows_PE/Reader_T.h"
#include "libreverse/io/input/File_Readers/Windows_PE/PE_Machine_Types.h"
#include "libreverse/io/File_ID.h"
#include "libreverse/data_containers/Memory_Map.h"
#include <iostream>
#include "libreverse/include/config.h"

using namespace libreverse;
using namespace libreverse::io;
using namespace libreverse::wpef_module;
using namespace boost::unit_test;
using namespace boost::unit_test_framework;


void test_dos_header_read ()
{
  boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
  	"/test_targets/GenuineCheck-w32parite-b.exe" ) );

  Reader<32> m_reader ( m_file, true, true );

  m_reader.read_DOS_Header ();

  wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

  wpef_types::DOS_Header::ptr_t m_dos_hdr = m_hdr->get_DOS_Header ();


  // File Addr: 0x0
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Magic_Number (),
                      DOS_Header::DOS_MAGIC_SIGNATURE );

  // File Addr: 0x2
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Size_Of_Last_Page(),
                      static_cast<boost::uint16_t>(0x0090) );

  // File Addr: 0x4
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Page_Total(),
                      static_cast<boost::uint16_t>(0x0003) );

  // File Addr: 0x6
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Number_Of_Relocations(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x8
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Header_Size(),
                      static_cast<boost::uint16_t>(0x0004) );

  // File Addr: 0xA
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Minimum_Alloc(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0xC
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Maximum_Alloc(),
                      static_cast<boost::uint16_t>(0xFFFF) );

  // File Addr: 0xE
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Initial_SS(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x10
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Initial_SP(),
                      static_cast<boost::uint16_t>(0x00B8) );

  // File Addr: 0x12
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Checksum(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x14
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_IP_Value(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x16
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Initial_CS(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x18
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_File_Address(),
                      static_cast<boost::uint16_t>(0x0040) );

  // File Addr: 0x1A
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Overlay_Number(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x1C
  // Check reserved word
  boost::uint8_t const* word_ptr = m_dos_hdr->get_Reserved_Word();
  for ( boost::uint8_t i = 0; i < DOS_Header::RES_SIZE; i++ )
    {
      BOOST_CHECK_EQUAL ( word_ptr[i], 0x00 );
    }

  // File Addr: 0x20
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_Behavior_Bits(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x22
  boost::uint8_t const* word2_ptr = m_dos_hdr->get_Reserved_Word2();
  for ( boost::uint8_t i = 0; i < DOS_Header::RES2_SIZE; i++ )
    {
      BOOST_CHECK_EQUAL ( word2_ptr[i], 0x00 );
    }

  // File Addr: 0x3C
  BOOST_CHECK_EQUAL ( m_dos_hdr->get_EXE_Header_Address(),
                      static_cast<boost::uint32_t>(0x00000110) );
}

void test_pe_header_read ()
{

  boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
  	"/test_targets/GenuineCheck-w32parite-b.exe" ) );

  Reader<32> m_reader ( m_file, true, true );

  m_reader.read_PE_Header ();

  wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

  wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

  // File Addr: 0x110
  BOOST_CHECK_EQUAL ( m_pe_hdr->get_Magic_Number (),
                      PE_Header<32>::PE_MAGIC_SIGNATURE );
}

void test_coff_header_read ()
{
  boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
  	"/test_targets/GenuineCheck-w32parite-b.exe" ) );

  Reader<32> m_reader ( m_file, true, true );

  m_reader.read_PE_Header ();

  wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

  wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

  wpef_types::COFF_Header::ptr_t m_coff_hdr = m_pe_hdr->get_COFF_Header();

  // File Addr: 0x114
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Machine_Number(),
                      PE_Machine_Types::IMAGE_FILE_MACHINE_I386 );

  // File Addr: 0x116
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Section_Header_Count(),
                      static_cast<boost::uint16_t>(0x0004) );

  // File Addr: 0x118
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Time_Stamp_Number (),
                      static_cast<boost::uint32_t>(0x456E01D3) );

  // File Addr: 0x11C
  // This is suppose to be 0x0 by the specification.
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Symbol_Table_Pointer (),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x120
  // This is suppose to be 0x0 by the specification.
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Number_Of_Symbols (),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Determine if file type is executable then the optional header
  // size should be non-zero. In this case we are expecting a valid
  // size/
  BOOST_REQUIRE ( m_coff_hdr->is_Executable() );

  // File Addr: 0x124
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Optional_Header_Size(),
                      static_cast<boost::uint16_t>(0x00E0) );

  // File Addr: 0x126
  BOOST_CHECK_EQUAL ( m_coff_hdr->get_Characteristic_Value(),
                      static_cast<boost::uint16_t>(0x0103) );
}

void test_optional_header_read ()
{
  boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
  	"/test_targets/GenuineCheck-w32parite-b.exe" ) );

  Reader<32> m_reader ( m_file, true, true );

  m_reader.read_PE_Header ();

  wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

  wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

  wpef_types::PE_Optional_Header<32>::ptr_t m_opt_hdr = m_pe_hdr->get_Optional_Header();

  // File Addr: 0x128
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Magic_Value(),
                      PE_Optional_Header<32>::PE_EXECUTABLE );

  // File Addr: 0x12A
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Linker_Version(),
                      0x08 );

  // File Addr: 0x12B
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Linker_Version(),
                      0x00 );

  // File Addr: 0x12C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Code(),
                      static_cast<boost::uint32_t>(0x00116600) );

  // File Addr: 0x130
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Init_Data(),
                      static_cast<boost::uint32_t>(0x0004FE00) );

  // File Addr: 0x134
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Uninitialized_Data(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x138
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Entry_Point(),
                      static_cast<boost::uint32_t>(0x00169000) );

  // File Addr: 0x13C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Of_Code(),
                      static_cast<boost::uint32_t>(0x00001000) );
  // File Addr: 0x140
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Of_Data(),
                      static_cast<boost::uint32_t>(0x000A2000) );

  // File Addr: 0x144
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Image_Base(),
                      static_cast<boost::uint32_t>(0x01000000) );

  // File Addr: 0x148
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Section_Alignment(),
                      static_cast<boost::uint32_t>(0x00001000) );

  // File Addr: 0x14C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_File_Alignment(),
                      static_cast<boost::uint32_t>(0x00000200) );

  BOOST_CHECK ( m_opt_hdr->get_Section_Alignment() >
                m_opt_hdr->get_File_Alignment() );


  BOOST_CHECK ( m_opt_hdr->get_File_Alignment() % 2 == 0 );

  BOOST_CHECK ( ( m_opt_hdr->get_File_Alignment() >= 512 ) &&
                ( m_opt_hdr->get_File_Alignment() <= 640000 ) );

  // File Addr: 0x150
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Operating_System_Version(),
                      static_cast<boost::uint16_t>(0x0006) );

  // File Addr: 0x152
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Operating_System_Version(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x154
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Image_Version(),
                      static_cast<boost::uint16_t>(0x5343) );

  // File Addr: 0x156
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Image_Version(),
                      static_cast<boost::uint16_t>(0x5020) );

  // File Addr: 0x158
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Subsystem_Version(),
                      static_cast<boost::uint16_t>(0x0004) );

  // File Addr: 0x15A
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Subsystem_Version(),
                      static_cast<boost::uint16_t>(0x0000) );

  // File Addr: 0x15C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Win32_Version_Value(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x160
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Image(),
                      static_cast<boost::uint32_t>(0x0016A000) );

  // File Addr: 0x164
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Headers(),
                      static_cast<boost::uint32_t>(0x00000400) );

  // File Addr: 0x168
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Checksum(),
                      static_cast<boost::uint32_t>(0x0016B62E) );

  // File Addr: 0x16C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Subsystem(),
                      static_cast<boost::uint16_t>(0x0002) );

  // File Addr: 0x16E
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_DLL_Characteristics(),
                      static_cast<boost::uint16_t>(0x8000) );

  // File Addr: 0x170
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Stack_Reserve(),
                      static_cast<boost::uint32_t>(0x00040000) );

  // File Addr: 0x174
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Stack_Commit(),
                      static_cast<boost::uint32_t>(0x00002000) );

  // File Addr: 0x178
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Heap_Reserve(),
                      static_cast<boost::uint32_t>(0x00100000) );

  // File Addr: 0x17C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Heap_Commit(),
                      static_cast<boost::uint32_t>(0x00001000) );

  // File Addr: 0x180
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Loader_Flags(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x184
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Number_Of_RVA_And_Sizes(),
                      static_cast<boost::uint32_t>(0x00000010) );

  // File Addr: 0x188
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Export_Table_Address (),
                      static_cast<boost::uint32_t>(0x00102A9C) );

  // File Addr: 0x18C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Export_Table_Size(),
                      static_cast<boost::uint32_t>(0x00000055) );

  // File Addr: 0x190
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Table_Address (),
                      static_cast<boost::uint32_t>(0x00115D9C) );
  // File Addr: 0x194
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Table_Size(),
                      static_cast<boost::uint32_t>(0x000000C8) );

  // File Addr: 0x198
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Resource_Table_Address (),
                      static_cast<boost::uint32_t>(0x0014C000) );
  // File Addr: 0x19C
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Resource_Table_Size(),
                      static_cast<boost::uint32_t>(0x0001C194) );

  // File Addr: 0x1A0
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Exception_Table_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1A4
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Exception_Table_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1A8
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Certificate_Table_Address (),
                      static_cast<boost::uint32_t>(0x00166800) );
  // File Addr: 0x1AC
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Certificate_Table_Size(),
                      static_cast<boost::uint32_t>(0x00001B30) );

  // File Addr: 0x1B0
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Relocation_Table_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1B4
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Relocation_Table_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1B8
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Debug_Table_Address (),
                      static_cast<boost::uint32_t>(0x001173D4) );
  // File Addr: 0x1BC
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Debug_Table_Size(),
                      static_cast<boost::uint32_t>(0x00000038) );

  // File Addr: 0x1C0
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Architecture_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1C4
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Architecture_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1C8
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Global_Ptr_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1CC
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Global_Ptr_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1D0
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Thread_Local_Storage_Table_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1D4
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Thread_Local_Storage_Table_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1D8
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Load_Config_Table_Address (),
                      static_cast<boost::uint32_t>(0x00015698) );
  // File Addr: 0x1DC
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Load_Config_Table_Size(),
                      static_cast<boost::uint32_t>(0x00000040) );

  // File Addr: 0x1E0
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Bound_Import_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1E4
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Bound_Import_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1E8
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Address_Table_Address (),
                      static_cast<boost::uint32_t>(0x00001000) );
  // File Addr: 0x1EC
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Address_Table_Size(),
                      static_cast<boost::uint32_t>(0x000003C8) );

  // File Addr: 0x1F0
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Delay_Import_Descriptor_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1F4
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Delay_Import_Descriptor_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x1F8
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Clr_Runtime_Header_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x1FC
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Clr_Runtime_Header_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // File Addr: 0x200
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Reserved_Address (),
                      static_cast<boost::uint32_t>(0x00000000) );
  // File Addr: 0x204
  BOOST_CHECK_EQUAL ( m_opt_hdr->get_Reserved_Size(),
                      static_cast<boost::uint32_t>(0x00000000) );;
}

void test_import_table_read ()
{
  boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
  	"/test_targets/GenuineCheck-w32parite-b.exe" ) );

  Reader<32> m_reader ( m_file, true, true );

  data_types::Memory_Map::ptr_t m_map = m_reader.get_Memory_Map ();

  wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

  BOOST_CHECK_EQUAL ( m_hdr->get_PE_Import_Directory_Count(),
                      static_cast<boost::uint32_t>(9) );

  wpef_types::Header<32>::Import_Directory_List_t::const_iterator pos =
    m_hdr->get_PE_Import_Directory_List_Begin();

  //-----------------------------------
  // First Table (Memory Addr: 0x1115D9C)
  //-----------------------------------

  // Mem Addr: 0x1115D9C
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x00115EE0) );

  // Mem Addr: 0x1115DA0
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DA4
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DA8
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115ED0) );

  // Mem Addr: 0x1115DAC
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x00001000) );

  //-----------------------------------
  // Second Table (Memory Addr: 0x1115DB0)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115DB0
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x001160EC) );

  // Mem Addr: 0x1115DB4
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DB8
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DBC
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115EC4) );

  // Mem Addr: 0x1115DC0
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x0000120C) );

  //-----------------------------------
  // Third Table (Memory Addr: 0x1115DC4)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115DC4
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x00116100) );

  // Mem Addr: 0x1115DC8
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DCC
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DD0
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115EB8) );

  // Mem Addr: 0x1115DD4
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x00001220) );

  //-----------------------------------
  // Fourth Table (Memory Addr: 0x1115DD8)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115DD8
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x00116154) );

  // Mem Addr: 0x1115DDC
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DE0
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DE4
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115EAC) );

  // Mem Addr: 0x1115DE8
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x00001274) );

  //-----------------------------------
  // Fifth Table (Memory Addr: 0x1115DEC(
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115DEC
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x00116178) );

  // Mem Addr: 0x1115DF0
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DF4
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115DF8
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115EA0) );

  // Mem Addr: 0x1115DFC
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x00001298) );

  //-----------------------------------
  // Sixth Table (Memory Addr: 0x1115E00)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115E00
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x001161B0) );

  // Mem Addr: 0x1115E04
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E08
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E0C
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115E94) );

  // Mem Addr: 0x1115E10
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x000012D0) );

  //-----------------------------------
  // Seventh Table (Memory Addr: 0x1115E14)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115E14
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x001161E4) );

  // Mem Addr: 0x1115E18
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E1C
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E20
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115E84) );

  // Mem Addr: 0x1115E24
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x00001304) );


  //-----------------------------------
  // Eighth Table (Memory Addr: 0x1115E28)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115E28
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x00116204) );

  // Mem Addr: 0x1115E2C
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E30
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E34
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115E74) );

  // Mem Addr: 0x1115E38
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x00001324) );

  //-----------------------------------
  // Ninh Table (Memory Addr: 0x11115E3C)
  //-----------------------------------
  pos++;

  // Mem Addr: 0x1115E3C
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                      static_cast<boost::uint32_t>(0x0011628C) );

  // Mem Addr: 0x1115E40
  BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E44
  BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
		      static_cast<boost::uint32_t>(0x00000000) );

  // Mem Addr: 0x1115E48
  BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
		      static_cast<boost::uint32_t>(0x00115E64) );

  // Mem Addr: 0x1115E4C
  BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
		      static_cast<boost::uint32_t>(0x000013AC) );

}

void test_section_headers ()
{
  boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
  	"/test_targets/GenuineCheck-w32parite-b.exe" ) );

  Reader<32> m_reader ( m_file, true, true );

  m_reader.read_Section_Headers();

  wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

  BOOST_CHECK_EQUAL ( m_hdr->get_PE_Section_Header_Count (),
		      static_cast<boost::uint16_t>(0x0004) );

  wpef_types::Header<32>::Section_Header_Map_t::const_iterator pos =
	  m_hdr->get_PE_Section_Header (".text");

  //-----------------------------------
  // First Section (File Addr: 0x208)
  //-----------------------------------
  //   - name ( 0x208 )
  BOOST_CHECK ( ((*pos).second)->get_Name().compare (".text") == 0 );

  //   - virtual size (0x210)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
		      static_cast<boost::uint32_t>(0x00116461) );

  //   - virtual address (0x214)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
		      static_cast<boost::uint32_t>(0x00001000) );

  //   - size of raw data (0x218)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                      static_cast<boost::uint32_t>(0x000116600) );

  //   - pointer to raw data (0x21C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
		      static_cast<boost::uint32_t>(0x00000400) );

  //   - pointer to relocations (0x220)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
		      static_cast<boost::uint32_t>(0x00000000) );

  //   - pointer to line numbers (0x224)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
		      static_cast<boost::uint32_t>(0x00000000) );

  //   - number of relocations (0x228) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - number of line numbers (0x22A) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - characteristics (0x228)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
		      static_cast<boost::uint32_t>(0xE0000020) );

  //-----------------------------------
  // Second Section (File Addr: 0x230)
  //-----------------------------------
  pos = m_hdr->get_PE_Section_Header (".data");

  //   - name ( 0x230 )
  BOOST_CHECK ( ((*pos).second)->get_Name().compare (".data") == 0 );

  //   - virtual size (0x238)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
		      static_cast<boost::uint32_t>(0x00033AE1) );

  //   - virtual address (0x23C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                      static_cast<boost::uint32_t>(0x00118000) );

  //   - size of raw data (0x240)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
		      static_cast<boost::uint32_t>(0x00033C00) );

  //   - pointer to raw data (0x244)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                      static_cast<boost::uint32_t>(0x000116A00) );

  //   - pointer to relocations (0x248)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
		      static_cast<boost::uint32_t>(0x00000000) );

  //   - pointer to line numbers (0x24C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
		      static_cast<boost::uint32_t>(0x00000000) );

  //   - number of relocations (0x250) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - number of line numbers (0x252) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - characteristics (0x254) = 0xC0000040
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
		      static_cast<boost::uint32_t>(0xC0000040) );

  //-----------------------------------
  // Third Section (File Addr: 0x258)
  //-----------------------------------
  pos = m_hdr->get_PE_Section_Header (".rsrc");

  //   - name ( 0x258 )
  BOOST_CHECK ( ((*pos).second)->get_Name().compare (".rsrc") == 0 );

  //   - virtual size (0x260)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
		      static_cast<boost::uint32_t>(0x0001C194) );

  //   - virtual address (0x264)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
		      static_cast<boost::uint32_t>(0x0014C000) );

  //   - size of raw data (0x268)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
		      static_cast<boost::uint32_t>(0x0001C200) );

  //   - pointer to raw data (0x26C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
		      static_cast<boost::uint32_t>(0x0014A600) );

  //   - pointer to relocations (0x270)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
		      static_cast<boost::uint32_t>(0x00000000) );

  //   - pointer to line numbers (0x274)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
		      static_cast<boost::uint32_t>(0x00000000) );

  //   - number of relocations (0x278) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - number of line numbers (0x27A) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - characteristics (0x27C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
		      static_cast<boost::uint32_t>(0x40000040) );

  //-----------------------------------
  // Fourth Section (File Addr: 0x280)
  //-----------------------------------
  pos = m_hdr->get_PE_Section_Header (".spm\a");;

  //   - name ( 0x280 )
  BOOST_CHECK ( ((*pos).second)->get_Name().compare (".spm\a") == 0 );

  //   - virtual size (0x288)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
		      static_cast<boost::uint32_t>(0x00001000) );

  //   - virtual address (0x28C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
		      static_cast<boost::uint32_t>(0x00169000) );

  //   - size of raw data (0x290)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
		      static_cast<boost::uint32_t>(0x00000600) );

  //   - pointer to raw data (0x294)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
		      static_cast<boost::uint32_t>(0x00168400) );

  //   - pointer to relocations (0x298)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
		      static_cast<boost::uint32_t>(0xFFF79A57) );

  //   - pointer to line numbers (0x29C)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
		      static_cast<boost::uint32_t>(0x001EE180) );

  //   - number of relocations (0x2A0) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - number of line numbers (0x2A2) = 0x0
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
		      static_cast<boost::uint16_t>(0x0000) );

  //   - characteristics (0x2A4)
  BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
		      static_cast<boost::uint32_t>(0xE0000020) );

}

test_suite*
init_unit_test_suite ( int , char** )
{
  test_suite* test = BOOST_TEST_SUITE ( "Cokegift test suite" );

  test->add ( BOOST_TEST_CASE ( &test_dos_header_read ) );
  test->add ( BOOST_TEST_CASE ( &test_pe_header_read ) );
  test->add ( BOOST_TEST_CASE ( &test_coff_header_read ) );
  test->add ( BOOST_TEST_CASE ( &test_optional_header_read ) );
  test->add ( BOOST_TEST_CASE ( &test_import_table_read ) );
  test->add ( BOOST_TEST_CASE ( &test_section_headers ) );

  return test;
}
