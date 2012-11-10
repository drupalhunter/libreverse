/*  Optimizer_Algorithm.h

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

#ifndef OPTIMIZER_ALGORITHM_H
#define OPTIMIZER_ALGORITHM_H

#include <list>
#include <string>

namespace libreverse
{
  namespace optimizer
  {
    class Optimizer_Algorithm {
    public:

      virtual ~Optimizer_Algorithm(){}
      
      virtual void process ( std::list<std::string>& ) {};

      virtual std::string print_Results ( void ) = 0;

      virtual void save_Data ( std::string output_string ) = 0;
    };

  } /* namespace optimizer */
} /* namespace libreverse */

#endif /* OPTIMIZER_ALGORITHM_H */
