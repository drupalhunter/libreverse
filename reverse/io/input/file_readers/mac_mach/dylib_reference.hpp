/*  Dylib_Reference.h

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

#ifndef DYLIB_REFERENCE_H
#define DYLIB_REFERENCE_H

#include "Load_Command.h"

namespace reverse { namespace mach_module {

  class Dylib_Reference {
  public:

    /*! \brief Default Constructor */
    Dylib_Reference();

  private:

    /*! \brief An index into the symbol table for the symbol being referenced. */
    boost::uint32_t m_isym; // bits: 0-23?

    /*! \brief A constant for the type of reference being made. */
    boost::uint32_t m_flags; // bits 24 - 31?

  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* DYLIB_REFERENCE_H */
