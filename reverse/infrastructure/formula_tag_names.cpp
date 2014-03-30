/*  Formula_Tag_Names.cpp

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

#include <reverse/infrastructure/formula_tag_names.hpp>

namespace libreverse {
  namespace infrastructure {

    std::string const formula_tag_names::TAG_FORMULA_MAP = "formula_map";
    std::string const formula_tag_names::TAG_NODE = "node";
    std::string const formula_tag_names::TAG_PREDECESSORS = "predecessors";
    std::string const formula_tag_names::TAG_NAME = "name";
    std::string const formula_tag_names::TAG_NODE_REF = "node_ref";
    std::string const formula_tag_names::ATTRIBUTE_ID = "id";
    std::string const formula_tag_names::ATTRIBUTE_IDREF = "idref";

  } /* namespace infrastructure */
} /* namespace reverse */
