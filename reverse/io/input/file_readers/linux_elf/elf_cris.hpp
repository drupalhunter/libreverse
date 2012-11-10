/*  Elf_cris.h

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
  CRIS ELF support for BFD.

  Copyright 2000, 2001 Free Software Foundation, Inc.  Contributed by
  Axis Communications AB, Lund, Sweden.  Written by Hans-Peter
  Nilsson.

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

#ifndef _ELF_CRIS_H
#define _ELF_CRIS_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

  class Elf_cris {
  public:

      static inline std::string get_Type ( boost::uint32_t type );

      /* User symbols in this file have a leading underscore.  */
      static const boost::uint32_t EF_CRIS_UNDERSCORE = 0x00000001;
  };

} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_cris.inl"

#endif /* _ELF_CRIS_H */
