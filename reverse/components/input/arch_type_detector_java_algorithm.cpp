/*  Arch_Type_Detector_Java_Algorithm.cpp

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

#include "Arch_Type_Detector_Java_Algorithm.h"

#include "io/input/File_Readers/Java_Class/Reader.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace component {

    std::string
    Arch_Type_Detector_Java_Algorithm::run ( io_types::File_ID::const_ptr_t file_ptr  )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Entering Arch_Type_Detector_Java_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */


      java_types::Reader::ptr_t file_reader_ptr ( new java_module::Reader ( file_ptr ) );

      std::string result = file_reader_ptr->get_Arch_Type ();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Exiting Arch_Type_Detector_Java_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */


      return result;
    }

} /* namespace component */
} /* namespace libreverse */

