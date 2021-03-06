/*  Configuration_Tag_Names.h

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

#ifndef REVERSE_INFRASTRUCTURE_CONFIGURATION_TAG_NAMES_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_CONFIGURATION_TAG_NAMES_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace infrastructure {

    class configuration_tag_names {
    public:

      static std::string const TAG_TRANSFER_TYPE;
      static std::string const TAG_FORMULA_DIRECTORY;
      static std::string const TAG_FILE_PREFIX;
      static std::string const TAG_DATABASE;
      static std::string const TAG_MEMORY;
      static std::string const TAG_HOST;
      static std::string const TAG_USER;
      static std::string const TAG_PASSWORD;
      static std::string const TAG_GRNN_DATA_FILE;

      virtual ~configuration_tag_names(){}

    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_CONFIGURATION_TAG_NAMES_HPP_INCLUDED */

