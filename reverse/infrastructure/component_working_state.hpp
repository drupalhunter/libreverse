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

#ifndef COMPONENT_WORKING_STATE_H_
#define COMPONENT_WORKING_STATE_H_

#include "infrastructure/Component_State_Algorithm.h"

namespace libreverse { namespace infrastructure {

    class Component_Working_State : public Component_State_Algorithm
    {
    public:

        /*!
         * \brief Constructor
         * \param id Unique id for the instance of this filter
         */
        explicit Component_Working_State ( infrastructure_types::Component_Data::ptr_t comp_ptr );

        /*!
         * \brief Copy constructor
         */
        Component_Working_State ( const Component_Working_State& ref );

        /*!
         * \brief Default constructor
         */
        virtual ~Component_Working_State(){}

        /**
         *  Component_Working_State API
         */

        /**
         * \brief Return the ID number of this Component_Working_State
         *
         * \return ID number
         */
        virtual boost::uint32_t get_ID (void) const;

        virtual void run ( infrastructure_types::Component_Actor::ptr_t child_ptr,
                           infrastructure_types::Component_Graph::Data_Map_t* input_data_ptr );

        virtual void switch_State ( infrastructure_types::Component_State::ptr_t state_ptr,
                                    boost::uint32_t id );

        Component_Working_State& operator= ( Component_Working_State const& ref );

        void swap ( Component_Working_State& ref );

    private:

        // An algorithm has a pointer to the data to perform work
        infrastructure_types::Component_Data::ptr_t m_data_ptr;

    };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* COMPONENT_WORKING_STATE_H_ */
