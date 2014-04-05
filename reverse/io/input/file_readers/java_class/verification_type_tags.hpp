/*  Verification_Type_Tags.h

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

#ifndef VERIFICATION_TYPE_TAGS_H
#define VERIFICATION_TYPE_TAGS_H

#include <boost/cstdint.hpp>

namespace reverse { namespace java_module {

    class Verification_Type_Tags {

    public:

      static boost::uint8_t const TOP;
      static boost::uint8_t const INTEGER;
      static boost::uint8_t const FLOAT;
      static boost::uint8_t const LONG;
      static boost::uint8_t const DOUBLE;
      static boost::uint8_t const NULL_TYPE;
      static boost::uint8_t const UNINITIALIZED_THIS;
      static boost::uint8_t const OBJECT;
      static boost::uint8_t const UNINITIALIZED;

    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* VERIFICATION_TYPE_TAGS_H */
