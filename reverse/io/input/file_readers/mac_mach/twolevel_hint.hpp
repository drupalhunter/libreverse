/*  Twolevel_Hint.h

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

#ifndef TWOLEVEL_HINT_H
#define TWOLEVEL_HINT_H

#include "Load_Command.h"
#include <vector>

namespace reverse { namespace mach_module {

  class Twolevel_Hint {
  public:

    Twolevel_Hint();

  private:

    boost::uint32_t m_isubimage; // bits: 0-8?
    boost::uint32_t m_itoc; // bits 9 - 31?

  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* TWOLEVEL_HINT_H */
