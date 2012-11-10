/*  main_test.cpp

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

#include "Elf_Reader_Factory.hpp"
#include <boost/shared_ptr.hpp>

using namespace libreverse::io;
using namespace libreverse::elf_module;

int main () {

  try {
    std::string filename ("/bin/cp");

    boost::shared_ptr<File_ID> target
      (new File_ID(filename));

    boost::shared_ptr<Elf_Reader_Factory> reader_factory_ptr =
      Elf_Reader_Factory::get_Factory();

    boost::shared_ptr<File_Reader> file_reader =
      reader_factory_ptr->create_Reader (target);
  
    file_reader->init();

    return 0;
  }
  catch (std::exception &ex)
    {
      std::cerr << "Caught: " << ex.what() << std::endl;
      exit(-1);
    }
};
