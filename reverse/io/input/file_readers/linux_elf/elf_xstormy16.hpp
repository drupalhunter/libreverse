/*  Elf_xstormy16.h

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
  XSTORMY16 ELF support for BFD.
  Copyright (C) 2001, 2002 Free Software Foundation, Inc.

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
  along with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_XSTORMY16_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_XSTORMY16_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_xstormy16 {
	  public:

	    static std::string get_type ( boost::uint32_t type );

	    /* Define the data & instruction memory discriminator.  In a
	       linked executable, an symbol should be deemed to point to an
	       instruction if ((address & XSTORMY16_INSN_MASK) ==
	       XSTORMY16_INSN_VALUE), and similarly for the data space.  See
	       also `ld/emulparams/elf32xstormy16.sh'.  */

	    static const boost::uint32_t XSTORMY16_DATA_MASK   = 0xffc00000;
	    static const boost::uint32_t XSTORMY16_DATA_VALUE  = 0x00000000;
	    static const boost::uint32_t XSTORMY16_INSN_MASK   = 0xffc00000;
	    static const boost::uint32_t XSTORMY16_INSN_VALUE  = 0x00400000;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_xstormy16.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_XSTORMY16_HPP_INCLUDED
