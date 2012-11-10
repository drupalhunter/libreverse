/*  symbol_test.cpp

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

#include <inttypes.h>
#include <iostream>
#include "Elf_Symbol_T.hpp"

int main (int, char*) {


  try
    {
      libreverse::elf_module::Elf_Symbol<32> a (3);
      a.get_size();
      a.size_of();

      return 0;
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return -1;
    }
}
