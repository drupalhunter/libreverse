/*  Elf_Relocation_Add_64.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_ADD_64_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_ADD_64_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct elf_relocation_add_64 {

	    /*!
	     * \brief This member gives the location at which to apply the
	     * relocation action. For a relocatable file, the value is the byte
	     * offset from the beginning of the section to the storage unit
	     * affected by the relocation. For an executable file or a shared
	     * object, the value is the virtual address of the storage unit
	     * affected by the relocation. (Elf)
	     */
	    Elf64_Addr r_offset;

	    /*!
	     * \brief This member gives both the symbol table index with respect
	     * to which the relocation must be made, and the type of relocation
	     * to apply. (Elf)
	     */
	    Elf64_Word r_info;

	    /*!
	     * \brief This member specifies a constant addend used to compute the
	     * value to be stored into the relocatable field. (Elf)
	     */
	    Elf64_Sword r_addend;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_relocation_add_64,
			   ( Elf64_Addr, r_offset )
			   ( Elf64_Word, r_info )
			   ( Elf64_Sword, r_addend )
			   )

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_ADD_64_HPP
