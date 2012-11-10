/*  Elf_frv.h

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

  FRV ELF support for BFD.
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

#ifndef _ELF_FRV_H
#define _ELF_FRV_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_frv {
    public:

      static inline std::string get_Type ( boost::uint32_t type );

      /* Processor specific flags for the ELF header e_flags field.  */

      /* gpr support */
      static const boost::uint32_t EF_FRV_GPR_MASK = 0x00000003;	/* mask for # of gprs */
      static const boost::uint32_t EF_FRV_GPR_32 = 0x00000001;	/* -mgpr-32 */
      static const boost::uint32_t EF_FRV_GPR_64 = 0x00000002;	/* -mgpr-64 */

      /* fpr support */
      static const boost::uint32_t EF_FRV_FPR_MASK = 0x0000000c;	/* mask for # of fprs */
      static const boost::uint32_t  EF_FRV_FPR_32 = 0x00000004;	/* -mfpr-32 */
      static const boost::uint32_t  EF_FRV_FPR_64 = 0x00000008;	/* -mfpr-64 */
      static const boost::uint32_t  EF_FRV_FPR_NONE = 0x0000000c; /* -msoft-float */

      /* double word support */

      /* mask for dword support */
      static const boost::uint32_t  EF_FRV_DWORD_MASK = 0x00000030; 

      /* use double word insns */
      static const boost::uint32_t  EF_FRV_DWORD_YES = 0x00000010;

      /* don't use double word insn*/
      static const boost::uint32_t  EF_FRV_DWORD_NO = 0x00000020;
    
      static const boost::uint32_t  EF_FRV_DOUBLE = 0x00000040;	/* -mdouble */
      static const boost::uint32_t  EF_FRV_MEDIA	 = 0x00000080;	/* -mmedia */

      static const boost::uint32_t  EF_FRV_PIC = 0x00000100;	/* -fpic */

      /* used non pic safe relocs */
      static const boost::uint32_t  EF_FRV_NON_PIC_RELOCS = 0x00000200;

      static const boost::uint32_t  EF_FRV_MULADD = 0x00000400;	/* -mmuladd */
      static const boost::uint32_t  EF_FRV_BIGPIC = 0x00000800;	/* -fPIC */
      static const boost::uint32_t  EF_FRV_LIBPIC = 0x00001000;	/* -mlibrary-pic */
      static const boost::uint32_t  EF_FRV_G0	 = 0x00002000;	/* -G 0, no small data ptr */
      static const boost::uint32_t  EF_FRV_NOPACK = 0x00004000;	/* -mnopack */
      static const boost::uint32_t  EF_FRV_CPU_MASK = 0xff000000;	/* specific cpu bits */
      static const boost::uint32_t  EF_FRV_CPU_GENERIC = 0x00000000;	/* generic FRV */
      static const boost::uint32_t  EF_FRV_CPU_FR500 = 0x01000000;	/* FRV500 */
      static const boost::uint32_t  EF_FRV_CPU_FR300 = 0x02000000;	/* FRV300 */
      static const boost::uint32_t  EF_FRV_CPU_SIMPLE = 0x03000000;	/* SIMPLE */
      static const boost::uint32_t  EF_FRV_CPU_TOMCAT = 0x04000000;

      /* Tomcat, FR500 prototype */
      static const boost::uint32_t  EF_FRV_CPU_FR400 = 0x05000000;	/* FRV400 */

      /* Mask of PIC related bits */
      static const boost::uint32_t EF_FRV_PIC_FLAGS = (EF_FRV_PIC | EF_FRV_LIBPIC | EF_FRV_BIGPIC);

      /* Mask of all flags */
      static const boost::uint32_t  EF_FRV_ALL_FLAGS = (EF_FRV_GPR_MASK | \
							EF_FRV_FPR_MASK | \
							EF_FRV_DWORD_MASK | \
							EF_FRV_DOUBLE | \
							EF_FRV_MEDIA | \
							EF_FRV_PIC_FLAGS | \
							EF_FRV_NON_PIC_RELOCS | \
							EF_FRV_MULADD | \
							EF_FRV_G0 | \
							EF_FRV_NOPACK | \
							EF_FRV_CPU_MASK);

    };
  } /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_frv.inl"

#endif /* _ELF_FRV_H */
