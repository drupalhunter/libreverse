/*  Elf_arc.h

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
  ARC ELF support for BFD.
  Copyright 1995, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.
  Contributed by Doug Evans, (dje@cygnus.com)

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

/* This file holds definitions specific to the ARC ELF ABI.  */

#ifndef _ELF_ARC_H
#define _ELF_ARC_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse {
namespace elf_module {

  class Elf_arc {
  public:

    static inline std::string get_Type ( boost::uint32_t type );

    /* Processor specific flags for the ELF header e_flags field.  */

    /* Four bit ARC machine type field.  */

    static const boost::uint32_t EF_ARC_MACH = 0x0000000f;

    /* Various CPU types.  */
    static const boost::uint8_t E_ARC_MACH_ARC5 = 0;
    static const boost::uint8_t E_ARC_MACH_ARC6 = 1;
    static const boost::uint8_t E_ARC_MACH_ARC7 = 2;
    static const boost::uint8_t E_ARC_MACH_ARC8 = 3;

    /* Leave bits 0xf0 alone in case we ever have more than 16 cpu types.  */

    /* File contains position independent code.  */
    static const boost::uint32_t EF_ARC_PIC = 0x00000100;
  };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_arc.inl"

#endif /* _ELF_ARC_H */
