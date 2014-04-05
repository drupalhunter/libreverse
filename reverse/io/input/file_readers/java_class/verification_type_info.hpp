/*  Verification_Type_Info.h

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

#ifndef VERIFICATION_TYPE_INFO_H
#define VERIFICATION_TYPE_INFO_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include "Java_Types.h"

namespace reverse { namespace java_module {

    class Verification_Type_Info {

    public:

        friend class Class_File;

        virtual ~Verification_Type_Info(){}

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        virtual boost::uint8_t get_Tag (void) const = 0;

        virtual std::string to_String ( boost::uint16_t index ) const = 0;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr ) = 0;

        virtual bool is_Type ( boost::uint8_t id ) const = 0;

    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* VERIFICATION_TYPE_INFO_H */
