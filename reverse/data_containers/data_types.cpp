/*  Data_Types.cpp

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

#include "Data_Types.h"

namespace libreverse { namespace data_types {

    boost::int8_t const Memory_Map::SUCCESS = 0;
    boost::int8_t const Memory_Map::INVALID_INDEX = -1;
    boost::int8_t const Memory_Map::OUT_OF_RANGE = -2;

} /* namespace data_types */
} /* namespace libreverse */

