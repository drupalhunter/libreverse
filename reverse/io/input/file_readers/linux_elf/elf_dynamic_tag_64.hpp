/*  Elf_Dynamic_Tag_64.h

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

#ifndef ELF_DYNAMIC_TAG_64_H
#define ELF_DYNAMIC_TAG_64_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace elf_module {

  class Elf_Dynamic_Tag_64
  {
  public:

    void convert (void);

    std::string to_String ();

    /*! \brief Entry tag value */
    boost::uint64_t d_tag;

    /*! \brief Dynamic section structure. Uknown usage */
    /* NOTE: Since both variables are the same size and type
     *       we are going to replace both with one for now
     * union {
     *   typename Type_Mapper<bitsize>::arch_t	d_val;
     *   typename Type_Mapper<bitsize>::arch_t	d_ptr;
     * } d_un;
     */
    boost::uint64_t d_un;
  };


} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_DYNAMIC_TAG_64_H */
