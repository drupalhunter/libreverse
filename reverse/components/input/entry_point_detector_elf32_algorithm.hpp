/*  Entry_Point_Detector_Elf32_Algorithm.h

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

#ifndef ENTRY_POINT_DETECTOR_Elf32_ALGORITHM_H
#define ENTRY_POINT_DETECTOR_Elf32_ALGORITHM_H

#include "Entry_Point_Detector_Algorithm.h"

#include "io/IO_Types.h"

namespace libreverse {

    namespace component {

      class Entry_Point_Detector_Elf32_Algorithm : public Entry_Point_Detector_Algorithm {
      public:
	
	typedef boost::shared_ptr<Entry_Point_Detector_Elf32_Algorithm> ptr_t;

	virtual ~Entry_Point_Detector_Elf32_Algorithm(){}

	virtual meta::Meta_Object::ptr_t run ( io_types::File_ID::const_ptr_t file_ptr );
      };

    } /* namespace component */
} /* namespace libreverse */

#endif /* ENTRY_POINT_DETECTOR_Elf32_ALGORITHM_H */
