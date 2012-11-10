/*  Relocation_Info.cpp

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

#include "Relocation_Info.h"

namespace libreverse { namespace mach_module {

  Relocation_Info::Relocation_Info()
    : m_r_address ( 0 ),
      m_r_symbolnum ( 0 ),
      m_r_pcrel ( false ),
      m_r_length ( 0 ),
      m_r_extern ( false ),
      m_r_type ( 0 )
  {}


} /* namespace mach_module */
} /* namespace libreverse */
