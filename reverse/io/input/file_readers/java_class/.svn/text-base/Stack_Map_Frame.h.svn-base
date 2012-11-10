/*  Stack_Map_Frame.h

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

#ifndef JAVA_STACK_MAP_FRAME_H_
#define JAVA_STACK_MAP_FRAME_H_

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include "Java_Types.h"

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Stack_Map_Frame
     * \date 2007
     * \author Stephen Torri
     */
    class Stack_Map_Frame {

    public:

        /*!
         * \brief Default Destructor
         */
        virtual ~Stack_Map_Frame(){}

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        virtual std::string to_String ( boost::uint16_t index = 0 ) const = 0;

        virtual boost::uint8_t get_Tag (void) const = 0;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr ) = 0;

    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_STACK_MAP_FRAME_H_ */
