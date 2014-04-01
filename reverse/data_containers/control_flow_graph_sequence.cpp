/*  control_flow_graph_sequence.cpp

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

#include "control_flow_graph_sequence.h"
#include "Control_Flow_Graph.h"

#include "errors/Internal_Exception.h"
#include "data_containers/Basic_Block.h"
#include "io/Preconditions.h"

#include <sstream>
#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace data_container {

    control_flow_graph_sequence::control_flow_graph_sequence ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside control_flow_graph_sequence constructor" );
#endif /* LIBREVERSE_DEBUG */
    }

    control_flow_graph_sequence::control_flow_graph_sequence ( control_flow_graph_sequence const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering control_flow_graph_sequence copy constructor" );
#endif /* LIBREVERSE_DEBUG */


	for ( data_types::control_flow_graph_sequence::Sequence_t::const_iterator cpos = rhs.m_graph_list.begin();
	      cpos != rhs.m_graph_list.end();
	      ++cpos )
	  {
	    data_types::Control_Flow_Graph::const_ptr_t cfg_ptr = (*cpos);
	    data_types::Control_Flow_Graph::ptr_t copied_cfg_ptr ( new data_container::Control_Flow_Graph ( *cfg_ptr ) );
	    m_graph_list.push_back ( copied_cfg_ptr );
	  }
	    

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting control_flow_graph_sequence copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    control_flow_graph_sequence::add_Control_Flow_Graph ( boost::shared_ptr < Control_Flow_Graph > input_cfg_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering control_flow_graph_sequence::add_Control_Flow_Graph" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( input_cfg_ptr );

	m_graph_list.push_back ( input_cfg_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting control_flow_graph_sequence::add_Control_Flow_Graph" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::vector < boost::shared_ptr<Control_Flow_Graph> >::iterator
    control_flow_graph_sequence::begin()
    {
      return m_graph_list.begin();
    }

    std::vector < boost::shared_ptr<Control_Flow_Graph> >::iterator
    control_flow_graph_sequence::end()
    {
      return m_graph_list.end();
    }

    std::vector < boost::shared_ptr<Control_Flow_Graph> >::const_iterator
    control_flow_graph_sequence::begin() const
    {
      return m_graph_list.begin();
    }

    std::vector < boost::shared_ptr<Control_Flow_Graph> >::const_iterator
    control_flow_graph_sequence::end() const
    {
      return m_graph_list.end();
    }

    bool
    control_flow_graph_sequence::empty () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside control_flow_graph_sequence::empty ()" );
#endif /* LIBREVERSE_DEBUG */

        return m_graph_list.empty();
    }

    control_flow_graph_sequence&
    control_flow_graph_sequence::operator= ( control_flow_graph_sequence const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering control_flow_graph_sequence::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        control_flow_graph_sequence temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting control_flow_graph_sequence::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    control_flow_graph_sequence::swap ( control_flow_graph_sequence& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering control_flow_graph_sequence::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_graph_list.swap ( rhs.m_graph_list );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting control_flow_graph_sequence::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::ostream& operator<< ( std::ostream& os, control_flow_graph_sequence const& rhs )
    {
 
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering control_flow_graph_sequence::to_String" );

        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
			     boost::str ( boost::format ( "Control Flow Graph count: %1%" ) % m_graph_list.size() ) );

#endif /* LIBREVERSE_DEBUG */

        for ( data_types::control_flow_graph_sequence::Sequence_t::const_iterator cpos = m_graph_list.begin();
              cpos != m_graph_list.end();
              ++cpos )
            {
	      data_types::Control_Flow_Graph::ptr_t cfg_ptr = (*cpos);

	      // print out text version of graph
	      os << cfg_ptr->to_String() << std::endl;

	    }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting control_flow_graph_sequence::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return os;
    }

}  /* namespace data_types */
} /* namespace libreverse */
