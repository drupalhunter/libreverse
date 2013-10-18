/*  Elf_sparc.h

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

/* SPARC ELF support for BFD.
   Copyright 1996, 1997, 1998, 1999, 2000, 2002 Free Software Foundation, Inc.
   By Doug Evans, Cygnus Support, <dje@cygnus.com>.

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SPARC_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SPARC_HPP_INCLUDED

/* Processor specific flags for the ELF header e_flags field.  */

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_sparc {
	  public:

	    /* These are defined by Sun.  */
	    static const boost::uint32_t EF_SPARC_32PLUS_MASK	= 0xffff00;	/* bits indicating V8+ type */
	    static const boost::uint32_t EF_SPARC_32PLUS	= 0x000100;	/* generic V8+ features */
	    static const boost::uint32_t EF_SPARC_SUN_US1	= 0x000200;	/* Sun UltraSPARC1 extensions */
	    static const boost::uint32_t EF_SPARC_HAL_R1	= 0x000400;	/* HAL R1 extensions */
	    static const boost::uint32_t EF_SPARC_SUN_US3	= 0x000800;	/* Sun UltraSPARCIII extensions */

	    static const boost::uint32_t EF_SPARC_LEDATA       = 0x800000;	/* little endian data */

	    /* This name is used in the V9 ABI.  */
	    static const boost::uint32_t EF_SPARC_EXT_MASK	= 0xffff00;	/* reserved for vendor extensions */

	    /* V9 memory models */
	    static const boost::uint8_t EF_SPARCV9_MM		= 0x3;		/* memory model mask */
	    static const boost::uint8_t EF_SPARCV9_TSO		= 0x0;		/* total store ordering */
	    static const boost::uint8_t EF_SPARCV9_PSO		= 0x1;		/* partial store ordering */
	    static const boost::uint8_t EF_SPARCV9_RMO		= 0x2;		/* relaxed store ordering */

	    /* Section indices.  */
	    static const boost::uint16_t SHN_BEFORE		= 0xff00;		/* used with SHF_ORDERED */
	    static const boost::uint16_t SHN_AFTER		= 0xff01;		/* used with SHF_ORDERED */

	    /* Section flags.  */
	    // ERROR: g++ says this declaration does not declare anything
	    //static const boost::uint32_t SHF_EXCLUDE	   = 0x80000000;	/* exclude from linking */
	    static const boost::uint32_t SHF_ORDERED	   = 0x40000000;	/* treat sh_link,sh_info specially */

	    /* Symbol types.  */

	    static const boost::uint8_t STT_REGISTER	   = 13;		/* global reg reserved to app. */

	    static const boost::uint8_t R_SPARC_NONE      =  0;
	    static const boost::uint8_t R_SPARC_8         =  1;
	    static const boost::uint8_t R_SPARC_16        =  2;
	    static const boost::uint8_t R_SPARC_32        =  3;
	    static const boost::uint8_t R_SPARC_DISP8     =  4;
	    static const boost::uint8_t R_SPARC_DISP16    =  5;
	    static const boost::uint8_t R_SPARC_DISP32    =  6;
	    static const boost::uint8_t R_SPARC_WDISP30   =  7;
	    static const boost::uint8_t R_SPARC_WDISP22   =  8;
	    static const boost::uint8_t R_SPARC_HI22      =  9;
	    static const boost::uint8_t R_SPARC_22        =  10;
	    static const boost::uint8_t R_SPARC_13        =  11;
	    static const boost::uint8_t R_SPARC_LO10      =  12;
	    static const boost::uint8_t R_SPARC_GOT10     =  13;
	    static const boost::uint8_t R_SPARC_GOT13     =  14;
	    static const boost::uint8_t R_SPARC_GOT22     =  15;
	    static const boost::uint8_t R_SPARC_PC10      =  16;
	    static const boost::uint8_t R_SPARC_PC22      =  17;
	    static const boost::uint8_t R_SPARC_WPLT30    =  18;
	    static const boost::uint8_t R_SPARC_COPY      =  19;
	    static const boost::uint8_t R_SPARC_GLOB_DAT  =  20;
	    static const boost::uint8_t R_SPARC_JMP_SLOT  =  21;
	    static const boost::uint8_t R_SPARC_RELATIVE  =  22;
	    static const boost::uint8_t R_SPARC_UA32      =  23;

	    /* ??? These 6 relocs are new but not currently used.  For binary
	       compatibility in the sparc64-elf toolchain      =  we leave them out.
	       A non-binary upward compatible change is expected for sparc64-elf.  */
#ifndef SPARC64_OLD_RELOCS
	    /* ??? New relocs on the UltraSPARC.  Not sure what they're for yet.  */
	    static const boost::uint8_t R_SPARC_PLT32      =  24;
	    static const boost::uint8_t R_SPARC_HIPLT22    =  25;
	    static const boost::uint8_t R_SPARC_LOPLT10    =  26;
	    static const boost::uint8_t R_SPARC_PCPLT32    =  27;
	    static const boost::uint8_t R_SPARC_PCPLT22    =  28;
	    static const boost::uint8_t R_SPARC_PCPLT10    =  29;
#endif

	    /* v9 relocs */
	    static const boost::uint8_t R_SPARC_10         =  30;
	    static const boost::uint8_t R_SPARC_11         =  31;
	    static const boost::uint8_t R_SPARC_64         =  32;
	    static const boost::uint8_t R_SPARC_OLO10      =  33;
	    static const boost::uint8_t R_SPARC_HH22       =  34;
	    static const boost::uint8_t R_SPARC_HM10       =  35;
	    static const boost::uint8_t R_SPARC_LM22       =  36;
	    static const boost::uint8_t R_SPARC_PC_HH22    =  37;
	    static const boost::uint8_t R_SPARC_PC_HM10    =  38;
	    static const boost::uint8_t R_SPARC_PC_LM22    =  39;
	    static const boost::uint8_t R_SPARC_WDISP16    =  40;
	    static const boost::uint8_t R_SPARC_WDISP19    =  41;
	    static const boost::uint8_t R_SPARC_UNUSED_42  =  42;
	    static const boost::uint8_t R_SPARC_7          =  43;
	    static const boost::uint8_t R_SPARC_5          =  44;
	    static const boost::uint8_t R_SPARC_6          =  45;
	    static const boost::uint8_t R_SPARC_DISP64     =  46;
	    static const boost::uint8_t R_SPARC_PLT64      =  47;
	    static const boost::uint8_t R_SPARC_HIX22      =  48;
	    static const boost::uint8_t R_SPARC_LOX10      =  49;
	    static const boost::uint8_t R_SPARC_H44        =  50;
	    static const boost::uint8_t R_SPARC_M44        =  51;
	    static const boost::uint8_t R_SPARC_L44        =  52;
	    static const boost::uint8_t R_SPARC_REGISTER   =  53;
	    static const boost::uint8_t R_SPARC_UA64       =  54;
	    static const boost::uint8_t R_SPARC_UA16       =  55;

	    static const boost::uint8_t R_SPARC_TLS_GD_HI22   =  56;
	    static const boost::uint8_t R_SPARC_TLS_GD_LO10   =  57;
	    static const boost::uint8_t R_SPARC_TLS_GD_ADD    =  58;
	    static const boost::uint8_t R_SPARC_TLS_GD_CALL   =  59;
	    static const boost::uint8_t R_SPARC_TLS_LDM_HI22  =  60;
	    static const boost::uint8_t R_SPARC_TLS_LDM_LO10  =  61;
	    static const boost::uint8_t R_SPARC_TLS_LDM_ADD   =  62;
	    static const boost::uint8_t R_SPARC_TLS_LDM_CALL  =  63;
	    static const boost::uint8_t R_SPARC_TLS_LDO_HIX22 =  64;
	    static const boost::uint8_t R_SPARC_TLS_LDO_LOX10 =  65;
	    static const boost::uint8_t R_SPARC_TLS_LDO_ADD   =  66;
	    static const boost::uint8_t R_SPARC_TLS_IE_HI22   =  67;
	    static const boost::uint8_t R_SPARC_TLS_IE_LO10   =  68;
	    static const boost::uint8_t R_SPARC_TLS_IE_LD     =  69;
	    static const boost::uint8_t R_SPARC_TLS_IE_LDX    =  70;
	    static const boost::uint8_t R_SPARC_TLS_IE_ADD    =  71;
	    static const boost::uint8_t R_SPARC_TLS_LE_HIX22  =  72;
	    static const boost::uint8_t R_SPARC_TLS_LE_LOX10  =  73;
	    static const boost::uint8_t R_SPARC_TLS_DTPMOD32  =  74;
	    static const boost::uint8_t R_SPARC_TLS_DTPMOD64  =  75;
	    static const boost::uint8_t R_SPARC_TLS_DTPOFF32  =  76;
	    static const boost::uint8_t R_SPARC_TLS_DTPOFF64  =  77;
	    static const boost::uint8_t R_SPARC_TLS_TPOFF32   =  78;
	    static const boost::uint8_t R_SPARC_TLS_TPOFF64   =  79;

	    static const boost::uint8_t R_SPARC_GNU_VTINHERIT =  250;
	    static const boost::uint8_t R_SPARC_GNU_VTENTRY   =  251;
	    static const boost::uint8_t R_SPARC_REV32         =  252;


	    /* Relocation macros.  */
	    static inline std::string get_Type (boost::uint32_t type);

	    /* NOTE: Need to figure what were are going to do with these

	       #define ELF64_R_TYPE_DATA(info) \
	       (((bfd_signed_vma)(ELF64_R_TYPE(info) >> 8) ^ 0x800000) - 0x800000)
	       #define ELF64_R_TYPE_ID(info) \
	       ((info) & 0xff)
	       #define ELF64_R_TYPE_INFO(data, type) \
	       (((bfd_vma) ((data) & 0xffffff) << 8) | (bfd_vma) (type))
	    */

	    /* Values for Elf64_Dyn.d_tag.  */

	    static const boost::uint64_t DT_SPARC_REGISTER = 0x70000001;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_sparc.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SPARC_HPP_INCLUDED
