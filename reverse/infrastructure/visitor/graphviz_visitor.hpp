/*  Graphviz_Visitor.h

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

#ifndef REVERSE_INFRASTRUCTURE_VISITOR_GRAPHVIZ_VISITOR_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_VISITOR_GRAPHVIZ_VISITOR_HPP_INCLUDED

#include <reverse/infrastructure/component_graph.hpp>

#include <sstream>

namespace reverse {
  namespace infrastructure {
    namespace visitor {

      class graphviz_visitor
      {
      public:

        static void visit ( infrastructure::component_graph const& graph_ref,
                            std::stringstream& output );
      };

    } // namespace visitor
  } // namespace infrastructure 
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_VISITOR_GRAPHVIZ_VISITOR_HPP_INCLUDED
