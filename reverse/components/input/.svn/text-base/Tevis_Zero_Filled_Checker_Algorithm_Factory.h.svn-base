/*  Tevis_Zero_Filled_Checker_Algorithm_Factory.h

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

#ifndef TEVIS_ZERO_FILLED_CHECKER_ALGORITHM_FACTORY_H
#define TEVIS_ZERO_FILLED_CHECKER_ALGORITHM_FACTORY_H

#include "Tevis_Zero_Filled_Checker_Algorithm.h"

namespace libreverse { namespace component {

    class Tevis_Zero_Filled_Checker_Algorithm_Factory {
    public:

        static Tevis_Zero_Filled_Checker_Algorithm_Factory& Instance ()
        {
            static Tevis_Zero_Filled_Checker_Algorithm_Factory fact_ref;
            return fact_ref;
        }

        Tevis_Zero_Filled_Checker_Algorithm::ptr_t get_Algorithm ( std::string name );

    private:

        
      Tevis_Zero_Filled_Checker_Algorithm_Factory (){}

      Tevis_Zero_Filled_Checker_Algorithm_Factory ( const Tevis_Zero_Filled_Checker_Algorithm_Factory& );
      
      Tevis_Zero_Filled_Checker_Algorithm_Factory& operator = ( const Tevis_Zero_Filled_Checker_Algorithm_Factory& );
      
      ~Tevis_Zero_Filled_Checker_Algorithm_Factory (){}
    };

} /* namespace component */
} /* namespace libreverse */

#endif /* UNPACKAGE_ALGORITHM_FACTORY_H */
