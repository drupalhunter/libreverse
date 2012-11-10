/*  Candidate_Solution.cpp

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
// C++ Implementation: Candidate_Solution
//
// Description:
//
//
// Author: Stephen Torri, Winard Britt <storri@dell>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Candidate_Solution.h"


#include <boost/format.hpp>
#include <sstream>

using namespace libreverse::alloc;

namespace libreverse
{

  namespace classifier
  {

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    Candidate_Solution<Classifier_Type, Data_Type>::Candidate_Solution ( double sigma,
							double fitness,
							typename classifier_types::Configuration<Data_Type>::ptr_t config )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    Candidate_Solution<Classifier_Type, Data_Type>::Candidate_Solution ( const Candidate_Solution& rhs )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void
    Candidate_Solution<Classifier_Type, Data_Type>::evaluate ( typename classifier_types::Training_Set<Data_Type>::ptr_t data )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void Candidate_Solution<Classifier_Type, Data_Type>::test ( typename classifier_types::Training_Set<Data_Type>::ptr_t data )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void Candidate_Solution<Classifier_Type, Data_Type>::set_Sigma ( double new_sigma )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    double
    Candidate_Solution<Classifier_Type, Data_Type>::get_Fitness ( void ) const

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    double
    Candidate_Solution<Classifier_Type, Data_Type>::get_Sigma ( void ) const

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    typename classifier_types::Configuration<Data_Type>::ptr_t
    Candidate_Solution<Classifier_Type, Data_Type>::get_Config ( void )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>    
    std::string
    Candidate_Solution<Classifier_Type, Data_Type>::to_String ( void )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void Candidate_Solution<Classifier_Type, Data_Type>::set_Iteration_Count ( boost::uint32_t count )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    double Candidate_Solution<Classifier_Type, Data_Type>::get_Mean_Distance_Squared ( void ) const

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    boost::uint32_t
    Candidate_Solution<Classifier_Type, Data_Type>::get_Iteration_Count ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
			   TraceLevel::DETAIL,
			   "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Iteration_Count" );
#endif /* LIBREVERSE_DEBUG */


      return m_iteration_count;
    }

  } /* namespace classifier */
} /* namespace libreverse */
