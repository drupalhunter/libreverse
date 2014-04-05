/*  Class_Access_Flags_Rules.h

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

#ifndef CLASS_ACCESS_FLAGS_RULES_H_
#define CLASS_ACCESS_FLAGS_RULES_H_

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

#include <boost/cstdint.hpp>

namespace reverse { namespace java_module {

    class Class_Access_Flags_Rules {
    public:

        /*!
         * \brief Evaulate the flags of the Class_Access flag to see if
         *  they are ok.
         *
         * \return TRUE (Ok) or FALSE.
         */
      static bool validate_Flags ( boost::uint16_t value );

    private:

        /*!
         * \brief An interface is distinguished by its ACC_INTERFACE
         * flag being set. If its ACC_INTERFACE is not set, this class
         * file defines a class, not an interface.
         */
        static bool is_Interface ( boost::uint16_t value );

        /*!
         * \brief If the ACC_INTERFACE flag of this class file is
         * set, its ACC_ABSTRACT flag must be also be set and its
         * ACC_PUBLIC flag may be set. Such a class file may not have
         * any of the other flags set.
         */
        static bool is_Abstract ( boost::uint16_t value );
        static bool is_Public ( boost::uint16_t value );
        static bool is_Final ( boost::uint16_t value );
	static bool is_Enum ( boost::uint16_t value );
	static bool is_Annotation ( boost::uint16_t value );

        /*!
         * \brief The setting of the ACC_SUPER flag indicates which
         * of two alternative semantics for its invokespecial
         * instruction the Java virtual machine is to express; the
         * ACC_SUPER flag exists for backward compatibility for code
         * compiled by Sun's older compilers for Java.
         *
         * All new compilers to the instruction set of the Java
         * virtual machine should set the ACC_SUPER flag. Older
         * compilers generate files with this unset.
         */
        static bool is_Super ( boost::uint16_t value );

        /*!
         * \brief All bits of the class_access_flags item not assigned are
         * reserved for future use. They should be set to zero in
         * generated class files and should be ignored by the JVM.
         */
        static bool are_Non_Assigned_Bits_Clear ( boost::uint16_t value );

    };

} /* namespace java_module */
} /* namespace reverse */

#endif /* CLASS_ACCESS_FLAGS_RULES_H_ */
