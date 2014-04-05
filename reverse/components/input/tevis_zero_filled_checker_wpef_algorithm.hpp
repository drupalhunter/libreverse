/*  Tevis_Zero_Filled_Checker_WPEF_Algorithm.h

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

#ifndef TEVIS_ZERO_FILLED_CHECKER_WPEF_ALGORITHM_H
#define TEVIS_ZERO_FILLED_CHECKER_WPEF_ALGORITHM_H

#include "Tevis_Zero_Filled_Checker_Algorithm.h"
#include "meta/meta_object.h"

namespace reverse { namespace component {

    class Tevis_Zero_Filled_Checker_WPEF_Algorithm : public Tevis_Zero_Filled_Checker_Algorithm {
    public:

        virtual std::string run ( std::string filename );

    };

} /* namespace component */
} /* namespace reverse */

#endif /* UNPACKAGE_WPEF_ALGORITHM_H */
