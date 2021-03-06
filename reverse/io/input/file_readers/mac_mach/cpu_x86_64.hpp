/*  CPU_X86_64.h

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
// C++ Interface: CPU_X86_64
//
// Description:
//
//
// Author: Stephen Torri,,, <storri@torri.org>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CPU_X86_64_H
#define CPU_X86_64_H

#include <string>
#include "errors/IO_Exception.h"

namespace reverse
{
    namespace mach_module
    {
        class CPU_X86_64
        {
            public:

                typedef boost::uint64_t data_type;

                enum Registers
                {
                    RAX = 0,
                    RBX = 1,
                    RCX = 2,
                    RDX = 3,
                    RDI = 4,
                    RSI = 5,
                    RBP = 6,
                    RSP = 7,
                    R8 = 8,
                    R9 = 9,
                    R10 = 10,
                    R11 = 11,
                    R12 = 12,
                    R13 = 13,
                    R14 = 14,
                    R15 = 15,
                    RIP = 16,
                    RFLAGS = 17,
                    CS = 18,
                    FS = 19,
                    GS = 20,
                    MAX_COUNT = 21
                };

                /*!
                 * \brief Return the register name for the given index
                 *
                 * \param index Unsigned integer index for the target register
                 *
                 * \exception IO_Exception(INVALID_INDEX) Exception thrown for invalid index between the ranges of SSR0 and GS.
                 *
                 * \return Register string name
                 */
                static std::string get_Register_Name ( boost::uint32_t index );
        };
    }
}

#endif /* CPU_X86_64 */

