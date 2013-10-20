/*  Elf_m68hc11.h

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
  m68hc11 & m68hc12 ELF support for BFD.
  Copyright 1999, 2000, 2001, 2002 Free Software Foundation, Inc.

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_M68HC11_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_M68HC11_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_m68hc11 {
	  public:

	    static inline std::string get_type (boost::uint32_t type);

	    /* Processor specific flags for the ELF header e_flags field.  */

	    /* ABI identification.  */
	    static const boost::uint32_t EF_M68HC11_ABI = 0x00000000F;

	    /* Integers are 32-bit long. */
	    static const boost::uint32_t E_M68HC11_I32 = 0x000000001;

	    /* Doubles are 64-bit long.  */
	    static const boost::uint32_t E_M68HC11_F64 = 0x000000002;

	    /* Uses 68HC12 memory banks.  */
	    static const boost::uint32_t E_M68HC12_BANKS = 0x000000004;

	    static const boost::uint8_t EF_M68HC11_MACH_MASK = 0xF0;

	    /* Generic 68HC12/backward compatibility.  */
	    static const boost::uint8_t EF_M68HC11_GENERIC = 0x00;

	    /* 68HC12 microcontroller.  */
	    static const boost::uint8_t EF_M68HC12_MACH = 0x10;

	    /* 68HCS12 microcontroller.  */
	    static const boost::uint8_t EF_M68HCS12_MACH = 0x20;

	    static inline const boost::uint8_t EF_M68HC11_MACH ( boost::uint8_t mach );

	    /* True if we can merge machines.  A generic HC12 can work on any proc
	       but once we have specific code, merge is not possible.  */
	    static inline const bool EF_M68HC11_CAN_MERGE_MACH ( boost::uint8_t mach1,
								 boost::uint8_t mach2 );

	    /*
	      #define EF_M68HC11_MERGE_MACH(mach1, mach2) \
	      (((EF_M68HC11_MACH (mach1) == EF_M68HC11_MACH (mach2)) \
	      || (EF_M68HC11_MACH (mach1) == EF_M68HC11_GENERIC)) ? \
	      EF_M68HC11_MACH (mach2) : EF_M68HC11_MACH (mach1))
	    */


	    /* Special values for the st_other field in the symbol table.
	       These are used for 68HC12 to identify far functions (must be
	       called with 'call' and returns with 'rtc').  */
	    static const boost::uint8_t STO_M68HC12_FAR = 0x80;

	    /*
	      Identify interrupt handlers.  This is used by the debugger to
	      correctly compute the stack frame.
	    */
	    static const boost::uint8_t STO_M68HC12_INTERRUPT = 0x40;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_m68hc11.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_M68HC11_HPP_INCLUDED
