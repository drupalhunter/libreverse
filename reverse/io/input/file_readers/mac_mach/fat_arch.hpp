/*  Fat_Arch.h

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

#ifndef FAT_ARCH_H_
#define FAT_ARCH_H_

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse
{
    namespace mach_module
    {

        /*!
         * \class Arch
         * \date 2003
         * \author Stephen Torri
         */
        class Fat_Arch
        {
            public:

                /*!
                 * \brief Default Constructor
                 */
                Fat_Arch();

                /*!
                 * \brief Default Destructor
                 */
                ~Fat_Arch() {}

                /*!
                 * \brief Change the bit-ordering if required
                 */
                void convert ();

                /*!
                 * \brief String representation of MACH Arch
                 * \return String output of header
                 */
                std::string const to_String ( void ) const;

                /*!
                 * \brief Get cpu type
                 * \return Unsigned integer representing CPU type
                 */
                boost::uint32_t get_CPU_Type ( void ) const;

                /*!
                 * \brief Get cpu subtype
                 * \return Unsigned integer representing CPU sub-type
                 */
                boost::uint32_t get_CPU_SubType ( void ) const;

                /*!
                 * \brief Get offset
                 * \return Unsigned integer representing offset value
                 */
                boost::uint32_t get_Offset ( void ) const;

                /*!
                 * \brief Get size of mach header
                 * \return Unsigned integer representing header size (bytes)
                 */
                boost::uint32_t get_Header_Size ( void ) const;

                /*!
                 * \brief Get memory alignment
                 * \return Unsigned integer representing memory alignment (bytes)
                 */
                boost::uint32_t get_Alignment ( void ) const;

                /*! \brief Return a boolean if the header is 64-bit (TRUE) or not (FALSE)
                 * \return Boolean value indicating 64-bit header attribute
                 */
                bool is_64bit ( void ) const;

            private:

                friend class Mach_File;

                /*! \brief An enumeration value of type cpu_type_t. Specifies the CPU family. */
                boost::uint32_t m_cputype;

                /*! \brief An enumeration value of type cpu_subtype_t. Specifies the specific member of the CPU family
                 *         on which this entry may be used or a constant specifying all members.
                 */
                boost::uint32_t m_cpu_subtype;

                /*! \brief Offset to the beginning of the data for this CPU. */
                boost::uint32_t m_offset;

                /*! \brief Size of the data for this CPU. */
                boost::uint32_t m_size;

                /*! \brief The power of 2 alignment for the offset of the object file for the architecture specified in cputype
                 *         within the binary. This is required to ensure that, if this binary is changed, the contents it retains
                 *         are correctly aligned for virtual memory paging and other uses.
                 */
                boost::uint32_t m_align;

        };

    } /* namespace mach_module */
} /* namespace libreverse */

#endif /* FAT_ARCH_H_ */
