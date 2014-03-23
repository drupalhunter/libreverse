project(reverse_io_readers)

add_subdirectory ( linux_elf )
#add_subdirectory ( java_class )
#add_subdirectory ( mac_mach )
#add_subdirectory ( windows_pe )

set ( IO_READERS_SOURCES
  reader_factory.cpp )

set ( IO_READERS_HEADERS
  base_header.hpp
  file_reader.hpp
  reader_factory.hpp )

include_directories ( ${CMAKE_SOURCE_DIR} )

add_library ( ${PROJECT_NAME} ${IO_READERS_SOURCES} ${IO_READERS_HEADERS} )
