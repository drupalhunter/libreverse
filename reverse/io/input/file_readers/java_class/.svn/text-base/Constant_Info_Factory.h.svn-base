/*  Constant_Info_Factory.h

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

#ifndef CONSTANT_INFO_FACTORY_H_
#define CONSTANT_INFO_FACTORY_H_

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "Java_Types.h"

namespace libreverse { namespace java_module {

    /*!
     * \class Constant_Info_Factory
     * \date 2007
     */
    class Constant_Info_Factory {
    public:

        /* Read ClassFile header from file */
        static java_types::Constant_Pool_Info::ptr_t create ( boost::uint16_t id );
    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* CONSTANT_INFO_FACTORY_H_ */
