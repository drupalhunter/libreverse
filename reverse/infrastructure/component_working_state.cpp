/*  Component_Working_State.cpp

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

#include <reverse/trace.hpp>
#include <reverse/infrastructure/component_working_state.hpp>
#include <reverse/infrastructure/component_actor.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/infrastructure/component.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace infrastructure {

    component_working_state::component_working_state ( boost::shared_ptr < infrastructure::component_data > data_ptr )
        : m_data_ptr ( data_ptr )
    {
      trace::infrastructure_detail ( "Inside Component_Working_State constructor" );
    }

    component_working_state::component_working_state( component_working_state const& rhs )
        : component_state_algorithm ( rhs ),
          m_data_ptr ( rhs.m_data_ptr )
    {
      trace::infrastructure_detail ( "Inside Component_Working_State copy constructor" );
    }

    boost::uint32_t
    component_working_state::get_id (void) const
    {
      trace::infrastructure_detail ( "Inside Component_Working_State::get_ID" );

      return m_data_ptr->get_id();
    }

    void
    component_working_state::run ( boost::shared_ptr < infrastructure::component_actor > child_ptr,
                                   infrastructure::component_graph::data_map_t* input_data_ptr )
    {
      trace::infrastructure_detail ( "Entering Component_Working_State::run" );

      m_data_ptr->gather_inputs ( input_data_ptr );

      // Call child process function to do work.
      child_ptr->process ();

      trace::infrastructure_detail ( "Exiting Component_Working_State::run" );
    }

    void
    component_working_state::switch_state ( boost::shared_ptr < infrastructure::component_state > state_ptr,
                                            boost::uint32_t mode )
    {
      trace::infrastructure_detail ( "Entering Component_Working_State::switch_State" );

      if ( mode == component::source_mode )
	{
	  state_ptr->set_state ( state_ptr->m_source_state_ptr );
	}
      
      trace::infrastructure_detail ( "Exiting Component_Working_State::switch_State" );
    }
    
    component_working_state&
    component_working_state::operator= ( component_working_state const& rhs )
    {
      trace::infrastructure_detail ( "Entering Component_Working_State::operator= (assignment)" );

      component_working_state temp ( rhs );
      swap ( temp );

      trace::infrastructure_detail ( "Exiting Component_Working_State::operator= (assignment)" );

      return *this;
    }

    void
    component_working_state::swap ( component_working_state& rhs )
    {
        trace::infrastructure_detail ( "Entering Component_Working_State::swap" );

        m_data_ptr.swap ( rhs.m_data_ptr );

        trace::infrastructure_detail ( "Exiting Component_Working_State::swap" );
    }
    
  } /* namespace infrastructure */
} /* namespace reverse */
