
/*  Optimizer.cpp

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

#include "Optimizer.h"

#include "Create.h"


#include <iostream>
#include <boost/format.hpp>

using namespace libreverse::alloc;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace classifier
  {

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    Optimizer<Classifier_Type, Data_Type>::Optimizer()


    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void
    Optimizer<Classifier_Type, Data_Type>::init ( typename classifier_types::Training_Set<Data_Type>::ptr_t data,
						  double mutation_amount,
						  boost::uint32_t iteration_limit )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void
    Optimizer<Classifier_Type, Data_Type>::process ()

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t
    Optimizer<Classifier_Type, Data_Type>::test ()

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>    
    void
    Optimizer<Classifier_Type, Data_Type>::mutate_Attributes ( )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void
    Optimizer<Classifier_Type, Data_Type>::mutate_Sigma ()

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void
    Optimizer<Classifier_Type, Data_Type>::populate_Gene_Pool ( boost::uint32_t number )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t
    Optimizer<Classifier_Type, Data_Type>::get_Parent ()

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t
    Optimizer<Classifier_Type, Data_Type>::breed
    ( typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_one,
      typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_two )

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
    void
    Optimizer<Classifier_Type, Data_Type>::replace_Worst ()

  } /* namespace classifier */
} /* namespace libreverse */
