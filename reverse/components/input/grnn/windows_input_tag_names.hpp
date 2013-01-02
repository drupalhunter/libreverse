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

#ifndef REVERSE_COMPONENTS_GRNN_INPUT_WINDOWS_INPUT_TAG_NAMES_HPP_INCLUDED
#define REVERSE_COMPONENTS_GRNN_INPUT_WINDOWS_INPUT_TAG_NAMES_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {
   
	class windows_input_tag_names {
	public:

	  static std::string const tag_data;
	  static std::string const tag_target_id;
	  static std::string const tag_file;
	  static std::string const tag_file_size;
	  static std::string const tag_exe_header_address;
	  static std::string const tag_coff_section_count;
	  static std::string const tag_pe_opt_linker_version;
	  static std::string const tag_pe_opt_code_size;
	  static std::string const tag_pe_opt_base_of_data;
	  static std::string const tag_pe_opt_entry_point;
	  static std::string const tag_pe_opt_image_size;

	};

      } // namespace input
    } // namespace grnn
  } // namespace components
} // namespace reverse


#endif /* ifdef REVERSE_COMPONENTS_GRNN_INPUT_WINDOWS_INPUT_TAG_NAMES_HPP_INCLUDED */
