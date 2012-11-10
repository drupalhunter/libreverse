/*  Elf_xtensa.h

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
  Xtensa ELF support for BFD.
  Copyright 2003 Free Software Foundation, Inc.
  Contributed by Bob Wilson (bwilson@tensilica.com) at Tensilica.

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
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* This file holds definitions specific to the Xtensa ELF ABI.  */

#ifndef _ELF_XTENSA_H
#define _ELF_XTENSA_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_xtensa {
    public:

        static inline std::string get_Type ( boost::uint32_t type );

        /* Processor-specific flags for the ELF header e_flags field.  */
    
        /* Four-bit Xtensa machine type field.  */
        static const boost::uint32_t EF_XTENSA_MACH  = 0x0000000f;

        /* Various CPU types.  */
        static const boost::uint32_t E_XTENSA_MACH    = 0x00000000;

        /* Leave bits 0xf0 alone in case we ever have more than 16 cpu
           types.  Highly unlikely, but what the heck.  */

        static const boost::uint32_t EF_XTENSA_XT_INSN   = 0x00000100;
        static const boost::uint32_t EF_XTENSA_XT_LIT   = 0x00000200;

        /* Processor-specific dynamic array tags.  */

        /* Offset of the table that records the GOT location(s).  */
        static const boost::uint32_t DT_XTENSA_GOT_LOC_OFF   = 0x70000000;

        /* Number of entries in the GOT location table.  */
        static const boost::uint32_t DT_XTENSA_GOT_LOC_SZ   = 0x70000001;


        /* Definitions for instruction and literal property tables.  The
           instruction tables for ".gnu.linkonce.t.*" sections are placed
           in the following sections:

           instruction tables: .gnu.linkonce.x.* literal tables:
           .gnu.linkonce.p.*
        */

        static std::string XTENSA_INSN_SEC_NAME;
        static std::string XTENSA_LIT_SEC_NAME;

        /*
          typedef struct property_table_entry_t
          {
          bfd_vma address;
          bfd_vma size;
          } property_table_entry;
        */
    };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_xtensa.inl"

#endif /* _ELF_XTENSA_H */
