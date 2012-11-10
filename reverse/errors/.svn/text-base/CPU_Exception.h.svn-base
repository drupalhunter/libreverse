/*  CPU_Exception.h

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

#ifndef CPU_EXCEPTION_H_
#define CPU_EXCEPTION_H_

#include "Reverse_Exception.h"

namespace libreverse { namespace errors {

    class CPU_Exception : public virtual Reverse_Exception {
    public:

        CPU_Exception ( boost::uint32_t message_id );

        /*!
         * \brief Destructor
         */
        virtual ~CPU_Exception (void) throw(){}

        const char* what (void) const throw();

        /*!
         * \brief Return tne name of the exception
         */
        const char* name (void) const throw();

        enum {
            UNSUPPORTED_ARCHITECTURE
        };

    private:

        static const char* m_exception_name;

        static const char* m_messages[];
    };

} /* namespace errors */
} /* namespace libreverse */

#endif /* CPU_EXCEPTION_H_ */
