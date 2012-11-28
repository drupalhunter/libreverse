/*  PE_Machine_Types.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_MACHINE_TYPES_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_MACHINE_TYPES_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header are taken from the
  Microsoft Portable Executable and // Common Object File Format -
  Revision 8, May 16, 2006.
*/

#include <string>
#include <boost/cstdint.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  class pe_machine_types {
	  public:

	    enum values {

	      // 0x0: the contents of this field are assumed to be applicable to
	      // any machine type.
	      image_file_machine_unknown = 0x0,

	      // 0x1d3: matsushita am33
	      image_file_machine_am33 = 0x1d3,

	      // 0x8664: x64
	      image_file_machine_amd64 = 0x8664,
            
	      // 0xebc: efi byte code
	      image_file_machine_ebc = 0xebc,

	      // 0x14c: intel 386 or later processors and compatible processors.
	      image_file_machine_i386 = 0x14c,

	      // 0x200: intel itanium processor family
	      image_file_machine_ia64 = 0x200,

	      // 0x9041: mitsubishi m32r little endian
	      image_file_machine_m32r = 0x9041,

	      // 0x266: mips16
	      image_file_machine_mips16 = 0x266,

	      // 0x366: mips with fpu
	      image_file_machine_mipsfpu = 0x366,

	      // 0x466: mips16 with fpu
	      image_file_machine_mipsfpu16 = 0x466,

	      // 0x1f0: power pc little endian
	      image_file_machine_powerpc = 0x1f0,

	      // 0x1f1: power pc with floating point support
	      image_file_machine_powerpcfp = 0x1f1,

	      // 0x166: mips little endian
	      image_file_machine_r4000 = 0x166,

	      // 0x1a2: hitachi sh3
	      image_file_machine_sh3 = 0x1a2,

	      // 0x1a3: hitachi sh3 dsp
	      image_file_machine_sh3dsp = 0x1a3,

	      // 0x1a6: hitachi sh4
	      image_file_machine_sh4 = 0x1a6,

	      // 0x1a8: hitachi sh5
	      image_file_machine_sh5 = 0x1a8,

	      // 0x1c2: thumb
	      image_file_machine_thumb = 0x1c2,

	      // 0x169: mips little-endian wce v2 sv2
	      image_file_machine_wcemip = 0x169
	    };

	    static std::string get_string_name ( boost::uint16_t val );

	    static bool is_valid_value ( boost::uint16_t val );
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_MACHINE_TYPES_HPP_INCLUDED
