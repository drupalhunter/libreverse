/*  Line_Number_Item.h

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

#ifndef JAVA_LINE_NUMBER_ITEM_H_
#define JAVA_LINE_NUMBER_ITEM_H_

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <vector>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Line_Number_Item_
     * \date 2007
     * \author Stephen Torri
     */
    class Line_Number_Item {

    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Line_Number_Item ( void );

        /*!
         * \brief Default Destructor
         */
        virtual ~Line_Number_Item(){}

        /*!
         * \brief String representation of JAVA Header
         * \return String output of header
         */
        virtual std::string to_String ( boost::uint16_t index );

    private:

        boost::uint16_t m_start_pc;

        boost::uint16_t m_line_number;
  };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_EXCEPTION_ATTRIBUTE_H_ */
