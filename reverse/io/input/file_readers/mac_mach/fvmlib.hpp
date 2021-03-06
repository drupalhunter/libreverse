/*  Fvmlib.h

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

#ifndef FVMLIB_H
#define FVMLIB_H

#include "Mach_Types.h"

namespace reverse { namespace mach_module {

  class Fvmlib {
  public:

    friend class Mach_File;

    /*! \brief Default Constructor */
    Fvmlib ();

  private:

    /*! \brief Name of the library */
    mach_types::LC_Str::ptr_t m_name;

    /*! \brief ? */
    boost::uint64_t m_minor_version;

  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* FVMLIB_T_H */
