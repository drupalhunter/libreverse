CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.0 )

project(io_elf)

add_subdirectory ( parsing )

file ( GLOB IO_ELF_SOURCES "*.cpp" )

file ( GLOB IO_ELF_HEADERS "*.hpp" )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( io_elf ${IO_ELF_SOURCES} ${IO_ELF_HEADERS} )

