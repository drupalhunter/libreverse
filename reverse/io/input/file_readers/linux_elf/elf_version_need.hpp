/*  Elf_Version_Need.h

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

#ifndef ELF_VERSION_NEED_H_
#define ELF_VERSION_NEED_H_

#include "io/input/File_Readers/Base_Header.h"

namespace libreverse {
namespace elf_module {

  /*!
   * \class Elf_Version_Need
   * \date 2003
   * \author Stephen Torri
   */
  class Elf_Version_Need : public header::Base_Header {
  public:

    /*!
     * \brief Convert bit ordering
     *
     * Convert the bit ordering from the target file bit ordering
     * to the host system.
     */
    virtual void convert ();

    /*! \brief Version number of structure. */
    boost::uint16_t vn_version;

    /*! \brief Number of vernaux entries.  */
    boost::uint16_t vn_cnt;

    /*! \brief String table offset of library name. */
    boost::uint32_t vn_file;

    /*! \brief Offset to vernaux entries. */
    boost::uint32_t vn_aux;

    /*! \brief Offset to next verneed. */
    boost::uint32_t vn_next;
  };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_VERSION_NEED_H_ */
