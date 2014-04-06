/*  Control_Flow_Graph.h

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

#ifndef REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_HPP_INCLUDED
#define REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_HPP_INCLUDED

#include <reverse/data_containers/basic_block.hpp>

#include <boost/graph/adjacency_list.hpp>

#include <string>

namespace reverse {
  namespace data_containers {

    class control_flow_graph
    {
    public:

      /*! \brief Each Vertex will contain a Basic Block object */
      typedef boost::property< boost::vertex_name_t,
			       boost::shared_ptr<basic_block> >
      vertex_property_t;

      /*! \brief A graph type is a directed graph of Basic Blocks. */
      typedef boost::adjacency_list<boost::vecS, // OutEdgeList
				    boost::vecS, // VertexList
				    boost::directedS, // Directed
				    vertex_property_t> // vertex properties
      graph_t;

      /*! \brief Reverse loop up map to the Basic Block object stored in the Graph.
       *
       * key = Graph object
       *
       * value = Graph vertex node associated with the target object.
       *       
       */
      typedef boost::property_map<graph_t, boost::vertex_name_t>::type
      basic_block_map_t;

      /*! \brief Iterator for Vertices */
      typedef boost::graph_traits<graph_t>::vertex_descriptor
      vertex_t;

      /*! \brief Iterator for Edges */
      typedef boost::graph_traits<graph_t>::edge_descriptor
      edge_t;

      /*! \brief Data type used to obtain the results of adding an
          edge to a graph. At present the first value to the Edge
          iterator is not used. Only the bool value which indicates
          successful entry (TRUE) or a duplicate was found (FALSE) is
          used when the debug build is enabled.
       */
      typedef std::pair< edge_t, bool>
      add_edge_result_t;

      /*! \brief Data type used to associated the id with the Vertex
       * containing the desired Basic Block Object.
       *
       * key = Component ID
       * value = Graph Vertex containing Basic Block
       */
      typedef std::map<boost::uint32_t, vertex_t>
      id_vertex_map_t;

      /*! \brief Iterator for Edges coming into a Vertex. */
      typedef boost::graph_traits<graph_t>::in_edge_iterator
	in_edge_iterator_t;

      /*! \brief Iterator for Edges leaving a Vertex. */
      typedef boost::graph_traits<graph_t>::out_edge_iterator
	out_edge_iterator_t;

      /*! \brief Iterator for Vertex in the Control Flow Graph. */
      typedef boost::graph_traits<graph_t>::vertex_iterator
	vertex_iterator_t;


      explicit control_flow_graph ( std::string name );

      control_flow_graph ( control_flow_graph const& rhs );

      void add_basic_block ( boost::shared_ptr<basic_block>& input_block_ptr );

      void add_edge ( boost::uint32_t source_id,
		      boost::uint32_t destination_id );

      virtual ~control_flow_graph (){}

      boost::shared_ptr < basic_block > get_basic_block ( vertex_t node ) const;

      graph_t const& get_graph (void) const;

      bool empty () const;

      control_flow_graph& operator= ( control_flow_graph const& rhs );

      void swap ( control_flow_graph& rhs );

      vertex_t const& get_vertex ( boost::uint32_t id ) const;

      graph_t::vertices_size_type size () const;

      std::string get_name () const;
      
      id_vertex_map_t::const_iterator vertex_begin() const;
      
      id_vertex_map_t::const_iterator vertex_end() const;

    private:

      std::string m_name;

      graph_t m_graph;

      id_vertex_map_t m_index;
      
      basic_block_map_t m_basic_block_map;
    };
    
    std::ostream& operator<< ( std::ostream& os, control_flow_graph const& rhs );

  } // namespace data_containers
} // namespace reverse

#endif // #ifndef REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_HPP_INCLUDED

