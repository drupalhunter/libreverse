/*  graph_test.cpp

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

#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <iostream>

using namespace boost;

class Base {
}

class A : public Base {
public:
  static uint16_t id = 500;
}

class B : public Base {
public:
  static uint16_t id = 2000;
}

class Component_Factory {
public:

  boost::shared_ptr<Base> get_A ()
  {
    return boost::shared_ptr<Base> ( new A());
  }

  boost::shared_ptr<Base> get_B ()
  {
    return boost::shared_ptr<Base> ( new B());
  }

  boost::shared_ptr<Component_Factory> get_Factory ()
  {
    if (m_factory.get() == 0)
      {
        m_factory.reset (new Component_Factory());
      }
    return m_factory;
  }

private:

  boost::shared_ptr<Component_Factory> m_factory;

  Actual_Component ()
  {}
  
};


//======== my data structure

class Component {
public:
  Component ()
    : m_id (0)
  {}

  Component (const uint32_t id)
    : m_id (id)
  {}

  const uint32_t get_ID (void) const
  {
    return m_id;
  }

  template <class char_t, class traits_t>
  friend std::basic_istream<char_t,traits_t>&
  operator >> (std::basic_istream<char_t,traits_t>& input, Component& data)
  {
    input >> data.m_id;
    return input;
  }

  template <class char_t, class traits_t>
  friend std::basic_ostream<char_t,traits_t>&
  operator << (std::basic_ostream<char_t,traits_t>& input, Component& data)
  {
    input << data.m_id;
    return input;
  }

private:

  uint32_t m_id;

};


class Graph {
public:

  typedef property< vertex_index_t, uint32_t,
                    property< vertex_name_t, Component > >
  VertexProperty;

  typedef adjacency_list<setS, // OutEdgeList
                         setS, // VertexList
                         directedS, // Directed
                         VertexProperty> // VertexProperties
  Graph_Type;

  void write_Graph (Graph_Type& g2)
  {
    std::ofstream writer ("data2_graphviz.dot");
    //write_graphviz(writer, g2);

    // Print out all the vertex IDs
    boost::property_map<Graph_Type, vertex_index_t>::type
      id = get(vertex_index, g2);

    boost::graph_traits<Graph_Type>::vertex_iterator vi;
    for (vi = vertices(g2).first; vi != vertices(g2).second; ++vi)
      std::cout << id[*vi] <<  " ";
    std::cout << std::endl;

    // Print Component IDs
    boost::property_map<Graph_Type, vertex_name_t>::type
      comp = get(vertex_name, g2);

    for (vi = vertices(g2).first; vi != vertices(g2).second; ++vi)
      std::cout << comp[*vi].get_ID() <<  " ";
    std::cout << std::endl;

  }

  void read_Graph (void)
  {
    Graph_Type g2;
    std::ifstream readFile2("data2.txt");
    readFile2 >> read( g2 );

    write_Graph (g2);
  }

};

int main () {

  // read Graph2 and all internal properties
  Graph g;
  g.read_Graph();

  return 0;
}
