#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_32_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_32_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_eident_header.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_header_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_program_header_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_section_header_32.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <list>

namespace reverse {
namespace io {
namespace input {
namespace file_readers {
namespace linux_elf {

struct elf_file_32 {

     elf_eident_header base;
     elf_header_32 elf_header;
     elf_program_header_32 program_header;
     std::list < elf_section_header_32 > section_headers;
};

} // namespace linux_elf
} // namespace file_readers
} // namespace input
} //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
     struct reverse::io::input::file_readers::linux_elf::elf_file_32,
     ( struct elf_eident_header, base )
     ( struct elf_header_3, elf_header )
     ( struct elf_program_header_32, program_header )
     ( std::list < struct reverse::io::input::file_readers::linux_elf::elf_section_header_32 >, section_headers )
)

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_32_HPP
