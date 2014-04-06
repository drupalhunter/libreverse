/*  Data_Section_Detector_WPEF32_Algorithm.h

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

#ifndef DATA_SECTION_DETECTOR_WPEF32_ALGORITHM_H
#define DATA_SECTION_DETECTOR_WPEF32_ALGORITHM_H

#include "Data_Section_Detector_Algorithm.h"

#include "io/IO_Types.h"

namespace reverse {

    namespace component {

      class Data_Section_Detector_WPEF32_Algorithm : public Data_Section_Detector_Algorithm {
      public:
	
	typedef boost::shared_ptr<Data_Section_Detector_WPEF32_Algorithm> ptr_t;

	virtual ~Data_Section_Detector_WPEF32_Algorithm(){}

	virtual meta::meta_object::ptr_t run ( io_types::File_ID::const_ptr_t file_ptr );
      };

    } /* namespace component */
} /* namespace reverse */

#endif /* DATA_SECTION_DETECTOR_WPEF32_ALGORITHM_H */
