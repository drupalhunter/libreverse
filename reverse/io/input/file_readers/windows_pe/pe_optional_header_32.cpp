/*  PE_Optional_Header_32.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_optional_header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_subsystem.hpp>
#include <reverse/io/byte_converter.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>
#include <iomanip>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  boost::uint16_t const pe_optional_header_32::rom_image = 0x0107;

	  boost::uint16_t const pe_optional_header_32::pe_executable = 0x010b;

	  boost::uint16_t const pe_optional_header_32::pe_plus_executable = 0x020b;

	  pe_optional_header_32::pe_optional_header_32()
	    : m_magic ( 0 ),
	      m_major_linker_version ( 0 ),
	      m_minor_linker_version ( 0 ),
	      m_size_of_code ( 0 ),
	      m_size_of_init_data ( 0 ),
	      m_size_of_uninit_data ( 0 ),
	      m_addr_of_entry_point ( 0 ),
	      m_base_of_code ( 0 ),
	      m_base_of_data ( 0 ),
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
	  pe_optional_header_32::to_string ( void ) const
	  {
	    std::stringstream output_str;

	    output_str << "pe optional header:" << std::endl;

	    output_str << boost::format ( "  magic:                      %1%" ) %
	      boost::io::group ( std::hex,
				 m_magic )
		       << std::endl;

	    output_str << boost::format ( "  linker version:             %1%.%2%" ) %
	      static_cast<boost::uint16_t> ( m_major_linker_version ) %
	      boost::io::group ( std::setfill ( '0' ),
				 std::setw ( 2 ),
				 static_cast<boost::uint16_t> ( m_minor_linker_version ) )
		       << std::endl;

	    output_str << boost::format ( "  size of code:               %1x" ) %
	      m_size_of_code
		       << std::endl;

	    output_str << boost::format ( "  size of initialized data:   %1x" ) %
	      m_size_of_init_data
		       << std::endl;

	    output_str << boost::format ( "  size of uninitialized data: %1x" ) %
	      m_size_of_uninit_data
		       << std::endl;

	    output_str << boost::format ( "  address of entry point:     %1x" ) %
	      m_addr_of_entry_point
		       << std::endl;

	    output_str << boost::format ( "  base of code:               %1x" ) %
	      m_base_of_code
		       << std::endl;

	    output_str << boost::format ( "  base of data:               %1x" ) %
	      m_base_of_data
		       << std::endl;

	    output_str << boost::format ( "  base of image:              %1x" ) %
	      m_image_base
		       << std::endl;

	    output_str << boost::format ( "  section alignment:          %1x" ) %
	      m_section_alignment
		       << std::endl;

	    output_str << boost::format ( "  file alignment:             %1x" ) %
	      m_file_alignment
		       << std::endl;

	    output_str << boost::format ( "  os system version:          %1%.%2%" ) %
	      m_major_operating_system_version %
	      boost::io::group ( std::setfill ( '0' ),
				 std::setw ( 2 ),
				 m_minor_operating_system_version )
		       << std::endl;

	    output_str << boost::format ( "  image version:              %1%.%2%" ) %
	      m_major_image_version %
	      boost::io::group ( std::setfill ( '0' ),
				 std::setw ( 2 ),
				 m_minor_image_version )
		       << std::endl;

	    output_str << boost::format ( "  subsystem version:          %1%.%2%" ) %
	      m_major_subsystem_version %
	      boost::io::group ( std::setfill ( '0' ),
				 std::setw ( 2 ),
				 m_minor_subsystem_version )
		       << std::endl;

	    output_str << "  win32 version:              "
		       << m_win32_version_value
		       << std::endl;

	    output_str << boost::format ( "  size of image:              %1x" ) %
	      m_size_of_image
		       << std::endl;

	    output_str << boost::format ( "  size of headers:            %1x" ) %
	      m_size_of_headers
		       << std::endl;

	    output_str << boost::format ( "  checksum:                   %1x" ) %
	      m_checksum
		       << std::endl;

	    output_str << boost::format ( "  sub-system:                 %1% (%2%)" )
	      % m_subsystem
	      % pe_subsystem::get_string_name ( m_subsystem )
		       << std::endl;

	    output_str << boost::format ( "  dll characteristics:        %1x" ) %
	      m_dll_characteristics
		       << std::endl;

	    output_str << boost::format ( "  stack reserve size:         %1x" ) %
	      m_size_of_stack_reserve
		       << std::endl;

	    output_str << boost::format ( "  stack commit size:          %1x" ) %
	      m_size_of_stack_commit
		       << std::endl;

	    output_str << boost::format ( "  heap reserve size:          %1x" ) %
	      m_size_of_heap_reserve
		       << std::endl;

	    output_str << boost::format ( "  heap commit size:           %1x" ) %
	      m_size_of_heap_commit
		       << std::endl;

	    output_str << boost::format ( "  loader flags:               %1x" ) %
	      m_loader_flags
		       << std::endl;

	    output_str << boost::format ( "  number of rva and sizes:    %1x" ) %
	      m_number_of_rva_and_sizes
		       << std::endl;

	    output_str << boost::format ( "  export table:                  %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_export_table_address ) %
	      boost::io::group ( std::hex,
				 m_export_table_size )
		       << std::endl;

	    output_str << boost::format ( "  import table:                  %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_import_table_address ) %
	      boost::io::group ( std::hex,
				 m_import_table_size )
		       << std::endl;

	    output_str << boost::format ( "  resource table:                %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_resource_table_address ) %
	      boost::io::group ( std::hex,
				 m_resource_table_size )
		       << std::endl;

	    output_str << boost::format ( "  exception table:               %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_exception_table_address ) %
	      boost::io::group ( std::hex,
				 m_exception_table_size )
		       << std::endl;

	    output_str << boost::format ( "  certificate table:             %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_certificate_table_address ) %
	      boost::io::group ( std::hex,
				 m_certificate_table_size )
		       << std::endl;

	    output_str << boost::format ( "  base relocation table:         %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_base_relocation_table_address ) %
	      boost::io::group ( std::hex,
				 m_base_relocation_table_size )
		       << std::endl;

	    output_str << boost::format ( "  debug table:                   %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_debug_table_address ) %
	      boost::io::group ( std::hex,
				 m_debug_table_size )
		       << std::endl;

	    output_str << boost::format ( "  architecture:                  %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_architecture_address ) %
	      boost::io::group ( std::hex,
				 m_architecture_size )
		       << std::endl;

	    output_str << boost::format ( "  global pointer table:          %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_global_ptr_address ) %
	      boost::io::group ( std::hex,
				 m_global_ptr_size )
		       << std::endl;

	    output_str << boost::format ( "  thread local storage table:    %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_thread_local_storage_table_address ) %
	      boost::io::group ( std::hex,
				 m_thread_local_storage_table_size )
		       << std::endl;

	    output_str << boost::format ( "  load config table:             %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_load_config_table_address ) %
	      boost::io::group ( std::hex,
				 m_load_config_table_size )
		       << std::endl;

	    output_str << boost::format ( "  bound import table:            %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_bound_import_address ) %
	      boost::io::group ( std::hex,
				 m_bound_import_size )
		       << std::endl;

	    output_str << boost::format ( "  import address table:          %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_import_address_table_address ) %
	      boost::io::group ( std::hex,
				 m_import_address_table_size )
		       << std::endl;

	    output_str << boost::format ( "  delay import descriptor table: %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_delay_import_descriptor_address ) %
	      boost::io::group ( std::hex,
				 m_delay_import_descriptor_size )
		       << std::endl;

	    output_str << boost::format ( "  clr runtime table:             %1% [ %2% ]" ) %
	      boost::io::group ( std::hex,
				 m_clr_runtime_header_address ) %
	      boost::io::group ( std::hex,
				 m_clr_runtime_header_size )
		       << std::endl;

	    output_str << boost::format ( "  reserved:                      %1% [ %2% ]" ) %
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
	  pe_optional_header_32::convert ()
	  {
	    io::byte_converter::convert ( m_size_of_code );
	    io::byte_converter::convert ( m_size_of_init_data );
	    io::byte_converter::convert ( m_size_of_uninit_data );
	    io::byte_converter::convert ( m_addr_of_entry_point );
	    io::byte_converter::convert ( m_base_of_code );
	    io::byte_converter::convert ( m_base_of_data );
	    io::byte_converter::convert ( m_image_base );
	    io::byte_converter::convert ( m_section_alignment );
	    io::byte_converter::convert ( m_file_alignment );
	    io::byte_converter::convert ( m_major_operating_system_version );
	    io::byte_converter::convert ( m_minor_operating_system_version );
	    io::byte_converter::convert ( m_major_image_version );
	    io::byte_converter::convert ( m_minor_image_version );
	    io::byte_converter::convert ( m_major_subsystem_version );
	    io::byte_converter::convert ( m_minor_subsystem_version );
	    io::byte_converter::convert ( m_win32_version_value );
	    io::byte_converter::convert ( m_size_of_image );
	    io::byte_converter::convert ( m_size_of_headers );
	    io::byte_converter::convert ( m_checksum );
	    io::byte_converter::convert ( m_subsystem );
	    io::byte_converter::convert ( m_dll_characteristics );
	    io::byte_converter::convert ( m_size_of_stack_reserve );
	    io::byte_converter::convert ( m_size_of_stack_commit );
	    io::byte_converter::convert ( m_size_of_heap_reserve );
	    io::byte_converter::convert ( m_size_of_heap_commit );
	    io::byte_converter::convert ( m_loader_flags );
	    io::byte_converter::convert ( m_number_of_rva_and_sizes );
	    io::byte_converter::convert ( m_export_table_address );
	    io::byte_converter::convert ( m_export_table_size );
	    io::byte_converter::convert ( m_import_table_address );
	    io::byte_converter::convert ( m_import_table_size );
	    io::byte_converter::convert ( m_resource_table_address );
	    io::byte_converter::convert ( m_resource_table_size );
	    io::byte_converter::convert ( m_exception_table_address );
	    io::byte_converter::convert ( m_exception_table_size );
	    io::byte_converter::convert ( m_certificate_table_address );
	    io::byte_converter::convert ( m_certificate_table_size );
	    io::byte_converter::convert ( m_base_relocation_table_address );
	    io::byte_converter::convert ( m_base_relocation_table_size );
	    io::byte_converter::convert ( m_debug_table_address );
	    io::byte_converter::convert ( m_debug_table_size );
	    io::byte_converter::convert ( m_architecture_address );
	    io::byte_converter::convert ( m_architecture_size );
	    io::byte_converter::convert ( m_global_ptr_address );
	    io::byte_converter::convert ( m_global_ptr_size );
	    io::byte_converter::convert ( m_thread_local_storage_table_address );
	    io::byte_converter::convert ( m_thread_local_storage_table_size );
	    io::byte_converter::convert ( m_load_config_table_address );
	    io::byte_converter::convert ( m_load_config_table_size );
	    io::byte_converter::convert ( m_bound_import_address );
	    io::byte_converter::convert ( m_bound_import_size );
	    io::byte_converter::convert ( m_import_address_table_address );
	    io::byte_converter::convert ( m_import_address_table_size );
	    io::byte_converter::convert ( m_delay_import_descriptor_address );
	    io::byte_converter::convert ( m_delay_import_descriptor_size );
	    io::byte_converter::convert ( m_clr_runtime_header_address );
	    io::byte_converter::convert ( m_clr_runtime_header_size );
	    io::byte_converter::convert ( m_reserved_address );
	    io::byte_converter::convert ( m_reserved_size );
	  }

	  bool
	  pe_optional_header_32::is_pe_file ( void )
	  {
	    return ( m_magic == pe_header_32::pe_magic_signature );
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_magic_value ( void ) const
	  {
	    return m_magic;
	  }

	  boost::uint8_t
	  pe_optional_header_32::get_major_linker_version ( void ) const
	  {
	    return m_major_linker_version;
	  }

	  boost::uint8_t
	  pe_optional_header_32::get_minor_linker_version ( void ) const
	  {
	    return m_minor_linker_version;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_code ( void ) const
	  {
	    return m_size_of_code;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_init_data ( void ) const
	  {
	    return m_size_of_init_data;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_uninitialized_data ( void ) const
	  {
	    return m_size_of_uninit_data;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_entry_point ( void ) const
	  {
	    return m_addr_of_entry_point;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_base_of_code ( void ) const
	  {
	    return m_base_of_code;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_base_of_data ( void ) const
	  {
	    return m_base_of_data;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_image_base ( void ) const
	  {
	    return m_image_base;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_section_alignment ( void ) const
	  {
	    return m_section_alignment;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_file_alignment ( void ) const
	  {
	    return m_file_alignment;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_major_operating_system_version ( void ) const
	  {
	    return m_major_operating_system_version;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_minor_operating_system_version ( void ) const
	  {
	    return m_minor_operating_system_version;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_major_image_version ( void ) const
	  {
	    return m_major_image_version;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_minor_image_version ( void ) const
	  {
	    return m_minor_image_version;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_major_subsystem_version ( void ) const
	  {
	    return m_major_subsystem_version;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_minor_subsystem_version ( void ) const
	  {
	    return m_minor_subsystem_version;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_win32_version_value ( void ) const
	  {
	    return m_win32_version_value;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_image ( void ) const
	  {
	    return m_size_of_image;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_headers ( void ) const
	  {
	    return m_size_of_headers;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_checksum ( void ) const
	  {
	    return m_checksum;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_subsystem ( void ) const
	  {
	    return m_subsystem;
	  }

	  boost::uint16_t
	  pe_optional_header_32::get_dll_characteristics ( void ) const
	  {
	    return m_dll_characteristics;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_stack_reserve ( void ) const
	  {
	    return m_size_of_stack_reserve;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_stack_commit ( void ) const
	  {
	    return m_size_of_stack_commit;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_heap_reserve ( void ) const
	  {
	    return m_size_of_heap_reserve;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_size_of_heap_commit ( void ) const
	  {
	    return m_size_of_heap_commit;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_loader_flags ( void ) const
	  {
	    return m_loader_flags;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_number_of_rva_and_sizes ( void ) const
	  {
	    return m_number_of_rva_and_sizes;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_export_table_address ( void ) const
	  {
	    return m_export_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_export_table_size ( void ) const
	  {
	    return m_export_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_import_table_address ( void ) const
	  {
	    return m_import_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_import_table_size ( void ) const
	  {
	    return m_import_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_resource_table_address ( void ) const
	  {
	    return m_resource_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_resource_table_size ( void ) const
	  {
	    return m_resource_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_exception_table_address ( void ) const
	  {
	    return m_exception_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_exception_table_size ( void ) const
	  {
	    return m_exception_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_certificate_table_address ( void ) const
	  {
	    return m_certificate_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_certificate_table_size ( void ) const
	  {
	    return m_certificate_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_base_relocation_table_address ( void ) const
	  {
	    return m_base_relocation_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_base_relocation_table_size ( void ) const
	  {
	    return m_base_relocation_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_debug_table_address ( void ) const
	  {
	    return m_debug_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_debug_table_size ( void ) const
	  {
	    return m_debug_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_architecture_address ( void ) const
	  {
	    return m_architecture_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_architecture_size ( void ) const
	  {
	    return m_architecture_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_global_ptr_address ( void ) const
	  {
	    return m_global_ptr_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_global_ptr_size ( void ) const
	  {
	    return m_global_ptr_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_thread_local_storage_table_address ( void ) const
	  {
	    return m_thread_local_storage_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_thread_local_storage_table_size ( void ) const
	  {
	    return m_thread_local_storage_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_load_config_table_address ( void ) const
	  {
	    return m_load_config_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_load_config_table_size ( void ) const
	  {
	    return m_load_config_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_bound_import_address ( void ) const
	  {
	    return m_bound_import_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_bound_import_size ( void ) const
	  {
	    return m_bound_import_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_import_address_table_address ( void ) const
	  {
	    return m_import_address_table_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_import_address_table_size ( void ) const
	  {
	    return m_import_address_table_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_delay_import_descriptor_address ( void ) const
	  {
	    return m_delay_import_descriptor_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_delay_import_descriptor_size ( void ) const
	  {
	    return m_delay_import_descriptor_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_clr_runtime_header_address ( void ) const
	  {
	    return m_clr_runtime_header_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_clr_runtime_header_size ( void ) const
	  {
	    return m_clr_runtime_header_size;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_reserved_address ( void ) const
	  {
	    return m_reserved_address;
	  }

	  boost::uint32_t
	  pe_optional_header_32::get_reserved_size ( void ) const
	  {
	    return m_reserved_size;
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

