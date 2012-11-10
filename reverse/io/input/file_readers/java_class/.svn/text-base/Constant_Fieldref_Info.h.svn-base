/*  Constant_Fieldref_Info.h

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

#ifndef JAVA_CONSTANT_FIELDREF_INFO_H_
#define JAVA_CONSTANT_FIELDREF_INFO_H_

#include "Constant_Pool_Info.h"
#include <boost/enable_shared_from_this.hpp>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Constant_Fieldref_Info
     * \date 2007
     * \author Stephen Torri
     */
    class Constant_Fieldref_Info
        : public Constant_Pool_Info,
          public boost::enable_shared_from_this<Constant_Fieldref_Info>
    {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Constant_Fieldref_Info();

        /*!
         * \brief Default Destructor
         */
        virtual ~Constant_Fieldref_Info(){}

        virtual std::string to_String (void) const;

        virtual boost::uint8_t get_Tag (void) const;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr );

        virtual bool is_Type ( boost::uint8_t id ) const;

        boost::uint16_t get_Class_Index (void) const;

        boost::uint16_t get_Name_And_Type_Index (void) const;

    private:

        boost::uint8_t m_tag;

        /*
         * !\brief The value of the class_index item must be a valid
         * index into the constant_pool table. The constant_pool entry
         * at that index must be a CONSTANT_Class_Info structure
         * representing the class or interface type that contains the
         * declaration of the field or method.
         */
        boost::uint16_t m_class_index;

        /* The value of the name_and_type_index item must be a index
         * into the constant_pool table. The constant_pool entry at
         * that index must be a CONSTANT_NameAndType_info structure.
         * This must be a field descriptor.
         */
        boost::uint16_t m_name_and_type_index;

  };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_CONSTANT_FIELDREF_INFO_H_ */
