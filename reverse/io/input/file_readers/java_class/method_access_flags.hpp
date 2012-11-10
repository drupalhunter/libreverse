/*  Method_Access_Flags.h

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

#ifndef METHOD_ACCESS_FLAGS_H_
#define METHOD_ACCESS_FLAGS_H_

#include <boost/cstdint.hpp>

namespace libreverse { namespace java_module {

    class Method_Access_Flags {
    public:

        static boost::uint16_t const ACC_PUBLIC;
        static boost::uint16_t const ACC_PRIVATE;
        static boost::uint16_t const ACC_PROTECTED;
        static boost::uint16_t const ACC_STATIC;
        static boost::uint16_t const ACC_FINAL;
        static boost::uint16_t const ACC_SYNCHRONIZED;
        static boost::uint16_t const ACC_NATIVE;
        static boost::uint16_t const ACC_ABSTRACT;
        static boost::uint16_t const ACC_STRICT;
        static boost::uint16_t const ACC_RESERVED;

        static bool has_Valid_Flags ( boost::uint16_t value );
    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* METHOD_ACCESS_FLAGS_H_ */
