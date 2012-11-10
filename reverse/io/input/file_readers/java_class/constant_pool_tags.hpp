/*  Constant_Pool_Tags.h

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

#ifndef JAVA_CONSTANT_POOL_TAGS_H_
#define JAVA_CONSTANT_POOL_TAGS_H_

#include <boost/cstdint.hpp>
#include <string>
#include <vector>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Constant_Pool_Tags
     * \date 2007
     * \author Stephen Torri
     */
    class Constant_Pool_Tags {

    public:

        static const boost::uint16_t UTF8;    // 0x1
        static const boost::uint16_t RESERVED; // 0x2
        static const boost::uint16_t INTEGER; // 0x3
        static const boost::uint16_t FLOAT;   // 0x4
        static const boost::uint16_t LONG;    // 0x5
        static const boost::uint16_t DOUBLE;  // 0x6
        static const boost::uint16_t CLASS;   // 0x7
        static const boost::uint16_t STRING;  // 0x8
        static const boost::uint16_t FIELD_REF; //0x9
        static const boost::uint16_t METHOD_REF; // 0xA
        static const boost::uint16_t INTERFACE_METHOD_REF; // 0xB
        static const boost::uint16_t NAME_AND_TYPE; // 0xC

        static bool is_Valid_Tag ( boost::uint16_t id );
  };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_CONSTANT_POOL_TAGS_H_ */
