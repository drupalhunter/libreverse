/*  PE_Characteristics.h

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

#ifndef PE_CHARACTERISTICS_H_
#define PE_CHARACTERISTICS_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace wpef_module {

    class PE_Characteristics {
    public:

        /* MS_PE_COFF:

        0x0001: Image only, Windows CE, and Microsoft Windows NT® and
        later.  This indicates that the file does not contain base
        relocations and must therefore be loaded at its preferred base
        address. If the base address is not available, the loader reports
        an error. The default behavior of the linker is to strip base
        relocations from executable (EXE) files.

        */
        static const boost::uint16_t PE_IMAGE_FILE_RELOCS_STRIPPED;

        /* MS_PE_COFF:

        0x0002: Image only. This indicates that the image file is valid
        and can be run.  If this flag is not set, it indicates a
        linker error.

        */
        static const boost::uint16_t PE_IMAGE_FILE_EXECUTABLE_IMAGE;

        /* MS_PE_COFF:

        0x0004: COFF line numbers have been removed. This flag is
        deprecated and should be zero.

        */
        static const boost::uint16_t PE_IMAGE_FILE_LINE_NUMS_STRIPPED;

        /* MS_PE_COFF:

        0x0008: COFF symbol table entries for local symbols have been
        removed. This flag is deprecated and should be zero.

        */
        static const boost::uint16_t PE_IMAGE_FILE_LOCAL_SYMS_STRIPPED;

        /* MS_PE_COFF:

        0x0010: Obsolete. Aggressively trim working set. This flag is
        deprecated for Windows 2000 and later and must be zero.

        */
        static const boost::uint16_t PE_IMAGE_FILE_AGGRESSIVE_WS_TRIM;

        /* MS_PE_COFF:

        0x0020: Application can handle > 2-GB addresses.

        */
        static const boost::uint16_t PE_IMAGE_FILE_LARGE_ADDRESS_AWARE;


        /* MS_PE_COFF:

        0x0040: This flag is reserved for future use.

        */
        static const boost::uint16_t PE_IMAGE_FILE_RESERVED_BIT;

        /* MS_PE_COFF:

        0x0080: Little endian: the least significant bit (LSB)
        precedes the most significant bit (MSB) in memory. This flag
        is deprecated and should be zero.

        */
        static const boost::uint16_t PE_IMAGE_FILE_BYTES_REVERSED_LO;

        /* MS_PE_COFF:

        0x0100: Machine is based on a 32-bit word architecture.

        */
        static const boost::uint16_t PE_IMAGE_FILE_32BIT_MACHINE;


        /* MS_PE_COFF:

        0x0200: Debugging information is removed from the image file.

        */
        static const boost::uint16_t PE_IMAGE_FILE_DEBUG_STRIPPED;

        /* MS_PE_COFF:

        0x0400: If the image is on removable media, fully load it and
        copy it to the swap file.

        */
        static const boost::uint16_t PE_IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP;

        /* MS_PE_COFF:

        0x0800: If the image is on network media, fully load it and
        copy it to the swap file.

        */
        static const boost::uint16_t PE_IMAGE_FILE_NET_RUN_FROM_SWAP;

        /* MS_PE_COFF:

        0x1000: The image file is a system file, not a user program.

        */
        static const boost::uint16_t PE_IMAGE_FILE_SYSTEM;

        /* MS_PE_COFF:

        0x2000: The image file is a dynamic-link library (DLL). Such
        files are considered executable files for almost all purposes,
        although they cannot be directly run.

        */
        static const boost::uint16_t PE_IMAGE_FILE_DLL;

        /* MS_PE_COFF:

        0x4000: The file should be run only on a uniprocessor machine.

        */
        static const boost::uint16_t PE_IMAGE_FILE_UP_SYSTEM_ONLY;

        /* MS_PE_COFF:

        0x8000: Big endian: the MSB precedes the LSB in memory. This
        flag is deprecated and should be zero.

        */
        static const boost::uint16_t PE_IMAGE_FILE_BYTES_REVERSED_HI;

        static std::string
        get_String_Name ( boost::uint16_t val );

        static std::string
        get_String_Name_List ( boost::uint16_t val );

        static bool
        has_Initialized_Data ( boost::uint16_t val );
    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_CHARACTERISTICS_H_ */

