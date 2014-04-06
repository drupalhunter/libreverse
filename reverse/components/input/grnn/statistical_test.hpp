/*  Statistical_Test.h

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

#ifndef STATISTICAL_TEST_H
#define STATISTICAL_TEST_H

#include "Statistical.h"
#include "Classifier_Types.h"

namespace reverse
{
  namespace classifier
  {

    class Statistical_Test
    {
    public:

      void test_Constructor ( void );

      void test_Column_Totals ( void );

      void test_Column_Averages ( void );

      void test_Column_Standard_Deviations ( void );

    private:

      void populate_PE_Training ( void );

      void test_Column_Standard_Deviations_Compiler_Zero ( Statistical<Windows_Training_Data> const& s_ref );

      void test_Column_Standard_Deviations_Compiler_One ( Statistical<Windows_Training_Data> const& s_ref );

      void test_Column_Standard_Deviations_Compiler_Two ( Statistical<Windows_Training_Data> const& s_ref );

      classifier_types::Training_Set<Windows_Training_Data>::Data_List_t m_pe_training;      
    };
  
  } /* namespace classifier */
} /* namespace reverse */

#endif /* STATISTICAL_TEST_H */
