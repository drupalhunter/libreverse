/*  Compiler_Classifier_Algorithm_Factory.h

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

#ifndef COMPILER_CLASSIFIER_ALGORITHM_FACTORY_H_
#define COMPILER_CLASSIFIER_ALGORITHM_FACTORY_H_

#include "Classifier_Types.h"

namespace libreverse { namespace classifier {

    class Compiler_Classifier_Algorithm_Factory {
    public:

      static Compiler_Classifier_Algorithm_Factory& Instance()
      {
	static Compiler_Classifier_Algorithm_Factory fact_ref;
	return fact_ref;
      }

      /**
       * \brief Create a new Classifier Algorithm
       *
       * \pre None
       *
       * \post Classifier Algorithm is not null
       *
       * \return Return a Component pointer to the new File Type Detector
       */
      classifier_types::Classifier_Algorithm::ptr_t
      get_Classifier ( std::string type );

    private:

      Compiler_Classifier_Algorithm_Factory (){}

      Compiler_Classifier_Algorithm_Factory ( const Compiler_Classifier_Algorithm_Factory& ){}
      
      Compiler_Classifier_Algorithm_Factory& operator= ( const Compiler_Classifier_Algorithm_Factory& ){}
      
      ~Compiler_Classifier_Algorithm_Factory (){}

    };

  } /* namespace classifier */
} /* namespace libreverse */

#endif /* COMPILER_CLASSIFIER_ALGORITHM_FACTORY_H_ */
