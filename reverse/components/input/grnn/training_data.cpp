/*  Training_Data.cpp

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

//
// C++ Implementation: Training_Data
//
// Description:
//
//
// Author: Stephen Torri, Winard Britt <storri@dell>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Training_Data.h"
#include "Configuration.h"
#include "Variable_Map.h"

#include <sstream>
#include <iostream>
#include <boost/format.hpp>

#include "Create.h"
#include "Reverse.h"
#include "errors/Internal_Exception.h"

using namespace reverse::alloc;
using namespace reverse::api;

#ifdef LIBREVERSE_DEBUG
using namespace reverse::trace;
#include "Trace.h"
#endif /* LIBREVERSE_DEBUG */

namespace reverse {

  namespace classifier
  {
    template <typename Data_Type>
    Training_Data<Data_Type>::Training_Data ()

    template <typename Data_Type>
    Training_Data<Data_Type>::~Training_Data ()

    template <typename Data_Type>
    classifier_types::Variable_Map::map_type::const_iterator
    Training_Data<Data_Type>::begin ( void ) const

    template <typename Data_Type>
    classifier_types::Variable_Map::map_type::iterator
    Training_Data<Data_Type>::begin ( void )

    template <typename Data_Type>
    classifier_types::Variable_Map::map_type::const_iterator
    Training_Data<Data_Type>::end ( void ) const

    template <typename Data_Type>
    classifier_types::Variable_Map::map_type::iterator
    Training_Data<Data_Type>::end ( void )

    template <typename Data_Type>
    std::string
    Training_Data<Data_Type>::get_Attribute_String_List ( typename classifier_types::Configuration<Data_Type>::ptr_t config )

    template <typename Data_Type>
    std::string
    Training_Data<Data_Type>::to_String ( typename classifier_types::Configuration<Data_Type>::ptr_t config ) const

    template <typename Data_Type>
    std::string
    Training_Data<Data_Type>::to_XML ( typename classifier_types::Configuration<Data_Type>::ptr_t config ) const

    template <typename Data_Type>
    bool
    Training_Data<Data_Type>::is_Valid (void) const

    template <typename Data_Type>
    void
    Training_Data<Data_Type>::set_Attribute ( boost::uint32_t index, double value )

    template <typename Data_Type>
    double
    Training_Data<Data_Type>::get_Attribute ( boost::uint32_t index ) const

    template <typename Data_Type>
    bool
    Training_Data<Data_Type>::empty ( void ) const
  } /* namespace classifier */
} /* namespace reverse */
