/*  Elf_File_Header_32.h

   Copyright (C) 2008 Stephen Torri

   This file is part of Libreverse.

   Libreverse is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   Libreverse is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_32_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_32_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {
	  
	  struct elf_header_32
	  {
	    /*! \brief  Object file type */
	    Elf32_Half e_type;

	    /*! \brief Required architecture for the file */
	    Elf32_Half e_machine;
	    
	    /*! \brief ELF version for the file */
	    Elf32_Word e_version;
	    
	    /*!
	     * \brief This memeber gives the virtual address to which the system
	     * first transfer control. If the file has no associated entry
	     * point, this member holds zero. [Elf Format]
	     */
	    Elf32_Word e_entry;
	    
	    /*! \brief  Program header table's file offset in bytes */
	    Elf32_Word e_phoff;
	    
	    /*! \brief  Section header table's file offset in bytes */
	    Elf32_Word e_shoff;
	    
	    /*! \brief  Processor-specific flags associated with the file */
	    Elf32_Word e_flags;
	    
	    /*! \brief  ELF header size in bytes */
	    Elf32_Half e_ehsize;
	    
	    /*! \brief  Program header table entry size */
	    Elf32_Half e_phentsize;

	    /*!
	     * \brief This members holds the number of entries in the program
	     * header table (bytes).
	     */
	    Elf32_Half e_phnum;
	    
	    /*! \brief  Section header table entry size (bytes) */
	    Elf32_Half e_shentsize;
	    
	    /*! \brief  Section header table entry count */
	    Elf32_Half e_shnum;
	    
	    /*!
	     * \brief Section header string table index of the entry associated
	     * with the section name string table.
	     */
	    Elf32_Half e_shstrndx;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
     struct reverse::io::input::file_readers::linux_elf::elf_header_32,
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_type )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_machine )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Word, e_version )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Word, e_entry )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Word, e_phoff )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Word, e_shoff )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Word, e_flags )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_ehsize )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_phentsize )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_phnum )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_shentsize )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_shnum )
     ( reverse::io::input::file_readers::linux_elf::Elf32_Half, e_shstrndx )
)

#endif /* ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_32_HPP */
