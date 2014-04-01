/*  Unpacker_Algorithm.h

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

#ifndef UNPACKER_ALGORITHM_H
#define UNPACKER_ALGORITHM_H

#include "infrastructure/Component.h"
#include "data_containers/Data_Types.h"
#include "meta/meta_object.h"

namespace libreverse {

    namespace component {

        class Unpacker_Algorithm {
        public:

            typedef boost::shared_ptr<Unpacker_Algorithm> ptr_t;

            virtual ~Unpacker_Algorithm(){}

            virtual data_types::memory_map::const_ptr_t
            run ( meta::meta_object::const_ptr_t meta_ptr,
                  data_types::memory_map::const_ptr_t file_map_ptr ) = 0;

            virtual void print_Color_Map (void) = 0;

            virtual infrastructure_types::Component::Meta_List_t
            get_Meta_Input_List_Impl (void) = 0;

        };

    } /* namespace component */
} /* namespace libreverse */

#endif /* UNPACKAGE_ALGORITHM_H */
