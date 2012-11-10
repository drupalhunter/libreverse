/*  Elf_Symbol_Info.h

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

#ifndef ELF_SYMBOL_INFO_H_
#define ELF_SYMBOL_INFO_H_

#include "io/Type_Mapper.h"
#include "io/input/File_Readers/Base_Header.h"

namespace elf_module {

/*!
 * \class Elf_Symbol_Info
 * \date 2003
 * \author Stephen Torri
 */
class Elf_Symbol_Info : public libreverse::header::Base_Header {
 public:

  /*! \brief Symbol info section item: Define */
  boost::uint16_t si_boundto;

  /*! \brief Symbol info section flags: Define */
  boost::uint16_t si_flags;
};

} /* Namespace elf */

#endif /* ELF_SYMBOL_INFO_H_ */
