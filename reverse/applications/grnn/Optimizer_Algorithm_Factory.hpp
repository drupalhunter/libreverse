/* Optimizer_Algorithm_Factory.h

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
#ifndef OPTIMIZER_ALGORITHM_FACTORY_H
#define OPTIMIZER_ALGORITHM_FACTORY_H

#include "Optimizer_Types.h"

#include "reverse/components/input/grnn/GRNN_Data_Types.h"

#include <string>

#ifdef LIBREVERSE_DEBUG
#include <reverse/Reverse.h>
#include <reverse/Trace.h>
using namespace reverse::trace;
using namespace reverse::api;
#endif

namespace reverse {
  namespace optimizer {

    class Optimizer_Algorithm_Factory {
    public:

      static Optimizer_Algorithm_Factory& Instance()
      {
	
#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::CLASSIFIER,
			     TraceLevel::DETAIL,
			     "Inside Candidate_Algorithm_Factory::Instance" );
#endif /* LIBREVERSE_DEBUG */

	static Optimizer_Algorithm_Factory fact_ref;
	return fact_ref;
      }

      template <template <typename Data_Type> class Classifier_Type>
      typename optimizer_types::Optimizer_Algorithm::ptr_t get_Algorithm ( classifier::GRNN_Data_Types::Value_Type type );

    private:

      Optimizer_Algorithm_Factory (){}

      Optimizer_Algorithm_Factory ( const Optimizer_Algorithm_Factory& ){}
      
      Optimizer_Algorithm_Factory& operator = ( const Optimizer_Algorithm_Factory& ){}
      
      ~Optimizer_Algorithm_Factory (){}

    };

  } /* namespace optimizer */
} /* namespace reverse */

#include "Optimizer_Algorithm_Factory.cpp"

#endif /* OPTIMIZER_ALGORITHM_FACTORY_H */

