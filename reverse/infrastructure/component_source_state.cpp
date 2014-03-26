/*  Component_Source_State.cpp

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
#include <reverse/infrastructure/component_source_state.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_actor.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/infrastructure/component.hpp>


#include <boost/format.hpp>

namespace reverse {
  namespace infrastructure {
  
    component_source_state::component_source_state ( boost::shared_ptr < const infrastructure::component_data > data_ptr )
        : m_data_ptr ( data_ptr )
    {
      trace::infrastructure_detail ( "Inside Component_Source_State constructor" );
    }

    component_source_state::component_source_state ( component_source_state const& rhs )
        : component_state_algorithm (rhs),
          m_data_ptr ( rhs.m_data_ptr )
    {
      trace::infrastructure_detail ( "Inside Component_Source_State copy constructor" );
    }

    boost::uint32_t
    component_source_state::get_id (void) const
    {
      trace::infrastructure_detail ( "Inside Component_Source_State::get_ID" );

      return static_cast<boost::uint32_t>(0);
    }

    void
    component_source_state::run ( boost::shared_ptr < infrastructure::component_actor >,
                                  infrastructure::component_graph::data_map_t* )
    {
      trace::infrastructure_detail ( "Inside Component_Source_State::run" );
    }

    void
    component_source_state::switch_state ( boost::shared_ptr < infrastructure::component_state > state_ptr,
                                           boost::uint32_t mode )
    {
      trace::infrastructure_detail ( "Entering Component_Source_State::switch_State" );

      if ( mode == component::working_mode )
	{
	  state_ptr->set_state ( state_ptr->m_working_state_ptr );
	}

      trace::infrastructure_detail ( "Exiting Component_Source_State::switch_State" );
    }

    component_source_state&
    component_source_state::operator= ( component_source_state const& rhs )
    {
      trace::infrastructure_detail ( "Entering Component_Source_State::operator= (assignment)" );

      component_source_state temp ( rhs );
      swap ( temp );

      trace::infrastructure_detail ( "Exiting Component_Source_State::operator= (assignment)" );

      return *this;
    }

    void
    component_source_state::swap ( component_source_state& rhs )
    {
      trace::infrastructure_detail ( "Entering Component_Source_State::swap" );

      m_data_ptr.swap ( rhs.m_data_ptr );

      trace::infrastructure_detail ( "Exiting Component_Source_State::swap" );
    }


  } /* namespace infrastructure */
} /* namespace reverse */
