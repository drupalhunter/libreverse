/*  Arch_Type_Detector_Algorithm_Factory.h

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

#ifndef ARCH_TYPE_DETECTOR_ALGORITHM_FACTORY_H
#define ARCH_TYPE_DETECTOR_ALGORITHM_FACTORY_H

#include "Arch_Type_Detector_Algorithm.h"

namespace libreverse { namespace component {

    class Arch_Type_Detector_Algorithm_Factory {
    public:

        // pointer type
        typedef boost::shared_ptr<Arch_Type_Detector_Algorithm_Factory> ptr_t;

        static Arch_Type_Detector_Algorithm_Factory& Instance()
        {
            static Arch_Type_Detector_Algorithm_Factory fact_ref;
            return fact_ref;
        }

        Arch_Type_Detector_Algorithm::ptr_t get_Algorithm ( std::string file_type );

    private:

      Arch_Type_Detector_Algorithm_Factory (){}

      Arch_Type_Detector_Algorithm_Factory ( const Arch_Type_Detector_Algorithm_Factory& );
      
      Arch_Type_Detector_Algorithm_Factory& operator = ( const Arch_Type_Detector_Algorithm_Factory& );
      
      ~Arch_Type_Detector_Algorithm_Factory (){}
    };

} /* namespace component */
} /* namespace libreverse */

#endif /* ARCH_TYPE_DETECTOR_ALGORITHM_FACTORY_H */
