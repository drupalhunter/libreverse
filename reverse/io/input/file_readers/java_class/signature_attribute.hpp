/*  Signature_Attribute.h

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

#ifndef JAVA_SIGNATURE_ATTRIBUTE_H_
#define JAVA_SIGNATURE_ATTRIBUTE_H_

#include "Attribute_Info.h"
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
     * \class Signature_Attribute
     * \date 2007
     * \author Stephen Torri
     */
    class Signature_Attribute : public Attribute_Info,
                                public boost::enable_shared_from_this<Signature_Attribute>
    {
    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Signature_Attribute ( boost::uint16_t index );

        /*!
         * \brief Default Destructor
         */
        virtual ~Signature_Attribute(){}

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

        boost::uint16_t m_signature_index;
  };

} /* namespace java_module */
} /* namespace reverse */

#endif /* JAVA_EXCEPTION_ATTRIBUTE_H_ */
