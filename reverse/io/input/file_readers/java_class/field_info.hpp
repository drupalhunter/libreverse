/*  Field_Info.h

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

#ifndef JAVA_FIELD_INFO_H_
#define JAVA_FIELD_INFO_H_

#include "Java_Types.h"
#include <string>
#include <vector>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace reverse { namespace java_module {

    /*!
     * \class Field_Info
     * \date 2007
     * \author Stephen Torri
     */
    class Field_Info {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Field_Info();

        /*!
         * \brief Default Destructor
         */
        virtual ~Field_Info(){}

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        std::string to_String ( boost::uint16_t indent_count );

    private:

        /*!
         * \brief The value of the access_flags item is a mask of
         * flags used to denote access permission to and properties of
         * this field.
         */
        boost::uint16_t m_access_flags;

        /*!
         * \brief The value of the name_index item must be a valid
         * index into the constant_pool table. The constant_pool entry
         * at that index must be a CONSTANT_Utf_info structure which
         * must represent a valid field name stored as a simple name.
         */
        boost::uint16_t m_name_index;
	std::string m_name_string;

        /*!
         * \brief The value of the descriptor_index must be a valid
         * index into the constant_pool table. The constant_pool entry
         * at that index must be a CONSTANT_Utf8_info structure that
         * must represent a valid field descriptor.
         */
        boost::uint16_t m_descriptor_index;
	std::string m_descriptor_string;

        /*!
         * \brief The value of attributes_count item indicates the
         * number of additional attributes of this field.
         */
        boost::uint16_t m_attributes_count;

        /*!
         * \brief Each value of the attributes table must be an
         * attribute structure. A field can have any number of
         * attributes associated with it. The attributes defined by
         * this specification as appearing in the attributes table of
         * a field_info structure are the ConstantValue, Synthetic,
         * and Deprecated attributes.
         */
        java_types::Class_Header::Attribute_Info_Map_t m_attributes;
  };

} /* namespace java_module */
} /* namespace reverse */

#endif /* JAVA_FIELD_INFO_H_ */
