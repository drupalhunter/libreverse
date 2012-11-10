/*  Elf_or32.h

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
  OR1K ELF support for BFD. Derived from ppc.h.
  Copyright (C) 2002 Free Software Foundation, Inc.
  Contributed by Ivan Guzvinec  <ivang@opencores.org>

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

#ifndef _ELF_OR32_H
#define _ELF_OR32_H

#include "Elf_Common.h"
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_or32 {
    public:

        static inline std::string get_Type (boost::uint32_t type);

        /* Four bit OR32 machine type field.  */
        static const boost::uint32_t EF_OR32_MACH = 0x0000000f;

        /* Various CPU types.  */
        static const boost::uint32_t E_OR32_MACH_BASE = 0x00000000;
        static const boost::uint32_t E_OR32_MACH_UNUSED1 = 0x00000001;
        static const boost::uint32_t E_OR32_MACH_UNUSED2 = 0x00000002;
        static const boost::uint32_t E_OR32_MACH_UNUSED4 =  0x00000003;
    
        /* Processor specific section headers, sh_type field */

        /* Link editor is to sort the entries in this section based on the
           address specified in the associated symbol table entry.  */
        static const boost::uint32_t SHT_ORDERED = Elf_Common::SHT_HIPROC;

        /* Processor specific section flags, sh_flags field */

        /* Link editor is to exclude this section from executable and
           shared objects that it builds when those objects are not to be
           furhter relocated.  */
        static const boost::uint32_t SHF_EXCLUDE = 0x80000000;

    };
} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_or32.inl"

#endif /* _ELF_OR32_H */
