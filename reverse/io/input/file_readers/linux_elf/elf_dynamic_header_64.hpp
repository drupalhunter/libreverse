/*  Elf_Dynamic_Header_64.h

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

#ifndef ELF_DYNAMIC_HEADER_64_H
#define ELF_DYNAMIC_HEADER_64_H

#include "Elf_Types.h"
#include "io/input/File_Readers/Base_Header.h"
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Dynamic_Header_64
     * \date 2003
     * \author Stephen Torri
     */
    class Elf_Dynamic_Header_64 : public header::Base_Header {

    public:

        /*!
         * \brief Convert bit ordering
         * Convert the bit ordering from the target file bit ordering
         * to the host system.
         */
        virtual void convert ();

        /*!
         * \brief Return the contents of Elf_Dynamic_Header as a screen
         * \return String represenation of contents of Elf_Dynamic_Header
         */
        virtual std::string toString (void);

        elf_types::Elf_Dynamic_Header_64::Tag_List_t m_dyn_tags;

    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_DYNAMIC_HEADER_64_H */
