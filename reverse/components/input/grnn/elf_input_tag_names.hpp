/*  Elf_Training_Data_Parser.h

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

#ifndef Elf_Input_Tag_Names_H
#define Elf_Input_Tag_Names_H

#include <string>

namespace libreverse {

  namespace classifier {
   
    class Elf_Input_Tag_Names {
    public:
      static std::string const TAG_TARGET_ID;
      static std::string const TAG_DATA;
      static std::string const TAG_FILE;
      static std::string const TAG_FILESIZE;
      static std::string const TAG_ENTRY_POINT_ADDRESS;
      static std::string const TAG_SECTION_HEADERS_START;
      static std::string const TAG_PROGRAM_HEADER_COUNT;
      static std::string const TAG_SECTION_HEADER_COUNT;
      static std::string const TAG_SECTION_HEADER_STRING_TABLE_INDEX;
      static std::string const TAG_TEXT_SECTION_SIZE;

    };

  } /* namespace classifier */
} /* namespace classifier */

#endif /* Elf_Input_Tag_Names_H */
