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

#include "Windows_Input_Tag_Names.h"

namespace libreverse
{
  namespace classifier
  {
    std::string const Windows_Input_Tag_Names::TAG_DATA = "data";
    std::string const Windows_Input_Tag_Names::TAG_TARGET_ID = "target_id";
    std::string const Windows_Input_Tag_Names::TAG_FILE = "file";
    std::string const Windows_Input_Tag_Names::TAG_FILE_SIZE = "size";
    std::string const Windows_Input_Tag_Names::TAG_EXE_HEADER_ADDRESS = "exe_header_address";
    std::string const Windows_Input_Tag_Names::TAG_COFF_SECTION_COUNT = "coff_section_header_count";
    std::string const Windows_Input_Tag_Names::TAG_PE_OPT_LINKER_VERSION = "pe_opt_linker_version";
    std::string const Windows_Input_Tag_Names::TAG_PE_OPT_CODE_SIZE = "pe_opt_code_size";
    std::string const Windows_Input_Tag_Names::TAG_PE_OPT_BASE_OF_DATA = "pe_opt_base_of_data";
    std::string const Windows_Input_Tag_Names::TAG_PE_OPT_ENTRY_POINT = "pe_opt_entry_point";
    std::string const Windows_Input_Tag_Names::TAG_PE_OPT_IMAGE_SIZE = "pe_opt_image_size";
  } /* namespace classifier */
} /* namespace libreverse */
