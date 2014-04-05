/*  CPU_Type.h

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

#ifndef CPU_TYPE_H
#define CPU_TYPE_H

#include <boost/cstdint.hpp>
#include <string>

namespace reverse
{
    namespace mach_module
    {

        class CPU_Type
        {
            public:

                static const boost::uint32_t CPU_ARCH_MASK = 0xFF000000;
                static const boost::uint32_t CPU_ARCH_ABI64 = 0x01000000;

                /*!
                 * \brief Values and names taken from mach/machine.h
                 */
                enum Values
                {
                    CPU_TYPE_ANY = 0x80000000,
                    CPU_TYPE_VAX = 0x1,
                    CPU_TYPE_MC680x0 = 0x6,
                    CPU_TYPE_X86  = 0x7,
                    CPU_TYPE_X86_64 = ( CPU_TYPE_X86 | CPU_ARCH_ABI64 ),
                    CPU_TYPE_MIPS = 0x8,
                    CPU_TYPE_MC98000 = 0xa,
                    CPU_TYPE_HPPA = 0xb,
                    CPU_TYPE_ARM = 0xc,
                    CPU_TYPE_MC88000 = 0xd,
                    CPU_TYPE_SPARC = 0xe,
                    CPU_TYPE_I860 = 0xf,
                    CPU_TYPE_ALPHA = 0x10,
                    CPU_TYPE_POWERPC = 0x12,
                    CPU_TYPE_POWERPC64 = ( CPU_TYPE_POWERPC | CPU_ARCH_ABI64 )
                };

                /*!
                 * \brief Return the CPU name as a string
                 *
                 * \param cputype Unsigned integer representing the type of CPU
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown if the cputype is not in the list of Values
                 *
                 * \return CPU name contained in a string
                 */
                static std::string get_String_Name ( boost::uint32_t cputype );

        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* CPU_Type::CPU_TYPE_32BIT_H */
