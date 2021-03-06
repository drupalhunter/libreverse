/*  Component_State_Algorithm.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_STATE_ALGORITHM_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_STATE_ALGORITHM_HPP_INCLUDED

#include <reverse/infrastructure/component_graph.hpp>

#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace infrastructure {

    class component_actor;
    class component_state;

    class component_state_algorithm
    {
    public:

        /*!
         * \brief Default constructor
         */
        virtual ~component_state_algorithm(){}

        /**
         *  Component_State_Algorithm API
         */

        /**
         * \brief Return the ID number of this Component_State_Algorithm
         *
         * Called by the Component_State->get_ID to return the appropriate
         * id for this component.
         *
         * pre: m_id variable of Component_State is initialized either 
         *      a non-negative integer value (0 or greater)
         *
         * post: Component_Data unchanged
         *
         * \return ID number (copy)
         */
        virtual boost::uint32_t get_id (void) const = 0;

        /**
         * Based upon the state:
         *
         *   SOURCE: Do nothing
         *
         *   WORKING: Call process on the Component_Working_Algorithm_Impl
         */
      virtual void run ( boost::shared_ptr < infrastructure::component_actor > child_ptr,
			 infrastructure::component_graph::data_map_t* data_ptr ) = 0;

      /**
       * If the mode is valid and different this object
       * we set the state in the Component_State
       */
      virtual void switch_state ( boost::shared_ptr < infrastructure::component_state > state_ptr,
				  boost::uint32_t mode ) = 0;

    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_COMPONENT_STATE_ALGORITHM_HPP_INCLUDED */
