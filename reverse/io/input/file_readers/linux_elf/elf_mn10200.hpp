/*  Elf_mn10200.h

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
  MN10200 ELF support for BFD.  Copyright 1998, 2000 Free Software
  Foundation, Inc.

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

/* This file holds definitions specific to the MN10200 ELF ABI. */

#ifndef _ELF_MN10200_H
#define _ELF_MN10200_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

  class Elf_mn10200 {
  public:

      static inline std::string get_Type (boost::uint32_t type);

  };
} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_mn10200.inl"

#endif /* _ELF_MN10200_H */
