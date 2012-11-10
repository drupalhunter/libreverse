/*  Elf_Classifier_Algorithm.h

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

#ifndef ELF_CLASSIFIER_ALGORITHM_H
#define ELF_CLASSIFIER_ALGORITHM_H

#include "Classifier_Algorithm.h"
#include <string>
#include "meta/Meta_Object.h"

namespace libreverse
{
  namespace classifier
  {
    class Elf_Classifier_Algorithm : public Classifier_Algorithm {
    public:

      virtual ~Elf_Classifier_Algorithm(){}

      virtual meta::Meta_Object::ptr_t execute ( std::string filename );

    private:

      std::string get_Compiler_Name ( double value );

      meta::Meta_Object::ptr_t process_File ( libreverse::elf_module::Elf_Reader_32 const& reader32_obj ) const;

      meta::Meta_Object::ptr_t process_File ( libreverse::elf_module::Elf_Reader_64 const& reader64_obj ) const;

      enum Values {
	GCC_4_1 = 0,
	PGCC = 1,
	INTEL = 2
      };
    };

  } /* namespace classifier */
} /* namespace libreverse */

#endif /* ELF_CLASSIFIER_ALGORITHM_H */
