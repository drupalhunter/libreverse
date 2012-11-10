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

#include <reverse/io/Byte_Converter.h>
#include <reverse/io/input/File_Readers/Windows_PE/AMD_IA_64_Exception_Table_Entry.h>
#include <reverse/io/input/File_Readers/Windows_PE/PE_File.h>

#include <boost/format.hpp>

#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  AMD_IA_64_Exception_Table_Entry::AMD_IA_64_Exception_Table_Entry()
	    : m_begin_address ( 0 ),
	      m_end_address ( 0 ),
	      m_unwind_information ( 0 )
	  {
	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Inside AMD_IA_64_Exception_Table_Entry () constructor" );
	  }

	  void
	  AMD_IA_64_Exception_Table_Entry::read_Entry ( wpef_types::PE_File::ptr_t file_ptr )
	  {
	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Entering AMD_IA_64_Exception_Table_Entry::read_Entry" );

	    file_ptr->read_AMD_IA_64_Exception ( this->shared_from_this() );

	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Exiting AMD_IA_64_Exception_Table_Entry::read_Entry" );
	  }

	  std::string
	  AMD_IA_64_Exception_Table_Entry::to_String (void)
	  {
	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Entering AMD_IA_64_Exception_Table_Entry::to_String" );

	    std::stringstream output;

	    output << boost::format("   begin address.....: 0x%|1X|") % m_begin_address
		   << std::endl
		   << boost::format("   end address.......: 0x%|1X|") % m_end_address
		   << std::endl
		   << boost::format("   unwind information: 0x%|1X|") % m_unwind_information
		   << std::endl;

	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Exiting AMD_IA_64_Exception_Table_Entry::to_String" );

	    return output.str();
	  }

	  void
	  AMD_IA_64_Exception_Table_Entry::convert ()
	  {
	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Entering AMD_IA_64_Exception_Table_Entry::convert" );

	    // NOTE: Itanium can be either little-endian or big endian so we have to check
	    io::Byte_Converter::convert ( m_begin_address );
	    io::Byte_Converter::convert ( m_end_address );
	    io::Byte_Converter::convert ( m_unwind_information );

	    Trace::write_Trace ( trace_area::IO,
				 trace_level::DETAIL,
				 "Exiting AMD_IA_64_Exception_Table_Entry::convert" );
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


