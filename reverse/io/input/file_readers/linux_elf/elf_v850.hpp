/*  Elf_v850.h

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
  V850 ELF support for BFD.
  Copyright 1997, 1998, 2000, 2002 Free Software Foundation, Inc.
  Created by Michael Meissner, Cygnus Support <meissner@cygnus.com>

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

/* This file holds definitions specific to the MIPS ELF ABI.  Note
   that most of this is not actually implemented by BFD.  */

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_V850_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_V850_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_v850 {
	  public:

	    /* Processor specific flags for the ELF header e_flags field.  */

	    /* Four bit V850 architecture field.  */
	    static const boost::uint32_t EF_V850_ARCH = 0xf0000000;

	    /* v850 code.  */
	    static const boost::uint32_t E_V850_ARCH = 0x00000000;

	    /* v850e code.  */
	    static const boost::uint32_t E_V850E_ARCH = 0x10000000;

	    /* Flags for the st_other field.  */

	    /* Symbol had SDA relocations.  */
	    static const boost::uint8_t V850_OTHER_SDA = 0x01;

	    /* Symbol had ZDA relocations.  */
	    static const boost::uint8_t V850_OTHER_ZDA	= 0x02;

	    /* Symbol had TDA relocations.  */
	    static const boost::uint8_t V850_OTHER_TDA = 0x04;

	    /* Symbol had TDA byte relocations.  */
	    static const boost::uint8_t V850_OTHER_TDA_BYTE = 0x08;

	    /* Symbol had an error reported.  */
	    static const boost::uint8_t V850_OTHER_ERROR = 0x80;

	    /* V850 relocations.  */
	    static inline std::string get_type ( boost::uint32_t type );


	    /* Processor specific section indices.  These sections do not
	       actually exist.  Symbols with a st_shndx field corresponding to
	       one of these values have a special meaning.  */

	    /* Small data area common symbol.  */
	    static const boost::uint16_t SHN_V850_SCOMMON	 = 0xff00;

	    /* Tiny data area common symbol.  */
	    static const boost::uint16_t SHN_V850_TCOMMON	 = 0xff01;

	    /* Zero data area common symbol.  */
	    static const boost::uint16_t SHN_V850_ZCOMMON	 = 0xff02;

	    /* Processor specific section types.  */
	    /* Section contains the .scommon data.  */
	    static const boost::uint32_t SHT_V850_SCOMMON = 0x70000000;

	    /* Section contains the .scommon data.  */
	    static const boost::uint32_t SHT_V850_TCOMMON = 0x70000001;

	    /* Section contains the .scommon data.  */
	    static const boost::uint32_t SHT_V850_ZCOMMON = 0x70000002;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_v850.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_V850_HPP_INCLUDED
