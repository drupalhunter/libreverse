/* Compiler_Dump_Algorithm_Factory.h

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
#ifndef COMPILER_DUMP_ALGORITHM_FACTORY_H
#define COMPILER_DUMP_ALGORITHM_FACTORY_H

#include "Optimizer_Types.h"

#include "reverse/components/input/grnn/GRNN_Data_Types.h"

#include <string>

namespace reverse {
  namespace optimizer {

    class Compiler_Dump_Algorithm_Factory {
    public:

      static Compiler_Dump_Algorithm_Factory& Instance();

      optimizer_types::Compiler_Dump_Algorithm::ptr_t get_Algorithm ( classifier::GRNN_Data_Types::Value_Type type );

    private:

      Compiler_Dump_Algorithm_Factory (){}

      Compiler_Dump_Algorithm_Factory ( const Compiler_Dump_Algorithm_Factory& ){}
      
      Compiler_Dump_Algorithm_Factory& operator = ( const Compiler_Dump_Algorithm_Factory& ){}
      
      ~Compiler_Dump_Algorithm_Factory (){}

    };

  } /* namespace optimizer */
} /* namespace reverse */

#endif /* COMPILER_DUMP_ALGORITHM_FACTORY_H */

