/*  PE_Subsystem.h

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

#ifndef PE_SUBSYSTEM_H
#define PE_SUBSYSTEM_H

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/cstdint.hpp>
#include <string>

namespace reverse { namespace wpef_module {

    class PE_Subsystem {
    public:

        // MS_PE_COFF: 0 - An unknown subsystem
        static const boost::uint8_t IMAGE_SUBSYSTEM_UNKNOWN;

        // MS_PE_COFF: 1 - Device drivers and native Windows processes
        static const boost::uint8_t IMAGE_SUBSYSTEM_NATIVE;

        // MS_PE_COFF: 2 - The Windows graphical user interface (GUI) subsystem
        static const boost::uint8_t IMAGE_SUBSYSTEM_WINDOWS_GUI;

        // MS_PE_COFF: 3 - The Windows character subsystem
        static const boost::uint8_t IMAGE_SUBSYSTEM_WINDOWS_CUI;

        // MS_PE_COFF: 7 - The Posix character subsystem
        static const boost::uint8_t IMAGE_SUBSYSTEM_POSIX_CUI;

        // MS_PE_COFF: 9 - Windows CE
        static const boost::uint8_t IMAGE_SUBSYSTEM_WINDOWS_CE_GUI;

        // MS_PE_COFF: 10 - An Extensible Firmware Interface (EFI) application
        static const boost::uint8_t IMAGE_SUBSYSTEM_EFI_APPLICATION;

        // MS_PE_COFF: 11 - An EFI driver with boot services
        static const boost::uint8_t IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER;

        // MS_PE_COFF: 12 - An EFI driver with run-time services
        static const boost::uint8_t IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER;

        // MS_PE_COFF: 13 - An EFI ROM image
        static const boost::uint8_t IMAGE_SUBSYSTEM_EFI_ROM;

        // MS_PE_COFF: 14 - XBOX
        static const boost::uint8_t IMAGE_SUBSYSTEM_XBOX;

        static std::string
        get_String_Name ( boost::uint16_t val );
    };

} /* namespace wpef_module */
} /* namespace reverse */

#endif /* PE_SUBSYSTEM_H */
