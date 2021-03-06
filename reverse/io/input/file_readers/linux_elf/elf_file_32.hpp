#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_32_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_32_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_header_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_file_header_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_program_header_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_section_header_32.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <vector>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {
	  
	  struct elf_file_32
	  {  
	    elf_file_header_32 elf_file_header;
	    std::vector < elf_program_header_32 > program_headers;
	    //std::vector < elf_section_header_32 > section_headers;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
     struct reverse::io::input::file_readers::linux_elf::elf_file_32,
     ( struct reverse::io::input::file_readers::linux_elf::elf_file_header_32, elf_file_header )
     ( struct reverse::io::input::file_readers::linux_elf::elf_program_header_32, program_header )
     //( std::vector < struct reverse::io::input::file_readers::linux_elf::elf_section_header_32 >, section_headers )
)

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_32_HPP
