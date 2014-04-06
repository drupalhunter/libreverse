/*  Stack_Map_Frame_Tags.h

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

#ifndef STACK_MAP_FRAME_TAGS_H
#define STACK_MAP_FRAME_TAGS_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

namespace reverse { namespace java_module {

    class Stack_Map_Frame_Tags {

    public:

      static boost::uint8_t const SAME_LOWER_LIMIT;
      static boost::uint8_t const SAME_UPPER_LIMIT;
      static boost::uint8_t const SAME_LOCALS_ONE_ITEM_LOWER_LIMIT;
      static boost::uint8_t const SAME_LOCALS_ONE_ITEM_UPPER_LIMIT;
      static boost::uint8_t const SAME_LOCALS_EXTENDED;
      static boost::uint8_t const CHOP_FRAME_LOWER_LIMIT;
      static boost::uint8_t const CHOP_FRAME_UPPER_LIMIT;
      static boost::uint8_t const SAME_FRAME_EXTENDED;
      static boost::uint8_t const APPEND_FRAME_LOWER_LIMIT;
      static boost::uint8_t const APPEND_FRAME_UPPER_LIMIT;
      static boost::uint8_t const FULL_FRAME;

    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* STACK_MAP_FRAME_TAGS_H */
