/*  Elf_ppc64.h

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
  PPC64 ELF support for BFD.
  Copyright 2003 Free Software Foundation, Inc.

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

#ifndef _ELF_PPC64_H
#define _ELF_PPC64_H

#include "Elf_Common.h"

namespace libreverse { namespace elf_module {
    
    class Elf_ppc64 {
    public:
        
        static inline std::string get_Type (boost::uint32_t type);
        
        static inline bool IS_PPC64_TLS_RELOC (boost::uint32_t value);

        /* Specify the start of the .glink section.  */
        static const boost::uint32_t DT_PPC64_GLINK = Elf_Common::DT_LOPROC;

        /* Specify the start and size of the .opd section.  */
        static const boost::uint32_t DT_PPC64_OPD = (Elf_Common::DT_LOPROC + 1);
        static const boost::uint32_t DT_PPC64_OPDSZ = (Elf_Common::DT_LOPROC + 2);

    };
} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_ppc64.inl"

#endif /* _ELF_PPC64_H */
