/*  Integer_Variable_Info.h

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

#ifndef JAVA_INTEGER_VARIABLE_INFO_H_
#define JAVA_INTEGER_VARIABLE_INFO_H_

#include "Verification_Type_Info.h"

namespace libreverse { namespace java_module {

    class Integer_Variable_Info : public Verification_Type_Info {
    public:

        Integer_Variable_Info ();

        virtual ~Integer_Variable_Info(){}

        virtual std::string to_String ( boost::uint16_t index ) const;

        virtual void read_Input ( java_types::Class_File::ptr_t ){};

        virtual boost::uint8_t get_Tag (void) const;

        virtual bool is_Type ( boost::uint8_t id ) const;

    private:

        boost::uint8_t m_tag;
    };
    
} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_INTEGER_VARIABLE_INFO_H_ */
