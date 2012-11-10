/*  PE_Machine_Types.cpp

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

#include "PE_Machine_Types.h"

namespace libreverse { namespace wpef_module {

    std::string
    PE_Machine_Types::get_String_Name ( boost::uint16_t val )
    {
        std::string result;

        switch ( val )
            {
            case IMAGE_FILE_MACHINE_UNKNOWN:
                {
                    result = "PE:Unknown";
                    break;
                }
            case IMAGE_FILE_MACHINE_AM33:
                {
                    result = "PE:AM33";
                    break;
                }
            case IMAGE_FILE_MACHINE_AMD64:
                {
                    result = "PE:AMD64";
                    break;
                }
            case IMAGE_FILE_MACHINE_EBC:
                {
                    result = "PE:EBC";
                    break;
                }
            case IMAGE_FILE_MACHINE_I386:
                {
                    result = "PE:i386";
                    break;
                }
            case IMAGE_FILE_MACHINE_IA64:
                {
                    result = "PE:ia64";
                    break;
                }
            case IMAGE_FILE_MACHINE_M32R:
                {
                    result = "PE:M32R";
                    break;
                }
            case IMAGE_FILE_MACHINE_MIPS16:
                {
                    result = "PE:MIPS16";
                    break;
                }
            case IMAGE_FILE_MACHINE_MIPSFPU:
                {
                    result = "PE:MIPSFPU";
                    break;
                }
            case IMAGE_FILE_MACHINE_MIPSFPU16:
                {
                    result = "PE:MIPSFPU16";
                    break;
                }
            case IMAGE_FILE_MACHINE_POWERPC:
                {
                    result = "PE:PowerPC";
                    break;
                }
            case IMAGE_FILE_MACHINE_POWERPCFP:
                {
                    result = "PE:PowerPC(FPU)";
                    break;
                }
            case IMAGE_FILE_MACHINE_R4000:
                {
                    result = "PE:R4000";
                    break;
                }
            case IMAGE_FILE_MACHINE_SH3:
                {
                    result = "PE:SH3";
                    break;
                }
            case IMAGE_FILE_MACHINE_SH3DSP:
                {
                    result = "PE:SH3DSP";
                    break;
                }
            case IMAGE_FILE_MACHINE_SH4:
                {
                    result = "PE:SH4";
                    break;
                }
            case IMAGE_FILE_MACHINE_SH5:
                {
                    result = "PE:SH5";
                    break;
                }
            case IMAGE_FILE_MACHINE_THUMB:
                {
                    result = "PE:THUMB";
                    break;
                }
            case IMAGE_FILE_MACHINE_WCEMIP:
                {
                    result = "PE:WCEMIP";
                    break;
                }
            }

        return result;
    }

    bool
    PE_Machine_Types::is_Valid_Value ( boost::uint16_t val )
    {
        bool result = false;
        switch ( val )
            {
            case IMAGE_FILE_MACHINE_UNKNOWN:
            case IMAGE_FILE_MACHINE_AM33:
            case IMAGE_FILE_MACHINE_AMD64:
            case IMAGE_FILE_MACHINE_EBC:
            case IMAGE_FILE_MACHINE_I386:
            case IMAGE_FILE_MACHINE_IA64:
            case IMAGE_FILE_MACHINE_M32R:
            case IMAGE_FILE_MACHINE_MIPS16:
            case IMAGE_FILE_MACHINE_MIPSFPU:
            case IMAGE_FILE_MACHINE_MIPSFPU16:
            case IMAGE_FILE_MACHINE_POWERPC:
            case IMAGE_FILE_MACHINE_POWERPCFP:
            case IMAGE_FILE_MACHINE_R4000:
            case IMAGE_FILE_MACHINE_SH3:
            case IMAGE_FILE_MACHINE_SH3DSP:
            case IMAGE_FILE_MACHINE_SH4:
            case IMAGE_FILE_MACHINE_SH5:
            case IMAGE_FILE_MACHINE_THUMB:
            case IMAGE_FILE_MACHINE_WCEMIP:
                {
                    result = true;
                }
            }

        return result;
    }

} /* namespace wpef_module */
} /* namespace libreverse */
