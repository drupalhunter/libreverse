/*  Entry_Point_Detector_Elf64_Algorithm.cpp

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

#include "Entry_Point_Detector_Elf64_Algorithm.h"
#include "Entry_Point_Detector.h"

#include "io/File_ID.h"
#include "io/input/File_Readers/Elf/Elf_Reader_64.h"
#include "io/input/File_Readers/Elf/Elf_Header_64.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace component {

    meta::meta_object::ptr_t
    Entry_Point_Detector_Elf64_Algorithm::run ( io_types::File_ID::const_ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Entering Entry_Point_Detector_Elf64_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */


      elf_types::Elf_Reader_64::ptr_t file_reader_ptr ( new elf_module::Elf_Reader_64 ( file_ptr ) );
      file_reader_ptr->read_Headers();

      elf_types::Elf_Header_64::ptr_t elf_hdr_ptr = file_reader_ptr->get_Header();

      meta::meta_object::ptr_t meta_ptr ( new meta::meta_object() );

      // Exception is thrown if a '.text' section is not found. We
      // will not catch it because we are expecting a section header
      // to contain the executable data. Therefore we will stop
      // processing the target file.
      elf_types::Elf_File_Header_64::const_ptr_t elf_file_hdr_ptr = elf_hdr_ptr->get_File_Header ();

      std::string entry_point_address = boost::str ( boost::format ("%1%" ) % elf_file_hdr_ptr->get_Entry() );

      meta_ptr->add ( "entry_point_address",
		      entry_point_address,
		      meta::meta_object::HEX );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Exiting Entry_Point_Detector_Elf64_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */


      return meta_ptr;
    }

} /* namespace component */
} /* namespace libreverse */

