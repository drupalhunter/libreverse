/*  Constant_Utf8_Info.h

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

#ifndef JAVA_CONSTANT_UTF8_INFO_H_
#define JAVA_CONSTANT_UTF8_INFO_H_

#include "Constant_Pool_Info.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <unicode/ustring.h>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace reverse { namespace java_module {

    class Class_File;

    /*!
     * \class Constant_Utf8_Info
     * \date 2007
     * \author Stephen Torri
     */
    class Constant_Utf8_Info
        : public Constant_Pool_Info,
          public boost::enable_shared_from_this<Constant_Utf8_Info>
    {
    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Constant_Utf8_Info();

        /*!
         * \brief Default Destructor
         */
        virtual ~Constant_Utf8_Info(){}

        virtual std::string to_String (void) const;

        virtual boost::uint8_t get_Tag (void) const;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr );

        virtual bool is_Type ( boost::uint8_t id ) const;

        boost::uint16_t get_Length (void) const;

        std::string get_Text ( void ) const;

        std::vector<UChar> get_Chars ( void ) const;

    private:

        boost::uint8_t m_tag;

        boost::uint16_t m_length;

        std::vector<UChar> m_chars;

        std::string m_text;
  };

} /* namespace java_module */
} /* namespace reverse */

#endif /* JAVA_CONSTANT_LONG_INFO_H_ */
