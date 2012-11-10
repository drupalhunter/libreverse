/*  Stack_Map_Frame_Tags.cpp

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

#include "Stack_Map_Frame_Tags.h"

namespace libreverse { namespace java_module {

    boost::uint8_t const Stack_Map_Frame_Tags::SAME_LOWER_LIMIT = 0;
    boost::uint8_t const Stack_Map_Frame_Tags::SAME_UPPER_LIMIT = 63;
    boost::uint8_t const Stack_Map_Frame_Tags::SAME_LOCALS_ONE_ITEM_LOWER_LIMIT = 64;
    boost::uint8_t const Stack_Map_Frame_Tags::SAME_LOCALS_ONE_ITEM_UPPER_LIMIT = 127;
    boost::uint8_t const Stack_Map_Frame_Tags::SAME_LOCALS_EXTENDED = 247;
    boost::uint8_t const Stack_Map_Frame_Tags::CHOP_FRAME_LOWER_LIMIT = 248;
    boost::uint8_t const Stack_Map_Frame_Tags::CHOP_FRAME_UPPER_LIMIT = 250;
    boost::uint8_t const Stack_Map_Frame_Tags::SAME_FRAME_EXTENDED = 251;
    boost::uint8_t const Stack_Map_Frame_Tags::APPEND_FRAME_LOWER_LIMIT = 252;
    boost::uint8_t const Stack_Map_Frame_Tags::APPEND_FRAME_UPPER_LIMIT = 254;
    boost::uint8_t const Stack_Map_Frame_Tags::FULL_FRAME = 255;

} /* namespace java_module */
} /* namespace libreverse */

