/*  Append_Frame.h

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

#ifndef JAVA_APPEND_FRAME_H_
#define JAVA_APPEND_FRAME_H_

#include "Stack_Map_Frame.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>
#include "Java_Types.h"

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Append_Frame
     * \date 2007
     * \author Stephen Torri
     *
     * tag value range: 64 - 127
     */
    class Append_Frame : public Stack_Map_Frame,
                         public boost::enable_shared_from_this<Append_Frame>
    {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Append_Frame ( boost::uint8_t tag );

        /*!
         * \brief Default Destructor
         */
        virtual ~Append_Frame(){}

        virtual std::string to_String ( boost::uint16_t index = 0 ) const;
        
        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr );

        virtual boost::uint8_t get_Tag (void) const;

        boost::uint8_t get_Frame_Type ( void ) const;

    private:

        boost::uint8_t const m_tag;

        boost::uint16_t m_offset_delta;

        typedef std::vector< java_types::Verification_Type_Info::ptr_t > Append_Data_t;
        Append_Data_t m_data;
    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_APPEND_FRAME_H_ */
