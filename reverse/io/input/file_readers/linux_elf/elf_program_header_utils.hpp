/*  Elf_Program_Header_Utils.h

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

#ifndef ELF_PROGRAM_HEADER_UTILS_H
#define ELF_PROGRAM_HEADER_UTILS_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Program_Header_Utils
     * \date 2008
     * \author Stephen Torri
     *
     * (Elf) = Executable and Linkable Format specification
     */
    class Elf_Program_Header_Utils
    {
    public:

      static std::string get_segment_type ( boost::uint32_t type_value,
					    boost::uint16_t machine_arch );

      static std::string get_mips_segment_type ( boost::uint32_t type_value );

      static std::string get_parisc_segment_type ( boost::uint32_t type_value );

      static std::string get_ia64_segment_type ( boost::uint32_t type_value );

    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_PROGRAM_HEADER_UTILS_H */
