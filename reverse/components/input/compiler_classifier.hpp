/*  Compiler_Classifier.h

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

#ifndef COMPILER_CLASSIFIER_H
#define COMPILER_CLASSIFIER_H

#include "infrastructure/Component.h"
#include "infrastructure/Component_Actor.h"

#include <boost/enable_shared_from_this.hpp>

namespace reverse {

    namespace component {

        class Compiler_Classifier : public infrastructure::Component,
                         public infrastructure::Component_Actor,
                         public boost::enable_shared_from_this<Compiler_Classifier>
        {
        public:

            explicit Compiler_Classifier ();

            explicit Compiler_Classifier ( infrastructure_types::Component_State::ptr_t state_ptr );

            Compiler_Classifier ( Compiler_Classifier const& rhs );

            virtual ~Compiler_Classifier();

            Compiler_Classifier& operator= ( Compiler_Classifier const& rhs );

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

        protected:

            static const std::string m_name;

        private:

            infrastructure_types::Component_State::ptr_t m_state_ptr;
        };
    } /* namespace component */
} /* namespace reverse */

#endif /* COMPILER_CLASSIFIER_H */
