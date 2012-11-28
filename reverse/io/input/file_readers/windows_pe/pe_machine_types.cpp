/*  PE_Machine_Types.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_machine_types.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  std::string
	  pe_machine_types::get_string_name ( boost::uint16_t val )
	  {
	    std::string result;

	    switch ( val )
	      {
	      case image_file_machine_unknown:
                {
		  result = "pe:unknown";
		  break;
                }
	      case image_file_machine_am33:
                {
		  result = "pe:am33";
		  break;
                }
	      case image_file_machine_amd64:
                {
		  result = "pe:amd64";
		  break;
                }
	      case image_file_machine_ebc:
                {
		  result = "pe:ebc";
		  break;
                }
	      case image_file_machine_i386:
                {
		  result = "pe:i386";
		  break;
                }
	      case image_file_machine_ia64:
                {
		  result = "pe:ia64";
		  break;
                }
	      case image_file_machine_m32r:
                {
		  result = "pe:m32r";
		  break;
                }
	      case image_file_machine_mips16:
                {
		  result = "pe:mips16";
		  break;
                }
	      case image_file_machine_mipsfpu:
                {
		  result = "pe:mipsfpu";
		  break;
                }
	      case image_file_machine_mipsfpu16:
                {
		  result = "pe:mipsfpu16";
		  break;
                }
	      case image_file_machine_powerpc:
                {
		  result = "pe:powerpc";
		  break;
                }
	      case image_file_machine_powerpcfp:
                {
		  result = "pe:powerpc(fpu)";
		  break;
                }
	      case image_file_machine_r4000:
                {
		  result = "pe:r4000";
		  break;
                }
	      case image_file_machine_sh3:
                {
		  result = "pe:sh3";
		  break;
                }
	      case image_file_machine_sh3dsp:
                {
		  result = "pe:sh3dsp";
		  break;
                }
	      case image_file_machine_sh4:
                {
		  result = "pe:sh4";
		  break;
                }
	      case image_file_machine_sh5:
                {
		  result = "pe:sh5";
		  break;
                }
	      case image_file_machine_thumb:
                {
		  result = "pe:thumb";
		  break;
                }
	      case image_file_machine_wcemip:
                {
		  result = "pe:wcemip";
		  break;
                }
	      }

	    return result;
	  }

	  bool
	  pe_machine_types::is_valid_value ( boost::uint16_t val )
	  {
	    bool result = false;
	    switch ( val )
	      {
	      case image_file_machine_unknown:
	      case image_file_machine_am33:
	      case image_file_machine_amd64:
	      case image_file_machine_ebc:
	      case image_file_machine_i386:
	      case image_file_machine_ia64:
	      case image_file_machine_m32r:
	      case image_file_machine_mips16:
	      case image_file_machine_mipsfpu:
	      case image_file_machine_mipsfpu16:
	      case image_file_machine_powerpc:
	      case image_file_machine_powerpcfp:
	      case image_file_machine_r4000:
	      case image_file_machine_sh3:
	      case image_file_machine_sh3dsp:
	      case image_file_machine_sh4:
	      case image_file_machine_sh5:
	      case image_file_machine_thumb:
	      case image_file_machine_wcemip:
                {
		  result = true;
                }
	      }

	    return result;
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

