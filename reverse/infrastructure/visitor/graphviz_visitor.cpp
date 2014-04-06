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

#include <reverse/infrastructure/visitor/graphviz_visitor.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/trace.hpp>

#include <boost/graph/topological_sort.hpp>
#include <boost/format.hpp>

#include <fstream>

namespace reverse {
    namespace infrastructure {
        namespace visitor {

            void
            graphviz_visitor::visit ( infrastructure::component_graph const& graph_ref,
                                      std::stringstream& output )
            {
                trace::infrastructure_detail ( "Entering Graphviz_Visitor::visit" );

                // Call topological_sort on graph
                typedef std::vector<infrastructure::component_graph::vertex_t> m_container;

                infrastructure::component_graph::vertex_t node;
                infrastructure::component_graph::out_edge_iterator_t pos;
                infrastructure::component_graph::out_edge_iterator_t end;

                infrastructure::component_graph::graph_t graph_obj = graph_ref.get_graph();
                m_container comp_list;

                boost::topological_sort ( graph_obj, std::back_inserter ( comp_list ) );

                for ( m_container::reverse_iterator ii = comp_list.rbegin();
                        ii != comp_list.rend();
                        ++ii ) {

                    boost::shared_ptr < infrastructure::component > src_obj_ptr = graph_ref.get_component ( *ii );

                    std::cout << boost::format ( "Graphviz_Visitor - discovering %s(%d)" )
                              % src_obj_ptr->get_name()
                              % src_obj_ptr->get_id()
                              << std::endl;

                    // Print out graphviz node for vertex
                    output << boost::format ( "%d [label=\"%s(%d)\"];" )
                           % src_obj_ptr->get_id()
                           % src_obj_ptr->get_name()
                           % src_obj_ptr->get_id()
                           << std::endl;

                    // For all children, print out path from vertex id to child id
                    for ( boost::tie ( pos, end ) = out_edges ( *ii, graph_obj );
                            pos != end;
                            ++pos ) {
                        node = target ( *pos, graph_obj );

                        boost::shared_ptr < infrastructure::component > target_obj_ptr = graph_ref.get_component ( node );

                        output << boost::format ( "%d -> %d;" )
                               % src_obj_ptr->get_id()
                               % target_obj_ptr->get_id()
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
    } /* namespace infrastructure */
} /* namespace reverse */
