#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_32_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_32_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {
    
	  /*!
	   * \class elf_program_header_32
	   * \date 2003
	   * \author Stephen Torri
	   *
	   * (Elf) = Executable and Linkable Format specification
	   */
	  struct elf_program_header_32
	  {
	
	    /*!
	     * \brief This member tells what kind of segment this array element
	     * described or how to interpret the array element's
	     * information. Type values and their meanings appear below. (Elf)
	     */
	    Elf32_Word p_type;

	    /*!
	     * \brief This member gives the offset from the beginning of the
	     * file at which the first byte of the segment resides. (Elf)
	     */
	    Elf32_Word p_offset;

	    /*!
	     * \brief This member gives the virtual address at which the first
	     * byte of the segment resides in memory.
	     */
	    Elf32_Word p_vaddr;

	    /*!
	     * \brief On systems for which physical addressing is relevant, this
	     * member is reserved for the segment's physical address. Because
	     * System V ignores physical addressing for application programs,
	     * this member has unspecified contents for executable files and
	     * shared objects. (Elf)
	     */
	    Elf32_Word p_paddr;

	    /*!
	     * \brief This member gives the number of bytes in the file image of
	     * the segment; it may be zero. (Elf)
	     */
	    Elf32_Word p_filesz;

	    /*!
	     * \brief This member gives the number of bytes in the memory image
	     * of the segment; it may be zero. (Elf)
	     */
	    Elf32_Word p_memsz;

	    /*!
	     * \brief This member gives the flags relevant to the segment. (Elf)
	     */
	    Elf32_Word p_flags;

	    /*!
	     * \brief This member gives the value to which the segments are
	     * aligned in memory and in the file. Values 0 and 1 mean no
	     * alignment is required. Otherwise, p_align should be positive,
	     * integral power of 2, and p_vaddr should equal p_offset modulo
	     * p_align. (Elf)
	     */
	    Elf32_Word p_align;

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_program_header_32,
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_type )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_offset )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_vaddr )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_paddr )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_filesz )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_memsz )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_flags )
			   ( reverse::io::input::file_readers::linux_elf::Elf32_Word, p_align )
			   )

#endif /* ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_32_HPP */
