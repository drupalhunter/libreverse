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

#ifndef PE_MACHINE_TYPES_H
#define PE_MACHINE_TYPES_H

/*
  All comments and hexidecimal values in this header are taken from the
  Microsoft Portable Executable and // Common Object File Format -
  Revision 8, May 16, 2006.
*/

#include <string>
#include <boost/cstdint.hpp>

namespace libreverse { namespace wpef_module {

    class PE_Machine_Types {
    public:

        enum Values {

            // 0x0: The contents of this field are assumed to be applicable to
            // any machine type.
            IMAGE_FILE_MACHINE_UNKNOWN = 0x0,

            // 0x1D3: Matsushita AM33
            IMAGE_FILE_MACHINE_AM33 = 0x1D3,

            // 0x8664: x64
            IMAGE_FILE_MACHINE_AMD64 = 0x8664,
            
            // 0xebc: EFI byte code
            IMAGE_FILE_MACHINE_EBC = 0xEBC,

            // 0x14c: Intel 386 or later processors and compatible processors.
            IMAGE_FILE_MACHINE_I386 = 0x14C,

            // 0x200: Intel Itanium processor family
            IMAGE_FILE_MACHINE_IA64 = 0x200,

            // 0x9041: Mitsubishi M32R little endian
            IMAGE_FILE_MACHINE_M32R = 0x9041,

            // 0x266: MIPS16
            IMAGE_FILE_MACHINE_MIPS16 = 0x266,

            // 0x366: MIPS with FPU
            IMAGE_FILE_MACHINE_MIPSFPU = 0x366,

            // 0x466: MIPS16 with FPU
            IMAGE_FILE_MACHINE_MIPSFPU16 = 0x466,

            // 0x1f0: Power PC little endian
            IMAGE_FILE_MACHINE_POWERPC = 0x1F0,

            // 0x1f1: Power PC with floating point support
            IMAGE_FILE_MACHINE_POWERPCFP = 0x1F1,

            // 0x166: MIPS little endian
            IMAGE_FILE_MACHINE_R4000 = 0x166,

            // 0x1a2: Hitachi SH3
            IMAGE_FILE_MACHINE_SH3 = 0x1A2,

            // 0x1a3: Hitachi SH3 DSP
            IMAGE_FILE_MACHINE_SH3DSP = 0x1A3,

            // 0x1a6: Hitachi SH4
            IMAGE_FILE_MACHINE_SH4 = 0x1A6,

            // 0x1a8: Hitachi SH5
            IMAGE_FILE_MACHINE_SH5 = 0x1A8,

            // 0x1c2: Thumb
            IMAGE_FILE_MACHINE_THUMB = 0x1C2,

            // 0x169: MIPS little-endian WCE v2 SV2
            IMAGE_FILE_MACHINE_WCEMIP = 0x169
        };

        static std::string get_String_Name ( boost::uint16_t val );

        static bool is_Valid_Value ( boost::uint16_t val );
    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_MACHINE_TYPES_H */
