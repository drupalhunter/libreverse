/*  Control_Flow_Graph_Graphviz_Visitor.cpp

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

#include "Control_Flow_Graph_Graphviz_Visitor.h"
#include "data_containers/Basic_Block.h"
#include "data_containers/Instruction.h"
#include <boost/graph/topological_sort.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace visitor {

    void
    Control_Flow_Graph_Graphviz_Visitor::visit ( data_container::Control_Flow_Graph const& graph_ref,
						 std::stringstream& output )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph_Graphviz_Visitor::visit" );

        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
                             "Dump of input Control flow Graph" );

	Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
			     graph_ref.to_String() );
#endif /* LIBREVERSE_DEBUG */

        data_types::Control_Flow_Graph::Vertex_t node;
        data_types::Control_Flow_Graph::Out_Edge_Iterator_t pos;
        data_types::Control_Flow_Graph::Out_Edge_Iterator_t end;

        data_types::Control_Flow_Graph::Graph_t graph_obj = graph_ref.get_Graph();
        data_types::Basic_Block::ptr_t target_obj_ptr;
        data_types::Basic_Block::ptr_t src_obj_ptr;

	// Write digraph header
	output << "Digraph CFG {" << std::endl;

	// NEW algorithm
	// - Get handle to first and last vertex
	// - For each vertex
	data_types::Control_Flow_Graph::Vertex_Iterator_t vertex_pos;
	data_types::Control_Flow_Graph::Vertex_Iterator_t vertex_end;
	for ( boost::tie ( vertex_pos, vertex_end ) = vertices ( graph_obj );
	      vertex_pos != vertex_end;
	      ++vertex_pos )
	  {



#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Basic block index: %1%" ) % *vertex_pos ) );
#endif /* LIBREVERSE_DEBUG */


	    //   - Print out basic block
	    src_obj_ptr = graph_ref.get_Basic_Block ( *vertex_pos );

	    // Print out graph_graphviz node for vertex
	    output << this->write_Basic_Block ( src_obj_ptr );

	    //   - If vertex has children, print out edges
	    // For all children, print out path from vertex id to child id
	    for ( boost::tie ( pos, end ) = out_edges( *vertex_pos, graph_obj );
		  pos != end;
		  ++pos )
	      {
		node = target ( *pos, graph_obj );
		
		target_obj_ptr = graph_ref.get_Basic_Block ( node );
		
		output << boost::format("%d -> %d;")
		  % src_obj_ptr->get_ID()
		  % target_obj_ptr->get_ID()
		       << std::endl;
	      }
	  }

	// Write digraph footer
	output << "}" << std::endl;

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Control_Flow_Graph_Graphviz_Visitor::visit" );
#endif /* LIBREVERSE_DEBUG */
    }

    std::string
    Control_Flow_Graph_Graphviz_Visitor::write_Basic_Block ( data_types::Basic_Block::ptr_t src_obj_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Control_Flow_Graph_Graphviz_Visitor::visit" );
#endif /* LIBREVERSE_DEBUG */

	std::stringstream output;

	output << boost::format("%d [shape=box,label=\"" ) % src_obj_ptr->get_ID();
	
	for ( data_types::Basic_Block::DataList_t::iterator pos = src_obj_ptr->begin();
	      pos != src_obj_ptr->end();
	      ++pos )
	  {
	    output << (*pos)->to_String() << "\\l";
	  }

	output << "\"];" << std::endl;

	return output.str();
    }


} /* namespace visitor */
} /* namespace reverse */
