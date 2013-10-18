/*  Elf_m32r.h

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
  M32R ELF support for BFD.
  Copyright 1996, 1997, 1998, 1999, 2000 Free Software Foundation, Inc.

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
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.

*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_M32R_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_M32R_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /* Relocations.  */
	  class elf_m32r {
	  public:

	    /* m32r Relocation types */
	    static inline std::string get_type (boost::uint32_t type);

	    /* Small common symbol.  */
	    static const boost::uint16_t SHN_M32R_SCOMMON = 0xFF00;

	    /* Processor specific section flags.  */

	    /* This section contains sufficient relocs to be relaxed.  When
	       relaxing, even relocs of branch instructions the assembler
	       could complete must be present because relaxing may cause the
	       branch target to move.
	    */
	    static const boost::uint32_t SHF_M32R_CAN_RELAX = 0x10000000;

	    /* Processor specific flags for the ELF header e_flags field.  */

	    /* Two bit m32r architecture field.  */
	    static const boost::uint32_t EF_M32R_ARCH = 0x30000000;

	    /* m32r code.  */
	    static const boost::uint32_t E_M32R_ARCH = 0x00000000;

	    /* m32rx code.  */
	    static const boost::uint32_t E_M32RX_ARCH = 0x10000000;

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_m32r.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_M32R_HPP_INCLUDED
