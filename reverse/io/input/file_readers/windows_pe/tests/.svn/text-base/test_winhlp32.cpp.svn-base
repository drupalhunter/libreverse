/*  test_winhlp32.cpp

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
                                                    "/test_targets/winhlp32.exe" ) );

    libreverse::wpef_module::Reader<32> m_reader ( m_file, true, true );

    m_reader.read_DOS_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::DOS_Header::ptr_t m_dos_hdr = m_hdr->get_DOS_Header ();


    // File Addr: 0x0
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Magic_Number (),
                        DOS_Header::DOS_MAGIC_SIGNATURE );

    // File Addr: 0x2
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Size_Of_Last_Page(),
                        0x0090 );

    // File Addr: 0x4
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Page_Total(),
                        0x0003 );

    // File Addr: 0x6
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Number_Of_Relocations(),
                        0x0000 );
 
    // File Addr: 0x8
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Header_Size(),
                        0x0004 );

    // File Addr: 0xA
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Minimum_Alloc(),
                        0x0000 );

    // File Addr: 0xC
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Maximum_Alloc(),
                        0xFFFF );

    // File Addr: 0xE
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Initial_SS(),
                        0x0000 );

    // File Addr: 0x10
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Initial_SP(),
                        0x00B8 );

    // File Addr: 0x12
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Checksum(),
                        0x0000 );

    // File Addr: 0x14
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_IP_Value(),
                        0x0000 );

    // File Addr: 0x16
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Initial_CS(),
                        0x0000 );

    // File Addr: 0x18
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_File_Address(),
                        0x0040 );

    // File Addr: 0x1A
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Overlay_Number(),
                        0x0000 );

    // File Addr: 0x1C
    // Check reserved word
    boost::uint8_t const* word_ptr = m_dos_hdr->get_Reserved_Word();
    for ( boost::uint8_t i = 0; i < DOS_Header::RES_SIZE; i++ )
        {
            BOOST_CHECK_EQUAL ( word_ptr[i], 0x00 );
        }

    // File Addr: 0x20
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_Behavior_Bits(),
                        0x0000 );

    // File Addr: 0x22
    boost::uint8_t const* word2_ptr = m_dos_hdr->get_Reserved_Word2();
    for ( boost::uint8_t i = 0; i < DOS_Header::RES2_SIZE; i++ )
        {
            BOOST_CHECK_EQUAL ( word2_ptr[i], 0x00 );
        }

    // File Addr: 0x3C
    BOOST_CHECK_EQUAL ( m_dos_hdr->get_EXE_Header_Address(),
                        static_cast<boost::uint32_t>(0x000000D8) );

}

void test_pe_header_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/winhlp32.exe" ) );

    libreverse::wpef_module::Reader<32> m_reader ( m_file, true, true );

    m_reader.read_PE_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

    // File Addr: 0xD8
    BOOST_CHECK_EQUAL ( m_pe_hdr->get_Magic_Number (),
                        PE_Header<32>::PE_MAGIC_SIGNATURE );
}

void test_coff_header_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/winhlp32.exe" ) );

    libreverse::wpef_module::Reader<32> m_reader ( m_file, true, true );

    m_reader.read_PE_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

    wpef_types::COFF_Header::ptr_t m_coff_hdr = m_pe_hdr->get_COFF_Header();

    // File Addr: 0xDC
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Machine_Number(),
                        PE_Machine_Types::IMAGE_FILE_MACHINE_I386 );

    // File Addr: 0xDE
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Section_Header_Count(),
                        0x0003 );

    // File Addr: 0xE0
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Time_Stamp_Number (),
                        static_cast<boost::uint32_t>(0x41107B1D) );

    // File Addr: 0xE4
    // This is suppose to be 0x0 by the specification.
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Symbol_Table_Pointer (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0xE8
    // This is suppose to be 0x0 by the specification.
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Number_Of_Symbols (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // Determine if file type is executable then the optional header
    // size should be non-zero. In this case we are expecting a valid
    // size/
    BOOST_REQUIRE ( m_coff_hdr->is_Executable() );

    // File Addr: 0xEC
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Optional_Header_Size(),
                        0x00E0 );

    // File Addr: 0xEE
    BOOST_CHECK_EQUAL ( m_coff_hdr->get_Characteristic_Value(),
                        0x010F );
}

void test_optional_header_read ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/winhlp32.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_PE_Header ();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    wpef_types::PE_Header<32>::ptr_t m_pe_hdr = m_hdr->get_PE_Header ();

    wpef_types::PE_Optional_Header<32>::ptr_t m_opt_hdr = m_pe_hdr->get_Optional_Header();

    //std::cout << m_opt_hdr->to_String() << std::endl;

    // File Addr: 0xF0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Magic_Value(),
                        PE_Optional_Header<32>::PE_EXECUTABLE );

    // File Addr: 0xF2
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Linker_Version(),
                        0x07 );

    // File Addr: 0xF3
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Linker_Version(),
                        0x0A );

    // File Addr: 0xF4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Code(),
                        static_cast<boost::uint32_t>(0x00038C00) );

    // File Addr: 0xF8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Init_Data(),
                        static_cast<boost::uint32_t>(0x0000EC00) );

    // File Addr: 0xFC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Uninitialized_Data(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x100
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Entry_Point(),
                        static_cast<boost::uint32_t>(0x00037D72) );

    // File Addr: 0x104
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Of_Code(),
                        static_cast<boost::uint32_t>(0x00001000) );
    // File Addr: 0x108
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Of_Data(),
                        static_cast<boost::uint32_t>(0x0003A000) );

    // File Addr: 0x10C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Image_Base(),
                        static_cast<boost::uint32_t>(0x01000000) );

    // File Addr: 0x110
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Section_Alignment(),
                        static_cast<boost::uint32_t>(0x00001000) );

    // File Addr: 0x114
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_File_Alignment(),
                        static_cast<boost::uint32_t>(0x00000200) );

    BOOST_CHECK ( m_opt_hdr->get_Section_Alignment() >
                  m_opt_hdr->get_File_Alignment() );


    BOOST_CHECK ( m_opt_hdr->get_File_Alignment() % 2 == 0 );

    BOOST_CHECK ( ( m_opt_hdr->get_File_Alignment() >= 512 ) &&
                  ( m_opt_hdr->get_File_Alignment() <= 640000 ) );

    // File Addr: 0x118
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Operating_System_Version(),
                        0x0005 );

    // File Addr: 0x11A
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Operating_System_Version(),
                        0x0001 );

    // File Addr: 0x11C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Image_Version(),
                        0x0005 );

    // File Addr: 0x11E
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Image_Version(),
                        0x0001 );

    // File Addr: 0x120
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Major_Subsystem_Version(),
                        0x0004 );

    // File Addr: 0x122
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Minor_Subsystem_Version(),
                        static_cast<boost::uint16_t>(0x0000) );

    // File Addr: 0x124
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Win32_Version_Value(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x128
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Image(),
                        static_cast<boost::uint32_t>(0x00049000) );

    // File Addr: 0x12C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Headers(),
                        static_cast<boost::uint32_t>(0x00000400) );  

    // File Addr: 0x130
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Checksum(),
                        static_cast<boost::uint32_t>(0x0004BF8A) );  

    // File Addr: 0x134
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Subsystem(),
                        0x0002 );  

    // File Addr: 0x136
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_DLL_Characteristics(),
                        static_cast<boost::uint16_t>(0x0000) );

    // File Addr: 0x138
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Stack_Reserve(),
                        static_cast<boost::uint32_t>(0x00040000) );

    // File Addr: 0x13C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Stack_Commit(),
                        static_cast<boost::uint32_t>(0x00001000) );

    // File Addr: 0x140
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Heap_Reserve(),
                        static_cast<boost::uint32_t>(0x00100000) );

    // File Addr: 0x144
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Size_Of_Heap_Commit(),
                        static_cast<boost::uint32_t>(0x00001000) );

    // File Addr: 0x148
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Loader_Flags(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x14C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Number_Of_RVA_And_Sizes(),
                        static_cast<boost::uint32_t>(0x00000010) );

    // File Addr: 0x150
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Export_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x154
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Export_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x158
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Table_Address (),
                        static_cast<boost::uint32_t>(0x00037FF4) );

    // File Addr: 0x15C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Table_Size(),
                        static_cast<boost::uint32_t>(0x0000008C) );

    // File Addr: 0x160
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Resource_Table_Address (),
                        static_cast<boost::uint32_t>(0x0003E000) );

    // File Addr: 0x164
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Resource_Table_Size(),
                        static_cast<boost::uint32_t>(0x0000AF00) );

    // File Addr: 0x168
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Exception_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x16C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Exception_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x170
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Certificate_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x174
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Certificate_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x178
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Relocation_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x17C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Base_Relocation_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x180
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Debug_Table_Address (),
                        static_cast<boost::uint32_t>(0x00001580) );

    // File Addr: 0x184
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Debug_Table_Size(),
                        static_cast<boost::uint32_t>(0x0000001C) );

    // File Addr: 0x188
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Architecture_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x18C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Architecture_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x190
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Global_Ptr_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x194
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Global_Ptr_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x198
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Thread_Local_Storage_Table_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x19C
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Thread_Local_Storage_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1A0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Load_Config_Table_Address (),
                        static_cast<boost::uint32_t>(0x00002B98) );

    // File Addr: 0x1A4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Load_Config_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000040) );

    // File Addr: 0x1A8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Bound_Import_Address (),
                        static_cast<boost::uint32_t>(0x00000248) );

    // File Addr: 0x1AC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Bound_Import_Size(),
                        static_cast<boost::uint32_t>(0x00000090) );

    // File Addr: 0x1B0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Address_Table_Address (),
                        static_cast<boost::uint32_t>(0x00001000) );

    // File Addr: 0x1B4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Import_Address_Table_Size(),
                        static_cast<boost::uint32_t>(0x00000574) );

    // File Addr: 0x1B8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Delay_Import_Descriptor_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1BC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Delay_Import_Descriptor_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );


    // File Addr: 0x1C0
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Clr_Runtime_Header_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1C4
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Clr_Runtime_Header_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1C8
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Reserved_Address (),
                        static_cast<boost::uint32_t>(0x00000000) );

    // File Addr: 0x1CC
    BOOST_CHECK_EQUAL ( m_opt_hdr->get_Reserved_Size(),
                        static_cast<boost::uint32_t>(0x00000000) );;
}

void test_import_table_read ()
{
    boost::shared_ptr<File_ID> m_file
        ( new File_ID ( PWD_PREFIX
                        "/test_targets/winhlp32.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    data_types::Memory_Map::ptr_t m_map = m_reader.get_Memory_Map ();

    //std::cout << m_map->to_String() << std::endl;

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    BOOST_CHECK_EQUAL ( m_hdr->get_PE_Import_Directory_Count(),
                        static_cast<boost::uint32_t>(6) );

    wpef_types::Header<32>::Import_Directory_List_t::const_iterator pos =
        m_hdr->get_PE_Import_Directory_List_Begin();

    //-----------------------------------
    // First Table (Memory Addr: 0x1037FF4)
    //-----------------------------------

    // Mem Addr: 0x1037FF4
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00038554) );

    // Mem Addr: 0x1037FF8
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1037FFC
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038000
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x000387B4) );

    // Mem Addr: 0x1038004
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000014D4) );

    //-----------------------------------
    // Second Table (Memory Addr: 0x1038008)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x1038008
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00038080) );

    // Mem Addr: 0x103800C
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038010
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038014
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00038824) );

    // Mem Addr: 0x1038018
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00001000) );

    //-----------------------------------
    // Third Table (Memory Addr: 0x103801C)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x103801C
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x000381C8) );

    // Mem Addr: 0x1038020
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038024
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038028
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00038E44) );

    // Mem Addr: 0x103802C
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00001148) );

    //-----------------------------------
    // Fourth Table (Memory Addr: 0x1038030)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x1038030
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00038098) );

    // Mem Addr: 0x1038034
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038038
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x103803C
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x000392FC) );

    // Mem Addr: 0x1038040
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x00001018) );

    //-----------------------------------
    // Fifth Table (Memory Addr: 0x1038044)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x1038044
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x0003832C) );

    // Mem Addr: 0x1038048
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x103804C
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038050
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00039BB6) );

    // Mem Addr: 0x1038054
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000012AC) );

    //-----------------------------------
    // Sixth Table (Memory Addr: 0x1038058)
    //-----------------------------------
    pos++;

    // Mem Addr: 0x1038058
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Lookup_Table(),
                        static_cast<boost::uint32_t>(0x00038324) );

    // Mem Addr: 0x103805C
    BOOST_CHECK_EQUAL ( (*pos)->get_Timestamp(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038060
    BOOST_CHECK_EQUAL ( (*pos)->get_Forwarder_Chain(),
                        static_cast<boost::uint32_t>(0xFFFFFFFF) );

    // Mem Addr: 0x1038064
    BOOST_CHECK_EQUAL ( (*pos)->get_Name_RVA(),
                        static_cast<boost::uint32_t>(0x00039BDC) );

    // Mem Addr: 0x1038068
    BOOST_CHECK_EQUAL ( (*pos)->get_Import_Address_Table(),
                        static_cast<boost::uint32_t>(0x000012A4) );
}

void test_section_headers ()
{
    boost::shared_ptr<File_ID> m_file ( new File_ID ( PWD_PREFIX
                                                      "/test_targets/winhlp32.exe" ) );

    Reader<32> m_reader ( m_file, true, true );

    m_reader.read_Section_Headers();

    wpef_types::Header<32>::ptr_t m_hdr = m_reader.get_Header ();

    BOOST_CHECK_EQUAL ( m_hdr->get_PE_Section_Header_Count (),
                        static_cast<boost::uint16_t>(0x0003) );

    wpef_types::Header<32>::Section_Header_Map_t::const_iterator pos =
        m_hdr->get_PE_Section_Header ( ".text" );

    //-----------------------------------
    // First Section (File Addr: 0x1D0)
    //-----------------------------------
    //   - name ( 0x1D0 ) = .text
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".text") == 0 );

    //   - virtual size (0x1D8) = 0x00038BE8
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00038BE8) );

    //   - virtual address (0x1DC) = 0x00001000 (RVA)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x00001000) );

    //   - size of raw data (0x1E0) = 0x00038C00
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00038C00) );

    //   - pointer to raw data (0x1E4) = 0x00000400
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00000400) );

    //   - pointer to relocations (0x1E8) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x1EC) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x1F0) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of line numbers (0x1F2) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - characteristics (0x1F4) = 0x60000020
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0x60000020) );

    //-----------------------------------
    // Second Section (File Addr: 0x1F8)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header (".data");

    //   - name ( 0x1F8 ) = .data
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".data") == 0 );

    //   - virtual size (0x200) = 0x00003A08
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x00003A08) );

    //   - virtual address (0x204) = 0x0003A000 (RVA)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x0003A000) );

    //   - size of raw data (0x208) = 0x00001400
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00001400) );

    //   - pointer to raw data (0x20C) = 0x00039000
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x00039000) );

    //   - pointer to relocations (0x210) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x214) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x218) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of line numbers (0x21A) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - characteristics (0x21C) = 0xC0000040
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0xC0000040) );

    //-----------------------------------
    // Third Section (File Addr: 0x220)
    //-----------------------------------
    pos = m_hdr->get_PE_Section_Header ( ".rsrc" );

    //   - name ( 0x220 ) = .rsrc
    BOOST_CHECK ( ((*pos).second)->get_Name().compare (".rsrc") == 0 );

    //   - virtual size (0x228) = 0x0000AF00
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Size(),
                        static_cast<boost::uint32_t>(0x0000AF00) );

    //   - virtual address (0x22C) = 0x0003E000 (RVA)
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Virtual_Address(),
                        static_cast<boost::uint32_t>(0x0003E000) );

    //   - size of raw data (0x230) = 0x0000B000
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Size_Of_Raw_Data(),
                        static_cast<boost::uint32_t>(0x0000B000) );

    //   - pointer to raw data (0x234) = 0x0003A400
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Raw_Data(),
                        static_cast<boost::uint32_t>(0x0003A400) );

    //   - pointer to relocations (0x238) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Relocations(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - pointer to line numbers (0x23C) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Pointer_To_Line_Numbers(),
                        static_cast<boost::uint32_t>(0x00000000) );

    //   - number of relocations (0x240) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Relocation_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - number of line numbers (0x242) = 0x0
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Line_Number_Count(),
                        static_cast<boost::uint16_t>(0x0000) );

    //   - characteristics (0x1F4) = 0x40000040
    BOOST_CHECK_EQUAL ( ((*pos).second)->get_Characteristics_Value(),
                        static_cast<boost::uint32_t>(0x40000040) );  
}

test_suite*
init_unit_test_suite ( int , char** )
{
    test_suite* test = BOOST_TEST_SUITE ( "Winhlp32 test suite" );

    test->add ( BOOST_TEST_CASE ( &test_dos_header_read ) );
    test->add ( BOOST_TEST_CASE ( &test_pe_header_read ) );
    test->add ( BOOST_TEST_CASE ( &test_coff_header_read ) );
    test->add ( BOOST_TEST_CASE ( &test_optional_header_read ) );
    test->add ( BOOST_TEST_CASE ( &test_import_table_read ) );
    test->add ( BOOST_TEST_CASE ( &test_section_headers ) );

    return test;
}
