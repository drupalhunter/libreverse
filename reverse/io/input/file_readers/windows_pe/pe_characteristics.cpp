/*  PE_Characteristics.cpp

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

#include "PE_Characteristics.h"
#include <sstream>
#include <iostream>

namespace libreverse { namespace wpef_module {

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_RELOCS_STRIPPED = 0x0001;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_LINE_NUMS_STRIPPED = 0x0004;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_LOCAL_SYMS_STRIPPED = 0x0008;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_AGGRESSIVE_WS_TRIM = 0x0010;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_RESERVED_BIT = 0x0040;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_BYTES_REVERSED_LO = 0x0080;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_32BIT_MACHINE = 0x0100;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_DEBUG_STRIPPED = 0x0200;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP = 0x0400;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_NET_RUN_FROM_SWAP = 0x0800;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_SYSTEM = 0x1000;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_DLL = 0x2000;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_UP_SYSTEM_ONLY = 0x4000;

    const boost::uint16_t
    PE_Characteristics::PE_IMAGE_FILE_BYTES_REVERSED_HI = 0x8000;

    std::string
    PE_Characteristics::get_String_Name ( boost::uint16_t val )
    {
        std::string result;

        switch ( val )
            {
            case PE_IMAGE_FILE_RELOCS_STRIPPED:
                {
                    result = "PE:relocs_stripped";
                    break;
                }
            case PE_IMAGE_FILE_EXECUTABLE_IMAGE:
                {
                    result = "PE:executable_image";
                    break;
                }
            case PE_IMAGE_FILE_LINE_NUMS_STRIPPED:
                {
                    result = "PE:line_nums_strippes";
                    break;
                }
            case PE_IMAGE_FILE_LOCAL_SYMS_STRIPPED:
                {
                    result = "PE:local_syms_stripped";
                    break;
                }
            case PE_IMAGE_FILE_AGGRESSIVE_WS_TRIM:
                {
                    result = "PE:aggressive_ws_trim";
                    break;
                }
            case PE_IMAGE_FILE_LARGE_ADDRESS_AWARE:
                {
                    result = "PE:large_address_aware";
                    break;
                }
            case PE_IMAGE_FILE_RESERVED_BIT:
                {
                    result = "PE:reverse_bit";
                    break;
                }
            case PE_IMAGE_FILE_BYTES_REVERSED_LO:
                {
                    result = "PE:bytes_reversed_lo";
                    break;
                }
            case PE_IMAGE_FILE_32BIT_MACHINE:
                {
                    result = "PE:32bit_machine";
                    break;
                }
            case PE_IMAGE_FILE_DEBUG_STRIPPED:
                {
                    result = "PE:debug_stripped";
                    break;
                }
            case PE_IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP:
                {
                    result = "PE:removable_run_from_swap";
                    break;
                }
            case PE_IMAGE_FILE_NET_RUN_FROM_SWAP:
                {
                    result = "PE:net_run_from_swap";
                    break;
                }
            case PE_IMAGE_FILE_SYSTEM:
                {
                    result = "PE:system_file";
                    break;
                }
            case PE_IMAGE_FILE_DLL:
                {
                    result = "PE:dynamic_link_library";
                    break;
                }
            case PE_IMAGE_FILE_UP_SYSTEM_ONLY:
                {
                    result = "PE:uniprocessor_system_only";
                    break;
                }
            case PE_IMAGE_FILE_BYTES_REVERSED_HI:
                {
                    result = "PE:bytes_reversed_hi";
                    break;
                }
            }

        return result;
    }


    std::string
    PE_Characteristics::get_String_Name_List ( boost::uint16_t val )
    {
        std::stringstream output;

        if ( val & PE_IMAGE_FILE_RELOCS_STRIPPED )
            {
                output << "    PE:relocs_stripped" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_EXECUTABLE_IMAGE )
            {
                output << "    PE:executable_image" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_LINE_NUMS_STRIPPED )
            {
                output << "    PE:line_nums_stripped" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_LOCAL_SYMS_STRIPPED )
            {
                output << "    PE:local_syms_stripped" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_AGGRESSIVE_WS_TRIM )
            {
                output << "    PE:aggressive_ws_trim" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_LARGE_ADDRESS_AWARE )
            {
                output << "    PE:large_address_aware" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_RESERVED_BIT )
            {
                output << "    PE:reverse_bit" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_BYTES_REVERSED_LO )
            {
                output << "    PE:bytes_reversed_lo" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_32BIT_MACHINE )
            {
                output << "    PE:32bit_machine" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_DEBUG_STRIPPED )
            {
                output << "    PE:debug_stripped" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP )
            {
                output << "    PE:removable_run_from_swap" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_NET_RUN_FROM_SWAP )
            {
                output << "    PE:net_run_from_swap" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_SYSTEM )
            {
                output << "    PE:system_file" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_DLL )
            {
                output << "    PE:dynamic_link_library" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_UP_SYSTEM_ONLY )
            {
                output << "    PE:uniprocessor_system_only" << std::endl;
            }
        if ( val & PE_IMAGE_FILE_BYTES_REVERSED_HI )
            {
                output << "    PE:bytes_reversed_hi" << std::endl;
            }

        return output.str();
    }

} /* namespace wpef_module */
} /* namespace libreverse */
