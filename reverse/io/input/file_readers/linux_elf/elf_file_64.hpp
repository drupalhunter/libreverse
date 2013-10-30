#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_64_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_64_GRAMMAR_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_file_header_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_program_header_64.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  struct elf_file_64 {

	    elf_file_header_64 elf_file_header;
	    std::vector < elf_program_header_64 > program_headers;
     
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_file_64,
			   ( struct elf_eident_header, base )
			   ( struct elf_program_header_64, program_header )
			   )

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_GRAMMAR_64_HPP
