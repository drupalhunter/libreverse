/*  Field_Access_Flags.h

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

#ifndef FIELD_ACCESS_FLAGS_H_
#define FIELD_ACCESS_FLAGS_H_

#include <boost/cstdint.hpp>

namespace libreverse { namespace java_module {

    class Field_Access_Flags {
    public:

        static boost::uint16_t const ACC_PUBLIC;
        static boost::uint16_t const ACC_PRIVATE;
        static boost::uint16_t const ACC_PROTECTED;
        static boost::uint16_t const ACC_STATIC;
        static boost::uint16_t const ACC_FINAL;
        static boost::uint16_t const ACC_VOLATILE;
        static boost::uint16_t const ACC_TRANSIENT;
        static boost::uint16_t const ACC_SYNTHETIC;
        static boost::uint16_t const ACC_ENUM;
        static boost::uint16_t const ACC_RESERVED;

        static bool has_Valid_Flags ( boost::uint16_t value );
    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* FIELD_ACCESS_FLAGS_H_ */
