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

#include <reverse/io/input/file_readers/windows_pe/pe_file.hpp>
#include <reverse/io/input/file_readers/windows_pe/amd_ia_64_exception_table_entry.hpp>
#include <reverse/io/input/file_readers/windows_pe/arm_powerpc_sh_exception_table_entry_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/arm_powerpc_sh_exception_table_entry_64.hpp>
#include <reverse/io/input/file_readers/windows_pe/coff_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/header_64.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_header_64.hpp>
#include <reverse/io/input/file_readers/windows_pe/dos_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/dos_relocation_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_section_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_resource_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_resource_directory_entry.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_resource_directory_string.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_resource_data_entry.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_export_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_import_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_debug_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_optional_header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_optional_header_64.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/trace.hpp>

#include <iostream>
#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  pe_file::pe_file ( boost::shared_ptr < const file_id > filename )
	    : m_file ( filename )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "inside pe_file constructor (file_id)" );
	  }

	  pe_file::pe_file ( boost::shared_ptr < data_containers::memory_map > file_img_ptr,
			     boost::shared_ptr < const io::file_id > filename )
	    : m_file ( file_img_ptr, filename )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "inside pe_file constructor (memory_map, file_id)" );
	  }

	  bool
	  pe_file::init (void)
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "inside pe_file::init" );

	    return m_file.init();
	  }

	  boost::uint32_t pe_file::get_file_size (void) const
	  {

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "inside pe_file::get_file_size" );

	    return m_file.size();
	  }

	  boost::shared_ptr < const data_containers::memory_map >
	  pe_file::get_memory_map (void) const
	  {
	    return m_file.get_map_ptr();
	  }

	  void pe_file::read_dos_header ( boost::shared_ptr < dos_header > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_dos_header" );

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

	    for (uint8_t i = 0; i < dos_header::res_size; i++)
	      {
		m_file.read(&(obj->e_res[i]));
	      }

	    m_file.read(&(obj->e_behavior_bits));

	    for (uint8_t i = 0; i < dos_header::res2_size; ++i)
	      {
		m_file.read(&(obj->e_res2[i]));
	      }

	    m_file.read(&(obj->e_lfanew));

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_dos_header" );
	  }

	  void pe_file::read_dos_relocation_header ( boost::shared_ptr < dos_relocation_header > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_dos_relocation_header" );
      
	    m_file.read(&(obj->m_offset));
	    m_file.read(&(obj->m_segment));

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_dos_relocation_header" );
	  }

	  void pe_file::read_pe_header ( boost::shared_ptr < pe_header_32 > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_header (32-bit)" );

	    m_file.read(&(obj->p_magic));

	    boost::shared_ptr < coff_header > coff_hdr_ptr (new coff_header());
	    this->read_coff_header(coff_hdr_ptr);
	    obj->m_coff_hdr_ptr = coff_hdr_ptr;

	    boost::shared_ptr < pe_optional_header_32 > opt_ptr ( new pe_optional_header_32() );
	    this->read_pe_optional_header(opt_ptr);
	    obj->m_opt_hdr_ptr = opt_ptr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_header (32-bit)" );
	  }

	  void pe_file::read_pe_header ( boost::shared_ptr < pe_header_64 > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_header (64-bit)" );

	    m_file.read(&(obj->p_magic));

	    boost::shared_ptr < coff_header > coff_hdr_ptr (new coff_header());
	    this->read_coff_header(coff_hdr_ptr);
	    obj->m_coff_hdr_ptr = coff_hdr_ptr;

	    boost::shared_ptr < pe_optional_header_64 > opt_ptr ( new pe_optional_header_64() );
	    this->read_pe_optional_header ( opt_ptr );
	    obj->m_opt_hdr_ptr = opt_ptr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_header (64-bit)" );
	  }

	  void pe_file::read_coff_header ( boost::shared_ptr < coff_header > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_coff_header" );

	    m_file.read(&(obj->m_machine));
	    m_file.read(&(obj->m_number_of_sections));
	    m_file.read(&(obj->m_time_date_stamp));
	    m_file.read(&(obj->m_pointer_to_symbol_table));
	    m_file.read(&(obj->m_number_of_symbols));
	    m_file.read(&(obj->m_size_of_optional_header));
	    m_file.read(&(obj->m_characteristics));

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_coff_header" );
	  }

	  void
	  pe_file::read_pe_optional_header ( boost::shared_ptr < pe_optional_header_32 > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_optional_header (32-bit)" );

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

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_optional_header (32-bit)" );
	  }

	  void
	  pe_file::read_pe_optional_header ( boost::shared_ptr < pe_optional_header_64 > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_optional_header (64-bit)" );

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

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_optional_header (64-bit)" );
	  }

	  void
	  pe_file::read_pe_section_header ( boost::shared_ptr < pe_section_header > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_section_header" );

	    obj->m_name = m_file.read_utf8_string ( pe_section_header::section_name_size );

	    m_file.read(&(obj->m_virtual_size));
	    m_file.read(&(obj->m_virtual_address));
	    m_file.read(&(obj->m_size_of_raw_data));
	    m_file.read(&(obj->m_pointer_to_raw_data));
	    m_file.read(&(obj->m_pointer_to_relocations));
	    m_file.read(&(obj->m_pointer_to_line_numbers));
	    m_file.read(&(obj->m_number_of_relocations));
	    m_file.read(&(obj->m_number_of_line_numbers));
	    m_file.read(&(obj->m_characteristics));

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_section_header" );
	  }

	  void
	  pe_file::read_pe_resource_directory ( boost::shared_ptr < pe_resource_directory > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_resource_directory" );

	    m_file.read (&(obj->m_characteristics ));
	    m_file.read (&(obj->m_time_date_stamp ));
	    m_file.read (&(obj->m_major_version ));
	    m_file.read (&(obj->m_minor_version ));
	    m_file.read (&(obj->m_num_of_name_entries ));
	    m_file.read (&(obj->m_num_of_id_entries ));

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_resource_directory" );
	  }

	  void
	  pe_file::read_pe_resource_directory_entry ( boost::shared_ptr < pe_resource_directory_entry > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_resource_directory_entry" );

	    m_file.read (&(obj->m_name ));
	    m_file.read (&(obj->m_rva ));

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_resource_directory_entry" );
	  }
    
	  results::values
	  pe_file::read_pe_resource_data_entry ( boost::shared_ptr < pe_resource_data_entry > obj,
						 boost::uint32_t base_address )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_resource_data_entry" );

	    m_file.read (&(obj->m_data_rva ));
	    m_file.read (&(obj->m_size ));
	    m_file.read (&(obj->m_codepage ));
	    m_file.read (&(obj->m_reserved ));

	    boost::shared_ptr < data_containers::memory_map > file_img_ptr = m_file.get_map_ptr();

	    if ( file_img_ptr->address_seek ( obj->m_data_rva + base_address )
		 != data_containers::memory_map::success )
	      {
		obj->m_data_rva = 0;
		obj->m_size = 0;
		obj->m_codepage = 0;
		obj->m_reserved = 0;

		return results::invalid_index;
	      }

	    std::pair < boost::shared_ptr < data_containers::memory_map > ,boost::int8_t > data_entry_map =
	      file_img_ptr->subset ( obj->m_size );

	    if ( data_entry_map.second != data_containers::memory_map::success )
	      {
		return results::invalid_index;
	      }

	    obj->m_data_string = data_entry_map.first->to_string();

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_resource_data_entry" );

	    return results::success;
	  }

	  void
	  pe_file::read_pe_export_directory ( boost::shared_ptr < pe_export_directory > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_export_directory" );

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

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_export_directory" );
	  }

	  void
	  pe_file::read_pe_resource_directory_string ( boost::shared_ptr < pe_resource_directory_string > obj )
	  {
	    m_file.read (&(obj->m_size ));

	    obj->m_text = m_file.read_utf16_string ( obj->m_size );
	  }

	  void
	  pe_file::read_pe_import_directory ( boost::shared_ptr < pe_import_directory > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_import_directory" );

	    m_file.read ( &( obj->m_import_lookup_table ) );
	    m_file.read ( &( obj->m_timestamp ) );
	    m_file.read ( &( obj->m_forwarder_chain ) );
	    m_file.read ( &( obj->m_name_rva ) );
	    m_file.read ( &( obj->m_import_address_table ) );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_import_directory" );
	  }

	  void
	  pe_file::read_null_terminated_string ( std::string& obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_null_terminated_string" );

	    std::stringstream output;

	    boost::uint8_t val = 0;
	    m_file.read ( &val );

	    while ( val != 0 )
	      {
		output << val;
		m_file.read ( &val );
	      }

	    boost::shared_ptr < data_containers::memory_map > file_img_ptr = m_file.get_map_ptr();

	    boost::uint32_t index = file_img_ptr->get_present_position_value () - 1;

	    if ( ! ( index % 2 == 0 ) )
	      {
		file_img_ptr->index_seek ( index++ );
	      }

	    obj = output.str();

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_null_terminated_string" );
	  }

	  void
	  pe_file::read_pe_debug_directory ( boost::shared_ptr < pe_debug_directory > obj)
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_pe_debug_directory" );

	    m_file.read ( &( obj->m_characteristics ) );
	    m_file.read ( &( obj->m_time_date_stamp ) );
	    m_file.read ( &( obj->m_major_version ) );
	    m_file.read ( &( obj->m_minor_version ) );
	    m_file.read ( &( obj->m_type ) );
	    m_file.read ( &( obj->m_size_of_data ) );
	    m_file.read ( &( obj->m_address_of_raw_data ) );
	    m_file.read ( &( obj->m_pointer_to_raw_data ) );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_pe_debug_directory" );
	  }

	  results::values
	  pe_file::address_seek ( boost::uint32_t address )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::address_seek" );

	    // - init source to where data will be read.
	    boost::shared_ptr < data_containers::memory_map > src_map_ptr = m_file.get_map_ptr();

	    if ( src_map_ptr->address_seek ( address ) != data_containers::memory_map::success )
	      {
		return results::invalid_index;
	      }

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::address_seek" );

	    return results::success;
	  }

	  void
	  pe_file::index_seek ( boost::uint32_t offset )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::index_seek" );

	    // - init source to where data will be read.
	    boost::shared_ptr < data_containers::memory_map > src_map_ptr = m_file.get_map_ptr();

	    src_map_ptr->index_seek ( offset );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::index_seek" );
	  }

	  void
	  pe_file::copy ( boost::shared_ptr < data_containers::memory_map > dest_ptr,
			  boost::uint32_t length )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::copy" );

	    boost::shared_ptr < data_containers::memory_map > src_map_ptr = m_file.get_map_ptr();
        
	    dest_ptr->copy ( src_map_ptr, length );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::copy" );
	  }

	  boost::shared_ptr < const io::file_id >
	  pe_file::get_id (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "inside pe_file::get_id" );

	    return m_file.get_id();
	  }

	  boost::uint32_t
	  pe_file::get_present_position_value (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "inside pe_file::get_present_position_value" );

	    boost::shared_ptr < data_containers::memory_map > src_map_ptr = m_file.get_map_ptr();

	    return src_map_ptr->get_present_position_value ();
	  }

	  void
	  pe_file::read_amd_ia_64_exception ( boost::shared_ptr < amd_ia_64_exception_table_entry > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_am_ia_64_exception" );

	    m_file.read ( &( obj->m_begin_address ) );
	    m_file.read ( &( obj->m_end_address ) );
	    m_file.read ( &( obj->m_unwind_information ) );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_am_ia_64_exception" );
	  }

	  void
	  pe_file::read_arm_powerpc_sh_exception ( boost::shared_ptr < arm_powerpc_sh_exception_table_entry_32 > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_am_powerpc_sh_exception (32-bit)" );

	    m_file.read ( &( obj->m_begin_address ) );

	    boost::uint32_t value = 0;
	    m_file.read ( &value );

	    // prolog length (bits 31-24)
	    // function length (bits 23-2)
	    // 32-bit flag (bit 1)
	    // exception flag (bit 0)
	    obj->m_prolog_length = ( value & 0xff000000 ) >> 24;
	    obj->m_function_length = ( value & 0x00fffffc ) >> 2;
	    obj->m_32bit_flag = ( value & 0x00000002 ) >> 1;
	    obj->m_exception_flag = ( value & 0x00000001 );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_am_powerpc_sh_exception (32-bit)" );
	  }

	  void
	  pe_file::read_arm_powerpc_sh_exception ( boost::shared_ptr < arm_powerpc_sh_exception_table_entry_64 > obj )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering pe_file::read_am_powerpc_sh_exception (64-bit)" );

	    m_file.read ( &( obj->m_begin_address ) );

	    boost::uint32_t value = 0;
	    m_file.read ( &value );

	    // prolog length (bits 31-24)
	    // function length (bits 23-2)
	    // 32-bit flag (bit 1)
	    // exception flag (bit 0)
	    obj->m_prolog_length = ( value & 0xff000000 ) >> 24;
	    obj->m_function_length = ( value & 0x00fffffc ) >> 2;
	    obj->m_32bit_flag = ( value & 0x00000002 ) >> 1;
	    obj->m_exception_flag = ( value & 0x00000001 );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "exiting pe_file::read_am_powerpc_sh_exception (64-bit)" );
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

