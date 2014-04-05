/*  CPU_Thread_State.h

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

//
// C++ Interface: CPU_Thread_State
//
// Description:
//
//
// Author: Stephen Torri,,, <storri@torri.org>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CPU_THREAD_STATE_H
#define CPU_THREAD_STATE_H

namespace reverse
{
    namespace mach_module
    {
        class CPU_Thread_State
        {
            public:

                /*!
                 * \brief Return a formatted string representation of the CPU state
                 *
                 * \return Formatted output string of CPU state
                 */
                virtual std::string to_String ( void ) = 0;

                /*!
                 * \brief Convert the byte order of register values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert ) = 0;

                /*!
                 * \brief Default destructor
                 */
                virtual ~CPU_Thread_State() {}
        };
    }
}

#endif /* CPU_THREAD_STATE */
