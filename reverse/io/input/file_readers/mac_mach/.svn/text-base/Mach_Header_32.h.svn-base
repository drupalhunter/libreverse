/*  Mach_Header_32.h

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

#ifndef Mach_Header_32_H
#define Mach_Header_32_H

#include <boost/cstdint.hpp>
#include <string>
#include "Mach_Types.h"

namespace libreverse
{
    namespace mach_module
    {

        class Mach_File;

        class Mach_Header_32
        {
            public:

                /*! \brief Default Constructor */
                Mach_Header_32();

                /*! \brief Default Destructor */
                virtual ~Mach_Header_32() {}

                /*!
                 * \brief Return a formatted string representation of the Mach_Header_32
                 *
                 * \return Formatted output string of Mach_Header_32 object
                 */
                std::string to_String ( void );

                /*!
                 * \brief Identify this file is a Mach file or not
                 * \return Boolean result that a file is a Mach file (TRUE) or not
                 */
                bool is_Mach_File ( void ) const;

                /*!
                 * \brief Convert the byte order of the command values
                 */
                void convert ( void );

                /*!
                 * \brief Determine if we need to convert the byte order of the fields in this header
                 *
                 * \return FALSE = Same endian type as the CPU, TRUE = Different endian type from the CPU
                 */
                bool needs_Convert ( void ) const;

                /*!
                 * \brief Return the Magic number of this header
                 * \return Unsigned integer representing magic number
                 */
                boost::uint32_t get_Magic ( void ) const;

                /*!
                 * \brief Return CPU type
                 * \return Unsigned integer representing CPU type
                 */
                boost::uint32_t get_Cputype ( void ) const;

                /*!
                 * \brief Return CPU sub-type
                 * \return Unsigned integer representing CPU sub-type
                 */
                boost::uint32_t get_CpuSubtype ( void ) const;

                /*!
                 * \brief Return file type
                 * \return Unsigned integer representing file type
                 */
                boost::uint32_t get_Filetype ( void ) const;

                /*!
                 * \brief Return number of load commands
                 * \return Unsigned integer representing number of load command
                 */
                boost::uint32_t get_Load_Command_Count ( void ) const;

                /*!
                 * \brief Return command size
                 * \return Unsigned integer representing command size
                 */
                boost::uint32_t get_Command_Size ( void ) const;

                /*!
                 * \brief Return flags
                 * \return Unsigned integer representing flags
                 */
                boost::uint32_t get_Flags ( void ) const;

            private:

                friend class Mach_File;

                enum Magic_Values
                {
                    MH_MAGIC = 0xfeedface,
                    MH_CIGAM = 0xcefaedfe
                };

                /*! \brief An integer containing a value identifying this file as a 32-bit Mach-O file.
                 *
                 *         Use the constant MH_MAGIC if the file is intended for use on a CPU with the same endianness as the computer
                 *         on which the compiler is running. The constant MH_CIGAM can be used when the byte ordering scheme of the
                 *         target machine is the reverse of the host CPU.
                 */
                boost::uint32_t m_magic;

                /*! \brief An integer indicating the architecture you intend to use the file on. Appropriate values include:
                 *         - CPU_TYPE_POWERPC to target PowerPC-based Macintosh computers
                 *         - CPU_TYPE_I386 to target the Intel-based Macintosh computers
                 */
                boost::uint32_t m_cputype;

                /*! \brief An integer specifying the exact model of the CPU. To run on all PowerPC or x86 processors
                 *         supported by the Mac OS X kernel, this should be set to CPU_SUBTYPE_POWERPC_ALL or CPU_SUBTYPE_I386_ALL
                 */
                boost::uint32_t m_cpusubtype;

                /*! \brief An integer indicating the usage and alignment of the file. */
                boost::uint32_t m_filetype;

                /*! \brief An integer indicating the number of load commands following the header structure. */
                boost::uint32_t m_ncmds;

                /*! \brief An integer indicating the number of bytes occupied by the load commands following the header structure. */
                boost::uint32_t m_sizeofcmds;

                /*! \brief An integer containing a set of bit flags that indicate the state of certain optional features of the
                 *         Mach-O file format.
                 */
                boost::uint32_t m_flags;

        };

    } /* namespace mach_module */
} /* namespace libreverse */

#endif /* Mach_Header_32_H */
