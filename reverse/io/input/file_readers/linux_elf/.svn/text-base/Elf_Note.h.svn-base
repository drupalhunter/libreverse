/*  Elf_Note.h

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

#ifndef ELF_NOTE_H_
#define ELF_NOTE_H_

#include <boost/cstdint.hpp>

namespace libreverse { namespace elf_module {

  /*!
   * \class Elf_Note
   * \date 2003
   * \author Stephen Torri
   */
  class Elf_Note
  {
  public:

    /*! \brief Default Destructor */
    virtual ~Elf_Note(){}

    /*!
     * \brief Convert the bit ordering from the target file bit ordering
     * to the host system. If the host system and the target file
     * match this is a no-op.
     */
    virtual void convert ();

    /*! \brief Size of entry's owner string */
    boost::uint32_t m_namesz;

    /*! \brief  Size of the note descriptor */
    boost::uint32_t m_descsz;

    /*! \brief Interpretation of the descriptor */
    boost::uint32_t m_type;

    /*! \brief Start of the name+desc data */
    boost::int8_t   m_name;
  };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_NOTE_H_ */
