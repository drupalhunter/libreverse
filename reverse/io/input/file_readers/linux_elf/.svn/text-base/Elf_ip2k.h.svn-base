/*  Elf_ip2k.h

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
  IP2xxx ELF support for BFD.
  Copyright (C) 2000, 2002 Free Software Foundation, Inc.

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

#ifndef _ELF_IP2K_H
#define _ELF_IP2K_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_ip2k {
    public:

        static inline std::string get_Type (boost::uint32_t type);

        /* Define the data & instruction memory discriminator.  In a
           linked executable, an symbol should be deemed to point to an
           instruction if ((address & IP2K_INSN_MASK) == IP2K_INSN_VALUE),
           and similarly for the data space.  See also
           `ld/emulparams/elf32ip2k.sh'.  */

        /* ??? Consider extending the _MASK values to include all the
           intermediate bits that must be zero due to the limited physical
           memory size on the IP2K.  */

        static const boost::uint32_t IP2K_DATA_MASK  = 0xff000000;
        static const boost::uint32_t IP2K_DATA_VALUE  = 0x01000000;
        static const boost::uint32_t IP2K_INSN_MASK  = 0xff000000;
        static const boost::uint32_t IP2K_INSN_VALUE = 0x02000000;

        /* The location of the memory mapped hardware stack.  */
        static const boost::uint32_t IP2K_STACK_VALUE = 0x0f000000;
        static const boost::uint8_t IP2K_STACK_SIZE  = 0x20;
    };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_ip2k.inl"

#endif /* _ELF_IP2K_H */
