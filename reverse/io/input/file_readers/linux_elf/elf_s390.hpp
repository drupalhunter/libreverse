/*  Elf_s390.h

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
  390 ELF support for BFD.
  Copyright 2000, 2001 Free Software Foundation, Inc.
  Contributed by Carl B. Pedersen and Martin Schwidefsky.

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
  02111-1307, USA.  */

#ifndef _ELF_390_H
#define _ELF_390_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_s390 {
    public:

        /* Processor specific flags for the ELF header e_flags field.  */

        /* Symbol types.  */
        static const boost::uint8_t STACK_REG = 15;   /* Global Stack reg */
        static const boost::uint8_t BACKL_REG = 14;   /* Global Backlink reg */
        static const boost::uint8_t BASE_REG = 13;    /* Global Base reg */
        static const boost::uint8_t GOT_REG = 12;	   /* Holds addr of GOT */

        /* Relocation types.  */
        static inline std::string get_Type (boost::uint32_t type);
    };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_s390.inl"

#endif /* _ELF_390_H */


  
