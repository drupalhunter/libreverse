/*  Formula_Tag_Names.h

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

#ifndef REVERSE_INFRASTRUCTURE_FORMULA_TAG_NAMES_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_FORMULA_TAG_NAMES_HPP_INCLUDED

#include <string>

namespace breverse {
  namespace infrastructure {

    class formula_tag_names {
    public:
        static std::string const TAG_FORMULA_MAP;
        static std::string const TAG_NODE;
        static std::string const TAG_PREDECESSORS;
        static std::string const TAG_NAME;
        static std::string const TAG_NODE_REF;
        static std::string const ATTRIBUTE_ID;
        static std::string const ATTRIBUTE_IDREF;

    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_FORMULA_TAG_NAMES_HPP_INCLUDED */

