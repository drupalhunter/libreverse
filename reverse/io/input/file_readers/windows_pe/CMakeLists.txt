project(io_windows_pe)

set ( IO_WINDOWS_PE_SOURCES
  amd_ia_64_exception_table_entry.cpp
  arm_powerpc_sh_exception_table_entry_32.cpp
  arm_powerpc_sh_exception_table_entry_64.cpp
  coff_header.cpp
  dos_header.cpp
  dos_relocation_header.cpp
  data_directory.cpp
  debug_types.cpp
  header_32.cpp
  header_64.cpp
  pe_characteristics.cpp
  pe_debug_directory.cpp
  pe_export_directory.cpp
  pe_file.cpp
  pe_header_32.cpp
  pe_header_64.cpp
  pe_import_directory.cpp
  pe_information_block.cpp
  pe_machine_types.cpp
  pe_meta_info.cpp
  pe_optional_header_32.cpp
  pe_optional_header_64.cpp
  pe_resource_data_entry.cpp
  pe_resource_directory.cpp
  pe_resource_directory_entry.cpp
  pe_resource_directory_string.cpp
  pe_resource_integer_types.cpp
  pe_section_header.cpp
  pe_subsystem.cpp
  reader_32.cpp
  reader_64.cpp
  section_flags.cpp )

set ( IO_WINDOWS_PE_HEADERS
  amd_ia_64_exception_table_entry.hpp
  arm_powerpc_sh_exception_table_entry_32.hpp
  arm_powerpc_sh_exception_table_entry_64.hpp
  coff_header.hpp
  dos_header.hpp
  dos_relocation_header.hpp
  data_directory.hpp
  debug_types.hpp
  header_32.hpp
  header_64.hpp
  pe_characteristics.hpp
  pe_debug_directory.hpp
  pe_exception_table_constants.hpp
  pe_exception_table_entry.hpp
  pe_export_directory.hpp
  pe_file.hpp
  pe_header_32.hpp
  pe_header_64.hpp
  pe_import_directory.hpp
  pe_information_block.hpp
  pe_load_config_directory.hpp
  pe_machine_types.hpp
  pe_meta_info.hpp
  pe_optional_header_32.hpp
  pe_optional_header_64.hpp
  pe_resource_data_entry.hpp
  pe_resource_directory.hpp
  pe_resource_directory_entry.hpp
  pe_resource_directory_string.hpp
  pe_resource_integer_types.hpp
  pe_section_header.hpp
  pe_subsystem.hpp
  pe_types.hpp
  reader_32.hpp
  reader_64.hpp
  section_flags.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( io_windows_pe ${IO_WINDOWS_PE_SOURCES} ${IO_WINDOWS_PE_HEADERS} )
