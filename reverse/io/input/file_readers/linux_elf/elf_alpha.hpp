/*  Elf_alpha.h

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
  ALPHA ELF support for BFD.
  Copyright 1996, 1998, 2000 Free Software Foundation, Inc.

  By Eric Youngdale, <eric@aib.com>.  No processor supplement available
  for this platform.

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

/* This file holds definitions specific to the ALPHA ELF ABI.  Note
   that most of this is not actually implemented by BFD.  */

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_ALPHA_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_ALPHA_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {


	  class elf_alpha {
	  public:

	    /* Processor specific flags for the ELF header e_flags field.  */

	    /* All addresses must be below 2GB.  */
	    static const boost::uint32_t EF_ALPHA_32BIT = 0x00000001;

	    /* All relocations needed for relaxation with code movement are
	       present.  */
	    static const boost::uint32_t EF_ALPHA_CANRELAX = 0x00000002;

	    /* Processor specific section flags.  */

	    /* This section must be in the global data area.  */
	    static const boost::uint32_t SHF_ALPHA_GPREL = 0x10000000;

	    /* Section contains some sort of debugging information.  The exact
	       format is unspecified.  It's probably ECOFF symbols.  */
	    static const boost::uint32_t SHT_ALPHA_DEBUG = 0x70000001;

	    /* Section contains register usage information. */
	    static const boost::uint32_t SHT_ALPHA_REGINFO = 0x70000002;

	    /* A section of type SHT_MIPS_REGINFO contains the following
	       structure.  */
	    typedef struct
	    {
	      /* Mask of general purpose registers used.  */
	      unsigned long ri_gprmask;
	      /* Mask of co-processor registers used.  */
	      unsigned long ri_cprmask[4];
	      /* GP register value for this object file.  */
	      long ri_gp_value;
	    } Elf64_RegInfo;

	    /* Special values for the st_other field in the symbol table.  */
	    static const boost::uint8_t STO_ALPHA_NOPV = 0x80;
	    static const boost::uint8_t STO_ALPHA_STD_GPLOAD =	0x88;

	    static inline std::string get_type ( boost::uint32_t type );

	    static const boost::uint8_t LITUSE_ALPHA_ADDR = 0;
	    static const boost::uint8_t LITUSE_ALPHA_BASE = 1;
	    static const boost::uint8_t LITUSE_ALPHA_BYTOFF = 2;
	    static const boost::uint8_t LITUSE_ALPHA_JSR = 3;
	    static const boost::uint8_t LITUSE_ALPHA_TLSGD = 4;
	    static const boost::uint8_t LITUSE_ALPHA_TLSLDM = 5;

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_alpha.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_ALPHA_HPP_INCLUDED
