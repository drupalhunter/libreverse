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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_ELF_INPUT_TAG_NAMES_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_ELF_INPUT_TAG_NAMES_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {
   
	class elf_input_tag_names {
	public:
	  static std::string const tag_target_id;
	  static std::string const tag_data;
	  static std::string const tag_file;
	  static std::string const tag_filesize;
	  static std::string const tag_entry_point_address;
	  static std::string const tag_section_headers_start;
	  static std::string const tag_program_header_count;
	  static std::string const tag_section_header_count;
	  static std::string const tag_section_header_string_table_index;
	  static std::string const tag_text_section_size;

	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif /* ifndef REVERSE_COMPONENTS_INPUT_GRNN_ELF_INPUT_TAG_NAMES_HPP_INCLUDED */
