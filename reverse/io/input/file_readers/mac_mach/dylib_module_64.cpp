/*  Dylib_Module_64.cpp

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

#include "Dylib_Module_64.h"

namespace reverse { namespace mach_module {

  Dylib_Module_64::Dylib_Module_64 ()
    : m_module_name ( 0 ),
    m_iextdefsym ( 0 ),
    m_nextdefsym ( 0 ),
    m_irefsym ( 0 ),
    m_nrefsym ( 0 ),
    m_ilocalsym ( 0 ),
    m_nlocalsym ( 0 ),
    m_iextrel ( 0 ),
    m_nextrel ( 0 ),
    m_iinit_iterm ( 0 ),
    m_ninit_iterm ( 0 ),
    m_objc_module_info_addr ( 0 ),
    m_objc_module_info_size ( 0 )
  {}

} /* namespace mach_module */
} /* namespace reverse */
