/*  CPU_PPC_64.h

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
// C++ Interface: CPU_PPC_64
//
// Description:
//
//
// Author: Stephen Torri,,, <storri@torri.org>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CPU_PPC_64_H
#define CPU_PPC_64_H

#include <string>
#include "errors/IO_Exception.h"

namespace reverse
{
    namespace mach_module
    {
        class CPU_PPC_64
        {
            public:

                typedef boost::uint64_t data_type;

                enum Registers
                {
                    SRR0 = 0,
                    SRR1 = 1,
                    R0 = 2,
                    R1 = 3,
                    R2 = 4,
                    R3 = 5,
                    R4 = 6,
                    R5 = 7,
                    R6 = 8,
                    R7 = 9,
                    R8 = 10,
                    R9 = 11,
                    R10 = 12,
                    R11 = 13,
                    R12 = 14,
                    R13 = 15,
                    R14 = 16,
                    R15 = 17,
                    R16 = 18,
                    R17 = 19,
                    R18 = 20,
                    R19 = 21,
                    R20 = 22,
                    R21 = 23,
                    R22 = 24,
                    R23 = 25,
                    R24 = 26,
                    R25 = 27,
                    R26 = 28,
                    R27 = 29,
                    R28 = 30,
                    R29 = 31,
                    R30 = 32,
                    R31 = 33,
                    CR = 34,
                    XER = 35,
                    LR = 36,
                    CTR = 37,
                    VRSAVE = 38,
                    MAX_COUNT = 39
                };

                /*!
                 * \brief Return the register name for the given index
                 *
                 * \param index Unsigned integer index for the target register
                 *
                 * \exception IO_Exception(INVALID_INDEX) Exception thrown for invalid index between the ranges of SSR0 and VRSAVE.
                 *
                 * \return Register string name
                 */
                static std::string get_Register_Name ( boost::uint32_t index );
        };
    }
}

#endif /* CPU_PPC_64 */

