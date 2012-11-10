/*  PE_File.cpp

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

#include "PE_File.h"
#include "AMD_IA_64_Exception_Table_Entry.h"
#include "ARM_POWERPC_SH_Exception_Table_Entry_32.h"
#include "ARM_POWERPC_SH_Exception_Table_Entry_64.h"
#include "Coff_Header.h"
#include "Header_32.h"
#include "Header_64.h"
#include "PE_Header_32.h"
#include "PE_Header_64.h"
#include "DOS_Header.h"
#include "DOS_Relocation_Header.h"
#include "PE_Section_Header.h"
#include "PE_Resource_Directory.h"
#include "PE_Resource_Directory_Entry.h"
#include "PE_Resource_Directory_String.h"
#include "PE_Resource_Data_Entry.h"
#include "PE_Export_Directory.h"
#include "PE_Import_Directory.h"
#include "PE_Debug_Directory.h"
#include "PE_Optional_Header_32.h"
#include "PE_Optional_Header_64.h"

#include "io/File_ID.h"
#include "Trace.h"

#include <iostream>
#include <sstream>

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse { namespace wpef_module {

    PE_File::PE_File ( io_types::File_ID::const_ptr_t filename )
      : m_file ( filename )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside PE_File constructor (File_ID)" );
    }

    PE_File::PE_File ( data_types::Memory_Map::ptr_t file_img_ptr,
		       io_types::File_ID::const_ptr_t filename )
      : m_file ( file_img_ptr, filename )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside PE_File constructor (Memory_Map, File_ID)" );
    }

    bool
    PE_File::init (void)
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside PE_File::init" );

      return m_file.init();
    }

    boost::uint32_t PE_File::get_File_Size (void) const
    {

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside PE_File::get_File_Size" );

      return m_file.size();
    }

    data_types::Memory_Map::ptr_t
    PE_File::get_Memory_Map (void) const
    {
      return m_file.get_Map_Ptr();
    }

    void PE_File::read_DOS_Header ( wpef_types::DOS_Header::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_DOS_Header" );

      m_file.read(&(obj->e_magic));
      m_file.read(&(obj->e_cblp));
      m_file.read(&(obj->e_cp));
      m_file.read(&(obj->e_crlc));
      m_file.read(&(obj->e_cparhdr));
      m_file.read(&(obj->e_minalloc));
      m_file.read(&(obj->e_maxalloc));
      m_file.read(&(obj->e_ss));
      m_file.read(&(obj->e_sp));
      m_file.read(&(obj->e_csum));
      m_file.read(&(obj->e_ip));
      m_file.read(&(obj->e_cs));
      m_file.read(&(obj->e_lfarlc));
      m_file.read(&(obj->e_ovno));

      for (uint8_t i = 0; i < DOS_Header::RES_SIZE; i++)
	{
	  m_file.read(&(obj->e_res[i]));
	}

      m_file.read(&(obj->e_behavior_bits));

      for (uint8_t i = 0; i < DOS_Header::RES2_SIZE; ++i)
	{
	  m_file.read(&(obj->e_res2[i]));
	}

      m_file.read(&(obj->e_lfanew));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_DOS_Header" );
    }

    void PE_File::read_DOS_Relocation_Header ( wpef_types::DOS_Relocation_Header::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_DOS_Relocation_Header" );
      
      m_file.read(&(obj->m_offset));
      m_file.read(&(obj->m_segment));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_DOS_Relocation_Header" );
    }

    void PE_File::read_PE_Header ( wpef_types::PE_Header_32::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Header (32-bit)" );

      m_file.read(&(obj->p_magic));

      wpef_types::COFF_Header::ptr_t coff_hdr_ptr (new COFF_Header());
      this->read_COFF_Header(coff_hdr_ptr);
      obj->m_coff_hdr_ptr = coff_hdr_ptr;

      wpef_types::PE_Optional_Header_32::ptr_t opt_ptr ( new PE_Optional_Header_32() );
      this->read_PE_Optional_Header(opt_ptr);
      obj->m_opt_hdr_ptr = opt_ptr;

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Header (32-bit)" );
    }

    void PE_File::read_PE_Header ( wpef_types::PE_Header_64::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Header (64-bit)" );

      m_file.read(&(obj->p_magic));

      wpef_types::COFF_Header::ptr_t coff_hdr_ptr (new COFF_Header());
      this->read_COFF_Header(coff_hdr_ptr);
      obj->m_coff_hdr_ptr = coff_hdr_ptr;

      wpef_types::PE_Optional_Header_64::ptr_t opt_ptr ( new PE_Optional_Header_64() );
      this->read_PE_Optional_Header ( opt_ptr );
      obj->m_opt_hdr_ptr = opt_ptr;

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Header (64-bit)" );
    }

    void PE_File::read_COFF_Header ( wpef_types::COFF_Header::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_COFF_Header" );

      m_file.read(&(obj->m_machine));
      m_file.read(&(obj->m_number_of_sections));
      m_file.read(&(obj->m_time_date_stamp));
      m_file.read(&(obj->m_pointer_to_symbol_table));
      m_file.read(&(obj->m_number_of_symbols));
      m_file.read(&(obj->m_size_of_optional_header));
      m_file.read(&(obj->m_characteristics));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_COFF_Header" );
    }

    void
    PE_File::read_PE_Optional_Header ( wpef_types::PE_Optional_Header_32::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Optional_Header (32-bit)" );

      m_file.read(&(obj->m_magic));
      m_file.read(&(obj->m_major_linker_version));
      m_file.read(&(obj->m_minor_linker_version));
      m_file.read(&(obj->m_size_of_code));
      m_file.read(&(obj->m_size_of_init_data));
      m_file.read(&(obj->m_size_of_uninit_data));
      m_file.read(&(obj->m_addr_of_entry_point));
      m_file.read(&(obj->m_base_of_code));
      m_file.read(&(obj->m_base_of_data));
      m_file.read(&(obj->m_image_base));
      m_file.read(&(obj->m_section_alignment));
      m_file.read(&(obj->m_file_alignment));
      m_file.read(&(obj->m_major_operating_system_version));
      m_file.read(&(obj->m_minor_operating_system_version));
      m_file.read(&(obj->m_major_image_version));
      m_file.read(&(obj->m_minor_image_version));
      m_file.read(&(obj->m_major_subsystem_version));
      m_file.read(&(obj->m_minor_subsystem_version));
      m_file.read(&(obj->m_win32_version_value));
      m_file.read(&(obj->m_size_of_image));
      m_file.read(&(obj->m_size_of_headers));
      m_file.read(&(obj->m_checksum));
      m_file.read(&(obj->m_subsystem));
      m_file.read(&(obj->m_dll_characteristics));
      m_file.read(&(obj->m_size_of_stack_reserve));
      m_file.read(&(obj->m_size_of_stack_commit));
      m_file.read(&(obj->m_size_of_heap_reserve));
      m_file.read(&(obj->m_size_of_heap_commit));
      m_file.read(&(obj->m_loader_flags));
      m_file.read(&(obj->m_number_of_rva_and_sizes));
      m_file.read(&(obj->m_export_table_address));
      m_file.read(&(obj->m_export_table_size));
      m_file.read(&(obj->m_import_table_address));
      m_file.read(&(obj->m_import_table_size));
      m_file.read(&(obj->m_resource_table_address));
      m_file.read(&(obj->m_resource_table_size));
      m_file.read(&(obj->m_exception_table_address));
      m_file.read(&(obj->m_exception_table_size));
      m_file.read(&(obj->m_certificate_table_address));
      m_file.read(&(obj->m_certificate_table_size));
      m_file.read(&(obj->m_base_relocation_table_address));
      m_file.read(&(obj->m_base_relocation_table_size));
      m_file.read(&(obj->m_debug_table_address));
      m_file.read(&(obj->m_debug_table_size));
      m_file.read(&(obj->m_architecture_address));
      m_file.read(&(obj->m_architecture_size));
      m_file.read(&(obj->m_global_ptr_address));
      m_file.read(&(obj->m_global_ptr_size));
      m_file.read(&(obj->m_thread_local_storage_table_address));
      m_file.read(&(obj->m_thread_local_storage_table_size));
      m_file.read(&(obj->m_load_config_table_address));
      m_file.read(&(obj->m_load_config_table_size));
      m_file.read(&(obj->m_bound_import_address));
      m_file.read(&(obj->m_bound_import_size));
      m_file.read(&(obj->m_import_address_table_address));
      m_file.read(&(obj->m_import_address_table_size));
      m_file.read(&(obj->m_delay_import_descriptor_address));
      m_file.read(&(obj->m_delay_import_descriptor_size));
      m_file.read(&(obj->m_clr_runtime_header_address));
      m_file.read(&(obj->m_clr_runtime_header_size));
      m_file.read(&(obj->m_reserved_address));
      m_file.read(&(obj->m_reserved_size));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Optional_Header (32-bit)" );
    }

    void
    PE_File::read_PE_Optional_Header ( wpef_types::PE_Optional_Header_64::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Optional_Header (64-bit)" );

      m_file.read(&(obj->m_magic));
      m_file.read(&(obj->m_major_linker_version));
      m_file.read(&(obj->m_minor_linker_version));
      m_file.read(&(obj->m_size_of_code));
      m_file.read(&(obj->m_size_of_init_data));
      m_file.read(&(obj->m_size_of_uninit_data));
      m_file.read(&(obj->m_addr_of_entry_point));
      m_file.read(&(obj->m_base_of_code));
      m_file.read(&(obj->m_image_base));
      m_file.read(&(obj->m_section_alignment));
      m_file.read(&(obj->m_file_alignment));
      m_file.read(&(obj->m_major_operating_system_version));
      m_file.read(&(obj->m_minor_operating_system_version));
      m_file.read(&(obj->m_major_image_version));
      m_file.read(&(obj->m_minor_image_version));
      m_file.read(&(obj->m_major_subsystem_version));
      m_file.read(&(obj->m_minor_subsystem_version));
      m_file.read(&(obj->m_win32_version_value));
      m_file.read(&(obj->m_size_of_image));
      m_file.read(&(obj->m_size_of_headers));
      m_file.read(&(obj->m_checksum));
      m_file.read(&(obj->m_subsystem));
      m_file.read(&(obj->m_dll_characteristics));
      m_file.read(&(obj->m_size_of_stack_reserve));
      m_file.read(&(obj->m_size_of_stack_commit));
      m_file.read(&(obj->m_size_of_heap_reserve));
      m_file.read(&(obj->m_size_of_heap_commit));
      m_file.read(&(obj->m_loader_flags));
      m_file.read(&(obj->m_number_of_rva_and_sizes));
      m_file.read(&(obj->m_export_table_address));
      m_file.read(&(obj->m_export_table_size));
      m_file.read(&(obj->m_import_table_address));
      m_file.read(&(obj->m_import_table_size));
      m_file.read(&(obj->m_resource_table_address));
      m_file.read(&(obj->m_resource_table_size));
      m_file.read(&(obj->m_exception_table_address));
      m_file.read(&(obj->m_exception_table_size));
      m_file.read(&(obj->m_certificate_table_address));
      m_file.read(&(obj->m_certificate_table_size));
      m_file.read(&(obj->m_base_relocation_table_address));
      m_file.read(&(obj->m_base_relocation_table_size));
      m_file.read(&(obj->m_debug_table_address));
      m_file.read(&(obj->m_debug_table_size));
      m_file.read(&(obj->m_architecture_address));
      m_file.read(&(obj->m_architecture_size));
      m_file.read(&(obj->m_global_ptr_address));
      m_file.read(&(obj->m_global_ptr_size));
      m_file.read(&(obj->m_thread_local_storage_table_address));
      m_file.read(&(obj->m_thread_local_storage_table_size));
      m_file.read(&(obj->m_load_config_table_address));
      m_file.read(&(obj->m_load_config_table_size));
      m_file.read(&(obj->m_bound_import_address));
      m_file.read(&(obj->m_bound_import_size));
      m_file.read(&(obj->m_import_address_table_address));
      m_file.read(&(obj->m_import_address_table_size));
      m_file.read(&(obj->m_delay_import_descriptor_address));
      m_file.read(&(obj->m_delay_import_descriptor_size));
      m_file.read(&(obj->m_clr_runtime_header_address));
      m_file.read(&(obj->m_clr_runtime_header_size));
      m_file.read(&(obj->m_reserved_address));
      m_file.read(&(obj->m_reserved_size));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Optional_Header (64-bit)" );
    }

    void
    PE_File::read_PE_Section_Header ( wpef_types::PE_Section_Header::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Section_Header" );

      obj->m_name = m_file.read_UTF8_String ( PE_Section_Header::SECTION_NAME_SIZE );

      m_file.read(&(obj->m_virtual_size));
      m_file.read(&(obj->m_virtual_address));
      m_file.read(&(obj->m_size_of_raw_data));
      m_file.read(&(obj->m_pointer_to_raw_data));
      m_file.read(&(obj->m_pointer_to_relocations));
      m_file.read(&(obj->m_pointer_to_line_numbers));
      m_file.read(&(obj->m_number_of_relocations));
      m_file.read(&(obj->m_number_of_line_numbers));
      m_file.read(&(obj->m_characteristics));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Section_Header" );
    }

    void
    PE_File::read_PE_Resource_Directory ( wpef_types::PE_Resource_Directory::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Resource_Directory" );

      m_file.read (&(obj->m_characteristics ));
      m_file.read (&(obj->m_time_date_stamp ));
      m_file.read (&(obj->m_major_version ));
      m_file.read (&(obj->m_minor_version ));
      m_file.read (&(obj->m_num_of_name_entries ));
      m_file.read (&(obj->m_num_of_id_entries ));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Resource_Directory" );
    }

    void
    PE_File::read_PE_Resource_Directory_Entry ( wpef_types::PE_Resource_Directory_Entry::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Resource_Directory_Entry" );

      m_file.read (&(obj->m_name ));
      m_file.read (&(obj->m_rva ));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Resource_Directory_Entry" );
    }
    
    api::Results::Values
    PE_File::read_PE_Resource_Data_Entry ( wpef_types::PE_Resource_Data_Entry::ptr_t obj,
					   boost::uint32_t base_address )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Resource_Data_Entry" );

      m_file.read (&(obj->m_data_rva ));
      m_file.read (&(obj->m_size ));
      m_file.read (&(obj->m_codepage ));
      m_file.read (&(obj->m_reserved ));

      data_types::Memory_Map::ptr_t file_img_ptr = m_file.get_Map_Ptr();

      if ( file_img_ptr->address_Seek ( obj->m_data_rva + base_address )
	   != data_types::Memory_Map::SUCCESS )
	{
	  obj->m_data_rva = 0;
	  obj->m_size = 0;
	  obj->m_codepage = 0;
	  obj->m_reserved = 0;

	  return api::Results::INVALID_INDEX;
	}

      std::pair<data_types::Memory_Map::ptr_t,boost::int8_t> data_entry_map =
	file_img_ptr->subset ( obj->m_size );

      if ( data_entry_map.second != data_types::Memory_Map::SUCCESS )
	{
	  return api::Results::INVALID_INDEX;
	}

      obj->m_data_string = data_entry_map.first->to_String();

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Resource_Data_Entry" );

      return api::Results::SUCCESS;
    }

    void
    PE_File::read_PE_Export_Directory ( wpef_types::PE_Export_Directory::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Export_Directory" );

      m_file.read (&(obj->m_export_flags ));
      m_file.read (&(obj->m_time_date_stamp ));
      m_file.read (&(obj->m_major_version ));
      m_file.read (&(obj->m_minor_version ));
      m_file.read (&(obj->m_name_rva ));
      m_file.read (&(obj->m_ordinal_base ));
      m_file.read (&(obj->m_address_table_entries ));
      m_file.read (&(obj->m_num_of_name_pointers ));
      m_file.read (&(obj->m_export_address_table_rva ));
      m_file.read (&(obj->m_name_pointer_rva ));
      m_file.read (&(obj->m_ordinal_table_rva ));

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Export_Directory" );
    }

    void
    PE_File::read_PE_Resource_Directory_String ( wpef_types::PE_Resource_Directory_String::ptr_t obj )
    {
      m_file.read (&(obj->m_size ));

      obj->m_text = m_file.read_UTF16_String ( obj->m_size );
    }

    void
    PE_File::read_PE_Import_Directory ( wpef_types::PE_Import_Directory::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Import_Directory" );

      m_file.read ( &( obj->m_import_lookup_table ) );
      m_file.read ( &( obj->m_timestamp ) );
      m_file.read ( &( obj->m_forwarder_chain ) );
      m_file.read ( &( obj->m_name_rva ) );
      m_file.read ( &( obj->m_import_address_table ) );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Import_Directory" );
    }

    void
    PE_File::read_Null_Terminated_String ( std::string& obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Null_Terminated_String" );

      std::stringstream output;

      boost::uint8_t val = 0;
      m_file.read ( &val );

      while ( val != 0 )
	{
	  output << val;
	  m_file.read ( &val );
	}

      data_types::Memory_Map::ptr_t file_img_ptr = m_file.get_Map_Ptr();

      boost::uint32_t index = file_img_ptr->get_Present_Position_Value () - 1;

      if ( ! ( index % 2 == 0 ) )
	{
	  file_img_ptr->index_Seek ( index++ );
	}

      obj = output.str();

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Null_Terminated_String" );
    }

    void
    PE_File::read_PE_Debug_Directory ( wpef_types::PE_Debug_Directory::ptr_t obj)
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_PE_Debug_Directory" );

      m_file.read ( &( obj->m_characteristics ) );
      m_file.read ( &( obj->m_time_date_stamp ) );
      m_file.read ( &( obj->m_major_version ) );
      m_file.read ( &( obj->m_minor_version ) );
      m_file.read ( &( obj->m_type ) );
      m_file.read ( &( obj->m_size_of_data ) );
      m_file.read ( &( obj->m_address_of_raw_data ) );
      m_file.read ( &( obj->m_pointer_to_raw_data ) );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_PE_Debug_Directory" );
    }

    api::Results::Values
    PE_File::address_Seek ( boost::uint32_t address )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::address_Seek" );

      // - Init source to where data will be read.
      data_types::Memory_Map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

      if ( src_map_ptr->address_Seek ( address ) != data_types::Memory_Map::SUCCESS )
	{
	  return api::Results::INVALID_INDEX;
	}

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::address_Seek" );

      return api::Results::SUCCESS;
    }

    void
    PE_File::index_Seek ( boost::uint32_t offset )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::index_Seek" );

      // - Init source to where data will be read.
      data_types::Memory_Map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

      src_map_ptr->index_Seek ( offset );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::index_Seek" );
    }

    void
    PE_File::copy ( data_types::Memory_Map::ptr_t dest_ptr,
		    boost::uint32_t length )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::copy" );

      data_types::Memory_Map::ptr_t src_map_ptr = m_file.get_Map_Ptr();
        
      dest_ptr->copy ( src_map_ptr, length );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::copy" );
    }

    io_types::File_ID::const_ptr_t
    PE_File::get_ID (void) const
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside PE_File::get_ID" );

      return m_file.get_ID();
    }

    boost::uint32_t
    PE_File::get_Present_Position_Value (void) const
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside PE_File::get_Present_Position_Value" );

      data_types::Memory_Map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

      return src_map_ptr->get_Present_Position_Value ();
    }

    void
    PE_File::read_AMD_IA_64_Exception ( wpef_types::AMD_IA_64_Exception_Table_Entry::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_AM_IA_64_Exception" );

      m_file.read ( &( obj->m_begin_address ) );
      m_file.read ( &( obj->m_end_address ) );
      m_file.read ( &( obj->m_unwind_information ) );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_AM_IA_64_Exception" );
    }

    void
    PE_File::read_ARM_POWERPC_SH_Exception ( wpef_types::ARM_POWERPC_SH_Exception_Table_Entry_32::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_AM_POWERPC_SH_Exception (32-bit)" );

      m_file.read ( &( obj->m_begin_address ) );

      boost::uint32_t value = 0;
      m_file.read ( &value );

      // Prolog length (Bits 31-24)
      // Function length (Bits 23-2)
      // 32-bit flag (Bit 1)
      // Exception flag (Bit 0)
      obj->m_prolog_length = ( value & 0xFF000000 ) >> 24;
      obj->m_function_length = ( value & 0x00FFFFFC ) >> 2;
      obj->m_32bit_flag = ( value & 0x00000002 ) >> 1;
      obj->m_exception_flag = ( value & 0x00000001 );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_AM_POWERPC_SH_Exception (32-bit)" );
    }

    void
    PE_File::read_ARM_POWERPC_SH_Exception ( wpef_types::ARM_POWERPC_SH_Exception_Table_Entry_64::ptr_t obj )
    {
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering PE_File::read_AM_POWERPC_SH_Exception (64-bit)" );

      m_file.read ( &( obj->m_begin_address ) );

      boost::uint32_t value = 0;
      m_file.read ( &value );

      // Prolog length (Bits 31-24)
      // Function length (Bits 23-2)
      // 32-bit flag (Bit 1)
      // Exception flag (Bit 0)
      obj->m_prolog_length = ( value & 0xFF000000 ) >> 24;
      obj->m_function_length = ( value & 0x00FFFFFC ) >> 2;
      obj->m_32bit_flag = ( value & 0x00000002 ) >> 1;
      obj->m_exception_flag = ( value & 0x00000001 );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting PE_File::read_AM_POWERPC_SH_Exception (64-bit)" );
    }

  } /* namespace wpef_module */
} /* namespace libreverse */
