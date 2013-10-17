/*  Elf_Relocation_32.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_32_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_32_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class elf_relocation_32
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct elf_relocation_32 {

	    /*!
	     * \brief This member gives the location at which to apply the
	     * relocation action. For a relocatable file, the value is the byte
	     * offset from the beginning of the section to the storage unit
	     * affected by the relocation. For an executable file or a shared
	     * object, the value is the virtual address of the storage unit
	     * affected by the relocation. (Elf)
	     */
	    boost::uint32_t r_offset;

	    /*!
	     * \brief This member gives both the symbol table index with respect
	     * to which the relocation must be made, and the type of relocation
	     * to apply. (Elf)
	     */

	    /*
	      Comment take from readelf.c:

	      In little-endian objects, r_info isn't really a 64-bit
	      little-endian value: it has a 32-bit little-endian symbol index
	      followed by four individual byte fields.  Reorder INFO
	      accordingly.

	      Note take from Executable and Linkable Format (ELF) manual:

	      This member gives both the symbol table index with respect to
	      which the relocation must be made, and the type of relocation to
	      apply. For example, a call instruction's relocation entry would
	      hold the symbol table index of the function being called. If the
	      index is STN_UNDEF, the undefined symbol index, the relocation
	      uses 0 as the symbol value.  Relocation types are
	      processor-specific. When the text refers to a relocation entry s
	      relocation type or symbol table index, it means the result of
	      applying ELF32_R_TYPE or ELF32_R_SYM, respectively, to the entry
	      s r_info member.
	    */
	    boost::uint32_t r_info;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   reverse::io::input::file_readers::linux_elf::elf_relocation_32,
			   (boost::uint32_t, r_offset)
			   (boost::uint32_t, r_info)
)

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_32_HPP_INCLUDED
