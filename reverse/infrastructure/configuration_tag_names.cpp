/*  Configuration_Tag_Names.cpp

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

#include <reverse/infrastructure/configuration_tag_names.hpp>

namespace reverse {
  namespace infrastructure {

    std::string const configuration_tag_names::TAG_TRANSFER_TYPE = "transfer_type";
    std::string const configuration_tag_names::TAG_FORMULA_DIRECTORY = "formula_directory";
    std::string const configuration_tag_names::TAG_FILE_PREFIX = "file_prefix";
    std::string const configuration_tag_names::TAG_DATABASE = "database";
    std::string const configuration_tag_names::TAG_MEMORY = "memory";
    std::string const configuration_tag_names::TAG_HOST = "host";
    std::string const configuration_tag_names::TAG_USER = "user";
    std::string const configuration_tag_names::TAG_PASSWORD = "password";
    std::string const configuration_tag_names::TAG_GRNN_DATA_FILE = "grnn_data_file";

  } /* namespace infrastructure */
} /* namespace reverse */
