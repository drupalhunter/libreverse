/*  Header_32.cpp

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

#include <reverse/io/input/file_readers/windows_pe/header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/dos_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_section_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_optional_header_32.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_resource_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_export_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_import_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_debug_directory.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_load_config_directory.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <iostream>
#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  header_32::header_32()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32 constructor" );
	  }

	  header_32::~header_32()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32 destructor" );
	  }

	  void
	  header_32::convert ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::convert" );

	    m_dos_hdr->convert ();
	    m_pe_hdr->convert ();

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::convert" );
	  }

	  std::string
	  header_32::to_string ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::to_String" );

	    std::stringstream output_str;

	    output_str << "---- WPEF Header dump: -----" << std::endl;
	    output_str << m_dos_hdr->to_string() << std::endl;

	    output_str << "---- WPEF PE Header dump: -----" << std::endl;
	    output_str << m_pe_hdr->to_string() << std::endl;

	    output_str << "---- WPEF Section Header dump: -----" << std::endl;
	    for ( header_32::section_header_map_t::iterator pos = m_sec_hdrs.begin();
		  pos != m_sec_hdrs.end();
		  ++pos)
	      {
                output_str << ((*pos).second)->to_string() << std::endl;
	      }

	    if ( m_res_ptr.get() != 0 )
	      {
                output_str << "---- WPEF Resource Directory dump: -----" << std::endl;
                output_str << m_res_ptr->to_string() << std::endl;
	      }

	    if ( m_export_dir_ptr.get() != 0 )
	      {
		boost::shared_ptr < const pe_optional_header_32 > opt_ptr = m_pe_hdr->get_optional_header();
		    
		output_str << "---- WPEF Export Directory dump: -----" << std::endl;
		output_str << m_export_dir_ptr->to_string ( opt_ptr->get_image_base() ) << std::endl;
	      }

	    if ( !m_import_dir_list.empty() )
	      {
		output_str << "---- WPEF Import Directory dump: -----" << std::endl;
		for ( header_32::import_directory_list_t::const_iterator pos = m_import_dir_list.begin();
		      pos != m_import_dir_list.end();
		      pos++ )
		  {
		    output_str << (*pos)->to_string() << std::endl;
		  }
	      }

	    if ( m_debug_ptr.get() != 0 )
	      {
		output_str << "---- WPEF Debug Directory dump: -----" << std::endl;
		output_str << m_debug_ptr->to_string() << std::endl;
	      }

	    if ( m_load_config_ptr.get() != 0 )
	      {
		output_str << "---- WPEF Load_Config Directory dump: -----" << std::endl;
		output_str << m_load_config_ptr->to_string() << std::endl;
	      }

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::to_string" );

	    return output_str.str();
	  }

	  void
	  header_32::get_text_string ( std::vector < std::string >& output )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "entering header_32::get_text_string" );

	    output.push_back ( this->to_string() );
	  }

	  /*-----------------------------*/
	  /*        DOS HEADER           */
	  /*-----------------------------*/

	  boost::shared_ptr < dos_header >
	  header_32::get_dos_header (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_DOS_Header" );
	    
	    return m_dos_hdr;
	  }

	  void header_32::set_dos_header ( boost::shared_ptr < dos_header > hdr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_DOS_Header" );

	    m_dos_hdr = hdr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_DOS_Header" );
	  }

	  /*-----------------------------*/
	  /*         PE HEADER           */
	  /*-----------------------------*/

	  boost::shared_ptr < const pe_header_32 >
	  header_32::get_pe_header (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Header" );

	    return m_pe_hdr;
	  }

	  void header_32::set_pe_header ( boost::shared_ptr < pe_header_32 > hdr)
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_PE_Header" );

	    m_pe_hdr = hdr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_PE_Header" );

	  }

	  /*-----------------------------*/
	  /*        SECTioN HEADER       */
	  /*-----------------------------*/

	  /*
	    bool
	    Header_32::has_PE_Section_Header (std::string const name)
	    {
	    bool result = false;

	    // IF we have a header associated with a name THEN return true
	    // ELSE return false
	    Section_Header_Map::const_iterator pos = m_sec_hdrs.find ( name );
	    if ( pos != m_sec_name_map.end() )
	    {
	    result = true;
	    }

	    return result;
	    }
	  */

	  header_32::section_header_map_t::const_iterator
	  header_32::get_pe_section_header ( std::string name ) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::get_PE_Section_Header" );

	    header_32::section_header_map_t::const_iterator pos = m_sec_hdrs.find ( name );

	    if ( pos == m_sec_hdrs.end() )
	      {
                trace::write_trace ( trace_area::io,
                                     trace_level::error,
                                     boost::str ( boost::format ( "Invalid section name given: %s" )
                                                  % name ) );
	      }

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::get_PE_Section_Header" );

	    return pos;
	  }

	  boost::uint32_t
	  header_32::get_pe_section_header_count (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Section_Header_Count" );

	    return m_sec_hdrs.size();
	  }

	  header_32::section_header_map_t::const_iterator
	  header_32::get_pe_section_header_list_begin () const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Section_Header_List_Begin" );

	    return m_sec_hdrs.begin();
	  }

	  header_32::section_header_map_t::const_iterator
	  header_32::get_pe_section_header_list_end () const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Section_Header_List_End" );

	    return m_sec_hdrs.end();
	  }

	  void header_32::set_pe_section_header ( boost::shared_ptr < pe_section_header > hdr)
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_PE_Section_Header " );

	    m_sec_hdrs.insert ( std::make_pair ( hdr->get_name(), hdr ) );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_PE_Section_Header " );

	  }

	  /*-----------------------------*/
	  /*      RESOURCE DIRECTORY     */
	  /*-----------------------------*/

	  void
	  header_32::set_resource_directory ( boost::shared_ptr < pe_resource_directory > r_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_Resource_Directory" );

	    m_res_ptr = r_ptr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_Resource_Directory" );
	  }

	  /*-----------------------------*/
	  /*       EXPORT DIRECTORY      */
	  /*-----------------------------*/

	  void
	  header_32::set_export_directory ( boost::shared_ptr < pe_export_directory > exp_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_Export_Directory" );

	    m_export_dir_ptr = exp_ptr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_Export_Directory" );
	  }

	  boost::shared_ptr < pe_export_directory >
	  header_32::get_export_directory () const
	  {
	    return m_export_dir_ptr;
	  }

	  /*-----------------------------*/
	  /*       IMPORT DIRECTORY      */
	  /*-----------------------------*/

	  void
	  header_32::add_import_directory ( boost::shared_ptr < pe_import_directory > exp_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::add_Import_Directory" );

	    m_import_dir_list.push_back ( exp_ptr );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::add_Import_Directory" );
	  }

	  boost::uint32_t
	  header_32::get_pe_import_directory_count (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Import_Directory_Count" );

	    return m_import_dir_list.size();
	  }

	  header_32::import_directory_list_t::iterator
	  header_32::get_pe_import_directory_list_begin ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Import_Directory_List_Begin" );

	    return m_import_dir_list.begin();
	  }

	  header_32::import_directory_list_t::iterator
	  header_32::get_pe_import_directory_list_end ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Import_Directory_List_End" );

	    return m_import_dir_list.end();
	  }

	  header_32::import_directory_list_t::const_iterator
	  header_32::get_pe_import_directory_list_begin () const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Import_Directory_List_Begin (const)" );

	    return m_import_dir_list.begin();
	  }

	  header_32::import_directory_list_t::const_iterator
	  header_32::get_pe_import_directory_list_end () const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Import_Directory_List_End (const)" );

	    return m_import_dir_list.end();
	  }

	  /*-----------------------------*/
	  /*        DEBUG DIRECTORY      */
	  /*-----------------------------*/

	  void
	  header_32::set_debug_directory ( boost::shared_ptr < pe_debug_directory > d_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_Debug_Directory" );

	    m_debug_ptr = d_ptr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_Debug_Directory" );

	  }

	  boost::shared_ptr < pe_debug_directory >
	  header_32::get_debug_directory () const
	  {
	    return m_debug_ptr;
	  }

	  /*-----------------------------*/
	  /*     LOAD CONFIG DIRECTORY   */
	  /*-----------------------------*/

	  void
	  header_32::set_load_config_directory ( boost::shared_ptr < pe_load_config_directory > d_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::set_Load_Config_Directory" );

	    m_load_config_ptr = d_ptr;

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::set_Load_Config_Directory" );
	  }

	  boost::shared_ptr < pe_resource_directory >
	  header_32::get_pe_resource_directory ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::get_PE_Resource_Directory" );

	    return m_res_ptr;
	  }

	  /*-----------------------------*/
	  /*       IMPORT DIRECTORY      */
	  /*-----------------------------*/

	  void
	  header_32::add_exception_table_entry ( boost::shared_ptr < const pe_exception_table_entry > exp_ptr )
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Entering Header_32::add_Exception_Table_Entry" );

	    m_exception_list.push_back ( exp_ptr );

	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Exiting Header_32::add_Exception_Table_Entry" );
	  }

	  boost::uint32_t
	  header_32::get_pe_exception_table_entry_count (void) const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Exception_Table_Entry_Count" );

	    return m_exception_list.size();
	  }

	  header_32::exception_table_list_t::iterator
	  header_32::get_pe_exception_table_list_begin ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Exception_Table_List_Begin" );

	    return m_exception_list.begin();
	  }

	  header_32::exception_table_list_t::iterator
	  header_32::get_pe_exception_table_list_end ()
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Exception_Table_List_End" );

	    return m_exception_list.end();
	  }

	  header_32::exception_table_list_t::const_iterator
	  header_32::get_pe_exception_table_list_begin () const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Exception_Table_List_Begin (const)" );

	    return m_exception_list.begin();
	  }

	  header_32::exception_table_list_t::const_iterator
	  header_32::get_pe_exception_table_list_end () const
	  {
	    trace::write_trace ( trace_area::io,
				 trace_level::detail,
				 "Inside Header_32::get_PE_Exception_Table_List_End (const)" );

	    return m_exception_list.end();
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

