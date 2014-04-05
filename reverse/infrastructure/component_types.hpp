/*  Component_Types.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_TYPES_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_TYPES_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <list>
#include <map>
#include <string>

namespace reverse {

  namespace infrastructure {

    class Component_Actor;
    class Component_State;
    class Component;
    class Component_Data;
    class Component_Graph;
    class Component_State;
    class Component_State_Algorithm;
    class Configuration_Data;
    class Configurator;
    class data_object;
    class Data_Source_Base;
    class Data_Source_Config_Base;
    class Data_Source_Factory;
    class Data_Source_Factory_Base;
    template <typename Transfer_Type> class Data_Source;
    class Database_Data_Source_Config;
    class Database_Data_Transfer;
    class File_Data_Source_Config;
    class File_Data_Transfer;
    class Formula_List;
    class Memory_Data_Source_Config;
    class Memory_Data_Transfer;
  }

  namespace infrastructure_types {

    /*! \brief infrastructure::Component typedefs */
    class Component
    {
    public:

      /*! \brief Meta information provided by a component is a list string data*/
      typedef std::list < std::string > Meta_List_t;

      /*! \brief Data information provided by a component is a list of string data
       *  \deprecated
       */
      typedef std::list < std::string > Data_List_t;

      /*! \brief shared pointer type */
      typedef boost::shared_ptr<infrastructure::Component> ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr<infrastructure::Component const> const_ptr_t;
    };

    /*! \brief infrastructure::Component_State typedefs */
    class Component_State
    {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Component_State > ptr_t;
    };

    /*! \brief infrastructure::Component_Data typedefs */
    class Component_Data
    {
    public:

      /*! \brief shared pointer type */	
      typedef boost::shared_ptr < infrastructure::Component_Data > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Component_Data const > const_ptr_t;

      /*! \brief This data type is used to contain the list of
          components providing input data to current component. 
	  key = component id,
	  value = input data available ( true = yes, false = no )
      */
      typedef std::map <boost::uint32_t const, bool> Input_Token_t;
    };

    /*! \brief infrastructure::Component_State typedefs */
    class Component_State_Algorithm
    {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Component_State_Algorithm > ptr_t;
    };

    /*! \brief infrastructure::Data_Source_Base typedefs */
    class Data_Source_Base {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Base > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Base const > const_ptr_t;
    };

    /*! \brief infrastructure::Data_Source typedefs */
    template <typename Transfer_Type>
    class Data_Source {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source<Transfer_Type> > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source<Transfer_Type> const > const_ptr_t;
    };

    /*! \brief infrastructure::Data_Source_Factory typedefs */      
    class Data_Source_Factory {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Factory > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Factory const > const_ptr_t;
    };

    /*! \brief infrastructure::Component_Graph typedefs */
    class Component_Graph {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Component_Graph > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Component_Graph const> const_ptr_t;

      /*! \brief Each vertex will contain a Component object */
      typedef boost::property< boost::vertex_name_t,
			       Component::ptr_t > VertexProperty_t;

      /*! \brief A graph type is a directed graph of Components. */
      typedef boost::adjacency_list<boost::vecS, // OutEdgeList
				    boost::vecS, // VertexList
				    boost::directedS, // Directed
				    VertexProperty_t> // VertexProperties
      Graph_t;

      /*! \brief Data type is used keep track of the output data from each component.
      *
      * \todo Investigate further why we care about the number of
      * children needing the results. Initial thoughts are that this
      * is second value is unnecessary.
      */
      typedef std::pair<Data_Source_Base::const_ptr_t,
			Graph_t::degree_size_type>
      Result_Data_t;

      /*! \brief Data type used to keep the results of data from each
          component.
       *
       *  key = component id
       *
       *  value = Result_Data_t pair
       */
      typedef std::map<boost::uint32_t, Result_Data_t> Data_Map_t;

      /*! \brief Map type for storing Graphs from the individual formula files
       *
       * Each Map is composed of a:
       *
       *    "input", Component_Graph (input)
       *    "analysis", Component_Graph (analysis)
       *    "output", Component_Graph (output)
       */
      typedef std::map<std::string, Component_Graph::ptr_t > Map_t;

      /*! \brief Shared pointer for Formula map type */
      typedef boost::shared_ptr<Map_t> Map_ptr_t;

      /*! \brief Iterator for Vertices */
      typedef boost::graph_traits<Graph_t>::vertex_descriptor
      Vertex_t;

      /*! \brief Iterator for Edges */
      typedef boost::graph_traits<Graph_t>::edge_descriptor
      Edge_t;
     
      /*! \brief Reverse loop up map to the Component object stored in the Graph.
       *
       * key = Graph object
       *
       * value = Graph vertex node associated with the target object.
       *       
       */
      typedef boost::property_map<Graph_t, boost::vertex_name_t>::type
      Component_Map_t;

      /*! \brief Iterator for Edges coming into a Vertex */
      typedef boost::graph_traits<Graph_t>::in_edge_iterator
      In_Edge_Iterator_t;

      /*! \brief Iterator for Edges leaving a Vertex */
      typedef boost::graph_traits<Graph_t>::out_edge_iterator
      Out_Edge_Iterator_t;

      /*! \brief Data type used to associated the Component ID with
       * the Vertex containing the desire Component Object. 
       *
       * key = Component ID
       * value = Graph Vertex containing Component
       */
      typedef std::map<boost::uint32_t, Vertex_t> IdVertexMap_t;

      /*! \brief Data type containing the start and end iterator for the input edges.
       *
       * \todo This should probably be removed.
       * \deprecated
       */
      typedef std::pair<In_Edge_Iterator_t,
			In_Edge_Iterator_t> Input_Edge_List_t;

      /*! \brief Data type containing the pointer to all the Component
       * objects in the Graph.
       */
      typedef std::vector < Component::ptr_t > Component_List_t;

      /*! \brief Data Type for the number of edges in or out of a Vertex.
       *
       * \todo This should probably be removed.
       * \deprecated
       */
      typedef boost::graph_traits<Graph_t>::degree_size_type
      Degree_Size_t;

    };

    /*! \brief infrastructure::Configurator typedefs */
    class Configurator {
    public:

      /*! \brief Data type associated with a Formula map
       *
       * key 1: Input file type
       * key 2: Desired output type
       * value: File associated with the two key pairs.
       */
      typedef std::map < std::pair<boost::uint32_t, boost::uint32_t>, infrastructure::Formula_List >
      Formula_Map_t;

      /*! \brief shared pointer type for Formula Maps */
      typedef boost::shared_ptr<Formula_Map_t> Formula_Map_ptr_t;

      /*! \brief shared pointer type */
      typedef boost::shared_ptr<infrastructure::Configurator> ptr_t;
    };

    /*! \brief infrastructure::Configuration_Data typedefs */
    class Configuration_Data {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr<infrastructure::Configuration_Data> ptr_t;
    };

    /*! \brief infrastructure::Data_Source_Factory_Base typedefs */
    class Data_Source_Factory_Base {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Factory_Base > ptr_t;
    };

    /*! \brief infrastructure::data_object typedefs */
    class data_object
    {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::data_object > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::data_object const > const_ptr_t;
    };

    /*! \brief infrastructure::Database_Data_Transfer typedefs */
    class Database_Data_Transfer {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Database_Data_Transfer > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Database_Data_Transfer const > const_ptr_t;
    };

    /*! \brief infrastructure::Database_Data_Source_Config typedefs */
    class Database_Data_Source_Config {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Database_Data_Source_Config > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Database_Data_Source_Config const > const_ptr_t;
    };

    /*! \brief infrastructure::Data_Source_Config_Base typedefs */
    class Data_Source_Config_Base {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Config_Base > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Data_Source_Config_Base const > const_ptr_t;
    };

    /*! \brief infrastructure::File_Data_Transfer typedefs */
    class File_Data_Transfer {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::File_Data_Transfer > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::File_Data_Transfer const > const_ptr_t;
    };

    /*! \brief infrastructure::File_Data_Source_Config typedefs */
    class File_Data_Source_Config {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::File_Data_Source_Config > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::File_Data_Source_Config const > const_ptr_t;
    };

    /*! \brief infrastructure::Memory_Data_Transfer typedefs */
    class Memory_Data_Transfer {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Memory_Data_Transfer > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Memory_Data_Transfer const > const_ptr_t;
    };

    /*! \brief infrastructure::Memory_Data_Source_Config typedefs */
    class Memory_Data_Source_Config {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Memory_Data_Source_Config > ptr_t;

      /*! \brief constant shared pointer type */
      typedef boost::shared_ptr < infrastructure::Memory_Data_Source_Config const > const_ptr_t;
    };

    /*! \brief infrastructure::Component_Actor typedefs */
    class Component_Actor
    {
    public:

      /*! \brief shared pointer type */
      typedef boost::shared_ptr < infrastructure::Component_Actor > ptr_t;
    };

  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_COMPONENT_TYPES_HPP_INCLUDED
