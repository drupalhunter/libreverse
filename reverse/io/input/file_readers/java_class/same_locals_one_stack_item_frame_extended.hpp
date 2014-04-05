/*  Same_Locals_One_Stack_Item_Frame_Extended.h

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

#ifndef JAVA_SAME_LOCALS_ONE_STACK_ITEM_FRAME_EXTENDED_H_
#define JAVA_SAME_LOCALS_ONE_STACK_ITEM_FRAME_EXTENDED_H_

#include "Stack_Map_Frame.h"
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
     * \class Same_Locals_One_Stack_Item_Frame_Extended
     * \date 2007
     * \author Stephen Torri
     *
     * tag value range: 64 - 127
     */
    class Same_Locals_One_Stack_Item_Frame_Extended : public Stack_Map_Frame,
                                                      public boost::enable_shared_from_this<Same_Locals_One_Stack_Item_Frame_Extended>
    {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Same_Locals_One_Stack_Item_Frame_Extended ( boost::uint8_t tag );

        /*!
         * \brief Default Destructor
         */
        virtual ~Same_Locals_One_Stack_Item_Frame_Extended(){}

        virtual std::string to_String ( boost::uint16_t index ) const;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr );

        virtual boost::uint8_t get_Tag ( void ) const;

        boost::uint8_t get_Frame_Type ( void ) const;

    private:

	boost::uint8_t m_tag;

        boost::uint16_t m_offset_delta;

        java_types::Verification_Type_Info::ptr_t m_data;
    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* JAVA_SAME_LOCALS_ONE_STACK_ITEM_FRAME_EXTENDED_H_ */
