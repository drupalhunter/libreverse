/*  Windows_Input_Tag_Names.h

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

#ifndef Windows_Input_Tag_Names_H
#define Windows_Input_Tag_Names_H

#include <string>

namespace libreverse {

  namespace classifier {
   
    class Windows_Input_Tag_Names {
    public:
      static std::string const TAG_DATA;
      static std::string const TAG_TARGET_ID;
      static std::string const TAG_FILE;
      static std::string const TAG_FILE_SIZE;
      static std::string const TAG_EXE_HEADER_ADDRESS;
      static std::string const TAG_COFF_SECTION_COUNT;
      static std::string const TAG_PE_OPT_LINKER_VERSION;
      static std::string const TAG_PE_OPT_CODE_SIZE;
      static std::string const TAG_PE_OPT_BASE_OF_DATA;
      static std::string const TAG_PE_OPT_ENTRY_POINT;
      static std::string const TAG_PE_OPT_IMAGE_SIZE;
    };

  } /* namespace classifier */
} /* namespace classifier */

#endif /* Windows_Input_Tag_Names_H */
