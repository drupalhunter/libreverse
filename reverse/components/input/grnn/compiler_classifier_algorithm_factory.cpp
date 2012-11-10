/*  Compiler_Classifier_Algorithm_Factory.cpp

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

#include "Compiler_Classifier_Algorithm_Factory.h"
#include "Java_Classifier_Algorithm.h"


#include <boost/format.hpp>

#include "io/input/File_Readers/Java_Class/Java_Meta_Info.h"
#include "Create.h"

using namespace libreverse::alloc;
using namespace libreverse::api;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace classifier {

    classifier_types::Classifier_Algorithm::ptr_t
    Compiler_Classifier_Algorithm_Factory::get_Classifier ( std::string type )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Compiler_Classifier_Algorithm_Factory::get_classifier" );
#endif /* LIBREVERSE_DEBUG */


      if ( type.compare ( java_module::Java_Meta_Info::FILE_TYPE ) == 0 )
	{
	  return Create::shared_pointer<Java_Classifier_Algorithm>();
	}
      else
	{
	  throw errors::Internal_Exception ( errors::Internal_Exception::UNSUPPORTED_FEATURE );
	}
    }

} /* namespace classifier */
} /* namespace libreverse */
