/*  Elf_msp430.h

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
  MSP430 ELF support for BFD.
  Copyright (C) 2002 Free Software Foundation, Inc.
  Contributed by Dmitry Diky <diwil@mail.ru>

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_MSP430_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_MSP430_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_msp430 {
	  public:

	    /* Processor specific flags for the ELF header e_flags field.  */
	    static const boost::uint8_t EF_MSP430_MACH = 0xff;

	    static const boost::uint8_t E_MSP430_MACH_MSP430x11x1 = 110;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x11 = 11;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x12 = 12;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x13 = 13;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x14 = 14;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x31 = 31;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x32 = 32;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x33 = 33;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x41 = 41;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x43 = 43;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x44 = 44;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x15 = 15;
	    static const boost::uint8_t E_MSP430_MACH_MSP430x16 = 16;

	    static inline std::string get_type (boost::uint32_t type);

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse


#include "elf_msp430.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_MSP430_HPP_INCLUDED
