/*  Coff_Header.cpp

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
#include <reverse/io/input/file_readers/windows_pe/coff_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_machine_types.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_characteristics.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>

#include <sstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  coff_header::coff_header()
	    : m_machine ( 0 ),
	      m_number_of_sections ( 0 ),
	      m_time_date_stamp ( 0 ),
	      m_pointer_to_symbol_table ( 0 ),
	      m_number_of_symbols ( 0 ),
	      m_size_of_optional_header ( 0 ),
	      m_characteristics ( 0 )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside COFF_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  /*!
	   * \brief Convert the header data into a string representation
	   * \return String representation of header data
	   */
	  std::string
	  coff_header::to_string ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering COFF_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream output_str;

	    output_str << "COFF Header:" << std::endl;

	    output_str << boost::format ( "  Machine:              %1%" )
	      % boost::io::group ( std::hex,
				   m_machine );
	    
	    output_str << " (" << this->get_machine_name() << ")" << std::endl;

	    boost::posix_time::ptime epoch ( boost::gregorian::date ( 1970, 1, 1 ) );
	    boost::posix_time::seconds s_time ( m_time_date_stamp );
	    boost::posix_time::ptime creation_date = epoch + s_time;

	    output_str << boost::format ( "  Number of sections:  %1%" )
	      % boost::io::group ( std::hex,
				   m_number_of_sections )
		       << std::endl;

	    output_str << "  Time stamp: "
		       << boost::posix_time::to_simple_string ( creation_date )
		       << std::endl;
	    
	    output_str << boost::format ( "  Symbol Token offset:  %1%" ) %
	      boost::io::group ( std::hex,
				 m_pointer_to_symbol_table )
		       << std::endl;

	    output_str << boost::format ( "  Number of symbols:    %1%" ) %
	      boost::io::group ( std::hex,
				 m_number_of_symbols )
		       << std::endl;
	    
	    output_str << boost::format ( "  Optional header size: %1%" ) %
	      boost::io::group ( std::hex,
				 m_size_of_optional_header )
		       << std::endl;
	    
	    output_str << boost::format ( "  Characteristics: %1%" ) %
	      boost::io::group ( std::hex,
				 m_characteristics )
		       << std::endl
		       << this->get_characteristics_string()
		       << std::endl;
	    

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting COFF_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    return output_str.str();
	  }

	  /*!
	   * \brief Convert the bit order of the stored data
	   */
	  void
	  coff_header::convert ()
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering COFF_Header::convert" );
#endif /* LIBREVERSE_DEBUG */

	    io::byte_converter::convert ( m_machine );
	    io::byte_converter::convert ( m_number_of_sections );
	    io::byte_converter::convert ( m_time_date_stamp );
	    io::byte_converter::convert ( m_pointer_to_symbol_table );
	    io::byte_converter::convert ( m_number_of_symbols );
	    io::byte_converter::convert ( m_size_of_optional_header );
	    io::byte_converter::convert ( m_characteristics );


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting COFF_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  std::string
	  coff_header::get_machine_name ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Machine_Name" );
#endif /* LIBREVERSE_DEBUG */

	    return pe_machine_types::get_string_name ( m_machine );
	  }

	  boost::uint16_t
	  coff_header::get_optional_header_size ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Optional_Header_Size" );
#endif /* LIBREVERSE_DEBUG */

	    return m_size_of_optional_header;
	  }

	  std::string
	  coff_header::get_characteristics_string ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering COFF_Header::get_Characteristics_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream result;

	    result << pe_characteristics::get_string_name_list ( m_characteristics );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting COFF_Header::get_Characteristics_String" );
#endif /* LIBREVERSE_DEBUG */

	    return result.str();
	  }

	  bool
	  coff_header::is_valid () const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::is_Valid" );
#endif /* LIBREVERSE_DEBUG */

	    return pe_machine_types::is_valid_value ( m_machine ) &&
	      ( m_time_date_stamp != 0 ) &&
	      ( m_pointer_to_symbol_table == 0 ) &&
	      ( m_number_of_symbols == 0 ) &&
	      ( m_size_of_optional_header != 0 );
	  }

	  boost::uint16_t
	  coff_header::get_machine_number ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Machine_Number" );
#endif /* LIBREVERSE_DEBUG */

	    return m_machine;
	  }

	  boost::uint16_t
	  coff_header::get_section_header_count ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Section_Header_Count" );
#endif /* LIBREVERSE_DEBUG */

	    return m_number_of_sections;
	  }

	  boost::uint32_t
	  coff_header::get_time_stamp_number ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Time_Stamp_Number" );
#endif /* LIBREVERSE_DEBUG */

	    return m_time_date_stamp;
	  }

	  boost::uint32_t
	  coff_header::get_symbol_table_pointer ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Symbol_Table_Pointer" );
#endif /* LIBREVERSE_DEBUG */

	    return m_pointer_to_symbol_table;
	  }

	  boost::uint32_t
	  coff_header::get_number_of_symbols ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Number_Of_Symbols" );
#endif /* LIBREVERSE_DEBUG */

	    return m_number_of_symbols;
	  }

	  bool
	  coff_header::is_executable ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering COFF_Header::is_Executable" );
#endif /* LIBREVERSE_DEBUG */

	    bool result = false;

	    if ( m_characteristics & pe_characteristics::pe_image_file_executable_image )
	      {
		result = true;
	      }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting COFF_Header::is_Executable" );
#endif /* LIBREVERSE_DEBUG */

	    return result;
	  }

	  boost::uint16_t
	  coff_header::get_characteristic_value ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside COFF_Header::get_Characteristic_Value" );
#endif /* LIBREVERSE_DEBUG */

	    return m_characteristics;
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

