/*  Source_File_Attribute.h

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

#ifndef JAVA_SOURCE_FILE_ATTRIBUTE_H_
#define JAVA_SOURCE_FILE_ATTRIBUTE_H_

#include "Attribute_Info.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Source_File_Attribute
     * \date 2007
     * \author Stephen Torri
     */
    class Source_File_Attribute : public Attribute_Info,
                                  public boost::enable_shared_from_this<Source_File_Attribute>
    {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Source_File_Attribute ( boost::uint16_t index );

        /*!
         * \brief Default Destructor
         */
        virtual ~Source_File_Attribute(){}

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        virtual std::string to_String ( boost::uint16_t index = 0 ) const;

        virtual std::string get_Tag (void) const;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr,
                                  java_types::Class_Header::ptr_t hdr_ptr );

        virtual bool is_Type ( std::string id ) const;

    private:

        boost::uint16_t m_name_index;

        std::string m_attribute_name;

        boost::uint32_t m_attribute_length;

        /*!
         * \brief The value of the source_file_index must be a
         * valid index into the constant_pool table. The constant_pool
         * entry at that index gives the constant value represented by
         * this attribute.
         */
        boost::uint16_t m_source_file_index;

        std::string m_source_file_name;

    };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_SOURCE_FILE_ATTRIBUTE_H_ */
