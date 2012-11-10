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

#ifndef _ELF_VAX_H
#define _ELF_VAX_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_vax {
    public:

        /* Relocation types.  */
        static inline std::string get_Type (boost::uint32_t const& type);

        /* Processor specific flags for the ELF header e_flags field.  */

        /* Object contains non-PIC code */
        static const boost::uint16_t EF_VAX_NONPIC = 0x0001;

        /* Object contains D-Float insn.  */
        static const boost::uint16_t EF_VAX_DFLOAT = 0x0100;

        /* Object contains G-Float insn.  */
        static const boost::uint16_t EF_VAX_GFLOAT = 0x0200;

    };
} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_vax.inl"

#endif
