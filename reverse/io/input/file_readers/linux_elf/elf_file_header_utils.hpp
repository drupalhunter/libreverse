/*  Elf_File_Header_Utils.h

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

#ifndef ELF_FILE_HEADER_UTILS_H_
#define ELF_FILE_HEADER_UTILS_H_

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_File_Header_Utils
     * \date 2003
     * \author Stephen Torri
     *
     * A major thanks to Eric Youngdale and Nick Clifton for the nice readelf utility.
     * All functions take and modified from readelf are noted with a message in
     * their description.
     *
     * ----------------------------------------------------------------------------
     * readelf.c -- display contents of an ELF format file
     *  Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.
     *
     *  Originally developed by Eric Youngdale <eric@andante.jic.com>
     *   Modifications by Nick Clifton <nickc@redhat.com>
     *
     *  This file is part of GNU Binutils.
     *-----------------------------------------------------------------------------
     */

    class Elf_File_Header_Utils {
    public:

        /*!
         * \brief Returns the string representation of the file type (e_type)
         *
         * \return String representation of target file type
         *
         * NOTE: Taken from readelf.c
         */
      static std::string get_File_Type_Meta ( boost::uint16_t e_type );

        /*!
         * \brief Returns the string representation of the cpu
         * architecutre of the target file (e_machine)
         *
         * \return String representation of the cpu architecture of the
         * target file
         *
         */
      static std::string get_Arch_Name ( boost::uint16_t e_machine );


        /*!
         * \brief Returns the machine name
         * \return String representation of machine name
         * NOTE: Taken from readelf.c
         */
      static std::string get_Machine_Name ( boost::uint16_t e_machine );

        /*!
         * \brief Returns the machine flags
         * \return String representation of machine flags
         * NOTE: Taken from readelf.c
         */
      static std::string get_Machine_Flags ( boost::uint32_t e_flags,
					     boost::uint16_t e_machine );

        /*!
         * \brief Returns the ARM machine flags
         * \return String representation of ARM machine flags
         * NOTE: Taken from readelf.c
         */
      static std::string decode_ARM_Machine_Flags ( boost::uint32_t e_flags );

      static std::string get_File_Type_Name ( boost::uint16_t e_type );

    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_FILE_HEADER_UTILS_H */
