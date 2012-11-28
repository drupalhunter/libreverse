/*  Debug_Types.cpp

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

#include <reverse/io/input/file_readers/windows_pe/debug_types.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  std::string
	  debug_types::get_type_name ( boost::uint32_t type )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Debug_Types::get_Type_Name" );

	    std::string result = "";

	    switch ( type )
	      {
	      case image_debug_type_unknown:
                {
		  result = "pe:debug_type_unknown";
		  break;
                }
	      case image_debug_type_coff:
                {
		  result = "pe:debug_type_coff";
		  break;
                }
	      case image_debug_type_codeview:
                {
		  result = "pe:debug_type_codeview";
		  break;
                }
	      case image_debug_type_fpo:
                {
		  result = "pe:debug_type_frame_pointer_omission";
		  break;
                }
	      case image_debug_type_misc:
                {
		  result = "pe:debug_type_dbg_file_location";
		  break;
                }
	      case image_debug_type_exception:
                {
		  result = "pe:debug_type_copy_of_pdata";
		  break;
                }
	      case image_debug_type_fixup:
                {
		  result = "pe:debug_type_reserved";
		  break;
                }
	      case image_debug_type_omap_to_src:
                {
		  result = "pe:debug_type_mapping_omap_to_src";
		  break;
                }
	      case image_debug_type_omap_from_src:
                {
		  result = "pe:debug_type_mapping_omap_from_src";
		  break;
                }
	      case image_debug_type_borland:
                {
		  result = "pe:debug_type_borland_reserved";
		  break;
                }
	      case image_debug_type_reserved10:
                {
		  result = "pe:debug_type_reserved_10";
		  break;
                }
	      case image_debug_type_clsid:
                {
		  result = "pe:debug_type_reserved_clsid";
		  break;
                }
	      }

	    std::stringstream output;
	    output << boost::format("%1s (%2x)") % result % type;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Debug_Types::get_Type_Name" );

	    return output.str();
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


