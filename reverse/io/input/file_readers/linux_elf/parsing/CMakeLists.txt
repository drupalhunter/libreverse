project(io_elf_parsing)

file ( GLOB IO_ELF_PARSING_HEADERS "*.hpp" )

add_custom_target ( io_elf_parsing SOURCES ${IO_ELF_HEADERS} )

