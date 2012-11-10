/*  Class_Access_Flags.h

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

#ifndef CLASS_ACCESS_FLAGS_H_
#define CLASS_ACCESS_FLAGS_H_

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace java_module {

    class Class_Access_Flags {
    public:

      enum Values {
	ACC_PUBLIC     = 0x0001,
	ACC_FINAL      = 0x0010,
        ACC_SUPER      = 0x0020,
        ACC_INTERFACE  = 0x0200,
        ACC_ABSTRACT   = 0x0400,
	ACC_SYNTHETIC  = 0x1000,
	ACC_ANNOTATION = 0x2000,
	ACC_ENUM       = 0x4000
      };

      static bool has_Valid_Flags ( boost::uint16_t value );
      
      static std::string to_String ( boost::uint16_t value );
    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* CLASS_ACCESS_FLAGS_H_ */
