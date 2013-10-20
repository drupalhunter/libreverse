/*  Elf_h8.h

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
  H8300/h8500 ELF support for BFD.
  Copyright 2001, 2003 Free Software Foundation, Inc.

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_H8_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_H8_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_h8 {
	  public:

	    static inline std::string get_type ( boost::uint32_t type );

	    /* Machine variant if we know it.  This field was invented at
	       Cygnus, but it is hoped that other vendors will adopt it.  If
	       some standard is developed, this code should be changed to
	       follow it. */

	    static const boost::uint32_t EF_H8_MACH = 0x00FF0000;
	    static const boost::uint32_t E_H8_MACH_H8300 = 0x00800000;
	    static const boost::uint32_t E_H8_MACH_H8300H = 0x00810000;
	    static const boost::uint32_t E_H8_MACH_H8300S = 0x00820000;
	    static const boost::uint32_t E_H8_MACH_H8300HN = 0x00830000;
	    static const boost::uint32_t E_H8_MACH_H8300SN = 0x00840000;
	  };


	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse


#include "elf_h8.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_H8_HPP_INCLUDED
