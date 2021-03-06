/*  CPU_SubType.h

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

#ifndef CPU_SUBTYPE_H
#define CPU_SUBTYPE_H

#include <boost/cstdint.hpp>
#include <string>

/* Values, comments and names taken from mach/machine.h */
namespace reverse
{
    namespace mach_module
    {
        class CPU_SubType
        {
            public:


                enum Values
                {
                    CPU_SUBTYPE_MULTIPLE = 0x80000000,
                    CPU_SUBTYPE_LITTLE_ENDIAN = 0x0,
                    CPU_SUBTYPE_BIG_ENDIAN = 0x1
                };

                /*!
                 * \brief VAX subtypes
                 *
                 * These do *not* necessary conform to the actual cpu
                 *  ID assigned by DEC available via the SID register.
                 */

                enum VAX_Values
                {
                    CPU_SUBTYPE_VAX_ALL = 0x0,
                    CPU_SUBTYPE_VAX780 = 0x1,
                    CPU_SUBTYPE_VAX785 = 0x2,
                    CPU_SUBTYPE_VAX750 = 0x3,
                    CPU_SUBTYPE_VAX730 = 0x4,
                    CPU_SUBTYPE_UVAXI = 0x5,
                    CPU_SUBTYPE_UVAXII = 0x6,
                    CPU_SUBTYPE_VAX8200 = 0x7,
                    CPU_SUBTYPE_VAX8500 = 0x8,
                    CPU_SUBTYPE_VAX8600 = 0x9,
                    CPU_SUBTYPE_VAX8650 = 0xa,
                    CPU_SUBTYPE_VAX8800 = 0xb,
                    CPU_SUBTYPE_UVAXIII = 0xc
                };

                /*!
                 * \brief 680x0 subtypes
                 *
                 * The subtype definitions here are unusual for historical reasons.
                 * NeXT used to consider 68030 code as generic 68000 code.  For
                 * backwards compatability:
                 *
                 *  CPU_SUBTYPE_MC68030 symbol has been preserved for source code
                 *  compatability.
                 *
                 *  CPU_SUBTYPE_MC680x0_ALL has been defined to be the same
                 *  subtype as CPU_SUBTYPE_MC68030 for binary comatability.
                 *
                 *  CPU_SUBTYPE_MC68030_ONLY has been added to allow new object
                 *  files to be tagged as containing 68030-specific instructions.
                 */
                enum MC680x0_Values
                {
                    CPU_SUBTYPE_MC68030 = 0x1,
                    CPU_SUBTYPE_MC68040 = 0x2,
                    CPU_SUBTYPE_MC68030_ONLY = 0x3
                };

                /*!
                 * \brief I386 subtypes
                 */
                enum Intel_Values
                {
                    CPU_SUBTYPE_386 = 0x03,
                    CPU_SUBTYPE_486 = 0x04,
                    CPU_SUBTYPE_486SX = 0x84,
                    CPU_SUBTYPE_586 = 0x05,
                    CPU_SUBTYPE_PENTPRO = 0x16,
                    CPU_SUBTYPE_PENTII_M3 = 0x36,
                    CPU_SUBTYPE_PENTII_M5 = 0x56,
                    CPU_SUBTYPE_CELERON = 0x67,
                    CPU_SUBTYPE_CELERON_MOBILE = 0x77,
                    CPU_SUBTYPE_PENTIUM_3 = 0x8,
                    CPU_SUBTYPE_PENTIUM_3_M = 0x18,
                    CPU_SUBTYPE_PENTIUM_3_XEON = 0x28,
                    CPU_SUBTYPE_PENTIUM_M = 0x9,
                    CPU_SUBTYPE_PENTIUM_4 = 0xA,
                    CPU_SUBTYPE_PENTIUM_4_M = 0x1A,
                    CPU_SUBTYPE_ITANIUM = 0xB,
                    CPU_SUBTYPE_ITANIUM_2 = 0x1B,
                    CPU_SUBTYPE_XEON = 0xC,
                    CPU_SUBTYPE_XEON_MP = 0x1C
                };

                /*!
                 * \brief Mips subtypes.
                 */
                enum MIPS_Values
                {
                    CPU_SUBTYPE_MIPS_ALL = 0x0,
                    CPU_SUBTYPE_MIPS_R2300 = 0x1,
                    CPU_SUBTYPE_MIPS_R2600  = 0x2,
                    CPU_SUBTYPE_MIPS_R2800  = 0x3,
                    CPU_SUBTYPE_MIPS_R2000a = 0x4, /* pmax */
                    CPU_SUBTYPE_MIPS_R2000  = 0x5,
                    CPU_SUBTYPE_MIPS_R3000a = 0x6, /* 3max */
                    CPU_SUBTYPE_MIPS_R3000  = 0x7
                };

                /*!
                 * \brief MC98000 (PowerPC) subtypes
                 */
                enum MC98000_Values
                {
                    CPU_SUBTYPE_MC98000_ALL = 0x0,
                    CPU_SUBTYPE_MC98601 = 0x1
                };

                /*!
                 * \brief HPPA subtypes for Hewlett-Packard HP-PA family of
                 *  risc processors. Port by NeXT to 700 series.
                 */
                enum HPPA_Values
                {
                    CPU_SUBTYPE_HPPA_7100 = 0x0,
                    CPU_SUBTYPE_HPPA_7100LC = 0x1
                };

                /*!
                 * \brief MC88000 subtypes.
                 */
                enum MC88000_Values
                {
                    CPU_SUBTYPE_MC88000_ALL = 0x0,
                    CPU_SUBTYPE_MC88100 = 0x1,
                    CPU_SUBTYPE_MC88110 = 0x2
                };

                /*
                 *  SPARC subtypes
                 */
                enum Sparc_Values
                {
                    CPU_SUBTYPE_SPARC_ALL = 0x0
                };

                /*!
                 * \brief I860 subtypes
                 */
                enum I860_Values
                {
                    CPU_SUBTYPE_I860_ALL = 0x0,
                    CPU_SUBTYPE_I860_860 = 0x1
                };

                /*!
                 * \brief PowerPC subtypes
                 */
                enum PowerPC_Values
                {
                    CPU_SUBTYPE_POWERPC_ALL = 0x0,
                    CPU_SUBTYPE_POWERPC_601 = 0x1,
                    CPU_SUBTYPE_POWERPC_602 = 0x2,
                    CPU_SUBTYPE_POWERPC_603 = 0x3,
                    CPU_SUBTYPE_POWERPC_603e = 0x4,
                    CPU_SUBTYPE_POWERPC_603ev = 0x5,
                    CPU_SUBTYPE_POWERPC_604 = 0x6,
                    CPU_SUBTYPE_POWERPC_604e = 0x7,
                    CPU_SUBTYPE_POWERPC_620 = 0x8,
                    CPU_SUBTYPE_POWERPC_750 = 0x9,
                    CPU_SUBTYPE_POWERPC_7400 = 0xA,
                    CPU_SUBTYPE_POWERPC_7450 = 0xB,
                    CPU_SUBTYPE_POWERPC_970 = 0x64
                };


                /*!
                 * \brief Return the string name for the given cpu type and sub-type
                 *
                 * \param cputype Unsigned integer value representing the cpu type
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu type is not supported
                 *
                 * \return Cpu string name
                 */
                static std::string get_String_Name ( boost::uint32_t cputype, boost::uint32_t cpu_subtype );

            private:
                /*!
                 * \brief Return the string name (VAX) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return VAX cpu sub-type string
                 */
                static std::string get_VAX_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (MIPS) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return MIPS cpu sub-type string
                 */
                static std::string get_MIPS_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (Intel) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return Intel cpu sub-type string
                 */
                static std::string get_Intel_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (MC680x0) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return MC680x0 cpu sub-type string
                 */
                static std::string get_MC680x0_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (MC98000) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return MC98000 cpu sub-type string
                 */
                static std::string get_MC98000_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (HPPA) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return HPPA cpu sub-type string
                 */
                static std::string get_HPPA_String_Name ( boost::uint32_t cpu_subtype );


                /*!
                 * \brief Return the string name (MC88000) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return MC88000 cpu sub-type string
                 */
                static std::string get_MC88000_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (I860) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return I860 cpu sub-type string
                 */
                static std::string get_I860_String_Name ( boost::uint32_t cpu_subtype );

                /*!
                 * \brief Return the string name (PowerPC) for the cpu sub-type
                 *
                 * \param cpu_subtype Unsigned integer value representing the cpu sub-type
                 *
                 * \exception IO_Exception(INVALID_VALUE) Thrown when the given cpu sub-type is not associated with any name
                 *
                 * \return PowerPC cpu sub-type string
                 */
                static std::string get_PowerPC_String_Name ( boost::uint32_t cpu_subtype );

        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* CPU_SUBTYPE_32BIT_H */
