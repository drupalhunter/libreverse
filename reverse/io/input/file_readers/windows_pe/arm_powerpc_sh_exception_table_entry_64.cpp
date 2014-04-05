/*  ARM_POWERPC_SH_Exception_Table_Entry_64.cpp

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

#include <reverse/io/input/file_readers/windows_pe/arm_powerpc_sh_exception_table_entry_64.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_file.hpp>

#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  arm_powerpc_sh_exception_table_entry_64::arm_powerpc_sh_exception_table_entry_64 ()
	    : m_begin_address ( 0 ),
	      m_prolog_length ( 0 ),
	      m_function_length ( 0 ),
	      m_32bit_flag ( false ),
	      m_exception_flag ( false )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside ARM_POWERPC_SH_Exception_Table_Entry_64 () constructor" );
	  }

	  void
	    arm_powerpc_sh_exception_table_entry_64::read_entry ( boost::shared_ptr < pe_file > file_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering ARM_POWERPC_SH_Exception_Table_Entry_64::read_Entry" );

	    file_ptr->read_arm_powerpc_sh_exception ( this->shared_from_this() );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting ARM_POWERPC_SH_Exception_Table_Entry_64::read_Entry" );
	  }

	  std::string
	  arm_powerpc_sh_exception_table_entry_64::to_string (void)
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering ARM_POWERPC_SH_Exception_Table_Entry_64::to_String" );

	    std::stringstream output;

	    output << boost::format("   begin address: 0x%|1X|") % m_begin_address
		   << std::endl
		   << boost::format("   prolog length: 0x%|1X|") % static_cast<boost::uint16_t>(m_prolog_length)
		   << std::endl
		   << boost::format("   function length: 0x%|1X|") % m_function_length
		   << std::endl
		   << "  32bit flag: ";

	    if ( m_32bit_flag )
	      {
                output << "TRUE" << std::endl;
	      }
	    else
	      {
                output << "FALSE" << std::endl;
	      }

	    output << "  Exception flag set: ";

	    if ( m_exception_flag )
	      {
                output << "TRUE" << std::endl;
	      }
	    else
	      {
                output << "FALSE" << std::endl;
	      }

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting ARM_POWERPC_SH_Exception_Table_Entry_64::to_String" );

	    return output.str();
	  }

	  void
	  arm_powerpc_sh_exception_table_entry_64::convert ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering ARM_POWERPC_SH_Exception_Table_Entry_64::convert" );
	    /* There is no need to convert a ARM binary exception table
	       entry since both the ARM (target) and Intel (host running
	       reverse) are both little endian */
	  }

  	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

