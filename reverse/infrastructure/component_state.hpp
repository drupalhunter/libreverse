/*  Component_State.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_STATE_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_STATE_HPP_INCLUDED

#include <reverse/infrastructure/component_data.hpp>

#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

      class data_source_base;

    } // namespace data_source

    class component_actor;
    class component_state_algorithm;

    class component_state : public boost::enable_shared_from_this<component_state>
    {
    public:

      friend class component_source_state;
      friend class component_working_state;

      /*!
       * \brief constructor
       */
      explicit component_state ( boost::uint32_t id );

      /*!
       * \brief copy constructor
       */
      explicit component_state ( component_state const& rhs );

      /*!
       * \brief default constructor
       */
      virtual ~component_state(){}

      /**
       *  component api
       */

      // set state ( working / source )
      void switch_state ( boost::uint32_t mode );

      boost::uint32_t get_id (void) const;

      void run ( boost::shared_ptr < infrastructure::component_actor > child_ptr,
		 infrastructure::component_graph::data_map_t* data_ptr );
        
      boost::shared_ptr < infrastructure::data_source::data_source_base> results (void) const;

      // check to see if the state value is valid
      bool check_mode_value ( boost::uint32_t mode );

      // add a new input source
      void add_input_source ( boost::uint32_t id );

      // we have received data and so we mark the state
      void received_input_source_data ( boost::uint32_t id );

      boost::shared_ptr < infrastructure::component_data > get_data (void) const;
        
      infrastructure::component_data::input_token_t::const_iterator get_source_list_begin (void) const;

      infrastructure::component_data::input_token_t::const_iterator get_source_list_end (void) const;

      component_state& operator= ( component_state const& rhs );

      void swap ( component_state& rhs );

    private:

      //---------------------------------
      //      state access methods
      //---------------------------------
      void set_state ( boost::shared_ptr < infrastructure::component_state_algorithm > );

      boost::shared_ptr < infrastructure::component_data > m_data_ptr;

      boost::shared_ptr < infrastructure::component_state_algorithm > m_working_state_ptr;

      boost::shared_ptr < infrastructure::component_state_algorithm > m_source_state_ptr;

      boost::shared_ptr < infrastructure::component_state_algorithm > m_present_state_ptr;

    };

  } // namespace infrastructure
} // namespace libreverse

#endif // #infdef REVERSE_INFRASTRUCTURE_COMPONENT_STATE_HPP_INCLUDED
