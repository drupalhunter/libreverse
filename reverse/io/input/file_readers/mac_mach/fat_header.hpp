/*  Fat_Header.h

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

#ifndef FAT_HEADER_H_
#define FAT_HEADER_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include "errors/IO_Exception.h"
#include <vector>
#include "Mach_Types.h"

namespace reverse
{
    namespace mach_module
    {

        /*!
         * \class Header
         * \date 2003
         * \author Stephen Torri
         */
        class Fat_Header : public header::Base_Header
        {

            public:

                enum Values
                {
                    FAT_MAGIC = 0xCAFEBABE,
                    FAT_CIGAM = 0xBEBAFECA
                };

                /*!
                 * \brief Default Constructor
                 */
                Fat_Header();

                /*!
                 * \brief Default Destructor
                 */
                virtual ~Fat_Header() {}

                /*!
                 * \brief Initialize Header
                 */
                virtual void init ( void );

                /*!
                 * \brief Get header bit size
                 * \return Unsigned integer representation of bit size
                 */
                virtual boost::uint32_t get_size ( void ) const;

                /*!
                 * \brief Change the bit-ordering if required
                 */
                virtual void convert ();

                /* FALSE = Same endian type as the CPU
                   TRUE = Different endian type from the CPU
                */
                bool needs_Convert ( void ) const;

                /*!
                 * \brief String representation of MACH Header
                 * \return String output of header
                 */
                std::string const to_String ( void ) const;

                /*!
                 * \brief Detect if file is Fat file
                 * \return Boolean value if file is a Fat file (TRUE) or not.
                 */
                bool is_Fat_File ( void ) const;

                /*!
                 * \brief Get Magic Number
                 * \return Unsigned integer representing magic number
                 */
                boost::uint32_t get_Magic ( void ) const;

                /*!
                 * \brief Get number of fat arch headers
                 * \return Unsigned integer representing the total number of fat arch headers
                 */
                boost::uint32_t get_Number_Of_Fat_Arch ( void ) const;

            private:

                friend class Mach_File;

                /*! \brief An integer containing the value 0xCAFEBABE in big-endian byte order format. On a big-endian
                 *         host CPU, this can be validated using the constant FAT_MAGIC; on a little-endian host CPU, it
                 *         can be validated using the constant FAT_CIGAM.
                 */
                boost::uint32_t m_magic;

                /*! \brief An integer specifying the number of fat_arch (page 59) data structures that follow. This is
                 *         the number of architectures contained in this binary.
                 */
                boost::uint32_t m_nfat_arch;

        };

    } /* namespace mach_module */
} /* namespace reverse */

#endif /* FAT_HEADER_H_ */
