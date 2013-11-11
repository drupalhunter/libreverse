CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.0 )

project(io_elf)

add_subdirectory ( parsing )

file ( GLOB IO_ELF_SOURCES "*.cpp" )

file ( GLOB IO_ELF_HEADERS "*.hpp" )

include_directories ( ${CMAKE_SOURCE_DIR} )

add_library ( io_elf ${IO_ELF_SOURCES} ${IO_ELF_HEADERS} )

install ( FILES ${IO_ELF_HEADERS} DESTINATION include/reverse/io/input/file_readers/linux_elf )

