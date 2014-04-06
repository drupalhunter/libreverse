/*  Field_Access_Flags_Rules.h

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

#ifndef FIELD_ACCESS_FLAGS_RULES_H_
#define FIELD_ACCESS_FLAGS_RULES_H_

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

#include <boost/cstdint.hpp>

namespace reverse { namespace java_module {

    class Field_Access_Flags_Rules {
    public:

        /*!
         * \brief Evaulate the flags of the Field_Access flag to see if
         *  they are ok.
         *
         * \return TRUE (Ok) or FALSE.
         */
        bool validate_Flags ( boost::uint16_t value ) const;

    private:

    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* FIELD_ACCESS_FLAGS_RULES_H_ */
