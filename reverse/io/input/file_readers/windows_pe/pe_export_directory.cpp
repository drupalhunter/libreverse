/*  PE_Export_Directory.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_export_directory.hpp>

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/functional/hash.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  pe_export_directory::pe_export_directory()
	    : m_export_flags ( 0 ),
	      m_time_date_stamp ( 0 ),
	      m_major_version ( 0 ),
	      m_minor_version ( 0 ),
	      m_name_rva ( 0 ),
	      m_ordinal_base ( 0 ),
	      m_address_table_entries ( 0 ),
	      m_num_of_name_pointers ( 0 ),
	      m_export_address_table_rva ( 0 ),
	      m_name_pointer_rva ( 0 ),
	      m_ordinal_table_rva ( 0 )
	  {}

	  boost::uint32_t
	  pe_export_directory::get_size ( void ) const
	  {
            return static_cast<boost::uint32_t> ( 32 );
	  }

	  std::string
	  pe_export_directory::to_string ( boost::uint32_t base_address )
	  {
            std::stringstream output_str;

            output_str << "PE Export Directory:" << std::endl;

            output_str << boost::format ( "  Export flags:             %1X" ) %
	      m_export_flags
		       << std::endl;

            boost::posix_time::ptime epoch
	      ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_time_date_stamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << boost::format ( "  Time & Date:              %1%" ) %
	      boost::posix_time::to_simple_string ( creation_date )
		       << std::endl;

            output_str << boost::format ( "  Version:                  %1%.%2%" ) %
	      m_major_version %
	      boost::io::group ( std::setfill ( '0' ),
				 std::setw ( 2 ),
				 m_minor_version )
		       << std::endl;

            output_str << boost::format ( "  Name RVA:                 %1% (%2%)" ) %
	      boost::io::group ( std::hex,
				 m_name_rva ) %
	      m_dll_name
		       << std::endl;

            output_str << boost::format ( "  Ordinal base:             %1%" ) %
	      m_ordinal_base
		       << std::endl;

            output_str << boost::format ( "  Address Table Entries:    %1%" ) %
	      m_address_table_entries
		       << std::endl;

            output_str << boost::format ( "  Number of Name Pointers:  %1%" ) %
	      m_num_of_name_pointers
		       << std::endl;

            output_str << boost::format ( "  Export Address Table RVA: %1X" ) %
	      m_export_address_table_rva
		       << std::endl;

            output_str << boost::format ( "  Name Pointer RVA:         %1X" ) %
	      m_name_pointer_rva
		       << std::endl;

            output_str << boost::format ( "  Ordinal Table RVA:        %1X" ) %
	      m_ordinal_table_rva
		       << std::endl;

            output_str << "  Export Table" << std::endl;
            output_str << "    address  = name ( ordinal )" << std::endl;

            for ( ordinal_list_t::const_iterator o_pos = m_ordinal_list.begin();
		  o_pos != m_ordinal_list.end();
		  o_pos++ )
	      {
                export_table_t::const_iterator e_begin = m_export_table.begin();
                export_table_t::const_iterator e_pos = m_export_table.find ( *o_pos );
                export_table_t::const_iterator e_end = m_export_table.end();

                rev_name_table_t::const_iterator n_begin = m_rev_name_hash_table.begin();
                rev_name_table_t::const_iterator n_pos = m_rev_name_hash_table.find ( *o_pos );
                rev_name_table_t::const_iterator n_end = m_rev_name_hash_table.end();

                name_string_table_t::const_iterator str_begin = m_name_string_table.begin();
                name_string_table_t::const_iterator str_pos = m_name_string_table.find ( n_pos->second );
                name_string_table_t::const_iterator str_end = m_name_string_table.end();

                output_str << boost::format ( "     %1% = %2% ( %3% )" )
		  % boost::io::group ( std::hex,
				       std::setw ( 8 ),
				       std::setfill ( '0' ),
				       ( base_address + e_pos->second ) )
		  % str_pos->second
		  % ( *o_pos )
			   << std::endl;
	      }

            return output_str.str();

	  }

	  void
	  pe_export_directory::convert ()
	  {
            io::byte_converter::convert ( m_export_flags );
            io::byte_converter::convert ( m_time_date_stamp );
            io::byte_converter::convert ( m_major_version );
            io::byte_converter::convert ( m_minor_version );
            io::byte_converter::convert ( m_name_rva );
            io::byte_converter::convert ( m_ordinal_base );
            io::byte_converter::convert ( m_address_table_entries );
            io::byte_converter::convert ( m_num_of_name_pointers );
            io::byte_converter::convert ( m_export_address_table_rva );
            io::byte_converter::convert ( m_name_pointer_rva );
            io::byte_converter::convert ( m_ordinal_table_rva );
	  }

	  void
	  pe_export_directory::set_dll_name ( std::string name )
	  {
            m_dll_name = name;
	  }

	  boost::uint32_t
	  pe_export_directory::get_address_table_entries ( void ) const
	  {
            return m_address_table_entries;
	  }

	  boost::uint32_t
	  pe_export_directory::get_export_address_table_rva ( void ) const
	  {
            return m_export_address_table_rva;
	  }

	  boost::uint32_t
	  pe_export_directory::get_number_of_name_pointers ( void ) const
	  {
            return m_num_of_name_pointers;
	  }

	  boost::uint32_t
	  pe_export_directory::get_name_pointer_rva ( void ) const
	  {
            return m_name_pointer_rva;
	  }

	  boost::uint32_t
	  pe_export_directory::get_ordinal_table_rva ( void ) const
	  {
            return m_ordinal_table_rva;
	  }

	  void
	  pe_export_directory::add_export_entry ( boost::uint32_t export_addr,
						  boost::uint16_t ordinal_value,
						  std::string symbol_name )
	  {
            m_ordinal_list.push_back ( static_cast<boost::uint32_t> ( ordinal_value ) + m_ordinal_base );

            boost::hash<std::string> string_hash;
            m_name_table.insert ( std::make_pair ( string_hash ( symbol_name ),
                                                   m_ordinal_list.size() - 1 ) );

            m_name_string_table.insert ( std::make_pair ( string_hash ( symbol_name ),
							  symbol_name ) );

            m_rev_name_hash_table.insert ( std::make_pair ( ordinal_value + m_ordinal_base,
							    string_hash ( symbol_name ) ) );

            m_export_table.insert ( std::make_pair ( ordinal_value + m_ordinal_base, export_addr ) );
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


