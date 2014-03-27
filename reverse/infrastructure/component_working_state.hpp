/*  Component_Working_State.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_WORKING_STATE_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_WORKING_STATE_HPP_INCLUDED

#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_state_algorithm.hpp>

namespace reverse {
  namespace infrastructure {

    class component_working_state : public component_state_algorithm
    {
    public:

      /*!
       * \brief Constructor
       * \param id Unique id for the instance of this filter
       */
      explicit component_working_state ( boost::shared_ptr < infrastructure::component_data > comp_ptr );

      /*!
       * \brief Copy constructor
       */
      component_working_state ( const component_working_state& ref );

      /*!
       * \brief Default constructor
       */
      virtual ~component_working_state(){}

      /**
       *  Component_Working_State API
       */
      
      /**
       * \brief Return the ID number of this Component_Working_State
       *
       * \return ID number
       */
        virtual boost::uint32_t get_id (void) const;

      virtual void run ( boost::shared_ptr < infrastructure::component_actor > child_ptr,
			 infrastructure::component_graph::data_map_t* input_data_ptr );

      virtual void switch_state ( boost::shared_ptr < infrastructure::component_state > state_ptr,
				  boost::uint32_t id );

      component_working_state& operator= ( component_working_state const& ref );
      
      void swap ( component_working_state& ref );
      
    private:

        // An algorithm has a pointer to the data to perform work
      boost::shared_ptr < infrastructure::component_data > m_data_ptr;

    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_COMPONENT_WORKING_STATE_HPP_INCLUDED */
