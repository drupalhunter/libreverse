/*  Elf_Header_Eident.h

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

#ifndef ELF_HEADER_EIDENT_
#define ELF_HEADER_EIDENT_

#include "Elf_Common.h"
#include "Elf_Types.h"
#include <boost/shared_ptr.hpp>
#include <string>

namespace libreverse
{
    namespace elf_module
    {

        /*!
         * \class Elf_Header_Eident
         * \date 2004
         * \author Stephen Torri
         */
        class Elf_Header_Eident
        {

                friend class Elf_File;

            public:

                Elf_Header_Eident ();

                bool is_Elf_File ();

                bool is_Little_Endian ( void );

                bool is_32bit ( void );

                //! \brief Default ELF magic number size
                static const boost::uint8_t SIZE;
                static const boost::uint32_t ELF_MAGIC;

                std::string to_String ( void );

                //!
                // \brief Returns the string representation of the elf class
                // \return String representation of Elf class type
                // NOTE: Taken from readelf.c

                std::string get_Elf_Class ( void );

                //!
                // \brief Returns the string representation of the data encoding
                // \return String representation of data encoding
                // NOTE: Taken from readelf.c

                std::string get_Data_Encoding ( void );

                //!
                // \brief Returns the string representation of the version
                // \return String representation of elf version
                // NOTE: Taken from readelf.c

                std::string get_Version ( void );

                //!
                // \brief Returns the string representation of the OS ABI
                // \return String representation of OS ABI
                // NOTE: Taken from readelf.c
                std::string get_Osabi_Name ( void );

            private:

                //! \brief ELF "magic number"
                boost::uint32_t m_magic;

                //! \brief ELF class type
                boost::uint8_t m_class;

                //! \brief ELF data encoding
                boost::uint8_t m_data_encoding;

                //! \brief ELF file version
                boost::uint8_t m_file_version;

                //! \brief Operating system/ABI indication
                boost::uint8_t m_os_abi;

                //! \brief ABI version
                boost::uint8_t m_abi_version;

        };
    } /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_HEADER_EIDENT_ */
