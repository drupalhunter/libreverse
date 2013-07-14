#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_64_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_64_GRAMMAR_HPP

#include <boost/cstdint.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
namespace io {
namespace input {
namespace file_readers {
namespace linux_elf {
    
    /*!
     * \class elf_program_header_64
     * \date 2003
     * \author Stephen Torri
     *
     * (Elf) = Executable and Linkable Format specification
     */
    struct elf_program_header_64
    {
	
      /*!
       * \brief This member tells what kind of segment this array element
       * described or how to interpret the array element's
       * information. Type values and their meanings appear below. (Elf)
       */
      boost::uint32_t p_type;

      /*!
       * \brief This member gives the offset from the beginning of the
       * file at which the first byte of the segment resides. (Elf)
       */
      boost::uint64_t p_offset;

      /*!
       * \brief This member gives the virtual address at which the first
       * byte of the segment resides in memory.
       */
      boost::uint64_t p_vaddr;

      /*!
       * \brief On systems for which physical addressing is relevant, this
       * member is reserved for the segment's physical address. Because
       * System V ignores physical addressing for application programs,
       * this member has unspecified contents for executable files and
       * shared objects. (Elf)
       */
      boost::uint64_t p_paddr;

      /*!
       * \brief This member gives the number of bytes in the file image of
       * the segment; it may be zero. (Elf)
       */
      boost::uint64_t p_filesz;

      /*!
       * \brief This member gives the number of bytes in the memory image
       * of the segment; it may be zero. (Elf)
       */
      boost::uint64_t p_memsz;

      /*!
       * \brief This member gives the flags relevant to the segment. (Elf)
       */
      boost::uint64_t p_flags;

      /*!
       * \brief This member gives the value to which the segments are
       * aligned in memory and in the file. Values 0 and 1 mean no
       * alignment is required. Otherwise, p_align should be positive,
       * integral power of 2, and p_vaddr should equal p_offset modulo
       * p_align. (Elf)
       */
      boost::uint64_t p_align;

    };

} // namespace linux_elf
} // namespace file_readers
} // namespace input
} //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
     struct reverse::io::input::file_readers::linux_elf::elf_program_header_64,
     ( boost::uint32_t, p_type )
     ( boost::uint64_t, p_offset )
     ( boost::uint64_t, p_vaddr )
     ( boost::uint64_t, p_paddr )
     ( boost::uint64_t, p_filesz )
     ( boost::uint64_t, p_memsz )
     ( boost::uint64_t, p_flags )
     ( boost::uint64_t, p_align )
)

#endif /* ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_64_GRAMMAR_HPP */
