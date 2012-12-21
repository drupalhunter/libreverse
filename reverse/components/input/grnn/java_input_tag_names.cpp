/*  Java_Training_Data_Parser.cpp

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

#include <reverse/components/input/grnn/java_input_tag_names.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	std::string const java_input_tag_names::tag_target_id = "target_id";
	std::string const java_input_tag_names::tag_this_index = "this_class_index";
	std::string const java_input_tag_names::tag_super_index = "super_class_index";
	std::string const java_input_tag_names::tag_version = "version";
	std::string const java_input_tag_names::tag_constant_pool_count = "constant_pool_count";
	std::string const java_input_tag_names::tag_constant_pool_info = "constant_pool_info";
	std::string const java_input_tag_names::tag_data = "data";
	std::string const java_input_tag_names::tag_file = "file";
	std::string const java_input_tag_names::tag_filesize = "size";
	std::string const java_input_tag_names::tag_field_count = "field_count";
	std::string const java_input_tag_names::tag_method_count = "method_count";
	std::string const java_input_tag_names::tag_constant_info_tag = "tag";
	std::string const java_input_tag_names::tag_constant_info_tag_count = "count";
	std::string const java_input_tag_names::tag_constant_info_tag_ratio = "ratio";
	std::string const java_input_tag_names::tag_maximum = "maximum";
	std::string const java_input_tag_names::tag_value = "value";
	std::string const java_input_tag_names::tag_max_value_key = "key";
	std::string const java_input_tag_names::tag_max_value_float = "float";

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse
