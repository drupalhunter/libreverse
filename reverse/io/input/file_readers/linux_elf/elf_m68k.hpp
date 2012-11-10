/*  Elf_m68k.h

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
  MC68k ELF support for BFD.
  Copyright 1998, 1999, 2000 Free Software Foundation, Inc.

  This file is part of BFD, the Binary File Descriptor library.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.

*/

#ifndef ELF_M68K_H_
#define ELF_M68K_H_

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_m68k {
    public:

        /* m68k Relocation Types */
        static inline std::string get_Type (boost::uint32_t type);

        static const boost::uint32_t EF_CPU32 =   0x00810000;

        static const boost::uint32_t EF_M68000 =  0x01000000;
    };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_m68k.inl"

#endif /* ELF_M68K_H_ */
