/*  Statistical.cpp

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
#include "Statistical.h"

#include "io/Preconditions.h"

#include <cmath>
#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
#endif /* LIBREVERSE_DEBUG */

namespace reverse
{
  namespace classifier
  {

    template <typename Data_Type>
    Statistical<Data_Type>::Statistical ( double sigma,
					  typename classifier_types::Training_Set<Data_Type>::Data_List_t const& training,
					  typename classifier_types::Configuration<Data_Type>::ptr_t config )

    template <typename Data_Type>
    double
    Statistical<Data_Type>::execute ( typename classifier_types::Training_Set<Data_Type>::Data_List_t const& target )

    template <typename Data_Type>
    double
    Statistical<Data_Type>::classify ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator& target_row )

    template <typename Data_Type>
    void
    Statistical<Data_Type>::calculate_Training_Stats ( void )


    template <typename Data_Type>
    void
    Statistical<Data_Type>::calculate_Column_Totals ( void )


    template <typename Data_Type>
    void
    Statistical<Data_Type>::calculate_Column_Averages ( void )


    template <typename Data_Type>
    void
    Statistical<Data_Type>::calculate_Column_Variances ( void )

    template <typename Data_Type>
    void
    Statistical<Data_Type>::calculate_Column_Standard_Deviations ( void )


    template <typename Data_Type>
    void
    Statistical<Data_Type>::calculate_Column_Bounds ( void )

    template <typename Data_Type>
    typename Statistical<Data_Type>::Double_List_t&
    Statistical<Data_Type>::get_List ( Compiler_Map_t& map_ref, double compiler_id )

    template <typename Data_Type>
    typename Statistical<Data_Type>::Double_List_t&
    Statistical<Data_Type>::get_Average_List ( double compiler_id )

    template <typename Data_Type>
    double
    Statistical<Data_Type>::get_Mean_Distance_Squared ( void ) const

  } /* namespace classifier */
} /* namespace reverse */
