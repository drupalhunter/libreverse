/*  Windows_Training_Data_Parser.cpp

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

#include <reverse/components/input/grnn/windows_input_tag_names.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	std::string const windows_input_tag_names::tag_data = "data";
	std::string const windows_input_tag_names::tag_target_id = "target_id";
	std::string const windows_input_tag_names::tag_file = "file";
	std::string const windows_input_tag_names::tag_file_size = "size";
	std::string const windows_input_tag_names::tag_exe_header_address = "exe_header_address";
	std::string const windows_input_tag_names::tag_coff_section_count = "coff_section_header_count";
	std::string const windows_input_tag_names::tag_pe_opt_linker_version = "pe_opt_linker_version";
	std::string const windows_input_tag_names::tag_pe_opt_code_size = "pe_opt_code_size";
	std::string const windows_input_tag_names::tag_pe_opt_base_of_data = "pe_opt_base_of_data";
	std::string const windows_input_tag_names::tag_pe_opt_entry_point = "pe_opt_entry_point";
	std::string const windows_input_tag_names::tag_pe_opt_image_size = "pe_opt_image_size";

      } // namespace input
    } // namespace grnn
  } // namespace components
} // namespace reverse

