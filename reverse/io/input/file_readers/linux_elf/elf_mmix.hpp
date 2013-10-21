/*  Elf_mmix.h

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

/*
  MMIX support for BFD.
  Copyright 2001, 2002 Free Software Foundation, Inc.

  This file is part of BFD, the Binary File Descriptor library.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/* This file holds definitions specific to the MMIX ELF ABI. */
#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_MMIX_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_MMIX_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_mmix {
	  public:

	    static inline std::string get_type (boost::uint32_t type);

	    /* Section Attributes.  */
	    /* A section containing necessary information for relaxation.  */
	    static const boost::uint32_t SHF_MMIX_CANRELAX = 0x80000000;

	    /* Symbol attributes.  */
	    /* A symbol with this section-index is a register.  */
	    static const boost::uint16_t SHN_REGISTER	= elf_common::SHN_LOPROC;

	    /* This section holds contents for each initialized register, at VMA
	       regno*8.  A symbol relative to this section will be transformed to an
	       absolute symbol with the value corresponding to the register number at
	       final link time.  A symbol with a value outside the inclusive range
	       32*8 .. 254*8 is an error.  It is highly recommended to only use an
	       upper bound of 253*8 or lower as specified in the (currently
	       unspecified) ABI.  */
	    static std::string MMIX_REG_CONTENTS_SECTION_NAME;

	    /* At link time, a section by this name is created, expected to be
	       included in MMIX_REG_CONTENTS_SECTION_NAME in the output.  */
	    static std::string MMIX_LD_ALLOCATED_REG_CONTENTS_SECTION_NAME;

	    /* This is a faked section holding symbols with SHN_REGISTER.  Don't
	       confuse it with MMIX_REG_CONTENTS_SECTION_NAME; this one has no
	       contents, just values.  It is an error for a value in this section to
	       be outside the range 32..255 and it must never become an actual section
	       in an object file.  */
	    static std::string MMIX_REG_SECTION_NAME;

	    /* Appended with a number N=0..65535, this is a representation of the
	       mmixal "BSPEC N" ... "ESPEC" directive pair; the contents go into an
	       ELF section by name ".MMIX.spec_data.N".  */
	    static std::string MMIX_OTHER_SPEC_SECTION_PREFIX;

	    /* A section SECNAME is noted to start at "__.MMIX.start.SECNAME" by the
	       presence of this symbol.  Currently only implemented for ".text"
	       through the symbol "__.MMIX.start..text".  */
	    static std::string MMIX_LOC_SECTION_START_SYMBOL_PREFIX;

	    /* This symbol is always a function.  */
	    static std::string MMIX_START_SYMBOL_NAME;


	    /* We smuggle in a few MMO specifics here.  We don't make a specific MMO
	       file, since we can't reasonably support MMO without ELF; we have to
	       include this file anyway.  */

	    static std::string MMO_TEXT_SECTION_NAME;
	    static std::string MMO_DATA_SECTION_NAME;

	    /* A definition for the flags we put in spec data in files.  A copy of our
	       own of some flags to keep immune to BFD flag changes.  See section.c of
	       2001-07-18 for flag documentation.  */
	    /*
	      #define MMO_SEC_ALLOC      0x001
	      #define MMO_SEC_LOAD       0x002
	      #define MMO_SEC_RELOC      0x004
	      #define MMO_SEC_READONLY   0x010
	      #define MMO_SEC_CODE       0x020
	      #define MMO_SEC_DATA       0x040
	      #define MMO_SEC_NEVER_LOAD 0x400
	      #define MMO_SEC_IS_COMMON 0x8000
	      #define MMO_SEC_DEBUGGING 0x10000
	    */

	    /*
	      #ifdef BFD_ARCH_SIZE
	      extern bfd_boolean _bfd_mmix_prepare_linker_allocated_gregs
	      PARAMS ((bfd *, struct bfd_link_info *));
	      extern bfd_boolean _bfd_mmix_finalize_linker_allocated_gregs
	      PARAMS ((bfd *, struct bfd_link_info *));
	      extern bfd_boolean _bfd_mmix_check_all_relocs
	      PARAMS ((bfd *, struct bfd_link_info *));
	      #endif
	    */

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse


#include "elf_mmix.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_MMIX_HPP_INCLUDED
