/*  PE_Resource_Integer_Types.cpp

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

#include "PE_Resource_Integer_Types.h"

namespace reverse { namespace wpef_module {

    const boost::uint8_t PE_Resource_Integer_Types::RT_CURSOR = 0x1;
    const boost::uint8_t PE_Resource_Integer_Types::RT_BITMAP = 0x2;
    const boost::uint8_t PE_Resource_Integer_Types::RT_ICON = 0x3;
    const boost::uint8_t PE_Resource_Integer_Types::RT_MENU = 0x4;
    const boost::uint8_t PE_Resource_Integer_Types::RT_DIALOG = 0x5;
    const boost::uint8_t PE_Resource_Integer_Types::RT_STRING = 0x6;
    const boost::uint8_t PE_Resource_Integer_Types::RT_FONTDIR = 0x7;
    const boost::uint8_t PE_Resource_Integer_Types::RT_FONT = 0x8;
    const boost::uint8_t PE_Resource_Integer_Types::RT_ACCELERATORS = 0x9;
    const boost::uint8_t PE_Resource_Integer_Types::RT_RCDATA = 0xA;
    const boost::uint8_t PE_Resource_Integer_Types::RT_MESSAGETABLE = 0xB;
    const boost::uint8_t PE_Resource_Integer_Types::RT_GROUP_CURSOR = 0xC;
    const boost::uint8_t PE_Resource_Integer_Types::RT_GROUP_ICON = 0xE;
    const boost::uint8_t PE_Resource_Integer_Types::RT_VERSION = 0x10;

    std::string
    PE_Resource_Integer_Types::get_String_Name ( boost::uint32_t val )
    {
        std::string result;

        switch ( val )
            {
            case RT_CURSOR:
                {
                    result = "CURSOR";
                    break;
                }
            case RT_BITMAP:
                {
                    result = "BITMAP";
                    break;
                }
            case RT_ICON:
                {
                    result = "ICON";
                    break;
                }
            case RT_MENU:
                {
                    result = "MENU";
                    break;
                }
            case RT_DIALOG:
                {
                    result = "DIALOG";
                    break;
                }
            case RT_STRING:
                {
                    result = "STRING";
                    break;
                }
            case RT_FONTDIR:
                {
                    result = "FONTDIR";
                    break;
                }
            case RT_FONT:
                {
                    result = "FONT";
                    break;
                }
            case RT_ACCELERATORS:
                {
                    result = "ACCELERATORS";
                    break;
                }
            case RT_RCDATA:
                {
                    result = "RCDATA";
                    break;
                }
            case RT_MESSAGETABLE:
                {
                    result = "MESSAGETABLE";
                    break;
                }
            case RT_GROUP_CURSOR:
                {
                    result = "GROUP_CURSOR";
                    break;
                }
            case RT_GROUP_ICON:
                {
                    result = "GROUP_ICON";
                    break;
                }
            case RT_VERSION:
                {
                    result = "VERSION";
                    break;
                }
            }

        return result;
    }

} /* namespace wpef_module */
} /* namespace reverse */
