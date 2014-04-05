/*  Mach_Header_Flags.h

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

#ifndef MACH_HEADER_FLAGS_H
#define MACH_HEADER_FLAGS_H

namespace reverse { namespace mach_module {

  class Mach_Header_Flags {
  public:

    enum Values {
      MH_NOUNDEFS,
      MH_INCRLINK,
      MH_DYLDLINK,
      MH_TWOLEVEL,
      MH_BINDATLOAD,
      MH_PREBOUND,
      MH_PREBINDABLE,
      MH_NOFIXPREBINDING,
      MH_ALLMODSBOUND,
      MH_CANONICAL,
      MH_SPLIT_SEGS,
      MH_FORCE_FLAT,
      MH_SUBSECTIONS_VIA_SYMBOLS,
      MH_NOMULTIDEFS
    };

  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* MACH_HEADER_FLAGS_H */
