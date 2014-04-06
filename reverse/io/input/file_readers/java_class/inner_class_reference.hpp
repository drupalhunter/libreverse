/*  Inner_Class_Reference.h

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

#ifndef JAVA_INNER_CLASS_REFERENCE_H_
#define JAVA_INNER_CLASS_REFERENCE_H_

#include "Java_Types.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace reverse { namespace java_module {

    /*!
     * \class Inner_Class_Reference
     * \date 2007
     * \author Stephen Torri
     */
    class Inner_Class_Reference :
    public boost::enable_shared_from_this<Inner_Class_Reference>
    {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Inner_Class_Reference ( void );

        /*!
         * \brief Default Destructor
         */
        virtual ~Inner_Class_Reference(){}

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        std::string to_String ( boost::uint16_t index );

        void read_Impl ( java_types::Class_File::ptr_t file_ptr,
                         java_types::Class_Header::ptr_t hdr_ptr );

    private:

        boost::uint16_t m_inner_class_info_index;

        boost::uint16_t m_outer_class_info_index;

        boost::uint16_t m_inner_name_index;

        std::string m_inner_name;

        boost::uint16_t m_inner_class_access_flags;

  };

} /* namespace java_module */
} /* namespace reverse */

#endif /* JAVA_EXCEPTION_ATTRIBUTE_H_ */
