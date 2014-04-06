/*  Unpacker_Java_Algorithm.cpp

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

#include "Unpacker_Java_Algorithm.h"
#include "data_containers/memory_map.h"
#include "meta/meta_object.h"

namespace reverse { namespace component {

    data_types::memory_map::const_ptr_t
    Unpacker_Java_Algorithm::run ( meta::meta_object::const_ptr_t,
                                   data_types::memory_map::const_ptr_t )
    {
        return data_types::memory_map::ptr_t();
    }

    void
    Unpacker_Java_Algorithm::create_Color_Map ()
    {}

    void
    Unpacker_Java_Algorithm::print_Color_Map (void)
    {}

    infrastructure_types::Component::Meta_List_t
    Unpacker_Java_Algorithm::get_Meta_Input_List_Impl (void)
    {
        infrastructure_types::Component::Meta_List_t result;
        result.push_back ( "arch_type" );
        return result;
    }


} /* namespace component */
} /* namespace reverse */

