/*  Elf_vax.h

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
  VAX ELF support for BFD.
  Copyright (C) 2002 Free Software Foundation, Inc.
  Contributed by Matt Thomas <matt@3am-software.com>.

  This file is part of BFD, the Binary File Descriptor library.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.

*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VAX_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VAX_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_vax {
	  public:

	    /* Relocation types.  */
	    static inline std::string get_type (boost::uint32_t const& type);

	    /* Processor specific flags for the ELF header e_flags field.  */

	    /* Object contains non-PIC code */
	    static const boost::uint16_t EF_VAX_NONPIC = 0x0001;

	    /* Object contains D-Float insn.  */
	    static const boost::uint16_t EF_VAX_DFLOAT = 0x0100;

	    /* Object contains G-Float insn.  */
	    static const boost::uint16_t EF_VAX_GFLOAT = 0x0200;

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_vax.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VAX_HPP_INCLUDED
