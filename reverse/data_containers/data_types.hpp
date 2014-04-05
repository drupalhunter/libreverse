/*  Data_Types.h

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

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <map>

namespace reverse {

  namespace data_container {
    class Basic_Block;
    class Control_Flow_Graph;
    class control_flow_graph_sequence;
    class filename;
    class Java_Assembly_Instruction;
    class Instruction;
    class memory_map;
  }

  namespace data_types {

    /*! \brief Base data type for Instructions objects */
    class Instruction
    {
    public:

      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::Instruction> ptr_t;

      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::Instruction const> const_ptr_t;
    };

    /*! \brief This data type is used to store Instruction objects at
        a Vertex in the Control Flow graph. */
    class Basic_Block
    {
    public:

      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::Basic_Block> ptr_t;

      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::Basic_Block const> const_ptr_t;

      /*! \brief Data type that contains the list of Instruction objects. */
      typedef std::vector<data_types::Instruction::ptr_t> DataList_t;
    };

    /*! \brief Data type used to describe the input file to be processed. */
    class filename
    {
    public:

      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::filename> ptr_t;

      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::filename const> const_ptr_t;
    };

    /*! \brief Data type used to describe how program control goes
      through all or part of an application. Each Vertex contains a
      Basic Block object.
    */
    class Control_Flow_Graph {
    public:

      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::Control_Flow_Graph> ptr_t;

      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::Control_Flow_Graph const> const_ptr_t;
	
      /*! \brief Each Vertex will contain a Basic Block object */
      typedef boost::property< boost::vertex_name_t,
			       Basic_Block::ptr_t >
      VertexProperty_t;

      /*! \brief A graph type is a directed graph of Basic Blocks. */
      typedef boost::adjacency_list<boost::vecS, // OutEdgeList
				    boost::vecS, // VertexList
				    boost::directedS, // Directed
				    VertexProperty_t> // VertexProperties
      Graph_t;

      /*! \brief Reverse loop up map to the Basic Block object stored in the Graph.
       *
       * key = Graph object
       *
       * value = Graph vertex node associated with the target object.
       *       
       */
      typedef boost::property_map<Graph_t, boost::vertex_name_t>::type
      Basic_Block_Map_t;

      /*! \brief Iterator for Vertices */
      typedef boost::graph_traits<Graph_t>::vertex_descriptor
      Vertex_t;

      /*! \brief Iterator for Edges */
      typedef boost::graph_traits<Graph_t>::edge_descriptor
      Edge_t;

      /*! \brief Data type used to obtain the results of adding an
          edge to a graph. At present the first value to the Edge
          iterator is not used. Only the bool value which indicates
          successful entry (TRUE) or a duplicate was found (FALSE) is
          used when the debug build is enabled.
       */
      typedef std::pair< Edge_t, bool>
      Add_Edge_Result_t;

      /*! \brief Data type used to associated the id with the Vertex
       * containing the desired Basic Block Object.
       *
       * key = Component ID
       * value = Graph Vertex containing Basic Block
       */
      typedef std::map<boost::uint32_t, Vertex_t>
      IdVertexMap_t;

      /*! \brief Iterator for Edges coming into a Vertex. */
      typedef boost::graph_traits<Graph_t>::in_edge_iterator
	In_Edge_Iterator_t;

      /*! \brief Iterator for Edges leaving a Vertex. */
      typedef boost::graph_traits<Graph_t>::out_edge_iterator
	Out_Edge_Iterator_t;

      /*! \brief Iterator for Vertex in the Control Flow Graph. */
      typedef boost::graph_traits<Graph_t>::vertex_iterator
	Vertex_Iterator_t;

    };

    class control_flow_graph_sequence
    {
    public:


      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::control_flow_graph_sequence> ptr_t;

      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::control_flow_graph_sequence const> const_ptr_t;
	
      typedef std::vector<data_types::Control_Flow_Graph::ptr_t> Sequence_t;

    };

    class memory_map
    {
    public:

      static boost::int8_t const SUCCESS;
      static boost::int8_t const INVALID_INDEX;
      static boost::int8_t const OUT_OF_RANGE;


      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::memory_map> ptr_t;
      
      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::memory_map const> const_ptr_t;

      // !\brief This type represents a byte
      typedef boost::uint8_t data_t;

      // !\brief The internal data structure of a Memory Map
      typedef std::vector <data_t> Values_t;

      // !\brief Map key is a 32-bit address in memory
      typedef boost::uint32_t map_key_t;

      // !\brief index where the data is in the Values_t list
      typedef boost::uint32_t index_t;

      // !\brief Table use for normal lookups ( address => index )
      typedef std::map<map_key_t, index_t> Address_Map_t;

      // !\brief Table used for reverse lookups ( index => address )
      //
      // Map key is the index where the data is in the Values_t list
      // Data value is the 32-bit address in memory
      typedef std::map<index_t, map_key_t> Reverse_Address_Map_t;

      typedef data_t* pointer_t;
      typedef Values_t::const_iterator const_iterator;
      typedef Values_t::iterator iterator;

    };

    class Java_Assembly_Instruction
    {
    public:

      /*! \brief Shared pointer type */
      typedef boost::shared_ptr<data_container::Java_Assembly_Instruction> ptr_t;

      /*! \brief Shared constant pointer type */
      typedef boost::shared_ptr<data_container::Java_Assembly_Instruction const> const_ptr_t;
    };


  }
}

#endif /* DATA_TYPES_H */
