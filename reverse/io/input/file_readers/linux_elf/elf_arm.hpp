/*  Elf_arm.h

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
  ARM ELF support for BFD.
  Copyright 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.

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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_ARM_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_ARM_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_arm {
	  public:

	    /* Processor specific flags for the ELF header e_flags field.  */
	    static const boost::uint8_t EF_ARM_RELEXEC     = 0x01;
	    static const boost::uint8_t EF_ARM_HASENTRY    = 0x02;
	    static const boost::uint8_t EF_ARM_INTERWORK   = 0x04;
	    static const boost::uint8_t EF_ARM_APCS_26     = 0x08;
	    static const boost::uint8_t EF_ARM_APCS_FLOAT  = 0x10;
	    static const boost::uint8_t EF_ARM_PIC         = 0x20;
	    static const boost::uint8_t EF_ARM_ALIGN8	    = 0x40;
	    /* 8-bit structure alignment is in use.  */
	    static const boost::uint8_t EF_ARM_NEW_ABI     = 0x80;

	    static const boost::uint16_t EF_ARM_OLD_ABI        = 0x100;
	    static const boost::uint16_t EF_ARM_SOFT_FLOAT     = 0x200;
	    static const boost::uint16_t EF_ARM_VFP_FLOAT      = 0x400;
	    static const boost::uint16_t EF_ARM_MAVERICK_FLOAT = 0x800;

	    /* Other constants defined in the ARM ELF spec. version B-01.  */

	    /* NB conflicts with EF_INTERWORK */
	    static const boost::uint8_t EF_ARM_SYMSARESORTED = 0x04;

	    /* NB conflicts with EF_APCS26 */
	    static const boost::uint8_t EF_ARM_DYNSYMSUSESEGIDX = 0x08;

	    /* NB conflicts with EF_APCS_FLOAT */
	    static const boost::uint8_t EF_ARM_MAPSYMSFIRST = 0x10;

	    static const boost::uint32_t EF_ARM_EABIMASK      = 0xFF000000;
	    static const boost::uint32_t EF_ARM_EABI_UNKNOWN  = 0x00000000;
	    static const boost::uint32_t EF_ARM_EABI_VER1     = 0x01000000;
	    static const boost::uint32_t EF_ARM_EABI_VER2     = 0x02000000;

	    static inline const boost::uint32_t EF_ARM_EABI_VERSION (boost::uint32_t flags);

	    /* Local aliases for some flags to match names used by COFF port.  */
	    static const boost::uint8_t F_INTERWORK  = EF_ARM_INTERWORK;
	    static const boost::uint8_t F_APCS26     =	EF_ARM_APCS_26;
	    static const boost::uint8_t F_APCS_FLOAT = EF_ARM_APCS_FLOAT;
	    static const boost::uint8_t F_PIC        = EF_ARM_PIC;
	    static const boost::uint16_t F_SOFT_FLOAT = EF_ARM_SOFT_FLOAT;
	    static const boost::uint16_t F_VFP_FLOAT  = EF_ARM_VFP_FLOAT;

	    /* Additional symbol types for Thumb.  */
	    /* A Thumb function.  */
	    static const boost::uint8_t STT_ARM_TFUNC = elf_common::STT_LOPROC;

	    /* A Thumb label.  */
	    static const boost::uint8_t STT_ARM_16BIT  = elf_common::STT_HIPROC;

	    /* ARM-specific values for sh_flags.  */

	    /* Section contains an entry point.  */
	    static const boost::uint32_t SHF_ENTRYSECT  = 0x10000000;

	    /* Section may be multiply defined in the input to a link step.  */
	    static const boost::uint32_t SHF_COMDEF     = 0x80000000;


	    /* ARM-specific program header flags.  */

	    /* Segment contains the location addressed by the static base.  */
	    static const boost::uint32_t PF_ARM_SB      = 0x10000000;

	    /* Segment is position-independent.  */
	    static const boost::uint32_t PF_ARM_PI      = 0x20000000;

	    /* Segment must be loaded at its base address.  */
	    static const boost::uint32_t PF_ARM_ABS     = 0x40000000;

	    /* Relocation types.  */
	    static inline std::string get_type ( boost::uint32_t type );

	    /* The name of the note section used to identify arm variants.  */
	    static const char* ARM_NOTE_SECTION;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_arm.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_ARM_HPP_INCLUDED
