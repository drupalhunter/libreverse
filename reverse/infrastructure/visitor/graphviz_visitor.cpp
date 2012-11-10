/*  Graphviz_Visitor.cpp

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

#include "Graphviz_Visitor.h"
#include <boost/graph/topological_sort.hpp>
#include <boost/format.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include "infrastructure/Component.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace visitor {

    void
    Graphviz_Visitor::visit ( infrastructure::Component_Graph const& graph_ref,
                              std::stringstream& output )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Graphviz_Visitor::visit" );
#endif /* LIBREVERSE_DEBUG */

        // Call topological_sort on graph
        typedef std::vector<infrastructure_types::Component_Graph::Vertex_t>
            m_container;

        infrastructure_types::Component_Graph::Vertex_t node;
        infrastructure_types::Component_Graph::Out_Edge_Iterator_t pos;
        infrastructure_types::Component_Graph::Out_Edge_Iterator_t end;

        infrastructure_types::Component_Graph::Graph_t graph_obj = graph_ref.get_Graph();
        infrastructure_types::Component::ptr_t target_obj_ptr;
        infrastructure_types::Component::ptr_t src_obj_ptr;
        m_container comp_list;

        boost::topological_sort ( graph_obj, std::back_inserter ( comp_list ) );

        for ( m_container::reverse_iterator ii = comp_list.rbegin();
              ii != comp_list.rend();
              ++ii )
            {
                src_obj_ptr = graph_ref.get_Component ( *ii );

                std::cout << boost::format("Graphviz_Visitor - discovering %s(%d)")
                    % src_obj_ptr->get_Name()
                    % src_obj_ptr->get_ID()
                          << std::endl;

                // Print out graphviz node for vertex
                output << boost::format("%d [label=\"%s(%d)\"];")
                    % src_obj_ptr->get_ID()
                    % src_obj_ptr->get_Name()
                    % src_obj_ptr->get_ID()
                       << std::endl;
                
                // For all children, print out path from vertex id to child id
                for ( boost::tie ( pos, end ) = out_edges( *ii, graph_obj );
                      pos != end;
                      ++pos )
                    {
                        node = target (*pos, graph_obj );

                        target_obj_ptr = graph_ref.get_Component ( node );

                        output << boost::format("%d -> %d;")
                            % src_obj_ptr->get_ID()
                            % target_obj_ptr->get_ID()
                               << std::endl;
                    }
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Graphviz_Visitor::visit" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace visitor */
} /* namespace libreverse */
