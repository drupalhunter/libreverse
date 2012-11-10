/*  Data_Source_Test.cpp

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

#include "infrastructure/Configurator.h"
#include "Data_Source_Base.h"
#include "Data_Source_Factory_Base.h"
#include "Data_Transfer_Base.h"
#include "Data_Source_T.h"
#include "Database_Data_Transfer.h"
#include "File_Data_Transfer.h"
#include "Memory_Data_Transfer.h"
#include "Data_Source_Factory.h"

using namespace libreverse::infrastructure;

int main (int, char*)
{
  boost::shared_ptr<Configurator> cfg_ptr =
    Configurator::get_Configurator();

  boost::shared_ptr < Data_Source_Factory >
    string_fact_ptr = Data_Source_Factory::get_Factory();

  return 0;
}
