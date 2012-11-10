/*  Arch_Type_Detector.h

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

#ifndef ARCH_TYPE_DECTECTOR_H
#define ARCH_TYPE_DECTECTOR_H

#include "infrastructure/Component.h"
#include "infrastructure/Component_Actor.h"

#include <boost/enable_shared_from_this.hpp>

namespace libreverse {

    namespace component {

        class Arch_Type_Detector : public infrastructure::Component,
                                   public infrastructure::Component_Actor,
                                   public boost::enable_shared_from_this<Arch_Type_Detector>
        {
        public:

            explicit Arch_Type_Detector ();

            explicit Arch_Type_Detector ( infrastructure_types::Component_State::ptr_t input_ptr );

            Arch_Type_Detector ( Arch_Type_Detector const& rhs );

            virtual ~Arch_Type_Detector();

            Arch_Type_Detector& operator= ( Arch_Type_Detector const& rhs );

            void swap ( Arch_Type_Detector& rhs );

            //------------------------------
            // Component required functions
            //------------------------------
            virtual void received_Input_Source_Data ( boost::uint32_t id );
            
            virtual void add_Input_Source ( boost::uint32_t id );

            virtual std::string get_Name (void) const;

            virtual void run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data );

            virtual infrastructure_types::Data_Source_Base::ptr_t results (void);

            virtual void set_State ( boost::uint32_t mode );

            virtual boost::uint32_t get_ID (void) const;

            virtual infrastructure_types::Component_Data::Input_Token_t::const_iterator get_Source_List_Begin (void) const;

            virtual infrastructure_types::Component_Data::Input_Token_t::const_iterator get_Source_List_End (void) const;

            //------------------------------
            // Component Actor required functions
            //------------------------------
            virtual void process (void);

            //------------------------------
            // Component Creator required functions
            //------------------------------
	    virtual infrastructure_types::Component::ptr_t operator() ( infrastructure_types::Component_State::ptr_t data_ptr );

            static const std::string NAME;

        private:

            infrastructure_types::Component_State::ptr_t m_state_ptr;
        };
    } /* namespace component */
} /* namespace libreverse */

#endif /* ARCH_TYPE_DECTECTOR_H */
