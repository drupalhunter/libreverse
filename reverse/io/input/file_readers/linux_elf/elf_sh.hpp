/*  Elf_sh.h

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
  SH ELF support for BFD.
  Copyright 1998, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SH_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SH_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_sh {
	  public:

	    /* Relocation types.  */

	    static inline std::string get_type (boost::uint32_t type);

	    /* Processor specific flags for the ELF header e_flags field.  */
	    static const boost::uint8_t EF_SH_MACH_MASK	= 0x1f;

	    /* For backwards compatibility.  */
	    static const boost::uint8_t EF_SH_UNKNOWN	   = 0;
	    static const boost::uint8_t EF_SH1		   = 1;
	    static const boost::uint8_t EF_SH2		   = 2;
	    static const boost::uint8_t EF_SH3		   = 3;
	    static const boost::uint8_t EF_SH_DSP	   = 4;
	    static const boost::uint8_t EF_SH3_DSP	   = 5;
	    static const boost::uint8_t EF_SH3E		   = 8;
	    static const boost::uint8_t EF_SH4		   = 9;
	    static const boost::uint8_t EF_SH5		   = 10;
	    static const boost::uint8_t EF_SH2E            = 11;

	    /* A reference to this symbol should by default add 1.  */
	    static const boost::uint8_t STO_SH5_ISA32 = 0x04;

	    /* Section contains only SHmedia code (no SHcompact code).  */
	    static const boost::uint32_t SHF_SH5_ISA32 = 0x40000000;

	    /* Section contains both SHmedia and SHcompact code, and possibly also
	       constants.  */
	    static const boost::uint32_t SHF_SH5_ISA32_MIXED = 0x20000000;

	    /* If applied to a .cranges section, marks that the section is sorted by
	       increasing cr_addr values.  */
	    static const boost::uint32_t SHT_SH5_CR_SORTED = 0x80000001;

	    /* Symbol should be handled as DataLabel (attached to global SHN_UNDEF
	       symbols).  */
	    static const boost::uint8_t STT_DATALABEL = elf_common::STT_LOPROC;

	    /**
	     * Functions
	     */
	    static inline bool EF_SH_HAS_FP (boost::uint8_t flags);

	    static inline bool EF_SH_HAS_DSP (boost::uint8_t flags);

	    /* This one can only mix in objects from other EF_SH5 objects.  */
	    static inline boost::uint8_t EF_SH_MERGE_MACH ( boost::uint8_t mach1,
							    boost::uint8_t mach2 );
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_sh.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SH_HPP_INCLUDED
