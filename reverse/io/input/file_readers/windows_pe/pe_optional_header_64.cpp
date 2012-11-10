/*  PE_Optional_Header_64.cpp

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

#include "PE_Optional_Header_64.h"
#include "PE_Subsystem.h"
#include "PE_Header_64.h"

#include "io/Byte_Converter.h"
#include "Trace.h"

#include <sstream>
#include <boost/format.hpp>
#include <iostream>
#include <iomanip>


using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse
{
    namespace wpef_module
    {

        boost::uint16_t const PE_Optional_Header_64::ROM_IMAGE = 0x0107;

        boost::uint16_t const PE_Optional_Header_64::PE_EXECUTABLE = 0x010B;

        boost::uint16_t const PE_Optional_Header_64::PE_PLUS_EXECUTABLE = 0x020B;

        PE_Optional_Header_64::PE_Optional_Header_64()
                : m_magic ( 0 ),
                m_major_linker_version ( 0 ),
                m_minor_linker_version ( 0 ),
                m_size_of_code ( 0 ),
                m_size_of_init_data ( 0 ),
                m_size_of_uninit_data ( 0 ),
                m_addr_of_entry_point ( 0 ),
                m_base_of_code ( 0 ),
                m_image_base ( 0 ),
                m_section_alignment ( 0 ),
                m_file_alignment ( 0 ),
                m_major_operating_system_version ( 0 ),
                m_minor_operating_system_version ( 0 ),
                m_major_image_version ( 0 ),
                m_minor_image_version ( 0 ),
                m_major_subsystem_version ( 0 ),
                m_minor_subsystem_version ( 0 ),
                m_win32_version_value ( 0 ),
                m_size_of_image ( 0 ),
                m_size_of_headers ( 0 ),
                m_checksum ( 0 ),
                m_subsystem ( 0 ),
                m_dll_characteristics ( 0 ),
                m_size_of_stack_reserve ( 0 ),
                m_size_of_stack_commit ( 0 ),
                m_size_of_heap_reserve ( 0 ),
                m_size_of_heap_commit ( 0 ),
                m_loader_flags ( 0 ),
                m_number_of_rva_and_sizes ( 0 ),
                m_export_table_address ( 0 ),
                m_export_table_size ( 0 ),
                m_import_table_address ( 0 ),
                m_import_table_size ( 0 ),
                m_resource_table_address ( 0 ),
                m_resource_table_size ( 0 ),
                m_exception_table_address ( 0 ),
                m_exception_table_size ( 0 ),
                m_certificate_table_address ( 0 ),
                m_certificate_table_size ( 0 ),
                m_base_relocation_table_address ( 0 ),
                m_base_relocation_table_size ( 0 ),
                m_debug_table_address ( 0 ),
                m_debug_table_size ( 0 ),
                m_architecture_address ( 0 ),
                m_architecture_size ( 0 ),
                m_global_ptr_address ( 0 ),
                m_global_ptr_size ( 0 ),
                m_thread_local_storage_table_address ( 0 ),
                m_thread_local_storage_table_size ( 0 ),
                m_load_config_table_address ( 0 ),
                m_load_config_table_size ( 0 ),
                m_bound_import_address ( 0 ),
                m_bound_import_size ( 0 ),
                m_import_address_table_address ( 0 ),
                m_import_address_table_size ( 0 ),
                m_delay_import_descriptor_address ( 0 ),
                m_delay_import_descriptor_size ( 0 ),
                m_clr_runtime_header_address ( 0 ),
                m_clr_runtime_header_size ( 0 ),
                m_reserved_address ( 0 ),
                m_reserved_size ( 0 )
        {}

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        std::string
        PE_Optional_Header_64::to_String ( void ) const
        {
            std::stringstream output_str;

            output_str << "PE Optional Header:" << std::endl;

            output_str << boost::format ( "  Magic:                      %1%" ) %
            boost::io::group ( std::hex,
                               m_magic )
            << std::endl;

            output_str << boost::format ( "  Linker version:             %1%.%2%" ) %
            static_cast<boost::uint16_t> ( m_major_linker_version ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::setw ( 2 ),
                               static_cast<boost::uint16_t> ( m_minor_linker_version ) )
            << std::endl;

            output_str << boost::format ( "  Size of code:               %1X" ) %
            m_size_of_code
            << std::endl;

            output_str << boost::format ( "  Size of Initialized Data:   %1X" ) %
            m_size_of_init_data
            << std::endl;

            output_str << boost::format ( "  Size of Uninitialized Data: %1X" ) %
            m_size_of_uninit_data
            << std::endl;

            output_str << boost::format ( "  Address of entry point:     %1X" ) %
            m_addr_of_entry_point
            << std::endl;

            output_str << boost::format ( "  Base of code:               %1X" ) %
            m_base_of_code
            << std::endl;

            output_str << boost::format ( "  Base of image:              %1X" ) %
            m_image_base
            << std::endl;

            output_str << boost::format ( "  Section alignment:          %1X" ) %
            m_section_alignment
            << std::endl;

            output_str << boost::format ( "  File alignment:             %1X" ) %
            m_file_alignment
            << std::endl;

            output_str << boost::format ( "  OS System version:          %1%.%2%" ) %
            m_major_operating_system_version %
            boost::io::group ( std::setfill ( '0' ),
                               std::setw ( 2 ),
                               m_minor_operating_system_version )
            << std::endl;

            output_str << boost::format ( "  Image version:              %1%.%2%" ) %
            m_major_image_version %
            boost::io::group ( std::setfill ( '0' ),
                               std::setw ( 2 ),
                               m_minor_image_version )
            << std::endl;

            output_str << boost::format ( "  Subsystem version:          %1%.%2%" ) %
            m_major_subsystem_version %
            boost::io::group ( std::setfill ( '0' ),
                               std::setw ( 2 ),
                               m_minor_subsystem_version )
            << std::endl;

            output_str << "  Win32 Version:              "
            << m_win32_version_value
            << std::endl;

            output_str << boost::format ( "  Size of image:              %1X" ) %
            m_size_of_image
            << std::endl;

            output_str << boost::format ( "  Size of headers:            %1X" ) %
            m_size_of_headers
            << std::endl;

            output_str << boost::format ( "  Checksum:                   %1X" ) %
            m_checksum
            << std::endl;

            output_str << boost::format ( "  Sub-system:                 %1% (%2%)" )
            % m_subsystem
            % PE_Subsystem::get_String_Name ( m_subsystem )
            << std::endl;

            output_str << boost::format ( "  DLL characteristics:        %1X" ) %
            m_dll_characteristics
            << std::endl;

            output_str << boost::format ( "  Stack reserve size:         %1X" ) %
            m_size_of_stack_reserve
            << std::endl;

            output_str << boost::format ( "  Stack commit size:          %1X" ) %
            m_size_of_stack_commit
            << std::endl;

            output_str << boost::format ( "  Heap reserve size:          %1X" ) %
            m_size_of_heap_reserve
            << std::endl;

            output_str << boost::format ( "  Heap commit size:           %1X" ) %
            m_size_of_heap_commit
            << std::endl;

            output_str << boost::format ( "  Loader flags:               %1X" ) %
            m_loader_flags
            << std::endl;

            output_str << boost::format ( "  Number of RVA and sizes:    %1X" ) %
            m_number_of_rva_and_sizes
            << std::endl;

            output_str << boost::format ( "  Export table:                  %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_export_table_address ) %
            boost::io::group ( std::hex,
                               m_export_table_size )
            << std::endl;

            output_str << boost::format ( "  Import table:                  %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_import_table_address ) %
            boost::io::group ( std::hex,
                               m_import_table_size )
            << std::endl;

            output_str << boost::format ( "  Resource table:                %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_resource_table_address ) %
            boost::io::group ( std::hex,
                               m_resource_table_size )
            << std::endl;

            output_str << boost::format ( "  Exception table:               %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_exception_table_address ) %
            boost::io::group ( std::hex,
                               m_exception_table_size )
            << std::endl;

            output_str << boost::format ( "  Certificate table:             %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_certificate_table_address ) %
            boost::io::group ( std::hex,
                               m_certificate_table_size )
            << std::endl;

            output_str << boost::format ( "  Base Relocation table:         %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_base_relocation_table_address ) %
            boost::io::group ( std::hex,
                               m_base_relocation_table_size )
            << std::endl;

            output_str << boost::format ( "  Debug table:                   %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_debug_table_address ) %
            boost::io::group ( std::hex,
                               m_debug_table_size )
            << std::endl;

            output_str << boost::format ( "  Architecture:                  %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_architecture_address ) %
            boost::io::group ( std::hex,
                               m_architecture_size )
            << std::endl;

            output_str << boost::format ( "  Global Pointer table:          %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_global_ptr_address ) %
            boost::io::group ( std::hex,
                               m_global_ptr_size )
            << std::endl;

            output_str << boost::format ( "  Thread Local Storage table:    %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_thread_local_storage_table_address ) %
            boost::io::group ( std::hex,
                               m_thread_local_storage_table_size )
            << std::endl;

            output_str << boost::format ( "  Load Config table:             %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_load_config_table_address ) %
            boost::io::group ( std::hex,
                               m_load_config_table_size )
            << std::endl;

            output_str << boost::format ( "  Bound Import table:            %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_bound_import_address ) %
            boost::io::group ( std::hex,
                               m_bound_import_size )
            << std::endl;

            output_str << boost::format ( "  Import Address table:          %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_import_address_table_address ) %
            boost::io::group ( std::hex,
                               m_import_address_table_size )
            << std::endl;

            output_str << boost::format ( "  Delay Import Descriptor table: %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_delay_import_descriptor_address ) %
            boost::io::group ( std::hex,
                               m_delay_import_descriptor_size )
            << std::endl;

            output_str << boost::format ( "  CLR Runtime table:             %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_clr_runtime_header_address ) %
            boost::io::group ( std::hex,
                               m_clr_runtime_header_size )
            << std::endl;

            output_str << boost::format ( "  Reserved:                      %1% [ %2% ]" ) %
            boost::io::group ( std::hex,
                               m_reserved_address ) %
            boost::io::group ( std::hex,
                               m_reserved_size )
            << std::endl;

            return output_str.str();
        }

        /*!
         * \brief Convert the bit order of the stored data if host and data
         * endian types differ
         *
         * \param host_endian Endian type of host
         * \param data_endian Endian type of data
         */
        void
        PE_Optional_Header_64::convert ()
        {
            io::Byte_Converter::convert ( m_size_of_code );
            io::Byte_Converter::convert ( m_size_of_init_data );
            io::Byte_Converter::convert ( m_size_of_uninit_data );
            io::Byte_Converter::convert ( m_addr_of_entry_point );
            io::Byte_Converter::convert ( m_base_of_code );
            io::Byte_Converter::convert ( m_image_base );
            io::Byte_Converter::convert ( m_section_alignment );
            io::Byte_Converter::convert ( m_file_alignment );
            io::Byte_Converter::convert ( m_major_operating_system_version );
            io::Byte_Converter::convert ( m_minor_operating_system_version );
            io::Byte_Converter::convert ( m_major_image_version );
            io::Byte_Converter::convert ( m_minor_image_version );
            io::Byte_Converter::convert ( m_major_subsystem_version );
            io::Byte_Converter::convert ( m_minor_subsystem_version );
            io::Byte_Converter::convert ( m_win32_version_value );
            io::Byte_Converter::convert ( m_size_of_image );
            io::Byte_Converter::convert ( m_size_of_headers );
            io::Byte_Converter::convert ( m_checksum );
            io::Byte_Converter::convert ( m_subsystem );
            io::Byte_Converter::convert ( m_dll_characteristics );
            io::Byte_Converter::convert ( m_size_of_stack_reserve );
            io::Byte_Converter::convert ( m_size_of_stack_commit );
            io::Byte_Converter::convert ( m_size_of_heap_reserve );
            io::Byte_Converter::convert ( m_size_of_heap_commit );
            io::Byte_Converter::convert ( m_loader_flags );
            io::Byte_Converter::convert ( m_number_of_rva_and_sizes );
            io::Byte_Converter::convert ( m_export_table_address );
            io::Byte_Converter::convert ( m_export_table_size );
            io::Byte_Converter::convert ( m_import_table_address );
            io::Byte_Converter::convert ( m_import_table_size );
            io::Byte_Converter::convert ( m_resource_table_address );
            io::Byte_Converter::convert ( m_resource_table_size );
            io::Byte_Converter::convert ( m_exception_table_address );
            io::Byte_Converter::convert ( m_exception_table_size );
            io::Byte_Converter::convert ( m_certificate_table_address );
            io::Byte_Converter::convert ( m_certificate_table_size );
            io::Byte_Converter::convert ( m_base_relocation_table_address );
            io::Byte_Converter::convert ( m_base_relocation_table_size );
            io::Byte_Converter::convert ( m_debug_table_address );
            io::Byte_Converter::convert ( m_debug_table_size );
            io::Byte_Converter::convert ( m_architecture_address );
            io::Byte_Converter::convert ( m_architecture_size );
            io::Byte_Converter::convert ( m_global_ptr_address );
            io::Byte_Converter::convert ( m_global_ptr_size );
            io::Byte_Converter::convert ( m_thread_local_storage_table_address );
            io::Byte_Converter::convert ( m_thread_local_storage_table_size );
            io::Byte_Converter::convert ( m_load_config_table_address );
            io::Byte_Converter::convert ( m_load_config_table_size );
            io::Byte_Converter::convert ( m_bound_import_address );
            io::Byte_Converter::convert ( m_bound_import_size );
            io::Byte_Converter::convert ( m_import_address_table_address );
            io::Byte_Converter::convert ( m_import_address_table_size );
            io::Byte_Converter::convert ( m_delay_import_descriptor_address );
            io::Byte_Converter::convert ( m_delay_import_descriptor_size );
            io::Byte_Converter::convert ( m_clr_runtime_header_address );
            io::Byte_Converter::convert ( m_clr_runtime_header_size );
            io::Byte_Converter::convert ( m_reserved_address );
            io::Byte_Converter::convert ( m_reserved_size );
        }

        bool
        PE_Optional_Header_64::is_PE_File ( void )
        {
            return ( m_magic == PE_Header_64::PE_MAGIC_SIGNATURE );
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Magic_Value ( void ) const
        {
            return m_magic;
        }

        boost::uint8_t
        PE_Optional_Header_64::get_Major_Linker_Version ( void ) const
        {
            return m_major_linker_version;
        }

        boost::uint8_t
        PE_Optional_Header_64::get_Minor_Linker_Version ( void ) const
        {
            return m_minor_linker_version;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Code ( void ) const
        {
            return m_size_of_code;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Init_Data ( void ) const
        {
            return m_size_of_init_data;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Uninitialized_Data ( void ) const
        {
            return m_size_of_uninit_data;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Entry_Point ( void ) const
        {
            return m_addr_of_entry_point;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Base_Of_Code ( void ) const
        {
            return m_base_of_code;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Image_Base ( void ) const
        {
            return m_image_base;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Section_Alignment ( void ) const
        {
            return m_section_alignment;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_File_Alignment ( void ) const
        {
            return m_file_alignment;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Major_Operating_System_Version ( void ) const
        {
            return m_major_operating_system_version;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Minor_Operating_System_Version ( void ) const
        {
            return m_minor_operating_system_version;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Major_Image_Version ( void ) const
        {
            return m_major_image_version;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Minor_Image_Version ( void ) const
        {
            return m_minor_image_version;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Major_Subsystem_Version ( void ) const
        {
            return m_major_subsystem_version;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Minor_Subsystem_Version ( void ) const
        {
            return m_minor_subsystem_version;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Win32_Version_Value ( void ) const
        {
            return m_win32_version_value;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Image ( void ) const
        {
            return m_size_of_image;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Headers ( void ) const
        {
            return m_size_of_headers;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Checksum ( void ) const
        {
            return m_checksum;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_Subsystem ( void ) const
        {
            return m_subsystem;
        }

        boost::uint16_t
        PE_Optional_Header_64::get_DLL_Characteristics ( void ) const
        {
            return m_dll_characteristics;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Stack_Reserve ( void ) const
        {
            return m_size_of_stack_reserve;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Stack_Commit ( void ) const
        {
            return m_size_of_stack_commit;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Heap_Reserve ( void ) const
        {
            return m_size_of_heap_reserve;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Size_Of_Heap_Commit ( void ) const
        {
            return m_size_of_heap_commit;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Loader_Flags ( void ) const
        {
            return m_loader_flags;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Number_Of_RVA_And_Sizes ( void ) const
        {
            return m_number_of_rva_and_sizes;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Export_Table_Address ( void ) const
        {
            return m_export_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Export_Table_Size ( void ) const
        {
            return m_export_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Import_Table_Address ( void ) const
        {
            return m_import_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Import_Table_Size ( void ) const
        {
            return m_import_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Resource_Table_Address ( void ) const
        {
            return m_resource_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Resource_Table_Size ( void ) const
        {
            return m_resource_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Exception_Table_Address ( void ) const
        {
            return m_exception_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Exception_Table_Size ( void ) const
        {
            return m_exception_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Certificate_Table_Address ( void ) const
        {
            return m_certificate_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Certificate_Table_Size ( void ) const
        {
            return m_certificate_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Base_Relocation_Table_Address ( void ) const
        {
            return m_base_relocation_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Base_Relocation_Table_Size ( void ) const
        {
            return m_base_relocation_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Debug_Table_Address ( void ) const
        {
            return m_debug_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Debug_Table_Size ( void ) const
        {
            return m_debug_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Architecture_Address ( void ) const
        {
            return m_architecture_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Architecture_Size ( void ) const
        {
            return m_architecture_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Global_Ptr_Address ( void ) const
        {
            return m_global_ptr_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Global_Ptr_Size ( void ) const
        {
            return m_global_ptr_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Thread_Local_Storage_Table_Address ( void ) const
        {
            return m_thread_local_storage_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Thread_Local_Storage_Table_Size ( void ) const
        {
            return m_thread_local_storage_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Load_Config_Table_Address ( void ) const
        {
            return m_load_config_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Load_Config_Table_Size ( void ) const
        {
            return m_load_config_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Bound_Import_Address ( void ) const
        {
            return m_bound_import_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Bound_Import_Size ( void ) const
        {
            return m_bound_import_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Import_Address_Table_Address ( void ) const
        {
            return m_import_address_table_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Import_Address_Table_Size ( void ) const
        {
            return m_import_address_table_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Delay_Import_Descriptor_Address ( void ) const
        {
            return m_delay_import_descriptor_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Delay_Import_Descriptor_Size ( void ) const
        {
            return m_delay_import_descriptor_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Clr_Runtime_Header_Address ( void ) const
        {
            return m_clr_runtime_header_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Clr_Runtime_Header_Size ( void ) const
        {
            return m_clr_runtime_header_size;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Reserved_Address ( void ) const
        {
            return m_reserved_address;
        }

        boost::uint32_t
        PE_Optional_Header_64::get_Reserved_Size ( void ) const
        {
            return m_reserved_size;
        }

    } /* namespace wpef_module */
} /* namespace libreverse */
