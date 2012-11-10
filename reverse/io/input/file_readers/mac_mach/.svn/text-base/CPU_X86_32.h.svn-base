/*  CPU_X86_32.h

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

#ifndef _CPU_X86_32_H
#define _CPU_X86_32_H

#include <string>
using namespace std;

#include <boost/cstdint.hpp>
using namespace boost;

namespace libreverse
{
    namespace mach_module
    {

        class CPU_X86_32
        {
            public:
                enum Registers
                {
                    EAX = 0,
                    EBX = 1,
                    ECX = 2,
                    EDX = 3,
                    EDI = 4,
                    ESI = 5,
                    EBP = 6,
                    ESP = 7,
                    SS = 8,
                    EFLAGS = 9,
                    EIP = 10,
                    DS = 11,
                    ES = 12,
                    FS = 13,
                    GS = 14,
                    MAX_COUNT = 15
                };

                typedef uint32_t data_type;

                /*!
                 * \brief Return the register name for the given index
                 *
                 * \param index Unsigned integer index for the target register
                 *
                 * \exception IO_Exception(INVALID_INDEX) Exception thrown for invalid index between the ranges of SSR0 and GS.
                 *
                 * \return Register string name
                 */
                static string get_Register_Name ( uint32_t index );

        };

    } /* namespace mach_module */
} /* namespace libreverse */

#endif
