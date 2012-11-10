/*  Elf_hppa.h

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

/* HPPA ELF support for BFD.
   Copyright 1993, 1994, 1995, 1998, 1999, 2000
   Free Software Foundation, Inc.

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

/* This file holds definitions specific to the HPPA ELF ABI.  Note
   that most of this is not actually implemented by BFD.  */

#ifndef _ELF_HPPA_H
#define _ELF_HPPA_H

#include "Elf_Common.h"
#include <string>

namespace libreverse { namespace elf_module {

    class Elf_hppa {
    public:

        /* Processor specific flags for the ELF header e_flags field.  */

        /* Trap null address dereferences.  */
        static const boost::uint32_t EF_PARISC_TRAPNIL	= 0x00010000;

        /* .PARISC.archext section is present.  */
        static const boost::uint32_t EF_PARISC_EXT		= 0x00020000;

        /* Program expects little-endian mode.  */
        static const boost::uint32_t EF_PARISC_LSB		= 0x00040000;

        /* Program expects wide mode.  */
        static const boost::uint32_t EF_PARISC_WIDE	= 0x00080000;

        /* Do not allow kernel-assisted branch prediction.  */
        static const boost::uint32_t EF_PARISC_NO_KABP	= 0x00100000;

        /* Allow lazy swap for dynamically allocated program segments.  */
        static const boost::uint32_t EF_PARISC_LAZYSWAP	= 0x00400000;

        /* Architecture version */
        static const boost::uint32_t EF_PARISC_ARCH	= 0x0000ffff;

        static const boost::uint16_t EFA_PARISC_1_0	= 0x020b;
        static const boost::uint16_t EFA_PARISC_1_1	= 0x0210;
        static const boost::uint16_t EFA_PARISC_2_0	= 0x0214;

        /* Special section indices.  */
        /* A symbol that has been declared as a tentative definition in an ANSI C
           compilation.  */
        static const boost::uint16_t SHN_PARISC_ANSI_COMMON = 0xff00;

        /* A symbol that has been declared as a common block using the
           huge memory model.  */
        static const boost::uint16_t SHN_PARISC_HUGE_COMMON = 0xff01;

        /* Processor specific section types.  */

        /* Section contains product specific extension bits.  */
        static const boost::uint32_t SHT_PARISC_EXT	= 0x70000000;

        /* Section contains unwind table entries.  */
        static const boost::uint32_t SHT_PARISC_UNWIND	= 0x70000001;

        /* Section contains debug information for optimized code.  */
        static const boost::uint32_t SHT_PARISC_DOC	= 0x70000002;

        /* Section contains code annotations.  */
        static const boost::uint32_t SHT_PARISC_ANNOT	= 0x70000003;

        /* These are strictly for compatibility with the older elf32-hppa
           implementation.  Hopefully we can eliminate them in the future.  */
        /* Optional section holding argument location/relocation info.  */
        static const boost::uint32_t SHT_PARISC_SYMEXTN    = Elf_Common::SHT_LOPROC+8;

        /* Option section for linker stubs.  */
        static const boost::uint32_t SHT_PARISC_STUBS      = Elf_Common::SHT_LOPROC+9;

        /* Processor specific section flags.  */

        /* Section contains code compiled for static branch prediction.  */
        static const boost::uint32_t SHF_PARISC_SBP	= 0x80000000;

        /* Section should be allocated from from GP.  */
        static const boost::uint32_t SHF_PARISC_HUGE	= 0x40000000;

        /* Section should go near GP.  */
        static const boost::uint32_t SHF_PARISC_SHORT	= 0x20000000;


        /* Identifies the entry point of a millicode routine.  */
        static const boost::uint8_t STT_PARISC_MILLI	= 13;

        /* ELF/HPPA relocation types */
        static inline std::string get_Type ( boost::uint32_t type );

        /*
          #ifndef RELOC_MACROS_GEN_FUNC
          typedef enum elf_hppa_reloc_type elf_hppa_reloc_type;
          #endif
        */

        static const boost::uint32_t PT_PARISC_ARCHEXT	= 0x70000000;
        static const boost::uint32_t PT_PARISC_UNWIND	= 0x70000001;
        static const boost::uint32_t PF_PARISC_SBP		= 0x08000000;
        static const boost::uint32_t PF_HP_PAGE_SIZE	= 0x00100000;
        static const boost::uint32_t PF_HP_FAR_SHARED	= 0x00200000;
        static const boost::uint32_t PF_HP_NEAR_SHARED	= 0x00400000;
        static const boost::uint32_t PF_HP_CODE		= 0x01000000;
        static const boost::uint32_t PF_HP_MODIFY		= 0x02000000;
        static const boost::uint32_t PF_HP_LAZYSWAP	= 0x04000000;
        static const boost::uint32_t PF_HP_SBP		= 0x08000000;

        /* Processor specific dynamic array tags.  */

        /* Arggh.  HP's tools define these symbols based on the
           old value of DT_LOOS.  So we must do the same to be
           compatible.  */
        static const boost::uint32_t DT_HP_LOAD_MAP	= (Elf_Common::OLD_DT_LOOS + 0x0);
        static const boost::uint32_t DT_HP_DLD_FLAGS	= (Elf_Common::OLD_DT_LOOS + 0x1);
        static const boost::uint32_t DT_HP_DLD_HOOK	= (Elf_Common::OLD_DT_LOOS + 0x2);
        static const boost::uint32_t DT_HP_UX10_INIT	= (Elf_Common::OLD_DT_LOOS + 0x3);
        static const boost::uint32_t DT_HP_UX10_INITSZ	= (Elf_Common::OLD_DT_LOOS + 0x4);
        static const boost::uint32_t DT_HP_PREINIT	        = (Elf_Common::OLD_DT_LOOS + 0x5);
        static const boost::uint32_t DT_HP_PREINITSZ	= (Elf_Common::OLD_DT_LOOS + 0x6);
        static const boost::uint32_t DT_HP_NEEDED	        = (Elf_Common::OLD_DT_LOOS + 0x7);
        static const boost::uint32_t DT_HP_TIME_STAMP	= (Elf_Common::OLD_DT_LOOS + 0x8);
        static const boost::uint32_t DT_HP_CHECKSUM	= (Elf_Common::OLD_DT_LOOS + 0x9);
        static const boost::uint32_t DT_HP_GST_SIZE	= (Elf_Common::OLD_DT_LOOS + 0xa);
        static const boost::uint32_t DT_HP_GST_VERSION	= (Elf_Common::OLD_DT_LOOS + 0xb);
        static const boost::uint32_t DT_HP_GST_HASHVAL	= (Elf_Common::OLD_DT_LOOS + 0xc);

        /* Values for DT_HP_DLD_FLAGS.  */
        static const boost::uint16_t DT_HP_DEBUG_PRIVATE	        = 0x0001; /* Map text private */
        static const boost::uint16_t DT_HP_DEBUG_CALLBACK	        = 0x0002; /* Callback */
        static const boost::uint16_t DT_HP_DEBUG_CALLBACK_BOR	= 0x0004; /* BOR callback */
        static const boost::uint16_t DT_HP_NO_ENVVAR		= 0x0008; /* No env var */
        static const boost::uint16_t DT_HP_BIND_NOW		= 0x0010; /* Bind now */
        static const boost::uint16_t DT_HP_BIND_NONFATAL		= 0x0020; /* Bind non-fatal */
        static const boost::uint16_t DT_HP_BIND_VERBOSE		= 0x0040; /* Bind verbose */
        static const boost::uint16_t DT_HP_BIND_RESTRICTED		= 0x0080; /* Bind restricted */
        static const boost::uint16_t DT_HP_BIND_SYMBOLIC		= 0x0100; /* Bind symbolic */
        static const boost::uint16_t DT_HP_RPATH_FIRST		= 0x0200; /* RPATH first */
        static const boost::uint16_t DT_HP_BIND_DEPTH_FIRST	= 0x0400; /* Bind depth-first */

        /* Program header extensions.  */
        static const boost::uint32_t PT_HP_TLS		= (Elf_Common::PT_LOOS + 0x0);
        static const boost::uint32_t PT_HP_CORE_NONE	= (Elf_Common::PT_LOOS + 0x1);
        static const boost::uint32_t PT_HP_CORE_VERSION	= (Elf_Common::PT_LOOS + 0x2);
        static const boost::uint32_t PT_HP_CORE_KERNEL	= (Elf_Common::PT_LOOS + 0x3);
        static const boost::uint32_t PT_HP_CORE_COMM	= (Elf_Common::PT_LOOS + 0x4);
        static const boost::uint32_t PT_HP_CORE_PROC	= (Elf_Common::PT_LOOS + 0x5);
        static const boost::uint32_t PT_HP_CORE_LOADABLE	= (Elf_Common::PT_LOOS + 0x6);
        static const boost::uint32_t PT_HP_CORE_STACK	= (Elf_Common::PT_LOOS + 0x7);
        static const boost::uint32_t PT_HP_CORE_SHM	= (Elf_Common::PT_LOOS + 0x8);
        static const boost::uint32_t PT_HP_CORE_MMF	= (Elf_Common::PT_LOOS + 0x9);
        static const boost::uint32_t PT_HP_PARALLEL	= (Elf_Common::PT_LOOS + 0x10);
        static const boost::uint32_t PT_HP_FASTBIND	= (Elf_Common::PT_LOOS + 0x11);

        /* Additional symbol types.  */
        static const boost::uint8_t STT_HP_OPAQUE		= (Elf_Common::STT_LOOS + 0x1);
        static const boost::uint8_t STT_HP_STUB		= (Elf_Common::STT_LOOS + 0x2);

    };
} /* namespace elf_module */
} /* namespace libreverse */

#include "Elf_hppa.inl"

#endif /* _ELF_HPPA_H */
