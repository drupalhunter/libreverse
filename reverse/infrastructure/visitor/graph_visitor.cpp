/*  Graph_Visitor.cpp

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

#include <reverse/infrastructure/visitor/graph_visitor.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/assert/assert.hpp>
#include <reverse/trace.hpp>

#include <boost/graph/topological_sort.hpp>

namespace reverse {
    namespace infrastructure {
        namespace visitor {

            void
            graph_visitor::visit ( reverse::infrastructure::component_graph const& graph_ref,
                                   infrastructure::component_graph::data_map_t* dmap )

            {
                trace::infrastructure_detail ( "Entering Graph_Visitor::visit" );

                // Size of data_map should be 1
                assert::bool_check ( dmap->size() == 1, "dmap->size() == 1" );

                // data_map.first must be set to 0
                assert::bool_check ( ( *dmap->begin() ).first == 0, "(*dmap->begin()).first == 0" );

                // results = data_map.second
                //   val = initialized Data_Source_Base object
                //#error Check here to see if the Data_Source_Base ptr in the shared_ptr is not set to 0x0. If its not null here then
                // where is it being set?
                assert::null_check ( ( ( ( dmap->begin() )->second ).first ).get(), " (((dmap->begin())->second).first.get())" );

                //   count = number of children nodes
                assert::bool_check ( ( ( *dmap->begin() ).second ).second == 1, "(dmap.second).second != 1" );

                typedef std::vector<infrastructure::component_graph::vertex_t>
                m_container;

                infrastructure::component_graph::out_edge_iterator_t pos;
                infrastructure::component_graph::out_edge_iterator_t end;
                infrastructure::component_graph::vertex_t node;
                infrastructure::component_graph::graph_t graph_obj = graph_ref.get_graph();

                m_container comp_list;

                boost::topological_sort ( graph_obj, std::back_inserter ( comp_list ) );

                for ( m_container::reverse_iterator ii = comp_list.rbegin();
                        ii != comp_list.rend();
                        ++ii ) {
                    boost::shared_ptr < infrastructure::component > src_obj_ptr = graph_ref.get_component ( *ii );

                    trace::infrastructure_data ( "Visiting node: %1%", src_obj_ptr->get_id() );

                    src_obj_ptr->run ( dmap );

                    infrastructure::component_graph::degree_size_t num_children = out_degree ( *ii, graph_obj );

                    trace::infrastructure_data ( "  Node(%d) - children: %d",
                                                 src_obj_ptr->get_id(),
                                                 num_children );

                    // Save results
                    infrastructure::component_graph::result_data_t result_data =
                        std::make_pair ( src_obj_ptr->results(), num_children );

                    dmap->insert ( std::make_pair ( src_obj_ptr->get_id(),
                                                    result_data ) );


                    // Initialize children
                    for ( boost::tie ( pos, end ) = out_edges ( *ii, graph_obj );
                            pos != end;
                            ++pos ) {
		      
                        node = target ( *pos, graph_obj );

                        boost::shared_ptr < infrastructure::component > target_obj_ptr = graph_ref.get_component ( node );

                        target_obj_ptr->received_input_source_data ( src_obj_ptr->get_id() );
                    }
                }

                trace::infrastructure_detail ( "Exiting Graph_Visitor::visit" );

            }

        } /* namespace visitor */
    } /* namespace infrastructure */
} /* namespace reverse */
