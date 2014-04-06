/*  Component_State.cpp

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
#include <reverse/errors/component_exception.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/infrastructure/component_actor.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/infrastructure/component_source_state.hpp>
#include <reverse/infrastructure/component_working_state.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>

#include <boost/format.hpp>

#include <iostream>

namespace reverse {
  namespace infrastructure {

    component_state::component_state ( boost::uint32_t id )
        :  m_data_ptr ( new component_data( id ) ),
           m_working_state_ptr ( new component_working_state ( m_data_ptr ) ),
           m_source_state_ptr ( new component_source_state ( m_data_ptr ) ),
           m_present_state_ptr ( m_working_state_ptr )
    {
      trace::infrastructure_detail ( "Inside Component_State constructor" );
    }

    component_state::component_state ( component_state const& rhs )
        : boost::enable_shared_from_this<component_state> (rhs),
          m_data_ptr ( new component_data( *rhs.m_data_ptr ) ),
          m_working_state_ptr ( new component_working_state ( m_data_ptr ) ),
          m_source_state_ptr ( new component_source_state ( m_data_ptr ) ),
          m_present_state_ptr ( m_working_state_ptr )
    {
      trace::infrastructure_detail ( "Inside Component_State copy constructor" );
    }

    void
    component_state::switch_state ( boost::uint32_t mode )
    {
      trace::infrastructure_detail ( "Entering Component_State::switch_State" );

      if ( this->check_mode_value ( mode ) )
	{
	  m_present_state_ptr->switch_state ( this->shared_from_this(),
					      mode );
	}
      else
	{
	  std::cerr << boost::format("Exception throw in %s at line %d")
	    % __FILE__
	    % __LINE__
		    << std::endl;
	  
	  throw errors::component_exception ( errors::component_exception::invalid_state );
	}

      trace::infrastructure_detail ( "Exiting Component_State::switch_State" );
    }

    void
    component_state::set_state ( boost::shared_ptr < infrastructure::component_state_algorithm > state_ptr )
    {
      trace::infrastructure_detail ( "Entering Component_State::set_State" );
      
      if ( state_ptr.get() != 0 )
	{
	  m_present_state_ptr = state_ptr;
	}
      else
	{
	  std::cerr << boost::format("Exception throw in %s at line %d")
	    % __FILE__
	    % __LINE__
		    << std::endl;
	  
	  throw errors::component_exception ( errors::component_exception::null_pointer );
	}
      
      trace::infrastructure_detail ( "Exiting Component_State::switch_State" );
    }

    bool
    component_state::check_mode_value ( boost::uint32_t mode )
    {
      trace::infrastructure_detail ( "Entering Component_State::check_Mode_Value" );

      bool result = false;

      if ( ( mode == component::working_mode ) ||
	   ( mode == component::source_mode ) )
	{
	  result = true;
	}

      trace::infrastructure_detail ( "Exiting Component_State::check_Mode_Value" );
      return result;
    }

    boost::uint32_t
    component_state::get_id (void) const
    {
        trace::infrastructure_detail ( "Inside Component_State::get_ID" );

        return m_present_state_ptr->get_id();
    }

    void
    component_state::run ( boost::shared_ptr < infrastructure::component_actor > child_ptr,
                           infrastructure::component_graph::data_map_t* data_ptr )
    {
        trace::infrastructure_detail ( "Inside Component_State::run" );

        m_present_state_ptr->run ( child_ptr, data_ptr );
    }

      boost::shared_ptr < infrastructure::component_data >
    component_state::results ( void ) const
    {
      trace::infrastructure_detail ( "Inside Component_State::results" );

      return m_data_ptr;
    }

    void
    component_state::add_input_source ( boost::uint32_t id )
    {
      trace::infrastructure_detail ( "Inside Component_State::add_Input_Source" );
      m_data_ptr->add_input_source ( id );
    }

    void
    component_state::received_input_source_data ( boost::uint32_t id )
    {
      trace::infrastructure_detail ( "Entering Component_State::received_Input_Source_Data" );
      if ( m_data_ptr->find ( id ) )
	{
	  std::cout
	    << boost::format("Node(%d) - initialized with data from component #%d")
	    % m_data_ptr->get_id()
	    % id
	    << std::endl;

	  m_data_ptr->received_input_source_data ( id );
	}
      else
	{
	  std::cerr << boost::format("Exception throw in %s at line %d")
	    % __FILE__
	    % __LINE__
		    << std::endl;
	  
	  throw errors::component_exception ( errors::component_exception::invalid_index );
	}
      
      trace::infrastructure_detail ( "Exiting Component_State::received_Input_Source_Data" );
    }

    boost::shared_ptr < infrastructure::component_data >
    component_state::get_data (void) const
    {

      trace::infrastructure_detail ( "Inside Component_State::get_Data" );

      return m_data_ptr;
    }

    infrastructure::component_data::input_token_t::const_iterator
    component_state::get_source_list_begin (void) const
    {
      trace::infrastructure_detail ( "Inside Component_State::get_Source_List_Begin" );

      return m_data_ptr->get_source_list_begin();
    }

    infrastructure::component_data::input_token_t::const_iterator
    component_state::get_source_list_end (void) const
    {
      trace::infrastructure_detail ( "Inside Component_State::get_Source_List_End" );

      return m_data_ptr->get_source_list_end();
    }
    
    component_state&
    component_state::operator= ( component_state const& rhs )
    {
      trace::infrastructure_detail ( "entering component_state::operator= (assignment)" );

      component_state temp ( rhs );
      swap ( temp );

      trace::infrastructure_detail ( "Exiting Component_State::operator= (assignment)" );

      return *this;
    }

    void
    component_state::swap ( component_state& rhs )
    {
      trace::infrastructure_detail ( "Entering Component_State::swap" );

      m_data_ptr.swap ( rhs.m_data_ptr );
      m_working_state_ptr.swap ( rhs.m_working_state_ptr );
      m_source_state_ptr.swap ( rhs.m_source_state_ptr );
      m_present_state_ptr.swap ( rhs.m_present_state_ptr );

      trace::infrastructure_detail ( "Exiting Component_State::swap" );
    }

  } /* namespace infrastructure */
} /* namespace reverse */
