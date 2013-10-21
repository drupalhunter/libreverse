/*  Elf_mmix.cpp

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

#include <reverse/io/input/file_readers/linux_elf/elf_mmix.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string elf_mmix::MMIX_REG_CONTENTS_SECTION_NAME = ".MMIX.reg_contents";

	  std::string elf_mmix::MMIX_LD_ALLOCATED_REG_CONTENTS_SECTION_NAME = ".MMIX.reg_contents.linker_allocated";

	  std::string elf_mmix::MMIX_REG_SECTION_NAME = "*REG*";

	  /* Appended with a number N=0..65535, this is a representation of
	     the mmixal "BSPEC N" ... "ESPEC" directive pair; the contents go
	     into an ELF section by name ".MMIX.spec_data.N".  */
	  std::string elf_mmix::MMIX_OTHER_SPEC_SECTION_PREFIX = ".MMIX.spec_data.";

	  /* A section SECNAME is noted to start at "__.MMIX.start.SECNAME" by
	     the presence of this symbol.  Currently only implemented for
	     ".text" through the symbol "__.MMIX.start..text".  */
	  std::string elf_mmix::MMIX_LOC_SECTION_START_SYMBOL_PREFIX = "__.MMIX.start.";

	  /* This symbol is always a function.  */
	  std::string elf_mmix::MMIX_START_SYMBOL_NAME = "Main";


	  /* We smuggle in a few MMO specifics here.  We don't make a specific
	     MMO file, since we can't reasonably support MMO without ELF; we
	     have to include this file anyway.  */

	  std::string elf_mmix::MMO_TEXT_SECTION_NAME = ".text";
	  std::string elf_mmix::MMO_DATA_SECTION_NAME = ".data";


	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

