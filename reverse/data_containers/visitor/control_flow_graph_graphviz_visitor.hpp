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

#ifndef CONTROL_FLOW_GRAPH_GRAPHVIZ_VISITOR_H_
#define CONTROL_FLOW_GRAPH_GRAPHVIZ_VISITOR_H_

#include <sstream>
#include "data_containers/Control_Flow_Graph.h"

namespace libreverse { namespace visitor {

    class Control_Flow_Graph_Graphviz_Visitor
    {
    public:

      void visit ( data_container::Control_Flow_Graph const& graph_ref,
		   std::stringstream& output );

    private:

      std::string write_Basic_Block ( data_types::Basic_Block::ptr_t bb_ptr );

    };

} /* namespace visitor */
} /* namespace libreverse */

#endif /* CONTROL_FLOW_GRAPH_GRAPHVIZ_VISITOR_H_ */
