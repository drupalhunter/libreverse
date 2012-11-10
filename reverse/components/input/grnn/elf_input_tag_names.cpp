/*  Elf_Training_Data_Parser.cpp

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

#include <reverse/components/input/grnn/elf_input_tag_names.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	std::string const elf_input_tag_names::tag_target_id = "target_id";
	std::string const elf_input_tag_names::tag_data = "data";
	std::string const elf_input_tag_names::tag_file = "file";
	std::string const elf_input_tag_names::tag_filesize = "size";
	std::string const elf_input_tag_names::tag_entry_point_address = "entry_point_address";
	std::string const elf_input_tag_names::tag_section_headers_start = "section_headers_start";
	std::string const elf_input_tag_names::tag_program_header_count = "program_header_count";
	std::string const elf_input_tag_names::tag_section_header_count = "section_header_count";
	std::string const elf_input_tag_names::tag_section_header_string_table_index = "section_header_string_table_index";
	std::string const elf_input_tag_names::tag_text_section_size = "text_section_size";

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

