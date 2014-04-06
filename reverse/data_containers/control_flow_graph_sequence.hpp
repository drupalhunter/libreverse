/*  control_flow_graph_sequence.h

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

      typedef std::vector < boost::shared_ptr<control_flow_graph> > sequence_t;
      
      explicit control_flow_graph_sequence ();

      control_flow_graph_sequence ( control_flow_graph_sequence const& rhs );

      void add_control_flow_graph ( boost::shared_ptr< control_flow_graph >& input_block_ptr );

      sequence_t::iterator begin();

      sequence_t::iterator end();

      sequence_t::const_iterator begin() const;

      sequence_t::const_iterator end() const;
      
      sequence_t::size_type size () const;

      virtual ~control_flow_graph_sequence (){}

      bool empty () const;

      control_flow_graph_sequence& operator= ( control_flow_graph_sequence const& rhs );

      void swap ( control_flow_graph_sequence& rhs );

    private:

      sequence_t m_graph_list;
    };
    
    std::ostream& operator<< ( std::ostream& os, control_flow_graph_sequence const& rhs );

  } // namespace data_containers
} // namespace reverse

#endif // #ifndef REVERSE_DATA_CONTAINER_CONTROL_FLOW_GRAPH_SEQEUENCE_HPP_INCLUDED

