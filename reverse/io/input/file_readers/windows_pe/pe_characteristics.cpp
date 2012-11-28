/*  PE_Characteristics.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_characteristics.hpp>

#include <sstream>
#include <iostream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  const boost::uint16_t
	  pe_characteristics::pe_image_file_relocs_stripped = 0x0001;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_executable_image = 0x0002;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_line_nums_stripped = 0x0004;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_local_syms_stripped = 0x0008;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_aggressive_ws_trim = 0x0010;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_large_address_aware = 0x0020;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_reserved_bit = 0x0040;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_bytes_reversed_lo = 0x0080;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_32bit_machine = 0x0100;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_debug_stripped = 0x0200;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_removable_run_from_swap = 0x0400;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_net_run_from_swap = 0x0800;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_system = 0x1000;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_dll = 0x2000;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_up_system_only = 0x4000;

	  const boost::uint16_t
	  pe_characteristics::pe_image_file_bytes_reversed_hi = 0x8000;

	  std::string
	  pe_characteristics::get_string_name ( boost::uint16_t val )
	  {
	    std::string result;

	    switch ( val )
	      {
	      case pe_image_file_relocs_stripped:
                {
		  result = "pe:relocs_stripped";
		  break;
                }
	      case pe_image_file_executable_image:
                {
		  result = "pe:executable_image";
		  break;
                }
	      case pe_image_file_line_nums_stripped:
                {
		  result = "pe:line_nums_strippes";
		  break;
                }
	      case pe_image_file_local_syms_stripped:
                {
		  result = "pe:local_syms_stripped";
		  break;
                }
	      case pe_image_file_aggressive_ws_trim:
                {
		  result = "pe:aggressive_ws_trim";
		  break;
                }
	      case pe_image_file_large_address_aware:
                {
		  result = "pe:large_address_aware";
		  break;
                }
	      case pe_image_file_reserved_bit:
                {
		  result = "pe:reverse_bit";
		  break;
                }
	      case pe_image_file_bytes_reversed_lo:
                {
		  result = "pe:bytes_reversed_lo";
		  break;
                }
	      case pe_image_file_32bit_machine:
                {
		  result = "pe:32bit_machine";
		  break;
                }
	      case pe_image_file_debug_stripped:
                {
		  result = "pe:debug_stripped";
		  break;
                }
	      case pe_image_file_removable_run_from_swap:
                {
		  result = "pe:removable_run_from_swap";
		  break;
                }
	      case pe_image_file_net_run_from_swap:
                {
		  result = "pe:net_run_from_swap";
		  break;
                }
	      case pe_image_file_system:
                {
		  result = "pe:system_file";
		  break;
                }
	      case pe_image_file_dll:
                {
		  result = "pe:dynamic_link_library";
		  break;
                }
	      case pe_image_file_up_system_only:
                {
		  result = "pe:uniprocessor_system_only";
		  break;
                }
	      case pe_image_file_bytes_reversed_hi:
                {
		  result = "pe:bytes_reversed_hi";
		  break;
                }
	      }

	    return result;
	  }


	  std::string
	  pe_characteristics::get_string_name_list ( boost::uint16_t val )
	  {
	    std::stringstream output;

	    if ( val & pe_image_file_relocs_stripped )
	      {
                output << "    pe:relocs_stripped" << std::endl;
	      }
	    if ( val & pe_image_file_executable_image )
	      {
                output << "    pe:executable_image" << std::endl;
	      }
	    if ( val & pe_image_file_line_nums_stripped )
	      {
                output << "    pe:line_nums_stripped" << std::endl;
	      }
	    if ( val & pe_image_file_local_syms_stripped )
	      {
                output << "    pe:local_syms_stripped" << std::endl;
	      }
	    if ( val & pe_image_file_aggressive_ws_trim )
	      {
                output << "    pe:aggressive_ws_trim" << std::endl;
	      }
	    if ( val & pe_image_file_large_address_aware )
	      {
                output << "    pe:large_address_aware" << std::endl;
	      }
	    if ( val & pe_image_file_reserved_bit )
	      {
                output << "    pe:reverse_bit" << std::endl;
	      }
	    if ( val & pe_image_file_bytes_reversed_lo )
	      {
                output << "    pe:bytes_reversed_lo" << std::endl;
	      }
	    if ( val & pe_image_file_32bit_machine )
	      {
                output << "    pe:32bit_machine" << std::endl;
	      }
	    if ( val & pe_image_file_debug_stripped )
	      {
                output << "    pe:debug_stripped" << std::endl;
	      }
	    if ( val & pe_image_file_removable_run_from_swap )
	      {
                output << "    pe:removable_run_from_swap" << std::endl;
	      }
	    if ( val & pe_image_file_net_run_from_swap )
	      {
                output << "    pe:net_run_from_swap" << std::endl;
	      }
	    if ( val & pe_image_file_system )
	      {
                output << "    pe:system_file" << std::endl;
	      }
	    if ( val & pe_image_file_dll )
	      {
                output << "    pe:dynamic_link_library" << std::endl;
	      }
	    if ( val & pe_image_file_up_system_only )
	      {
                output << "    pe:uniprocessor_system_only" << std::endl;
	      }
	    if ( val & pe_image_file_bytes_reversed_hi )
	      {
                output << "    pe:bytes_reversed_hi" << std::endl;
	      }

	    return output.str();
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

