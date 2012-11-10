/*  Elf_Relocation_Utils.h

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

#ifndef ELF_RELOCATION_UTILS_H
#define ELF_RELOCATION_UTILS_H

#include <string>
#include <boost/cstdint.hpp>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Relocation_Utils
     * \date 2003
     * \author Stephen Torri
     */
    class Elf_Relocation_Utils {
    public:

        /*!
         * \brief Return type name
	 * \param machine_value CPU of the target
	 * \param reloc_type Relocation type
         * \return String representation of section header type
         */
      static std::string get_Section_Type_Name ( boost::uint16_t machine_value,
						 boost::uint8_t reloc_type,
						 boost::uint8_t bitsize );

    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_RELOCATION_UTILS_H */
