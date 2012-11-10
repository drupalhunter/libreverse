/*  Dylib_Table_Of_Contents.cpp

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

#include "Dylib_Table_Of_Contents.h"

namespace libreverse { namespace mach_module {

  Dylib_Table_Of_Contents::Dylib_Table_Of_Contents ()
    : m_symbol_index ( 0 ),
      m_module_index ( 0 )
  {}

} /* namespace mach_module */
} /* namespace libreverse */
