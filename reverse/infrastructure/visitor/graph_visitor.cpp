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

#include "Graph_Visitor.h"
#include <boost/graph/topological_sort.hpp>
#include <boost/format.hpp>
#include <iostream>
#include "infrastructure/Component.h"

#include "Assert.h"
using namespace libreverse::assert;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace visitor {

    void
    Graph_Visitor::visit ( infrastructure::Component_Graph const& graph_ref,
                           infrastructure_types::Component_Graph::Data_Map_t* data_map )

    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Graph_Visitor::visit" );
#endif /* LIBREVERSE_DEBUG */


        // Size of data_map should be 1
        Assert::bool_check ( data_map->size() == 1, "data_map.size() == 1" );

        // data_map.first must be set to 0
        Assert::bool_check ( (*data_map->begin()).first == 0, "(*data_map->begin()).first == 0" );

        // results = data_map.second
        //   val = initialized Data_Source_Base object
        //#error Check here to see if the Data_Source_Base ptr in the shared_ptr is not set to 0x0. If its not null here then
        // where is it being set?
        Assert::null_check ( (((data_map->begin())->second).first).get(), " (((data_map->begin())->second).first.get())" );
        
        //   count = number of children nodes
        Assert::bool_check ( ((*data_map->begin()).second).second == 1, "(data_map.second).second != 1" );

        typedef std::vector<infrastructure_types::Component_Graph::Vertex_t>
            m_container;

        infrastructure_types::Component_Graph::Out_Edge_Iterator_t pos;
        infrastructure_types::Component_Graph::Out_Edge_Iterator_t end;
        infrastructure_types::Component_Graph::Vertex_t node;
        infrastructure_types::Component::ptr_t target_obj_ptr;
        infrastructure_types::Component_Graph::Graph_t graph_obj = graph_ref.get_Graph();

        infrastructure_types::Component::ptr_t src_obj_ptr;
        m_container comp_list;

        boost::topological_sort ( graph_obj, std::back_inserter ( comp_list ) );

        for ( m_container::reverse_iterator ii = comp_list.rbegin();
              ii != comp_list.rend();
              ++ii )
            {
                src_obj_ptr = graph_ref.get_Component(*ii);

                std::cout << "Visiting node: " << src_obj_ptr->get_ID() << std::endl;

                src_obj_ptr->run ( data_map );

                infrastructure_types::Component_Graph::Degree_Size_t num_children =
                    out_degree ( *ii, graph_obj );

                std::cout << boost::format("  Node(%d) - children: %d")
                    % src_obj_ptr->get_ID()
                    % num_children << std::endl;

                // Save results
                infrastructure_types::Component_Graph::Result_Data_t result_data =
                    std::make_pair ( src_obj_ptr->results(), num_children );

                data_map->insert ( std::make_pair ( src_obj_ptr->get_ID(),
                                                    result_data ) );


                // Initialize children
                for ( boost::tie ( pos, end ) = out_edges ( *ii, graph_obj );
                      pos != end;
                      ++pos )
                    {
                        node = target ( *pos, graph_obj );

                        target_obj_ptr = graph_ref.get_Component ( node );

                        target_obj_ptr->received_Input_Source_Data
                            ( src_obj_ptr->get_ID() );
                    }
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Graph_Visitor::visit" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace visitor */
} /* namespace libreverse */
