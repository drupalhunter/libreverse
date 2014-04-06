/*  Header.h

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

#ifndef JAVA_FILE_HEADER_H_
#define JAVA_FILE_HEADER_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include "errors/IO_Exception.h"
#include <vector>
#include "Java_Types.h"

namespace reverse { namespace java_module {

    /*!
     * \class Header
     * \date 2003
     * \author Stephen Torri
     */
    class Header : public header::Base_Header {

    public:

        /*!
         * \brief Default Constructor
         */
        Header();

        /*!
         * \brief Default Destructor
         */
        virtual ~Header(){}

        /*!
         * \brief Initialize Header
         */
        virtual void init (void);

        /*!
         * \brief Change the bit-ordering if required
         */
        virtual void convert ();

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        std::string const to_String (void) const;

        java_types::Class_Header::ptr_t get_Class_Header (void) const;

        void set_Class_Header ( java_types::Class_Header::ptr_t ch_ptr );

    private:

        java_types::Class_Header::ptr_t m_class_hdr;
    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* JAVA_FILE_HEADER_H_ */
