/*  Tevis_Unknown_Region_Checker_Algorithm.h

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

#ifndef TEVIS_UNKNOWN_REGION_CHECKER_ALGORITHM_H
#define TEVIS_UNKNOWN_REGION_CHECKER_ALGORITHM_H

#include "infrastructure/Component.h"
#include "data_containers/Data_Types.h"
#include "meta/meta_object.h"

namespace libreverse {

    namespace component {

        class Tevis_Unknown_Region_Checker_Algorithm {
        public:

            typedef boost::shared_ptr<Tevis_Unknown_Region_Checker_Algorithm> ptr_t;

            virtual ~Tevis_Unknown_Region_Checker_Algorithm(){}

            virtual std::string run ( std::string filename ) = 0;
        };

    } /* namespace component */
} /* namespace libreverse */

#endif /* UNPACKAGE_ALGORITHM_H */
