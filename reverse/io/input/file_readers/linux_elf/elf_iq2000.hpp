/*  Elf_iq2000.h

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
  IQ2000 ELF support for BFD.
  Copyright (C) 2002 Free Software Foundation, Inc.

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
  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef _ELF_IQ2000_H
#define _ELF_IQ2000_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_iq2000 {
    public:

        static inline std::string get_Type (boost::uint32_t type);

        /* default */
        static const boost::uint32_t EF_IQ2000_CPU_IQ2000	 = 0x00000001;
        /* IQ10 */
        static const boost::uint32_t EF_IQ2000_CPU_IQ10       = 0x00000002;
        /* specific cpu bits */
        static const boost::uint32_t EF_IQ2000_CPU_MASK	 = 0x00000003;
        static const boost::uint32_t EF_IQ2000_ALL_FLAGS = EF_IQ2000_CPU_MASK;

        /* Define the data & instruction memory discriminator.  In a linked
           executable, an symbol should be deemed to point to an instruction
           if ((address & IQ2000_INSN_MASK) == IQ2000_INSN_VALUE), and similarly
           for the data space.  */

        static const boost::uint32_t IQ2000_DATA_MASK    = 0x80000000;
        static const boost::uint32_t IQ2000_DATA_VALUE   = 0x00000000;
        static const boost::uint32_t IQ2000_INSN_MASK    = 0x80000000;
        static const boost::uint32_t IQ2000_INSN_VALUE   = 0x80000000;
    };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_iq2000.inl"

#endif /* _ELF_IQ2000_H */
