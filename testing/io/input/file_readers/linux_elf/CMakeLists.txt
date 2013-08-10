CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.0 )

project(io_elf_testing)

enable_testing()

add_test ( test_eident_parsing test_eident_parsing.cpp )
