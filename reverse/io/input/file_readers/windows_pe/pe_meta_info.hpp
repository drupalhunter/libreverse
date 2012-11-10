/*  PE_meta_info.h

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
#ifndef _PE_META_INFO_H
#define _PE_META_INFO_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse {
  namespace wpef_module {

  class PE_Meta_Info {
  public:

    static const std::string DOS_FILE_TYPE;
    static const std::string PE_FILE_TYPE_32BIT;
    static const std::string PE_FILE_TYPE_64BIT;

  };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* _PE_META_INFO_H */
