/*  Elf_Version_Aux.h

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

#ifndef ELF_VERSION_AUX_H_
#define ELF_VERSION_AUX_H_

#include "io/input/File_Readers/Base_Header.h"

namespace libreverse {
namespace elf_module {

  /*!
   * \class Elf_Version_Aux
   * \date 2003
   * \author Stephen Torri
   */
  class Elf_Version_Aux : public header::Base_Header {
  public:

    /*!
     * \brief Convert the bit ordering from the target file bit ordering
     * to the host system.
     */
    virtual void convert ();

    /*! \brief String table offset of name */
    boost::uint32_t vda_name;

    /*! \brief Offset to next verdaux */
    boost::uint32_t vda_next;
  };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_VERSION_AUX_H_ */
