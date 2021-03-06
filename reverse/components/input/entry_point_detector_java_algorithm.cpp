/*  Entry_Point_Detector_Java_Algorithm.cpp

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

#include "Entry_Point_Detector_Java_Algorithm.h"
#include "Entry_Point_Detector.h"

#include "io/File_ID.h"
#include "io/input/File_Readers/Elf/Elf_Reader_64.h"
#include "io/input/File_Readers/Elf/Elf_Header_64.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace component {

    meta::meta_object::ptr_t
    Entry_Point_Detector_Java_Algorithm::run ( io_types::File_ID::const_ptr_t )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Entering Entry_Point_Detector_Java_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */

      /* NOTE: It is interesting to note that Elf and PE have only one
	 section that contains all their executable data. Java class
	 files do not. They have all the data for each function within
	 the Method Object. There we do not have a definitive address
	 where the data starts and how long it is.
       */
      meta::meta_object::ptr_t meta_ptr ( new meta::meta_object() );

      meta_ptr->add ( "entry_point_address",
		      "0",
		      meta::meta_object::HEX );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Exiting Entry_Point_Detector_Java_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */


      return meta_ptr;
    }

} /* namespace component */
} /* namespace reverse */

