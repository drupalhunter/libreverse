/*  Elf_Common.h

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
  Utilized the header from readelf for libreverse. Original License is below.

  ELF support for BFD.
  Copyright 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000,
  2001, 2002, 2003
  Free Software Foundation, Inc.

  Written by Fred Fish @ Cygnus Support, from information published
  in "UNIX System V Release 4, Programmers Guide: ANSI C and
  Programming Support Tools".

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


/* This file is part of ELF support for BFD, and contains the portions
   that are common to both the internal and external representations.
   For example, ELFMAG0 is the byte 0x7F in both the internal (in-memory)
   and external (in-file) representations.  */

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_COMMON_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_COMMON_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {


	  class elf_common {
	  public:

	    static const boost::uint8_t ELFCLASSNONE = 0;   /* Invalid class */
	    static const boost::uint8_t ELFCLASS32   = 1;   /* 32-bit objects */
	    static const boost::uint8_t ELFCLASS64   = 2;   /* 64-bit objects */


	    static const boost::uint8_t ELFDATANONE  = 0;   /* Invalid data encoding */
	    static const boost::uint8_t ELFDATA2LSB  = 1;   /* 2's complement, little endian */
	    static const boost::uint8_t ELFDATA2MSB  = 2;   /* 2's complement, big endian */

	    static const boost::uint8_t ELFOSABI_NONE	       = 0;	/* UNIX System V ABI */
	    static const boost::uint8_t ELFOSABI_HPUX	       = 1;	/* HP-UX operating system */
	    static const boost::uint8_t ELFOSABI_NETBSD      = 2;	/* NetBSD */
	    static const boost::uint8_t ELFOSABI_LINUX       = 3;	/* GNU/Linux */
	    static const boost::uint8_t ELFOSABI_HURD	       = 4;	/* GNU/Hurd */
	    static const boost::uint8_t ELFOSABI_SOLARIS     = 6;	/* Solaris */
	    static const boost::uint8_t ELFOSABI_AIX	       = 7;	/* AIX */
	    static const boost::uint8_t ELFOSABI_IRIX	       = 8;	/* IRIX */
	    static const boost::uint8_t ELFOSABI_FREEBSD     = 9;	/* FreeBSD */
	    static const boost::uint8_t ELFOSABI_TRU64       = 10;	/* TRU64 UNIX */
	    static const boost::uint8_t ELFOSABI_MODESTO     = 11;	/* Novell Modesto */
	    static const boost::uint8_t ELFOSABI_OPENBSD     = 12;	/* OpenBSD */
	    static const boost::uint8_t ELFOSABI_OPENVMS     = 13;	/* OpenVMS */
	    static const boost::uint8_t ELFOSABI_NSK	       = 14;	/* Hewlett-Packard Non-Stop Kernel */
	    static const boost::uint8_t ELFOSABI_AROS	       = 15;	/* Amiga Research OS */
	    static const boost::uint8_t ELFOSABI_ARM	       = 97;	/* ARM */
	    static const boost::uint8_t ELFOSABI_STANDALONE  = 255;	/* Standalone (embedded) application */

	    /* Values for e_type, which identifies the object file type.  */

	    static const boost::uint8_t ET_NONE	= 0;	/* No file type */
	    static const boost::uint8_t ET_REL	= 1;	/* Relocatable file */
	    static const boost::uint8_t ET_EXEC	= 2;	/* Executable file */
	    static const boost::uint8_t ET_DYN	= 3;	/* Shared object file */
	    static const boost::uint8_t ET_CORE	= 4;	/* Core file */

	    static const boost::uint16_t ET_LOOS	= 0xFE00;	/* Operating system-specific */
	    static const boost::uint16_t ET_HIOS	= 0xFEFF;	/* Operating system-specific */
	    static const boost::uint16_t ET_LOPROC	= 0xFF00;	/* Processor-specific */
	    static const boost::uint16_t ET_HIPROC	= 0xFFFF;	/* Processor-specific */

	    /* Values for e_machine, which identifies the architecture.  These numbers
	       are officially assigned by registry@caldera.com.  See below for a list of
	       ad-hoc numbers used during initial development.  */

	    static const boost::uint8_t EM_NONE	  = 0;	/* No machine */
	    static const boost::uint8_t EM_M32	  = 1;	/* AT&T WE 32100 */
	    static const boost::uint8_t EM_SPARC  = 2;	/* SUN SPARC */
	    static const boost::uint8_t EM_386	  = 3;	/* Intel 80386 */
	    static const boost::uint8_t EM_68K	  = 4;	/* Motorola m68k family */
	    static const boost::uint8_t EM_88K	  = 5;	/* Motorola m88k family */
	    static const boost::uint8_t EM_486	  = 6;	/* Intel 80486 *//* Reserved for future use */
	    static const boost::uint8_t EM_860	  = 7;	/* Intel 80860 */
	    static const boost::uint8_t EM_MIPS	  = 8;	/* MIPS R3000 (officially, big-endian only) */
	    static const boost::uint8_t EM_S370	  = 9;	/* IBM System/370 */
	    static const boost::uint8_t EM_MIPS_RS3_LE  = 10;	/* MIPS R3000 little-endian (Oct 4 1999 Draft) Deprecated */

	    static const boost::uint8_t EM_PARISC	  = 15;	/* HPPA */

	    static const boost::uint8_t EM_VPP550	  = 17;	/* Fujitsu VPP500 */
	    static const boost::uint8_t EM_SPARC32PLUS  = 18;	/* Sun's "v8plus" */
	    static const boost::uint8_t EM_960	  = 19;	/* Intel 80960 */
	    static const boost::uint8_t EM_PPC	  = 20;	/* PowerPC */
	    static const boost::uint8_t EM_PPC64	  = 21;	/* 64-bit PowerPC */
	    static const boost::uint8_t EM_S390	  = 22;	/* IBM S/390 */

	    static const boost::uint8_t EM_V800	  = 36;	/* NEC V800 series */
	    static const boost::uint8_t EM_FR20	  = 37;	/* Fujitsu FR20 */
	    static const boost::uint8_t EM_RH32	  = 38;	/* TRW RH32 */
	    static const boost::uint8_t EM_MCORE	  = 39;	/* Motorola M*Core */ /* May also be taken by Fujitsu MMA */
	    static const boost::uint8_t EM_RCE	  = 39;	/* Old name for MCore */
	    static const boost::uint8_t EM_ARM	  = 40;	/* ARM */
	    static const boost::uint8_t EM_OLD_ALPHA	  = 41;	/* Digital Alpha */
	    static const boost::uint8_t EM_SH		  = 42;	/* Renesas (formerly Hitachi) / SuperH SH */
	    static const boost::uint8_t EM_SPARCV9	  = 43;	/* SPARC v9 64-bit */
	    static const boost::uint8_t EM_TRICORE	  = 44;	/* Siemens Tricore embedded processor */
	    static const boost::uint8_t EM_ARC          = 45;	/* ARC Cores */
	    static const boost::uint8_t EM_H8_300       = 46;	/* Renesas (formerly Hitachi) H8/300 */
	    static const boost::uint8_t EM_H8_300H      = 47;	/* Renesas (formerly Hitachi) H8/300H */
	    static const boost::uint8_t EM_H8S          = 48;	/* Renesas (formerly Hitachi) H8S */
	    static const boost::uint8_t EM_H8_500       = 49;	/* Renesas (formerly Hitachi) H8/500 */
	    static const boost::uint8_t EM_IA_64        = 50;	/* Intel IA-64 Processor */
	    static const boost::uint8_t EM_MIPS_X       = 51;	/* Stanford MIPS-X */
	    static const boost::uint8_t EM_COLDFIRE     = 52;	/* Motorola Coldfire */
	    static const boost::uint8_t EM_68HC12       = 53;	/* Motorola M68HC12 */
	    static const boost::uint8_t EM_MMA          = 54;	/* Fujitsu Multimedia Accelerator */
	    static const boost::uint8_t EM_PCP          = 55;	/* Siemens PCP */
	    static const boost::uint8_t EM_NCPU         = 56;	/* Sony nCPU embedded RISC processor */
	    static const boost::uint8_t EM_NDR1         = 57;	/* Denso NDR1 microprocesspr */
	    static const boost::uint8_t EM_STARCORE     = 58;	/* Motorola Star*Core processor */
	    static const boost::uint8_t EM_ME16         = 59;	/* Toyota ME16 processor */
	    static const boost::uint8_t EM_ST100        = 60;	/* STMicroelectronics ST100 processor */
	    static const boost::uint8_t EM_TINYJ        = 61;	/* Advanced Logic Corp. TinyJ embedded processor */
	    static const boost::uint8_t EM_X86_64       = 62;	/* Advanced Micro Devices X86-64 processor */

	    static const boost::uint8_t EM_PDP10        = 64; /* Digital Equipment Corp. PDP-10 */
	    static const boost::uint8_t EM_PDP11        = 65; /* Digital Equipment Corp. PDP-11 */
	    static const boost::uint8_t EM_FX66         = 66; /* Siemens FX66 microcontroller */
	    static const boost::uint8_t EM_ST9PLUS      = 67; /* STMicroelectronics ST9+ 8/16 bit microcontroller */
	    static const boost::uint8_t EM_ST7          = 68; /* STMicroelectronics ST7 8-bit microcontroller */
	    static const boost::uint8_t EM_68HC16       = 69; /* Motorola MC68HC16 Microcontroller */
	    static const boost::uint8_t EM_68HC11       = 70; /* Motorola MC68HC11 Microcontroller */
	    static const boost::uint8_t EM_68HC08       = 71; /* Motorola MC68HC08 Microcontroller */
	    static const boost::uint8_t EM_68HC05       = 72; /* Motorola MC68HC05 Microcontroller */
	    static const boost::uint8_t EM_SVX          = 73; /* Silicon Graphics SVx */
	    static const boost::uint8_t EM_ST19         = 74; /* STMicroelectronics ST19 8-bit cpu */
	    static const boost::uint8_t EM_VAX          = 75; /* Digital VAX */
	    static const boost::uint8_t EM_CRIS         = 76; /* Axis Communications 32-bit embedded processor */
	    static const boost::uint8_t EM_JAVELIN      = 77;	/* Infineon Technologies 32-bit embedded cpu */
	    static const boost::uint8_t EM_FIREPATH     = 78;	/* Element 14 64-bit DSP processor */
	    static const boost::uint8_t EM_ZSP          = 79;	/* LSI Logic's 16-bit DSP processor */
	    static const boost::uint8_t EM_MMIX         = 80;	/* Donald Knuth's educational 64-bit processor */
	    static const boost::uint8_t EM_HUANY        = 81;	/* Harvard's machine-independent format */
	    static const boost::uint8_t EM_PRISM        = 82;	/* SiTera Prism */
	    static const boost::uint8_t EM_AVR          = 83;	/* Atmel AVR 8-bit microcontroller */
	    static const boost::uint8_t EM_FR30         = 84;	/* Fujitsu FR30 */
	    static const boost::uint8_t EM_D10V         = 85;	/* Mitsubishi D10V */
	    static const boost::uint8_t EM_D30V         = 86;	/* Mitsubishi D30V */
	    static const boost::uint8_t EM_V850         = 87;	/* NEC v850 */
	    static const boost::uint8_t EM_M32R         = 88;	/* Renesas M32R (formerly Mitsubishi M32R) */
	    static const boost::uint8_t EM_MN10300      = 89;	/* Matsushita MN10300 */
	    static const boost::uint8_t EM_MN10200      = 90;	/* Matsushita MN10200 */
	    static const boost::uint8_t EM_PJ           = 91;	/* picoJava */
	    static const boost::uint8_t EM_OPENRISC     = 92;	/* OpenRISC 32-bit embedded processor */
	    static const boost::uint8_t EM_ARC_A5       = 93;	/* ARC Cores Tangent-A5 */
	    static const boost::uint8_t EM_XTENSA       = 94;	/* Tensilica Xtensa Architecture */

	    static const boost::uint8_t EM_IP2K         = 101;	/* Ubicom IP2022 micro controller */
	    static const boost::uint8_t EM_MSP430       = 105;	/* TI msp430 micro controller */

	    /* If it is necessary to assign new unofficial EM_* values, please pick large
	       random numbers (0x8523, 0xa7f2, etc.) to minimize the chances of collision
	       with official or non-GNU unofficial values.

	       NOTE: Do not just increment the most recent number by one.
	       Somebody else somewhere will do exactly the same thing, and you
	       will have a collision.  Instead, pick a random number.

	       Normally, each entity or maintainer responsible for a machine with an
	       unofficial e_machine number should eventually ask registry@caldera.com for
	       an officially blessed number to be added to the list above.	*/

	    static const boost::uint8_t EM_PJ_OLD = 99;	/* picoJava */

	    /* Cygnus PowerPC ELF backend.  Written in the absence of an ABI.  */
	    static const boost::uint16_t EM_CYGNUS_POWERPC = 0x9025;

	    /* Old version of Sparc v9, from before the ABI; this should be
	       removed shortly.  */
	    static const boost::uint8_t EM_OLD_SPARCV9 = 11;

	    /* Old version of PowerPC, this should be removed shortly. */
	    static const boost::uint8_t EM_PPC_OLD = 17;

	    /* (Deprecated) Temporary number for the OpenRISC processor.  */
	    static const boost::uint16_t EM_OR32 = 0x8472;

	    /* Cygnus M32R ELF backend.  Written in the absence of an ABI.  */
	    static const boost::uint16_t EM_CYGNUS_M32R = 0x9041;

	    /* Alpha backend magic number.  Written in the absence of an ABI.  */
	    static const boost::uint16_t EM_ALPHA = 0x9026;

	    /* old S/390 backend magic number. Written in the absence of an ABI.  */
	    static const boost::uint16_t EM_S390_OLD	= 0xa390;

	    /* D10V backend magic number.  Written in the absence of an ABI.  */
	    static const boost::uint16_t EM_CYGNUS_D10V = 0x7650;

	    /* D30V backend magic number.  Written in the absence of an ABI.  */
	    static const boost::uint16_t EM_CYGNUS_D30V = 0x7676;

	    /* V850 backend magic number.  Written in the absense of an ABI.  */
	    static const boost::uint16_t EM_CYGNUS_V850 = 0x9080;

	    /* mn10200 and mn10300 backend magic numbers.
	       Written in the absense of an ABI.  */
	    static const boost::uint16_t EM_CYGNUS_MN10200 = 0xdead;
	    static const boost::uint16_t EM_CYGNUS_MN10300 = 0xbeef;

	    /* FR30 magic number - no EABI available.  */
	    static const boost::uint16_t EM_CYGNUS_FR30 = 0x3330;

	    /* AVR magic number
	       Written in the absense of an ABI.  */
	    static const boost::uint16_t EM_AVR_OLD = 0x1057;

	    /* OpenRISC magic number
	       Written in the absense of an ABI.  */
	    static const boost::uint16_t EM_OPENRISC_OLD = 0x3426;

	    /* DLX magic number
	       Written in the absense of an ABI.  */
	    static const boost::uint16_t EM_DLX = 0x5aa5;

	    static const boost::uint16_t EM_XSTORMY16	= 0xad45;

	    /* FRV magic number - no EABI available??.  */
	    static const boost::uint16_t EM_CYGNUS_FRV = 0x5441;

	    /* Ubicom IP2xxx; no ABI */
	    static const boost::uint16_t EM_IP2K_OLD = 0x8217;

	    /* MSP430 magic number
	       Written in the absense everything.  */
	    static const boost::uint16_t EM_MSP430_OLD = 0x1059;

	    /* Vitesse IQ2000.  */
	    static const boost::uint16_t EM_IQ2000 = 0xFEBA;

	    /* Old, unofficial value for Xtensa.  */
	    static const boost::uint16_t EM_XTENSA_OLD = 0xabc7;

	    /* See the above comment before you add a new EM_* value here.  */

	    /* Values for e_version.  */

	    static const boost::uint8_t EV_NONE     = 0;		/* Invalid ELF version */
	    static const boost::uint8_t EV_CURRENT  = 1;		/* Current version */

	    /* Values for program header, p_type field.  */

	    static const boost::uint8_t PT_NULL       = 0;		/* Program header table entry unused */
	    static const boost::uint8_t PT_LOAD	= 1;		/* Loadable program segment */
	    static const boost::uint8_t PT_DYNAMIC	= 2;		/* Dynamic linking information */
	    static const boost::uint8_t PT_INTERP	= 3;		/* Program interpreter */
	    static const boost::uint8_t PT_NOTE	= 4;		/* Auxiliary information */
	    static const boost::uint8_t PT_SHLIB	= 5;		/* Reserved, unspecified semantics */
	    static const boost::uint8_t PT_PHDR	= 6;		/* Entry for header table itself */
	    static const boost::uint8_t PT_TLS	= 7;		/* Thread local storage segment */

	    static const boost::uint32_t PT_LOOS	= 0x60000000;	/* OS-specific */
	    static const boost::uint32_t PT_GNU_EH_FRAME = 0x6474e550;	/* GCC .eh_frame_hdr segment */
	    static const boost::uint32_t PT_GNU_STACK = 0x6474e551;	/* Indicates stack executability */
	    static const boost::uint32_t PT_GNU_RELRO = 0x6474e552;	/* Read-only after relocation */
	    static const boost::uint32_t PT_PAX_FLAGS = 0x65041580;	/* Indicates PaX flag markings */
	    static const boost::uint32_t PT_LOSUNW = 0x6ffffffa;
	    static const boost::uint32_t PT_SUNWBSS = 0x6ffffffa;	/* Sun Specific segment */
	    static const boost::uint32_t PT_SUNWSTACK = 0x6ffffffb;	/* Stack segment */

	    static const boost::uint32_t PT_HIOS	= 0x6fffffff;	/* OS-specific */
	    static const boost::uint32_t PT_LOPROC	= 0x70000000;	/* Processor-specific */
	    static const boost::uint32_t PT_HIPROC	= 0x7FFFFFFF;	/* Processor-specific */

	    /* Program segment permissions, in program header p_flags field.  */
	    static const boost::uint16_t PF_X = 1;	/* Segment is executable */
	    static const boost::uint16_t PF_W = 2;	/* Segment is writable */
	    static const boost::uint16_t PF_R = 4;	/* Segment is readable */

	    /* #define PF_MASKOS	0x0F000000    *//* OS-specific reserved bits */
	    static const boost::uint32_t PF_MASKOS	= 0x0FF00000;	/* New value, Oct 4, 1999 Draft */
	    static const boost::uint32_t PF_MASKPROC	= 0xF0000000;	/* Processor-specific reserved bits */

	    /* Values for section header, sh_type field.  */

	    static const boost::uint8_t SHT_NULL	= 0;		/* Section header table entry unused */
	    static const boost::uint8_t SHT_PROGBITS	= 1;		/* Program specific (private) data */
	    static const boost::uint8_t SHT_SYMTAB	= 2;		/* Link editing symbol table */
	    static const boost::uint8_t SHT_STRTAB	= 3;		/* A string table */
	    static const boost::uint8_t SHT_RELA	= 4;		/* Relocation entries with addends */
	    static const boost::uint8_t SHT_HASH	= 5;		/* A symbol hash table */
	    static const boost::uint8_t SHT_DYNAMIC	= 6;		/* Information for dynamic linking */
	    static const boost::uint8_t SHT_NOTE	= 7;		/* Information that marks file */
	    static const boost::uint8_t SHT_NOBITS	= 8;		/* Section occupies no space in file */
	    static const boost::uint8_t SHT_REL	= 9;		/* Relocation entries, no addends */
	    static const boost::uint8_t SHT_SHLIB	= 10;		/* Reserved, unspecified semantics */
	    static const boost::uint8_t SHT_DYNSYM	= 11;		/* Dynamic linking symbol table */

	    static const boost::uint8_t SHT_INIT_ARRAY    = 14;	/* Array of ptrs to init functions */
	    static const boost::uint8_t SHT_FINI_ARRAY    = 15;	/* Array of ptrs to finish functions */
	    static const boost::uint8_t SHT_PREINIT_ARRAY = 16;	/* Array of ptrs to pre-init funcs */
	    static const boost::uint8_t SHT_GROUP	    = 17;	/* Section contains a section group */
	    static const boost::uint8_t SHT_SYMTAB_SHNDX  = 18;	/* Indicies for SHN_XINDEX entries */

	    static const boost::uint32_t SHT_LOOS	= 0x60000000;	/* First of OS specific semantics */
	    static const boost::uint32_t SHT_HIOS	= 0x6fffffff;	/* Last of OS specific semantics */

	    static const boost::uint32_t SHT_GNU_LIBLIST	= 0x6ffffff7;	/* List of prelink dependencies */

	    /* The next three section types are defined by Solaris, and are named
	       SHT_SUNW*.  We use them in GNU code, so we also define SHT_GNU*
	       versions.  */
	    static const boost::uint32_t SHT_SUNW_verdef  = 0x6ffffffd;	/* Versions defined by file */
	    static const boost::uint32_t SHT_SUNW_verneed = 0x6ffffffe;	/* Versions needed by file */
	    static const boost::uint32_t SHT_SUNW_versym  = 0x6fffffff;	/* Symbol versions */

	    static const boost::uint32_t SHT_GNU_verdef    = SHT_SUNW_verdef;
	    static const boost::uint32_t SHT_GNU_verneed   = SHT_SUNW_verneed;
	    static const boost::uint32_t SHT_GNU_versym    = SHT_SUNW_versym;

	    static const boost::uint32_t SHT_LOPROC =	0x70000000;	/* Processor-specific semantics, lo */
	    static const boost::uint32_t SHT_HIPROC =	0x7FFFFFFF;	/* Processor-specific semantics, hi */
	    static const boost::uint32_t SHT_LOUSER =	0x80000000;	/* Application-specific semantics */
	    /* #define SHT_HIUSER	0x8FFFFFFF    *//* Application-specific semantics */
	    static const boost::uint32_t SHT_HIUSER =	0xFFFFFFFF;	/* New value, defined in Oct 4, 1999 Draft */

	    /* Values for section header, sh_flags field.  */

	    static const boost::uint64_t SHF_WRITE	         = 3;   // (1 << 0) Writable data during execution */
	    static const boost::uint64_t SHF_ALLOC	         = 2;   // (1 << 1) Occupies memory during execution */
	    static const boost::uint64_t SHF_EXECINSTR	         = 4;   // (1 << 2) Executable machine instructions */
	    static const boost::uint64_t SHF_MERGE	         = 8;   // (1 << 4) Data in this section can be merged */
	    static const boost::uint64_t SHF_STRINGS	         = 16;  // (1 << 5) Contains null terminated character strings */
	    static const boost::uint64_t SHF_INFO_LINK	         = 32;  // (1 << 6) sh_info holds section header table index */
	    static const boost::uint64_t SHF_LINK_ORDER          = 64;  // (1 << 7) Preserve section ordering when linking */
	    static const boost::uint64_t SHF_OS_NONCONFORMING    = 128; // (1 << 8) OS specific processing required */
	    static const boost::uint64_t SHF_GROUP	         = 256; // (1 << 9) Member of a section group */
	    static const boost::uint64_t SHF_TLS	         = 512; // (1 << 10) Thread local storage section */

	    /* #define SHF_MASKOS	0x0F000000    *//* OS-specific semantics */
	    static const boost::uint32_t SHF_MASKOS	= 0x0FF00000;	/* New value, Oct 4, 1999 Draft */
	    static const boost::uint32_t SHF_MASKPROC	= 0xF0000000;	/* Processor-specific semantics */

	    /* Values of note segment descriptor types for core files.  */

	    static const boost::uint8_t NT_PRSTATUS	= 1;		/* Contains copy of prstatus struct */
	    static const boost::uint8_t NT_FPREGSET	= 2;		/* Contains copy of fpregset struct */
	    static const boost::uint8_t NT_PRPSINFO	= 3;		/* Contains copy of prpsinfo struct */
	    static const boost::uint8_t NT_TASKSTRUCT	= 4;		/* Contains copy of task struct */
	    static const boost::uint32_t NT_PRXFPREG	= 0x46e62b7f;	/* Contains a user_xfpregs_struct; */
	    /*   note name must be "LINUX".  */

	    /* Note segments for core files on dir-style procfs systems.  */

	    static const boost::uint8_t NT_PSTATUS	  = 10;		/* Has a struct pstatus */
	    static const boost::uint8_t NT_FPREGS	  = 12;		/* Has a struct fpregset */
	    static const boost::uint8_t NT_PSINFO	  = 13;		/* Has a struct psinfo */
	    static const boost::uint8_t NT_LWPSTATUS	  = 16;		/* Has a struct lwpstatus_t */
	    static const boost::uint8_t NT_LWPSINFO	  = 17;		/* Has a struct lwpsinfo_t */
	    static const boost::uint8_t NT_WIN32PSTATUS = 18;		/* Has a struct win32_pstatus */

	    /* Note segments for core files on NetBSD systems.  Note name
	       must start with "NetBSD-CORE".  */

	    static const boost::uint8_t NT_NETBSDCORE_PROCINFO  = 1;	/* Has a struct procinfo */
	    static const boost::uint8_t NT_NETBSDCORE_FIRSTMACH = 32;	/* start of machdep note types */


	    /* Values of note segment descriptor types for object files.  */

	    static const boost::uint8_t NT_VERSION	= 1;		/* Contains a version string.  */
	    static const boost::uint8_t NT_ARCH	= 2;		/* Contains an architecture string.  */

	    /* Values for GNU .note.ABI-tag notes.  Note name is "GNU".  */

	    static const boost::uint8_t NT_GNU_ABI_TAG	= 1;
	    static const boost::uint8_t GNU_ABI_TAG_LINUX	= 0;
	    static const boost::uint8_t GNU_ABI_TAG_HURD	= 1;
	    static const boost::uint8_t GNU_ABI_TAG_SOLARIS	= 2;

	    /* Values for NetBSD .note.netbsd.ident notes.  Note name is "NetBSD".  */

	    static const boost::uint8_t NT_NETBSD_IDENT = 1;

	    /* Values for FreeBSD .note.ABI-tag notes.  Note name is "FreeBSD".  */

	    static const boost::uint8_t NT_FREEBSD_ABI_TAG = 1;

	    /* The 64bit and 32bit versions of these macros are identical, but
	       the ELF spec defines them, so here they are.  */
	    /*
	      NOTE: These are not listed, with the exception of ELF32_ST_BIND in the
	      ELF Format file we have read. So for now since we are using templates
	      to capture whether we are a 32/64 bit symbol these should not be required.

	      #define ELF32_ST_BIND  ELF_ST_BIND
	      #define ELF32_ST_TYPE  ELF_ST_TYPE
	      #define ELF32_ST_INFO  ELF_ST_INFO
	      #define ELF64_ST_BIND  ELF_ST_BIND
	      #define ELF64_ST_TYPE  ELF_ST_TYPE
	      #define ELF64_ST_INFO  ELF_ST_INFO
	    */

	    /* This macro disassembles and assembles a symbol's visibility into
	       the st_other field.  The STV_ defines specificy the actual visibility.  */
	    /* #define ELF_ST_VISIBILITY(v)		((v) & 0x3) */

	    /* The remaining bits in the st_other field are not currently used.
	       They should be set to zero.  */

	    /*
	      So for now since we are using templates to capture whether we
	      are a 32/64 bit symbol. These should not be required.
	    */
	    // #define ELF32_ST_VISIBILITY  ELF_ST_VISIBILITY
	    // #define ELF64_ST_VISIBILITY  ELF_ST_VISIBILITY


	    static const boost::uint8_t STN_UNDEF	= 0;		/* Undefined symbol index */

	    static const boost::uint8_t STB_LOCAL	= 0;		/* Symbol not visible outside obj */
	    static const boost::uint8_t STB_GLOBAL	= 1;		/* Symbol visible outside obj */
	    static const boost::uint8_t STB_WEAK	= 2;		/* Like globals, lower precedence */
	    static const boost::uint8_t STB_LOOS	= 10;		/* OS-specific semantics */
	    static const boost::uint8_t STB_HIOS	= 12;		/* OS-specific semantics */
	    static const boost::uint8_t STB_LOPROC	= 13;		/* Application-specific semantics */
	    static const boost::uint8_t STB_HIPROC	= 15;		/* Application-specific semantics */

	    static const boost::uint8_t STT_NOTYPE	= 0;		/* Symbol type is unspecified */
	    static const boost::uint8_t STT_OBJECT	= 1;		/* Symbol is a data object */
	    static const boost::uint8_t STT_FUNC	= 2;		/* Symbol is a code object */
	    static const boost::uint8_t STT_SECTION	= 3;		/* Symbol associated with a section */
	    static const boost::uint8_t STT_FILE	= 4;		/* Symbol gives a file name */
	    static const boost::uint8_t STT_COMMON	= 5;		/* An uninitialised common block */
	    static const boost::uint8_t STT_TLS	= 6;		/* Thread local data object */
	    static const boost::uint8_t STT_LOOS	= 10;		/* OS-specific semantics */
	    static const boost::uint8_t STT_HIOS	= 12;		/* OS-specific semantics */
	    static const boost::uint8_t STT_LOPROC	= 13;		/* Application-specific semantics */
	    static const boost::uint8_t STT_HIPROC	= 15;		/* Application-specific semantics */

	    /* Special section indices, which may show up in st_shndx fields, among
	       other places.  */

	    static const boost::uint8_t SHN_UNDEF	  = 0;		      /* Undefined section reference */
	    static const boost::uint16_t SHN_LORESERVE  = 0xFF00;	      /* Begin range of reserved indices */
	    static const boost::uint16_t SHN_LOPROC	  = 0xFF00;	      /* Begin range of appl-specific */
	    static const boost::uint16_t SHN_HIPROC	  = 0xFF1F;	      /* End range of appl-specific */
	    static const boost::uint16_t SHN_LOOS	  = 0xFF20;	      /* OS specific semantics, lo */
	    static const boost::uint16_t SHN_HIOS	  = 0xFF3F;	      /* OS specific semantics, hi */
	    static const boost::uint16_t SHN_ABS	  = 0xFFF1;	      /* Associated symbol is absolute */
	    static const boost::uint16_t SHN_COMMON	  = 0xFFF2;	      /* Associated symbol is in common */
	    static const boost::uint16_t SHN_XINDEX	  = 0xFFFF;	      /* Section index is held elsewhere */
	    static const boost::uint16_t SHN_HIRESERVE  = 0xFFFF;	      /* End range of reserved indices */

	    /* The following static constants control how a symbol may be accessed once it has
	       become part of an executable or shared library.  */

	    static const boost::uint8_t STV_DEFAULT	= 0;		/* Visibility is specified by binding type */
	    static const boost::uint8_t STV_INTERNAL	= 1;		/* OS specific version of STV_HIDDEN */
	    static const boost::uint8_t STV_HIDDEN	= 2;		/* Can only be seen inside currect component */
	    static const boost::uint8_t STV_PROTECTED	= 3;		/* Treat as STB_LOCAL inside current component */

	    /* Relocation info handling macros.  */
	    /*
	      #define ELF32_R_SYM(i)		((i) >> 8)
	      #define ELF32_R_TYPE(i)		((i) & 0xff)
	      #define ELF32_R_INFO(s,t)	(((s) << 8) + ((t) & 0xff))
	      #define ELF64_R_SYM(i)		((i) >> 32)
	      #define ELF64_R_TYPE(i)		((i) & 0xffffffff)
	      #define ELF64_R_INFO(s,t)	(((bfd_vma) (s) << 32) + (bfd_vma) (t))
	    */

	    /* Dynamic section tags.  */

	    static const boost::uint8_t DT_NULL	      = 0;
	    static const boost::uint8_t DT_NEEDED	      = 1;
	    static const boost::uint8_t DT_PLTRELSZ	      = 2;
	    static const boost::uint8_t DT_PLTGOT	      = 3;
	    static const boost::uint8_t DT_HASH	      = 4;
	    static const boost::uint8_t DT_STRTAB	      = 5;
	    static const boost::uint8_t DT_SYMTAB	      = 6;
	    static const boost::uint8_t DT_RELA	      = 7;
	    static const boost::uint8_t DT_RELASZ	      = 8;
	    static const boost::uint8_t DT_RELAENT	      = 9;
	    static const boost::uint8_t DT_STRSZ	      = 10;
	    static const boost::uint8_t DT_SYMENT	      = 11;
	    static const boost::uint8_t DT_INIT	      = 12;
	    static const boost::uint8_t DT_FINI	      = 13;
	    static const boost::uint8_t DT_SONAME	      = 14;
	    static const boost::uint8_t DT_RPATH	      = 15;
	    static const boost::uint8_t DT_SYMBOLIC	      = 16;
	    static const boost::uint8_t DT_REL	              = 17;
	    static const boost::uint8_t DT_RELSZ	      = 18;
	    static const boost::uint8_t DT_RELENT	      = 19;
	    static const boost::uint8_t DT_PLTREL	      = 20;
	    static const boost::uint8_t DT_DEBUG	      = 21;
	    static const boost::uint8_t DT_TEXTREL	      = 22;
	    static const boost::uint8_t DT_JMPREL	      = 23;
	    static const boost::uint8_t DT_BIND_NOW	      = 24;
	    static const boost::uint8_t DT_INIT_ARRAY	      = 25;
	    static const boost::uint8_t DT_FINI_ARRAY	      = 26;
	    static const boost::uint8_t DT_INIT_ARRAYSZ      = 27;
	    static const boost::uint8_t DT_FINI_ARRAYSZ      = 28;
	    static const boost::uint8_t DT_RUNPATH	      = 29;
	    static const boost::uint8_t DT_FLAGS	      = 30;
	    static const boost::uint8_t DT_ENCODING	      = 31;
	    static const boost::uint8_t DT_PREINIT_ARRAY     = 32;
	    static const boost::uint8_t DT_PREINIT_ARRAYSZ   = 33;

	    /* Note, the Oct 4, 1999 draft of the ELF ABI changed the values
	       for DT_LOOS and DT_HIOS.  Some implementations however, use
	       values outside of the new range (see below).	 */
	    static const boost::uint32_t OLD_DT_LOOS	= 0x60000000;
	    static const boost::uint32_t DT_LOOS	= 0x6000000d;
	    static const boost::uint32_t DT_HIOS	= 0x6fff0000;
	    static const boost::uint32_t OLD_DT_HIOS	= 0x6fffffff;
	    static const boost::uint32_t DT_LOPROC	= 0x70000000;
	    static const boost::uint32_t DT_HIPROC	= 0x7fffffff;

	    /* The next four dynamic tags are used on Solaris.  We support them
	       everywhere.	Note these values lie outside of the (new) range for
	       OS specific values.	This is a deliberate special case and we
	       maintain it for backwards compatability.  */
	    static const boost::uint32_t DT_VALRNGLO	     = 0x6ffffd00;
	    static const boost::uint32_t DT_GNU_PRELINKED  = 0x6ffffdf5;
	    static const boost::uint32_t DT_GNU_CONFLICTSZ = 0x6ffffdf6;
	    static const boost::uint32_t DT_GNU_LIBLISTSZ  = 0x6ffffdf7;
	    static const boost::uint32_t DT_CHECKSUM	     = 0x6ffffdf8;
	    static const boost::uint32_t DT_PLTPADSZ	     = 0x6ffffdf9;
	    static const boost::uint32_t DT_MOVEENT	     = 0x6ffffdfa;
	    static const boost::uint32_t DT_MOVESZ	     = 0x6ffffdfb;
	    static const boost::uint32_t DT_FEATURE	     = 0x6ffffdfc;
	    static const boost::uint32_t DT_POSFLAG_1	     = 0x6ffffdfd;
	    static const boost::uint32_t DT_SYMINSZ	     = 0x6ffffdfe;
	    static const boost::uint32_t DT_SYMINENT	     = 0x6ffffdff;
	    static const boost::uint32_t DT_VALRNGHI	     = 0x6ffffdff;

	    static const boost::uint32_t DT_ADDRRNGLO	     = 0x6ffffe00;
	    static const boost::uint32_t DT_GNU_CONFLICT   = 0x6ffffef8;
	    static const boost::uint32_t DT_GNU_LIBLIST    = 0x6ffffef9;
	    static const boost::uint32_t DT_CONFIG	     = 0x6ffffefa;
	    static const boost::uint32_t DT_DEPAUDIT	     = 0x6ffffefb;
	    static const boost::uint32_t DT_AUDIT	     = 0x6ffffefc;
	    static const boost::uint32_t DT_PLTPAD	     = 0x6ffffefd;
	    static const boost::uint32_t DT_MOVETAB	     = 0x6ffffefe;
	    static const boost::uint32_t DT_SYMINFO	     = 0x6ffffeff;
	    static const boost::uint32_t DT_ADDRRNGHI	     = 0x6ffffeff;

	    static const boost::uint32_t DT_RELACOUNT	     = 0x6ffffff9;
	    static const boost::uint32_t DT_RELCOUNT	     = 0x6ffffffa;
	    static const boost::uint32_t DT_FLAGS_1	     = 0x6ffffffb;
	    static const boost::uint32_t DT_VERDEF	     = 0x6ffffffc;
	    static const boost::uint32_t DT_VERDEFNUM	     = 0x6ffffffd;
	    static const boost::uint32_t DT_VERNEED	     = 0x6ffffffe;
	    static const boost::uint32_t DT_VERNEEDNUM     = 0x6fffffff;

	    /* This tag is a GNU extension to the Solaris version scheme.  */
	    static const boost::uint32_t DT_VERSYM	= 0x6ffffff0;

	    /* These section tags are used on Solaris.  We support them
	       everywhere, and hope they do not conflict.  */

	    static const boost::uint32_t DT_AUXILIARY	= 0x7ffffffd;
	    static const boost::uint32_t DT_USED	= 0x7ffffffe;
	    static const boost::uint32_t DT_FILTER	= 0x7fffffff;


	    /* Values used in DT_FEATURE .dynamic entry.  */
	    static const boost::uint32_t DTF_1_PARINIT = 0x00000001;
	    /* From

	       http://docs.sun.com:80/ab2/coll.45.13/LLM/@Ab2PageView/21165?Ab2Lang=C&Ab2Enc=iso-8859-1

	       DTF_1_CONFEXP is the same as DTF_1_PARINIT. It is a typo. The value
	       defined here is the same as the one in <sys/link.h> on Solaris 8.  */
	    static const boost::uint32_t DTF_1_CONFEXP = 0x00000002;

	    /* Flag values used in the DT_POSFLAG_1 .dynamic entry.	 */
	    static const boost::uint32_t DF_P1_LAZYLOAD  = 0x00000001;
	    static const boost::uint32_t DF_P1_GROUPPERM = 0x00000002;

	    /* Flag value in in the DT_FLAGS_1 .dynamic entry.  */
	    static const boost::uint32_t DF_1_NOW	  = 0x00000001;
	    static const boost::uint32_t DF_1_GLOBAL	  = 0x00000002;
	    static const boost::uint32_t DF_1_GROUP	  = 0x00000004;
	    static const boost::uint32_t DF_1_NODELETE  = 0x00000008;
	    static const boost::uint32_t DF_1_LOADFLTR  = 0x00000010;
	    static const boost::uint32_t DF_1_INITFIRST = 0x00000020;
	    static const boost::uint32_t DF_1_NOOPEN	  = 0x00000040;
	    static const boost::uint32_t DF_1_ORIGIN	  = 0x00000080;
	    static const boost::uint32_t DF_1_DIRECT	  = 0x00000100;
	    static const boost::uint32_t DF_1_TRANS	  = 0x00000200;
	    static const boost::uint32_t DF_1_INTERPOSE = 0x00000400;
	    static const boost::uint32_t DF_1_NODEFLIB  = 0x00000800;
	    static const boost::uint32_t DF_1_NODUMP	  = 0x00001000;
	    static const boost::uint32_t DF_1_CONLFAT	  = 0x00002000;

	    /* Flag values for the DT_FLAGS entry.	*/
	    static const boost::uint32_t DF_ORIGIN	 = (1 << 0);
	    static const boost::uint32_t DF_SYMBOLIC	 = (1 << 1);
	    static const boost::uint32_t DF_TEXTREL	 = (1 << 2);
	    static const boost::uint32_t DF_BIND_NOW   = (1 << 3);
	    static const boost::uint32_t DF_STATIC_TLS = (1 << 4);

	    /* These static constants are used for the version number of a Elf32_Verdef
	       structure.  */
	    static const boost::uint8_t VER_DEF_NONE	  = 0;
	    static const boost::uint8_t VER_DEF_CURRENT = 1;

	    /* These static constants appear in the vd_flags field of a Elf32_Verdef
	       structure.  */
	    static const boost::uint8_t VER_FLG_BASE = 0x1;
	    static const boost::uint8_t VER_FLG_WEAK = 0x2;

	    /* These special static constants can be found in an Elf32_Versym field.  */

	    static const boost::uint8_t VER_NDX_LOCAL	 = 0;
	    static const boost::uint8_t VER_NDX_GLOBAL = 1;

	    /* These static constants are used for the version number of a Elf32_Verneed
	       structure.  */
	    static const boost::uint8_t VER_NEED_NONE	   = 0;
	    static const boost::uint8_t VER_NEED_CURRENT = 1;

	    /* This flag appears in a Versym structure.  It means that the symbol
	       is hidden, and is only visible with an explicit version number.
	       This is a GNU extension.  */

	    static const boost::uint16_t VERSYM_HIDDEN = 0x8000;

	    /* This is the mask for the rest of the Versym information.  */

	    static const boost::uint16_t VERSYM_VERSION = 0x7fff;

	    /* This is a special token which appears as part of a symbol name.  It
	       indictes that the rest of the name is actually the name of a
	       version node, and is not part of the actual name.  This is a GNU
	       extension.  For example, the symbol name `stat@ver2' is taken to
	       mean the symbol `stat' in version `ver2'.  */

	    static const boost::uint8_t ELF_VER_CHR =	'@';

	    /* Possible values for si_boundto.  */

	    static const boost::uint16_t SYMINFO_BT_SELF	 = 0xffff;	/* Symbol bound to self */
	    static const boost::uint16_t SYMINFO_BT_PARENT	 = 0xfffe;	/* Symbol bound to parent */
	    static const boost::uint16_t SYMINFO_BT_LOWRESERVE = 0xff00;	/* Beginning of reserved entries */

	    /* Possible bitmasks for si_flags.  */

	    static const boost::uint16_t SYMINFO_FLG_DIRECT	= 0x0001;	/* Direct bound symbol */
	    static const boost::uint16_t SYMINFO_FLG_PASSTHRU	= 0x0002;	/* Pass-thru symbol for translator */
	    static const boost::uint16_t SYMINFO_FLG_COPY	= 0x0004;	/* Symbol is a copy-reloc */
	    static const boost::uint16_t SYMINFO_FLG_LAZYLOAD	= 0x0008;	/* Symbol bound to object to be lazy loaded */

	    /* Syminfo version values.  */
	    static const boost::uint8_t SYMINFO_NONE		= 0;
	    static const boost::uint8_t SYMINFO_CURRENT	= 1;
	    static const boost::uint8_t SYMINFO_NUM		= 2;

	    /* Section Group Flags.	 */

	    static const boost::uint8_t GRP_COMDAT		= 0x1;	/* A COMDAT group */
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_COMMON_HPP_INCLUDED
