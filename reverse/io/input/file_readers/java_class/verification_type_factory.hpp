/*  Verification_Type_Factory.h

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

#ifndef VERIFICATION_TYPE_FACTORY_H_
#define VERIFICATION_TYPE_FACTORY_H_

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "Java_Types.h"

namespace reverse { namespace java_module {

    /*!
     * \class Verification_Type_Factory
     * \date 2007
     */
    class Verification_Type_Factory {
    public:

        static java_types::Verification_Type_Info::ptr_t create ( boost::uint8_t tag );

    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* VERIFICATION_TYPE_FACTORY_H_ */
