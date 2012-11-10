/*  test_cokegift.cpp

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
    io_types::File_ID::ptr_t m_file ( new File_ID ( PWD_PREFIX
                                                    "/test_targets/cokegift.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_DOS_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::DOS_Header::ptr_t m_dos_hdr = m_hdr->get_DOS_Header ();


    // File Addr: 0x0
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Magic_Number (),
                        DOS_Header::DOS_MAGIC_SIGNATURE );

    // File Addr: 0x2
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Size_Of_Last_Page(),
                        static_cast<boost::uint16_t>(0x0050) );

    // File Addr: 0x4
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Page_Total(),
                        static_cast<boost::uint16_t>(0x0002) );

    // File Addr: 0x6
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Number_Of_Relocations(),
                        static_cast<boost::uint16_t>(0x0000) );

    // File Addr: 0x8
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Header_Size(),
                        static_cast<boost::uint16_t>(0x0004) );

    // File Addr: 0xA
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Minimum_Alloc(),
                        static_cast<boost::uint16_t>(0x000F) );

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
                        static_cast<boost::uint16_t>(0x001A) );

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
                        static_cast<boost::uint32_t>(0x00000100) );

}

void test_pe_header_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/cokegift.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_PE_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

    // File Addr: 0x100
    BOOST_CHECK_EQUAL ( m_pe_hdr->get_Magic_Number (),
                        PE_Header<32>::PE_MAGIC_SIGNATURE );
}

void test_coff_header_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/cokegift.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_PE_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

    wpef_types::COFF_Header::ptr_t m_coff_hdr = m_pe_hdr->get_COFF_Header();

    // File Addr: 0x104
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Machine_Number(),
                        PE_Machine_Types::IMAGE_FILE_MACHINE_I386 );

    // File Addr: 0x106
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Section_Header_Count(),
                        static_cast<boost::uint16_t>(0x0008) );

    // File Addr: 0x108
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Time_Stamp_Number (),
                        static_cast<boost::uint32_t>(0x2A425E19) );

    // File Addr: 0x10C
    // This is suppose to be 0x0 by the specification.
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Symbol_Table_Pointer (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x110
    // This is suppose to be 0x0 by the specification.
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Number_Of_Symbols (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Determine if file type is executable then the optional header
    // size should be non-zero. In this case we are expecting a valid
    // size/
    BOOST_REQUIRE ( m_coff_hdr->is_Executable() );

    // File Addr: 0x114
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Optional_Header_Size(),
                        static_cast<boost::uint16_t>(0x00E0) );

    // File Addr: 0x116
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Characteristic_Value(),
                        static_cast<boost::uint16_t>(0x818E) );
}

void test_optional_header_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/cokegift.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_PE_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

    wpef_types::PE_Optional_Header<32>::ptr_t m_opt_hdr = m_pe_hdr->get_Optional_Header();

    // File Addr: 0x118
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Magic_Value(),
                        PE_Optional_Header<32>::PE_EXECUTABLE );

    // File Addr: 0x11A
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Linker_Version(),
                        0x02 );

    // File Addr: 0x11B
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Linker_Version(),
                        0x19 );

    // File Addr: 0x11C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Code(),
                        static_cast<boost::uint32_t>(0x00031200) );

    // File Addr: 0x120
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Init_Data(),
                        static_cast<boost::uint32_t>(0x00010400) );

    // File Addr: 0x124
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Uninitialized_Data(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x128
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Entry_Point(),
                        static_cast<boost::uint32_t>(0x00031FF8) );

    // File Addr: 0x12C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Of_Code(),
                        static_cast<boost::uint32_t>(0x00001000) );
    // File Addr: 0x130
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Of_Data(),
                        static_cast<boost::uint32_t>(0x00033000) );

    // File Addr: 0x134
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Image_Base(),
                        static_cast<boost::uint32_t>(0x00400000) );

    // File Addr: 0x138
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Section_Alignment(),
                        static_cast<boost::uint32_t>(0x00001000) );

    // File Addr: 0x13C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_File_Alignment(),
                        static_cast<boost::uint32_t>(0x00000200) );

    BOOST_CHECK ( m_opt_hdr->get_Section_Alignment() >
                  m_opt_hdr->get_File_Alignment() );


    BOOST_CHECK ( m_opt_hdr->get_File_Alignment() % 2 == 0 );

    BOOST_CHECK ( ( m_opt_hdr->get_File_Alignment() >= 512 ) &&
                  ( m_opt_hdr->get_File_Alignment() <= 640000 ) );

    // File Addr: 0x140
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Operating_System_Version(),
                        0x0001 );

    // File Addr: 0x142
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Operating_System_Version(),
                        0x0000 );

    // File Addr: 0x144
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Image_Version(),
                        0x0000 );

    // File Addr: 0x146
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Image_Version(),
                        0x0000 );

    // File Addr: 0x148
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Subsystem_Version(),
                        0x0004 );

    // File Addr: 0x14A
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Subsystem_Version(),
                        0x0000 );

    // File Addr: 0x14C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Win32_Version_Value(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x150
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Image(),
                        static_cast<boost::uint32_t>(0x00048000) );

    // File Addr: 0x154
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Headers(),
                        static_cast<boost::uint32_t>(0x00000400) );

    // File Addr: 0x158
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Checksum(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x15C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Subsystem(),
                        0x0002 );

    // File Addr: 0x15E
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_DLL_Characteristics(),
                        0x0000 );

    // File Addr: 0x160
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Stack_Reserve(),
                        static_cast<boost::uint32_t>(0x00100000) );

    // File Addr: 0x164
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Stack_Commit(),
                        static_cast<boost::uint32_t>(0x00004000) );

    // File Addr: 0x168
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Heap_Reserve(),
                        static_cast<boost::uint32_t>(0x00100000) );

    // File Addr: 0x16C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Heap_Commit(),
                        static_cast<boost::uint32_t>(0x00001000) );

    // File Addr: 0x170
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Loader_Flags(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x174
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Number_Of_RVA_And_Sizes(),
                        static_cast<boost::uint32_t>(0x00000010) );

    // File Addr: 0x178
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Export_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x17C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Export_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x180
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Table_Address (),
                        static_cast<boost::uint32_t>(0x00035000) );
    // File Addr: 0x184
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Table_Size(),
                        static_cast<boost::uint32_t>(0x00001CC4) );

    // File Addr: 0x188
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Resource_Table_Address (),
                        static_cast<boost::uint32_t>(0x0003D000) );
    // File Addr: 0x18C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Resource_Table_Size(),
                        static_cast<boost::uint32_t>(0x0000A200) );

    // File Addr: 0x190
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Exception_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x194
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Exception_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x198
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Certificate_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x19C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Certificate_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1A0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Relocation_Table_Address (),
                        static_cast<boost::uint32_t>(0x00039000) );
    // File Addr: 0x1A4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Relocation_Table_Size(),
                        static_cast<boost::uint32_t>(0x00003514) );

    // File Addr: 0x1A8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Debug_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1AC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Debug_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1B0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Architecture_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1B4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Architecture_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1B8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Global_Ptr_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1BC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Global_Ptr_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1C0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Thread_Local_Storage_Table_Address (),
                        static_cast<boost::uint32_t>(0x00038000) );
    // File Addr: 0x1C4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Thread_Local_Storage_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000018) );

    // File Addr: 0x1C8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Load_Config_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1CC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Load_Config_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1D0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Bound_Import_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1D4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Bound_Import_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1D8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Address_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1DC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Address_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1E0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Delay_Import_Descriptor_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1E4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Delay_Import_Descriptor_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1E8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Clr_Runtime_Header_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );
    // File Addr: 0x1EC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Clr_Runtime_Header_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1F0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Reserved_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1F4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Reserved_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );;
}

void test_import_table_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/cokegift.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    data_types::Memory_Map::ptr_t m_map = m_reader.get_Memory_Map ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    BOOST_CHECK_EQUAL ( m_hdr->get_PE_Import_Directory_Count(),
                        static_cast<boost::uint32_t>(11) );

    wpef_types::Header<32>::Import_Directory_List_t::const_iterator pos =
        m_hdr->get_PE_Import_Directory_List_Begin();

    //-----------------------------------
    // First Table (Memory Addr: 0x435000)
    //-----------------------------------

    // Mem Addr: 0x435000
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000));

    // Mem Addr: 0x435004
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435008
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x43500C
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x0003563C) );

    // Mem Addr: 0x435010
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000350F0) );

    //-----------------------------------
    // Second Table (Memory Addr: 0x435014)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x435014
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435018
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x43501C
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435020
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00035876) );

    // Mem Addr: 0x435024
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00035178) );

    //-----------------------------------
    // Third Table (Memory Addr: 0x435028)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x435028
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x43502C
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435030
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435034
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x000358B0) );

    // Mem Addr: 0x435038
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00035188) );

    //-----------------------------------
    // Fourth Table (Memory Addr: 0x43503C)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x43503C
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435040
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435044
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435048
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x000358F0) );

    // Mem Addr: 0x43504C
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00035198) );

    //-----------------------------------
    // Fifth Table (Memory Addr: 0x435050)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x435050
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x0000000) );

    // Mem Addr: 0x435054
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435058
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x43505C
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00035980) );

    // Mem Addr: 0x435060
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000351B8) );

    //-----------------------------------
    // Sixth Table (Memory Addr: 0x435064)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x435064
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435068
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x43506C
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435070
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x000359E2) );

    // Mem Addr: 0x435074
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000351D0) );

    //-----------------------------------
    // Seventh Table (Memory Addr: 0x435078)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x435078
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x43507C
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435080
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435084
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00035A22) );

    // Mem Addr: 0x435088
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000351E0) );


    //-----------------------------------
    // Eighth Table (Memory Addr: 0x43508C)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x43508C
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435090
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435094
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x435098
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00035D76) );

    // Mem Addr: 0x43509C
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000352A8) );

    //-----------------------------------
    // Ninh Table (Memory Addr: 0x4350A0)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x4350A0
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350A4
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350A8
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350AC
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x000361FE) );

    // Mem Addr: 0x4350B0
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000353B0) );

    //-----------------------------------
    // Tenth Table (Memory Addr: 0x4350B4)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x4350B4
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350B8
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350BC
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350C0
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00036A7E) );

    // Mem Addr: 0x4350C4
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000355D0) );

    //-----------------------------------
    // Eleventh Table (Memory Addr: 0x4350C8)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x4350C8
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350CC
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350D0
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Mem Addr: 0x4350D4
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00036C92) );

    // Mem Addr: 0x4350D8
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00035630) );

}

void test_section_headers ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/cokegift.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_Section_Headers();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    BOOST_CHECK_EQUAL ( m_hdr->get_PE_Section_Header_Count (),
                        static_cast<boost::uint16_t>(0x0008) );

    wpef_types::Header<32>::Section_Header_Map_t::const_iterator pos =
        m_hdr->get_PE_Section_Header ( "CODE" );

    //-----------------------------------
    // Firsts Section (File Addr: 0x1F8)
    //-----------------------------------
    //   - name ( 0x1F8 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare ("CODE") == 0 );

    //   - virtual size (0x200)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00031040) );

    //   - virtual address (0x204)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00001000) );

    //   - size of raw data (0x208)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00031200) );

    //   - pointer to raw data (0x20C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00000400) );

    //   - pointer to relocations (0x210) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x214) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x218) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x21A) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x21C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0x60000020) );

    //-----------------------------------
    // Second Section (File Addr: 0x220)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( "DATA" );

    //   - name ( 0x220 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare ("DATA") == 0 );

    //   - virtual size (0x228)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00000B40) );

    //   - virtual address (0x22C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00033000) );

    //   - size of raw data (0x230)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00000C00) );

    //   - pointer to raw data (0x234)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00031600) );

    //   - pointer to relocations (0x238)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x23C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x240) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x242) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x244) = 0xC0000040
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0xC0000040) );

    //-----------------------------------
    // Third Section (File Addr: 0x248)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( "BSS" );

    //   - name ( 0x248 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare ("BSS") == 0 );

    //   - virtual size (0x250)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00000785) );

    //   - virtual address (0x254)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00034000) );

    //   - size of raw data (0x258)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x0000000) );

    //   - pointer to raw data (0x25C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00032200) );

    //   - pointer to relocations (0x260)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x264)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x268) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x26A) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x26C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0xC0000000) );

    //-----------------------------------
    // Fourth Section (File Addr: 0x270)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( ".idata" );

    //   - name ( 0x270 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".idata") == 0 );

    //   - virtual size (0x278)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00001CC4) );

    //   - virtual address (0x27C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00035000) );

    //   - size of raw data (0x280)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00001E00) );

    //   - pointer to raw data (0x284)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00032200) );

    //   - pointer to relocations (0x288)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x28C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x290) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x292) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x294)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0xC0000040) );

    //-----------------------------------
    // Fifth Section (File Addr: 0x298)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( ".tls" );

    //   - name ( 0x298 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".tls") == 0 );

    //   - virtual size (0x2A0)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00000008) );

    //   - virtual address (0x2A4)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00037000) );

    //   - size of raw data (0x2A8)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to raw data (0x2AC)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00034000) );

    //   - pointer to relocations (0x2B0)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x2B4)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x2B8) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x2BA) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x2BC)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0xC0000000) );

    //-----------------------------------
    // Sixth Section (File Addr: 0x2C0)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( ".rdata" );

    //   - name ( 0x2C0 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".rdata") == 0 );

    //   - virtual size (0x2C8)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00000018) );

    //   - virtual address (0x2CC)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00038000) );

    //   - size of raw data (0x2D0)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00000200) );

    //   - pointer to raw data (0x2D4)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00034000) );

    //   - pointer to relocations (0x2D8)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x2DC)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x2E0) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x2E2) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x2E4)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0x50000040) );

    //-----------------------------------
    // Seventh Section (File Addr: 0x2E8)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( ".reloc" );

    //   - name ( 0x2E8 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".reloc") == 0 );

    //   - virtual size (0x2F0)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00003514) );

    //   - virtual address (0x2F4)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00039000) );

    //   - size of raw data (0x2F8)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00003600) );

    //   - pointer to raw data (0x2FC)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00034200) );

    //   - pointer to relocations (0x300)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x304)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x308) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x30A) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x30C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0x50000040) );

    //-----------------------------------
    // Eigth Section (File Addr: 0x310)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( ".rsrc" );

    //   - name ( 0x310 )
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".rsrc") == 0 );

    //   - virtual size (0x318)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x0000A200) );

    //   - virtual address (0x31C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x0003D000) );

    //   - size of raw data (0x320)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x0000A200) );

    //   - pointer to raw data (0x324)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00037800) );

    //   - pointer to relocations (0x328)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x32C)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x330) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x332) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x334)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0x50000040) );
}

test_suite*
init_unit_test_suite ( int, char** )
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
