/*  PE_Subsystem.cpp

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

#include "PE_Subsystem.h"

namespace reverse { namespace wpef_module {

    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_UNKNOWN = 0;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_NATIVE = 1;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_WINDOWS_GUI = 2;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_WINDOWS_CUI = 3;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_POSIX_CUI = 7;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_WINDOWS_CE_GUI = 9;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_EFI_APPLICATION = 10;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER = 11;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER = 12;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_EFI_ROM = 13;
    const boost::uint8_t PE_Subsystem::IMAGE_SUBSYSTEM_XBOX = 14;

    std::string
    PE_Subsystem::get_String_Name ( boost::uint16_t val )
    {
        std::string result;
        switch ( val )
            {
            case IMAGE_SUBSYSTEM_UNKNOWN:
                {
                    result = "PE:unknown_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_NATIVE:
                {
                    result = "PE:native_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_WINDOWS_GUI:
                {
                    result = "PE:windows_gui_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_WINDOWS_CUI:
                {
                    result = "PE:windows_cui_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_POSIX_CUI:
                {
                    result = "PE:posix_cui_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
                {
                    result = "PE:windows_ce_gui_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_EFI_APPLICATION:
                {
                    result = "PE:efi_application_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
                {
                    result = "PE:efi_boot_service_driver_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
                {
                    result = "PE:efi_runtime_driver_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_EFI_ROM:
                {
                    result = "PE:efi_rom_subsystem";
                    break;
                }
            case IMAGE_SUBSYSTEM_XBOX:
                {
                    result = "PE:xbox_subsystem";
                    break;
                }
            }
        return result;
    }

} /* namespace wpef_module */
} /* namespace reverse */

