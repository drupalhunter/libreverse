/*  AMD_IA_64_Exception_Table_Entry.cpp

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

#include <reverse/io/byte_converter.hpp>
#include <reverse/io/input/file_readers/windows_pe/amd_ia_64_exception_table_entry.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_file.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  amd_ia_64_exception_table_entry::amd_ia_64_exception_table_entry()
	    : m_begin_address ( 0 ),
	      m_end_address ( 0 ),
	      m_unwind_information ( 0 )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside AMD_IA_64_Exception_Table_Entry () constructor" );
	  }

	  void
	  amd_ia_64_exception_table_entry::read_entry ( boost::shared_ptr < pe_file > file_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering AMD_IA_64_Exception_Table_Entry::read_Entry" );

	    file_ptr->read_amd_ia_64_exception ( this->shared_from_this() );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting AMD_IA_64_Exception_Table_Entry::read_Entry" );
	  }

	  std::string
	  amd_ia_64_exception_table_entry::to_string (void)
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering AMD_IA_64_Exception_Table_Entry::to_String" );

	    std::stringstream output;

	    output << boost::format("   begin address.....: 0x%|1X|") % m_begin_address
		   << std::endl
		   << boost::format("   end address.......: 0x%|1X|") % m_end_address
		   << std::endl
		   << boost::format("   unwind information: 0x%|1X|") % m_unwind_information
		   << std::endl;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting AMD_IA_64_Exception_Table_Entry::to_String" );

	    return output.str();
	  }

	  void
	  amd_ia_64_exception_table_entry::convert ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering AMD_IA_64_Exception_Table_Entry::convert" );

	    // NOTE: Itanium can be either little-endian or big endian so we have to check
	    io::byte_converter::convert ( m_begin_address );
	    io::byte_converter::convert ( m_end_address );
	    io::byte_converter::convert ( m_unwind_information );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting AMD_IA_64_Exception_Table_Entry::convert" );
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


