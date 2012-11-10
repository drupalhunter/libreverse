/*  graph_test3.cpp

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

#define BOOST_SPIRIT_DEBUG 1
#define PHOENIX_LIMIT 6
#define BOOST_SPIRIT_CLOSURE_LIMIT 6

#include <inttypes.h>
#include <boost/shared_ptr.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/spirit.hpp>
#include <boost/spirit/phoenix.hpp>
#include <boost/spirit/dynamic/while.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace boost;
using namespace boost::spirit;

//======== my data struture

template <class T>
class ToString {
public:

  static const T Convert (T val)
  {
    return val;
  }
};

template <class T>
class Data {
public:
  Data ()
  {}

  Data (const T val)
    : m_value (val)
  {}

  virtual ~Data(){}

  const T get_Value (void) const
  {
    return m_value;
  }

  virtual const std::string get_Name (void) const = 0;

  const std::string get_Label (void)
  {
    std::stringstream out;
    out << this->get_Name() << std::endl
        << "Value: " << ToString<T>::Convert(m_value)
        << std::endl;
    return out.str();
  }

private:

  T m_value;

};

class Unsigned_Int_Data : public Data<uint32_t> {
public:
  Unsigned_Int_Data (uint32_t val)
    : Data<uint32_t> (val)
  {}

  ~Unsigned_Int_Data(){}

  virtual const std::string get_Name (void) const
  {
    return "Unsigned Int Data";
  }
};

class Float_Data : public Data<float> {
public:
  Float_Data (float val)
    : Data<float> (val)
  {}

  ~Float_Data(){}

  virtual const std::string get_Name (void) const
  {
    return "Float Data";
  }

};

class Data_Factory {
private:

  static boost::shared_ptr<Data_Factory> m_factory;

public:

  boost::shared_ptr< Data<uint32_t> > get_Uint (uint32_t val)
  {
    return boost::shared_ptr< Data<uint32_t> >
      ( new Unsigned_Int_Data(val));
  }

  boost::shared_ptr< Data<float> > get_Float (float val)
  {
    return boost::shared_ptr< Data<float> >
      ( new Float_Data (val) );
  }

  static boost::shared_ptr<Data_Factory> get_Factory ()
  {
    if (m_factory.get() == 0)
      {
        m_factory.reset (new Data_Factory());
      }
    return m_factory;
  }

private:

  Data_Factory ()
  {}
  
};

boost::shared_ptr<Data_Factory> Data_Factory::m_factory;

class Data_Graph {
public:

  typedef property< vertex_index_t, uint32_t,
                    property< vertex_name_t, boost::shared_ptr<Data> > >
  VertexProperty;

  typedef adjacency_list<setS, // OutEdgeList
                         setS, // VertexList
                         directedS, // Directed
                         VertexProperty> // VertexProperties
  Graph_Type;

  typedef graph_traits<Graph_Type>::vertex_descriptor Vertex;
  typedef graph_traits<Graph_Type>::edge_descriptor Edge;
  typedef std::map<uint32_t, Vertex> IdVertexMap;

  Data_Graph ()
  {}

  void add_Source ( boost::shared_ptr<Data> obj_ptr )
  {
    bool found;
    IdVertexMap::iterator pos;
    Vertex node;

    boost::tie (pos, found) = m_index.insert
      (std::make_pair(obj_ptr->get_ID(), node));

    if (found)
      {
        // Insertion was successful
        // Make a new vertex and return handle to 'node'
        node = add_vertex(m_graph);

        // Get list of Datas
        boost::property_map<Graph_Type, vertex_name_t>::type clist
          = get(vertex_name, m_graph);
        // Assign component to vertex position
        clist[node] = obj_ptr;

        // Add vertex handle to map position
        pos->second = node;

        // Get list of indexes
        boost::property_map<Graph_Type, vertex_index_t>::type ilist
          = get(vertex_index, m_graph);

        ilist[node] = obj_ptr->get_ID();
      }
    else
      {
        std::cerr << "ERROR: Duplicate source found. Skipping Data"
                  << std::endl;
        return;
      }
  }

  void add_Data (uint32_t parent_id, boost::shared_ptr<Data> obj_ptr)
  {
    IdVertexMap::iterator pos;
    IdVertexMap::iterator cpos;
    Vertex child_node;
    bool cfound;

    pos = m_index.find (parent_id);

    if (pos != m_index.end())
      {
        boost::tie (cpos, cfound) =
          m_index.insert (std::make_pair(obj_ptr->get_ID(), child_node));

        if (cfound)
          {
            // Insertion was successful
            // Make a new vertex and return handle to 'node'
            child_node = add_vertex(m_graph);

            // Get list of Datas
            boost::property_map<Graph_Type, vertex_name_t>::type clist
              = get(vertex_name,m_graph);

            // Assign component to vertex position
            clist[child_node] = obj_ptr;

            // Add vertex handle to map position
            cpos->second = child_node;

            // Get list of indexes
            boost::property_map<Graph_Type, vertex_index_t>::type ilist
              = get(vertex_index, m_graph);

            ilist[child_node] = obj_ptr->get_ID();

          }
        else
          {
            std::cerr << "ERROR: Duplicate child found. Skipping Data #"
                      << obj_ptr->get_ID() << std::endl
                      << obj_ptr->get_Name() << std::endl;
            return;
          }
      }
    else
      {
        std::cerr << "ERROR: Cannot find parent. Skipping adding component #"
                  << obj_ptr->get_ID() << std::endl
                  << obj_ptr->get_Name() << std::endl;
        return;
      }

    // Add edge from parent to child
    Edge link;


    if (! (add_edge ( pos->second, child_node, m_graph).second))
      {
        std::cerr << "ERROR: Duplicate edge exists from " << parent_id
                  << " to " << obj_ptr->get_ID() << std::endl;
        return;
      }
  }

  const Graph_Type& get_Graph ()
  {
    return m_graph;
  }

  boost::shared_ptr<Data> get_Data (const Vertex& node)
  {
    // Get list of Datas
    boost::property_map<Graph_Type, vertex_name_t>::type clist
      = get(vertex_name, m_graph);
    // Assign component to vertex position
    return clist[node];
  }

private:

  Graph_Type m_graph;

  IdVertexMap m_index;

};

class Data_Writer {
public:

  Data_Writer (const boost::shared_ptr<Data_Graph> g)
    : m_graph (g)
  {}

  std::string operator[](const Data_Graph::Vertex& v) const
  {
    boost::shared_ptr<Data> obj_ptr = m_graph->get_Data(v);
    return obj_ptr->get_Label();
  }

private:

  const boost::shared_ptr<Data_Graph> m_graph;
};

class Graph_Grammar :
  public grammar<Graph_Grammar>
  {
  public:

    Graph_Grammar (boost::shared_ptr<Data_Graph> data)
      : m_data (data)
    {}

    struct string_closure :
      closure<string_closure, std::string>
    {
      member1 text;
    };

    struct source_closure :
      closure<source_closure, uint32_t, std::string>
    {
      member1 node_id;
      member2 name;
    };

    struct node_closure :
      closure<node_closure, uint32_t, std::string, uint32_t>
    {
      member1 child_id;
      member2 name;
      member3 parent_id;
    };

    static boost::shared_ptr<Data>
    get_Data (const uint32_t id,
                   const std::string name,
                   const uint32_t = 0)
    {
      boost::shared_ptr<Data_Factory> factory = 
        Data_Factory::get_Factory();

      boost::shared_ptr<Data> obj_ptr;

      if (name.compare("uint") == 0)
        {
          obj_ptr = factory->get_Uint (id);
        }
      else if (name.compare("float") == 0)
        {
          obj_ptr = factory->get_Float (id);
        }

      return obj_ptr;
    }

    struct construct_Data_ {
        
      template <typename Data,
                typename ID,
                typename Name,
                typename Parent_ID>
      struct result {
        typedef void type;
      };

      template <typename Data,
                typename ID,
                typename Name,
                typename Parent_ID>
      void operator()(Data& data,
                      const ID& id,
                      const Name& name,
                      const Parent_ID& pid) const
      {
        boost::shared_ptr<Data> obj_ptr =
          Graph_Grammar::get_Data (id,name,pid);
        data->add_Data ( pid, obj_ptr );
      }
    };

    phoenix::function<construct_Data_> construct_Data;

    struct construct_Source_ {
        
      template <typename Data,
                typename ID,
                typename Name>
      struct result {
        typedef void type;
      };

      template <typename Data,
                typename ID,
                typename Name>
      void operator()(Data& data,
                      const ID& id,
                      const Name& name) const
      {
        boost::shared_ptr<Data> obj_ptr =
          Graph_Grammar::get_Data (id,name);
        data->add_Source ( obj_ptr );
      }
    };

    phoenix::function<construct_Source_> construct_Source;

    template <typename ScannerT>
    struct definition
    {

      rule<ScannerT> graph;
      rule<ScannerT, source_closure::context_t> source_node;
      rule<ScannerT, node_closure::context_t> node;
      rule<ScannerT, string_closure::context_t> name;

      definition(Graph_Grammar const& self)
      {
        graph
          = source_node
            >> while_p (~epsilon_p(end_p))
          [
           node
          ];

        source_node = as_lower_d[str_p("source")]
          >> ch_p('{')
          >> uint_p [source_node.node_id = phoenix::arg1]
          >> ch_p(',')
          >> name [source_node.name = phoenix::arg1]
          >> str_p("};")
          [
           self.construct_Source (self.m_data,
                                  source_node.node_id,
                                  source_node.name)
           ];

        // Read this and add a semantic action to create a
        // File_Data_Source_Config object. Add to m_data.
        node = as_lower_d[str_p("node")]
          >> ch_p('{')
          >> uint_p [node.child_id = phoenix::arg1]
          >> ch_p(',')
          >> name [node.name = phoenix::arg1]
          >> ch_p (',')
          >> uint_p[node.parent_id = phoenix::arg1]
          >> str_p("};")
          [self.construct_Data (self.m_data,
                                     node.child_id,
                                     node.name,
                                     node.parent_id)];

        name = ch_p('"')
          >> (alnum_p
              >> *(alnum_p | ch_p('_')))
          [
           name.text =
           phoenix::construct_<std::string>(phoenix::arg1,
                                            phoenix::arg2)
           ]
          >> ch_p('"');
          
        BOOST_SPIRIT_DEBUG_NODE(graph);
        BOOST_SPIRIT_DEBUG_NODE(source_node);
        BOOST_SPIRIT_DEBUG_NODE(node);
        BOOST_SPIRIT_DEBUG_NODE(name);
      }
        
      rule<ScannerT> const& start() const
      {
        return graph;
      }
    };

    mutable boost::shared_ptr<Data_Graph> m_data;
};

template <typename Grammar>
bool parse_i (const std::string & file,
              const Grammar& grammar)
{
  boost::spirit::file_iterator<> first(file);
  
  if (!first) {
    std::cerr << "Configuration_Parser: Unable to open file '"
              << file
              << "'!" << std::endl;
    return false;
  }
  
  const boost::spirit::file_iterator<> last = first.make_end();
  
  typedef typename boost::spirit::position_iterator
    < boost::spirit::file_iterator<> > iterator_t;
  
  const parse_info<iterator_t> info =
    boost::spirit::parse(iterator_t(first, last, file), iterator_t(),
                         grammar, boost::spirit::space_p | boost::spirit::comment_p("#"));
  
  if (!info.full)
    {
      const boost::spirit::file_position fp = info.stop.get_position();
      
      std::cerr << "Parsing of file '" << fp.file
                << "' failed at line " << fp.line
                << ", column " << fp.column << ".\n";
    }
  
  return info.full;
}

int main ()
{

  // read Graph2 and all internal properties
  boost::shared_ptr<Data_Graph> m_data (new Data_Graph());
  Graph_Grammar grmr (m_data);

  std::ofstream file ("test.txt");
  file << "source{0,\"uint\"};"  << std::endl;
  file << "node{1,\"float\",0};"  << std::endl;
  file << "node{2,\"uint\",0};"  << std::endl;
  file << "node{3,\"uint\",1};"  << std::endl;
  file.close();

  if (!parse_i("test.txt", grmr))
    {
        std::cerr << "Invalid configuration file format." << std::endl;
    }

  std::ofstream gfile ("test.dot");
  write_graphviz (gfile,
                  m_data->get_Graph(),
                  make_label_writer(Data_Writer(m_data)));

  return 0;
}
