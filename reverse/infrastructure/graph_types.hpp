/*  Graph_Types.h

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

#ifndef REVERSE_INFRASTRUCTURE_GRAPH_BASE_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_GRAPH_BASE_HPP_INCLUDED

#include <reverse/infrastructure/data_source/Data_Source_Base.h>
#include <reverse/infrastructure/Component_Types.h>

#include <boost/graph/adjacency_list.hpp>

namespace reverse {
  namespace infrastructure {

    class Component;

    class Graph_Base
    {
    public:

        typedef boost::property< boost::vertex_name_t,
                                 boost::shared_ptr<Component> >
        VertexProperty_t;

        typedef boost::adjacency_list<boost::vecS, // OutEdgeList
                                      boost::vecS, // VertexList
                                      boost::directedS, // Directed
                                      VertexProperty_t> // VertexProperties
        Graph_t;

        typedef std::pair<infrastructure_types::Data_Source_Base::const_ptr_t,
                          Graph_t::degree_size_type>
        Result_Data_t;

        typedef std::map<boost::uint32_t, Result_Data_t> Data_Map_t;

    };

  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_GRAPH_BASE_HPP_INCLUDED
