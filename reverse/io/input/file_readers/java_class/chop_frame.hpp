/*  Chop_Frame.h

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

#ifndef JAVA_CHOP_FRAME_H_
#define JAVA_CHOP_FRAME_H_

#include "Stack_Map_Frame.h"
#include "Java_Types.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    class Class_File;

    /*!
     * \class Chop_Frame
     * \date 2007
     * \author Stephen Torri
     *
     * tag value range: 64 - 127
     */
    class Chop_Frame : public Stack_Map_Frame,
                       public boost::enable_shared_from_this<Chop_Frame>
    {
    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Chop_Frame ( boost::uint8_t tag );

        /*!
         * \brief Default Destructor
         */
        virtual ~Chop_Frame(){}

        virtual std::string to_String ( boost::uint16_t index ) const;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr );

        virtual boost::uint8_t get_Tag (void) const;

        boost::uint8_t get_Frame_Type ( void ) const;

    private:

        boost::uint8_t m_tag;

        boost::uint16_t m_offset_delta;

    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_CHOP_FRAME_H_ */
