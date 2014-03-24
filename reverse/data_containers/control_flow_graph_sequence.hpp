/*  Control_Flow_Graph_Sequence.h

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

#ifndef REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_SEQEUENCE_HPP_INCLUDED
#define REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_SEQEUENCE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

namespace reverse {
  namespace data_containers {

    class control_flow_graph;

    class control_flow_graph_sequence
    {
    public:

      explicit control_flow_graph_sequence ();

      control_flow_graph_sequence ( control_flow_graph_sequence const& rhs );

      void add_control_flow_graph ( boost::shared_ptr< control_flow_graph >& input_block_ptr );

      std::vector < boost::shared_ptr<control_flow_graph> >::iterator begin();

      std::vector < boost::shared_ptr<control_flow_graph> >::iterator end();

      std::vector < boost::shared_ptr<control_flow_graph> >::const_iterator begin() const;

      std::vector < boost::shared_ptr<control_flow_graph> >::const_iterator end() const;

      virtual ~control_flow_graph_sequence (){}

      bool empty () const;

      control_flow_graph_sequence& operator= ( control_flow_graph_sequence const& rhs );

      void swap ( control_flow_graph_sequence& rhs );

      std::string to_string ( void ) const;

    private:

      std::vector < boost::shared_ptr<control_flow_graph> > m_graph_list;

    };

  } // namespace data_containers
} // namespace reverse

#endif // #ifndef REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_SEQEUENCE_HPP_INCLUDED

