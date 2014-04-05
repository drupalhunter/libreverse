/*  Component_Graph.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_GRAPH_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_GRAPH_HPP_INCLUDED

#include <boost/graph/adjacency_list.hpp>
#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace infrastructure {

    class component;
    class component_data;
    
  } // namespace infrastructure
} // namespace reverse

namespace reverse {
  namespace infrastructure {

    class component_graph {
    public:

      /*! \brief each vertex will contain a component object */
      typedef boost::property< boost::vertex_name_t,
			       boost::shared_ptr < infrastructure::component> > vertex_property_t;

      /*! \brief a graph type is a directed graph of components. */
      typedef boost::adjacency_list<boost::vecS, // outedgelist
				    boost::vecS, // vertexlist
				    boost::directedS, // directed
				    vertex_property_t> // vertexproperties
      graph_t;

      /*! \brief data type is used keep track of the output data from each component.
       *
       * \todo investigate further why we care about the number of
       * children needing the results. initial thoughts are that this
       * is second value is unnecessary.
       */
      typedef std::pair< boost::shared_ptr < const infrastructure::component_data >,
			 graph_t::degree_size_type >
      result_data_t;

      /*! \brief data type used to keep the results of data from each
	component.
	*
	*  key = component id
	*
	*  value = result_data_t pair
	*/
      typedef std::map<boost::uint32_t, result_data_t> data_map_t;

      /*! \brief map type for storing graphs from the individual formula files
       *
       * each map is composed of a:
       *
       *    "input", component_graph (input)
       *    "analysis", component_graph (analysis)
       *    "output", component_graph (output)
       */
      typedef std::map<std::string, boost::shared_ptr < component_graph > > map_t;

      /*! \brief iterator for vertices */
      typedef boost::graph_traits<graph_t>::vertex_descriptor
      vertex_t;

      /*! \brief iterator for edges */
      typedef boost::graph_traits<graph_t>::edge_descriptor
      edge_t;
     
      /*! \brief reverse loop up map to the component object stored in the graph.
       *
       * key = graph object
       *
       * value = graph vertex node associated with the target object.
       *       
       */
      typedef boost::property_map<graph_t, boost::vertex_name_t>::type
      component_map_t;

      /*! \brief iterator for edges coming into a vertex */
      typedef boost::graph_traits<graph_t>::in_edge_iterator
      in_edge_iterator_t;

      /*! \brief iterator for edges leaving a vertex */
      typedef boost::graph_traits<graph_t>::out_edge_iterator
      out_edge_iterator_t;

      /*! \brief data type used to associated the component id with
       * the vertex containing the desire component object. 
       *
       * key = component id
       * value = graph vertex containing component
       */
      typedef std::map<boost::uint32_t, vertex_t> idvertexmap_t;

      /*! \brief data type containing the start and end iterator for the input edges.
       *
       * \todo this should probably be removed.
       * \deprecated
       */
      typedef std::pair<in_edge_iterator_t,
			in_edge_iterator_t> input_edge_list_t;

      /*! \brief data type containing the pointer to all the component
       * objects in the graph.
       */
      typedef std::vector < boost::shared_ptr < infrastructure::component > > component_list_t;

      /*! \brief data type for the number of edges in or out of a vertex.
       *
       * \todo this should probably be removed.
       * \deprecated
       */
      typedef boost::graph_traits<graph_t>::degree_size_type
      degree_size_t;

      explicit component_graph ();

      component_graph ( component_graph const& rhs );

      void add_component ( boost::shared_ptr < infrastructure::component > & obj_ptr );

      void add_child ( boost::uint32_t parent_id,
		       infrastructure::component_graph::vertex_t& child_node );

      component_graph::component_list_t
      get_parent_list ( component_graph::vertex_t const& v_ref );

      component_graph::component_list_t get_parent_list ( boost::uint32_t id );

      // setup the source component for the whole graph
      // this is used from within the reverse class after the configurator
      // has pieced together the entire component_graph from the three
      // individual files (input, analysis, and output)
      // it should not be used for anything else.
      //
      // note: change input to accept a component ptr. this pointer will
      // be for the data input to this graph. it is necessary so that the
      // precodition visitor will be able to check the root component (id 1)
      // has the right input from the data input (id 0). add pointer via
      // add_component to position 0
      void initialize_source ( boost::shared_ptr < infrastructure::component >& source_ptr );

      component_graph::graph_t const& get_graph () const;

      boost::shared_ptr < infrastructure::component > get_component ( component_graph::vertex_t const& node ) const;

      boost::shared_ptr < infrastructure::component > get_end_component (void) const;

      component_graph::vertex_t const& get_vertex ( boost::uint32_t id ) const;
      
      bool empty () const;

      component_graph& operator= ( component_graph const& rhs );
      
      void swap ( component_graph& rhs );
      
      std::string to_string (void) const;
      
    private:

      component_graph::graph_t m_graph;

      component_graph::idvertexmap_t m_index;

      component_graph::component_map_t m_comp_map;
    };

  } // namespace infrastructure
} // namespace reverse

#endif // REVERSE_INFRASTRUCTURE_COMPONENT_GRAPH_HPP_INCLUDED
