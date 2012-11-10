/*  Component_Source_State.h

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

#ifndef COMPONENT_SOURCE_STATE_H_
#define COMPONENT_SOURCE_STATE_H_

#include "infrastructure/Component_State_Algorithm.h"

namespace libreverse { namespace infrastructure {

    class Component_Data;
    class Component_State;

    class Component_Source_State : public Component_State_Algorithm
    {
    public:

        /*!
         * \brief Constructor
         * \param id Unique id for the instance of this filter
         */
      explicit Component_Source_State ( infrastructure_types::Component_Data::ptr_t data_ptr );

        /*!
         * \brief Copy constructor
         */
        Component_Source_State ( Component_Source_State const& ref );

        /*!
         * \brief Default constructor
         */
        virtual ~Component_Source_State(){}

        /**
         *  Component_Source_State API
         */

        /**
         * \brief Return the ID number of this Component_Source_State
         *
         * \return ID number
         */
        virtual boost::uint32_t get_ID (void) const;

        virtual void run ( infrastructure_types::Component_Actor::ptr_t,
                           infrastructure_types::Component_Graph::Data_Map_t* );

        virtual void switch_State ( infrastructure_types::Component_State::ptr_t state_ptr,
                                    boost::uint32_t mode );

        Component_Source_State& operator= ( Component_Source_State const& rhs );

        void swap ( Component_Source_State& rhs );

    private:

        // An algorithm has a pointer to the data to perform work
	infrastructure_types::Component_Data::ptr_t m_data_ptr;

    };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* COMPONENT_SOURCE_STATE_H_ */
