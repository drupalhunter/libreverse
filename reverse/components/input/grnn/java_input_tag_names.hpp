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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_JAVA_INPUT_TAG_NAMES_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_JAVA_INPUT_TAG_NAMES_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {
    
	class java_input_tag_names {
	public:
	  static std::string const tag_target_id;
	  static std::string const tag_this_index;
	  static std::string const tag_super_index;
	  static std::string const tag_version;
	  static std::string const tag_constant_pool_count;
	  static std::string const tag_constant_pool_info;
	  static std::string const tag_file;
	  static std::string const tag_data;
	  static std::string const tag_filesize;
	  static std::string const tag_field_count;
	  static std::string const tag_method_count;
	  static std::string const tag_constant_info_tag;
	  static std::string const tag_constant_info_tag_count;
	  static std::string const tag_constant_info_tag_ratio;
	  static std::string const tag_maximum;
	  static std::string const tag_value;
	  static std::string const tag_max_value_key;
	  static std::string const tag_max_value_float;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // REVERSE_COMPONENTS_INPUT_GRNN_JAVA_INPUT_TAG_NAMES_HPP_INCLUDED
