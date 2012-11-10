/*  Arch_Type_Detector_Algorithm.h

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

#ifndef ARCH_TYPE_DETECTOR_ALGORITHM_H
#define ARCH_TYPE_DETECTOR_ALGORITHM_H

#include "io/IO_Types.h"

namespace libreverse {

    namespace component {

        class Arch_Type_Detector_Algorithm {
        public:

            typedef boost::shared_ptr<Arch_Type_Detector_Algorithm> ptr_t;

            virtual ~Arch_Type_Detector_Algorithm(){}

            virtual std::string run ( io_types::File_ID::const_ptr_t file_ptr ) = 0;
        };

    } /* namespace component */
} /* namespace libreverse */

#endif /* UNPACKAGE_ALGORITHM_H */
