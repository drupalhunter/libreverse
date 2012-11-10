/*  Code_Section_Detector_Algorithm_Factory.h

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

#ifndef CODE_SECTION_DETECTOR_ALGORITHM_FACTORY_H
#define CODE_SECTION_DETECTOR_ALGORITHM_FACTORY_H

#include "Code_Section_Detector_Algorithm.h"

namespace libreverse { namespace component {

    class Code_Section_Detector_Algorithm_Factory {
    public:

        // pointer type
        typedef boost::shared_ptr<Code_Section_Detector_Algorithm_Factory> ptr_t;

        static Code_Section_Detector_Algorithm_Factory& Instance()
        {
            static Code_Section_Detector_Algorithm_Factory fact_ref;
            return fact_ref;
        }

        Code_Section_Detector_Algorithm::ptr_t get_Algorithm ( std::string file_type );

    private:

      Code_Section_Detector_Algorithm_Factory (){}

      Code_Section_Detector_Algorithm_Factory ( const Code_Section_Detector_Algorithm_Factory& );
      
      Code_Section_Detector_Algorithm_Factory& operator = ( const Code_Section_Detector_Algorithm_Factory& );
      
      ~Code_Section_Detector_Algorithm_Factory (){}
    };

} /* namespace component */
} /* namespace libreverse */

#endif /* CODE_SECTION_DETECTOR_ALGORITHM_FACTORY_H */
