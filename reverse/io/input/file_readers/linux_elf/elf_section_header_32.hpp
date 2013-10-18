/*  Elf_Section_Header_32.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_32_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_32_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  struct elf_section_header_32 {
	    
	    /*! \brief Section name, index in string tbl */
	    Elf32_Word sh_name;
	    
	    /*! \brief Type of section */
	    Elf32_Word sh_type;
	    
	    /*! \brief Miscellaneous section attributes */
	    Elf32_Word sh_flags;
	    
	    /*! \brief Section virtual addr at execution */
	    Elf32_Word sh_addr;
	    
	    /*! \brief Section file offset */
	    Elf32_Addr sh_offset;
	    
	    /*! \brief Size of section in bytes */
	    Elf32_Word sh_size;
	    
	    /*! \brief Index of another section */
	    Elf32_Word sh_link;
	    
	    /*! \brief Additional section information */
	    Elf32_Word sh_info;
	    
	    /*! \brief Section alignment */
	    Elf32_Word sh_addralign;
	    
	    /*! \brief Entry size if section holds table */
	    Elf32_Word sh_entsize;
	    
	  };
	  
	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
     struct reverse::io::input::file_readers::linux_elf::elf_section_header_32,
     ( Elf32_Word, sh_name )
     ( Elf32_Word, sh_type )
     ( Elf32_Word, sh_flags )
     ( Elf32_Word, sh_addr )
     ( Elf32_Addr, sh_offset )
     ( Elf32_Word, sh_size )
     ( Elf32_Word, sh_link )
     ( Elf32_Word, sh_info )
     ( Elf32_Word, sh_addralign )
     ( Elf32_Word, sh_entsize )
)

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_32_HPP
