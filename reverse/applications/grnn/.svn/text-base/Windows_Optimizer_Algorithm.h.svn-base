/*  Windows_Optimizer_Algorithm.h

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

#ifndef WINDOWS_OPTIMIZER_ALGORITHM_H
#define WINDOWS_OPTIMIZER_ALGORITHM_H

#include "Optimizer_Algorithm.h"

#include <string>

#include "libreverse/components/input/grnn/Classifier_Types.h"
#include "libreverse/components/input/grnn/Windows_Training_Data.h"

namespace libreverse
{
  namespace optimizer
  {
    template <template <typename Data_Type> class Classifier_Type>
    class Windows_Optimizer_Algorithm : public Optimizer_Algorithm {
    public:

      virtual ~Windows_Optimizer_Algorithm(){}

      virtual void process ( std::list<std::string>& data_files );

      virtual std::string print_Results ( void );

      virtual void save_Data ( std::string output_string );

    private:

      typename classifier_types::Training_Set<classifier::Windows_Training_Data>::ptr_t m_input_data;

      typename classifier_types::Candidate_Solution<Classifier_Type, classifier::Windows_Training_Data>::ptr_t m_best_solution;
    };

  } /* namespace optimizer */
} /* namespace libreverse */

#include "Windows_Optimizer_Algorithm.cpp"

#endif /* WINDOWS_OPTIMIZER_ALGORITHM_H */
