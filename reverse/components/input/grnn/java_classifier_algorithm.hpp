/*  Java_Classifier_Algorithm.h

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

#ifndef JAVA_CLASSIFIER_ALGORITHM_H
#define JAVA_CLASSIFIER_ALGORITHM_H

#include "Classifier_Algorithm.h"
#include <string>
#include "meta/Meta_Object.h"

namespace libreverse
{
  namespace classifier
  {
    class Java_Classifier_Algorithm : public Classifier_Algorithm {
    public:

      virtual ~Java_Classifier_Algorithm(){}

      virtual meta::Meta_Object::ptr_t execute ( std::string filename );

    private:

      std::string get_Compiler_Name ( double value );

      enum Values {
	SUN_JDK_6 = 0,
	SUN_JDK_5 = 1,
	ECJ = 2,
	JIKES = 3
      };
    };

  } /* namespace classifier */
} /* namespace libreverse */

#endif /* JAVA_CLASSIFIER_ALGORITHM_H */
