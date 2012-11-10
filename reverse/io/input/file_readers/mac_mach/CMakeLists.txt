project(io_mach)

set ( IO_MACH_SOURCES
  cpu_ppc_32.cpp
  cpu_ppc_64.cpp
  cpu_subtype.cpp
  cpu_type.cpp
  cpu_x86_32.cpp
  cpu_x86_64.cpp
  dylib.cpp
  dylib_command.cpp
  dylib_module.cpp
  dylib_module_64.cpp
  dylib_reference.cpp
  dylib_table_of_contents.cpp
  dylinker_command.cpp
  dysymtab_command.cpp
  fat_arch.cpp
  fat_header.cpp
  fat_reader.cpp
  fvmfile_command.cpp
  fvmlib.cpp
  fvmlib_command.cpp
  ident_command.cpp
  lc_str.cpp
  load_command.cpp
  load_command_factory.cpp
  mach_file.cpp
  mach_header_32.cpp
  mach_header_64.cpp
  mach_meta_info.cpp
  mach_reader_32.cpp
  mach_reader_64.cpp
  nlist.cpp
  nlist_64.cpp
  prebound_dylib_command.cpp
  relocation_info.cpp
  routines_command.cpp
  routines_command_64.cpp
  scattered_relocation_info.cpp
  section.cpp
  section_64.cpp
  segment_command.cpp
  segment_command_64.cpp
  skipped_command.cpp
  sub_client_command.cpp
  sub_framework_command.cpp
  sub_library_command.cpp
  sub_umbrella_command.cpp
  symtab_command.cpp
  thread_command.cpp
  twolevel_hint.cpp
  twolevel_hints_command.cpp
  uuid_command.cpp )

set ( IO_MACH_HEADERS
  cpu_ppc_32.hpp
  cpu_ppc_64.hpp
  cpu_state_t.hpp
  cpu_subtype.hpp
  cpu_thread_state.hpp
  cpu_type.hpp
  cpu_x86_32.hpp
  cpu_x86_64.hpp
  dylib.hpp
  dylib_command.hpp
  dylib_module.hpp
  dylib_module_64.hpp
  dylib_reference.hpp
  dylib_table_of_contents.hpp
  dylinker_command.hpp
  dysymtab_command.hpp
  fat_arch.hpp
  fat_header.hpp
  fat_reader.hpp
  filetypes.hpp
  fvmfile_command.hpp
  fvmlib.hpp
  fvmlib_command.hpp
  ident_command.hpp
  lc_str.hpp
  load_command.hpp
  load_command_constants.hpp
  load_command_factory.hpp
  mach_file.hpp
  mach_header_32.hpp
  mach_header_64.hpp
  mach_header_flags.hpp
  mach_meta_info.hpp
  mach_reader_32.hpp
  mach_reader_64.hpp
  mach_types.hpp
  nlist.hpp
  nlist_64.hpp
  prebound_dylib_command.hpp
  relocation_info.hpp
  routines_command.hpp
  routines_command_64.hpp
  scattered_relocation_info.hpp
  section.hpp
  section_64.hpp
  segment_command.hpp
  segment_command_64.hpp
  skipped_command.hpp
  sub_client_command.hpp
  sub_framework_command.hpp
  sub_library_command.hpp
  sub_umbrella_command.hpp
  symtab_command.hpp
  thread_command.hpp
  twolevel_hint.hpp
  twolevel_hints_command.hpp
  uuid_command.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( io_mach ${IO_MACH_SOURCES} ${IO_MACH_HEADERS} )

