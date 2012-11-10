/*  GRNN_Data_Tag_Names.h

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

#ifndef GRNN_DATA_TAG_NAMES_H
#define GRNN_DATA_TAG_NAMES_H

#include <string>

namespace libreverse {
namespace infrastructure {

    class GRNN_Data_Tag_Names {
    public:
        static std::string const TAG_GRNN_DATA;
        static std::string const TAG_ENTRY;
        static std::string const ATTRIBUTE_TYPE;
        static std::string const ATTRIBUTE_SIGMA;

    };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* GRNN_DATA_TAG_NAMES_H */

