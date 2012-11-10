/*  test_Elf_Version_Symbol.cpp

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

#include "Elf_Version_Symbol.hpp"
#include <iostream>
#include <boost/format.hpp>

using namespace boost;
using namespace std;
using namespace elf_module;

#define test_waypoint_mark(fmt) "test_Elf_Version_Symbol <%s: %d> " fmt, __FUNCTION__, __LINE__
#define test_printk_mark(fmt, args...) printf(test_waypoint_mark(fmt), ##args)
#define test_debug(fmt, args...) test_printk_mark(fmt, ## args)


int main () {

  Elf_Version_Symbol standard;
  Elf_Version_Symbol target;
  target.vs_vers = 0xFF00;

  /* If host and data endians are big-endian (true) */
  standard.vs_vers = 0xFF00;
  standard.convert(true,true);

  if (standard.vs_vers != target.vs_vers) {
    test_debug("true-true test failed\n");
    cout << format("standard.vs_vers: %1%  target: %2%") %
      standard.vs_vers % target.vs_vers << endl;
    return -1;
  }

  /* If host and data endians are big-endian (true) */
  standard.vs_vers = 0xFF00;
  target.vs_vers = 0xFF00;
  standard.convert(false,false);

  if (standard.vs_vers != target.vs_vers) {
    test_debug("false-false test failed\n");
    cout << format("standard.vs_vers: %1%  target: %2%") %
      standard.vs_vers % target.vs_vers << endl;
    return -1;
  }

  /* If host is big-endian (true) and data is little-endian (false) */
  standard.vs_vers = 0xFF00;
  target.vs_vers = 0x00FF;
  standard.convert (true,false);

  if (standard.vs_vers != target.vs_vers) {
    test_debug("true-false test failed\n");
    cout << format("standard.vs_vers: %1%  target: %2%") %
      standard.vs_vers % target.vs_vers << endl;
    return -1;
  }

  /* If host is big-endian (true) and data is little-endian (false) */
  standard.vs_vers = 0xFF00;
  target.vs_vers = 0x00FF;
  standard.convert (false,true);

  if (standard.vs_vers != target.vs_vers) {
    test_debug("false-true test failed\n");
    cout << format("standard.vs_vers: %1%  target: %2%") %
      standard.vs_vers % target.vs_vers << endl;
    return -1;
  }
  return 0;
}
