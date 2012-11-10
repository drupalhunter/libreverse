/*  Java_Training_Data_Parser.h

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

#ifndef Java_Input_Tag_Names_H
#define Java_Input_Tag_Names_H

#include <string>

namespace libreverse {

  namespace classifier {
   
    class Java_Input_Tag_Names {
    public:
      static std::string const TAG_TARGET_ID;
      static std::string const TAG_THIS_INDEX;
      static std::string const TAG_SUPER_INDEX;
      static std::string const TAG_VERSION;
      static std::string const TAG_CONSTANT_POOL_COUNT;
      static std::string const TAG_CONSTANT_POOL_INFO;
      static std::string const TAG_FILE;
      static std::string const TAG_DATA;
      static std::string const TAG_FILESIZE;
      static std::string const TAG_FIELD_COUNT;
      static std::string const TAG_METHOD_COUNT;
      static std::string const TAG_CONSTANT_INFO_TAG;
      static std::string const TAG_CONSTANT_INFO_TAG_COUNT;
      static std::string const TAG_CONSTANT_INFO_TAG_RATIO;
      static std::string const TAG_MAXIMUM;
      static std::string const TAG_VALUE;
      static std::string const TAG_MAX_VALUE_KEY;
      static std::string const TAG_MAX_VALUE_FLOAT;
    };

  } /* namespace classifier */
} /* namespace classifier */

#endif /* Java_Input_Tag_Names_H */
