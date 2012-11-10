/* Optimizer_Algorithm_Factory.cpp

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
#include "Elf_Optimizer_Algorithm.h"
#include "Java_Optimizer_Algorithm.h"
#include "Optimizer_Algorithm_Factory.h"
#include "Windows_Optimizer_Algorithm.h"

#include "libreverse/errors/Internal_Exception.h"
#include <boost/format.hpp>

namespace libreverse {
  namespace optimizer {

    template <template <typename Data_Type> class Classifier_Type> 
    typename optimizer_types::Optimizer_Algorithm::ptr_t
    Optimizer_Algorithm_Factory::get_Algorithm ( classifier::GRNN_Data_Types::Value_Type type )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::CLASSIFIER,
			   TraceLevel::DETAIL,
			   "Entering Candidate_Algorithm_Factory::get_Algorithm" );
#endif /* LIBREVERSE_DEBUG */


      switch ( type )
	{
	case classifier::GRNN_Data_Types::JAVA_CLASS:
	  {
	    typename optimizer_types::Java_Optimizer_Algorithm<Classifier_Type>::ptr_t
	      obj_ptr ( new Java_Optimizer_Algorithm<Classifier_Type>() );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Algorithm_Factory::get_Algorithm" );
#endif /* LIBREVERSE_DEBUG */


	    return obj_ptr;
	  }
	case classifier::GRNN_Data_Types::LINUX_ELF:
	  {
	    typename optimizer_types::Elf_Optimizer_Algorithm<Classifier_Type>::ptr_t
	      obj_ptr ( new Elf_Optimizer_Algorithm<Classifier_Type>() );
	    

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Algorithm_Factory::get_Algorithm" );
#endif /* LIBREVERSE_DEBUG */


	    return obj_ptr;
	  }
	case classifier::GRNN_Data_Types::WINDOWS_PE:
	  {
	    typename optimizer_types::Windows_Optimizer_Algorithm<Classifier_Type>::ptr_t
	      obj_ptr ( new Windows_Optimizer_Algorithm<Classifier_Type>() );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Algorithm_Factory::get_Algorithm" );
#endif /* LIBREVERSE_DEBUG */


	    return obj_ptr;
	  }
	case classifier::GRNN_Data_Types::MAC_MACH_O:
	default:
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::ERROR,
				 boost::str ( boost::format ( "classifier::GRNN_Data_Types::get_Types - unknown type. %1%" ) % type ) );
	    
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::ERROR,
				 boost::str ( boost::format("Exception throw in %s at line %d")
					      % __FILE__
					      % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


	    throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
	  }
	}
    }

  } /* namespace optimizer */
} /* namespace libreverse */


