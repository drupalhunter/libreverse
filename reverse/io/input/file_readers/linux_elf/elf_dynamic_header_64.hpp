/*  Elf_Dynamic_Header_64.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_DYNAMIC_HEADER_64_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_DYNAMIC_HEADER_64_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/cstdint.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Dynamic_Header_64
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct Elf_Dynamic_Header_64 {
	    
	    Elf64_Sword d_tag;

	    // d_tag controls the interpretation of d_un
	    // - Elf32_Word d_val = integer value
	    // - Elf32_Addr d_ptr = program virtual address	    
	    boost::variant < Elf64_Word, Elf64_Addr > d_un;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_DYNAMIC_HEADER_64_HPP_INCLUDED
