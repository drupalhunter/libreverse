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

#include "PE_Export_Directory.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/functional/hash.hpp>

namespace libreverse
{
    namespace wpef_module
    {

        PE_Export_Directory::PE_Export_Directory()
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
        PE_Export_Directory::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        std::string
        PE_Export_Directory::to_String ( boost::uint32_t base_address )
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


            for ( Ordinal_List_t::const_iterator o_pos = m_ordinal_list.begin();
                    o_pos != m_ordinal_list.end();
                    o_pos++ )
            {
                Export_Table_t::const_iterator e_begin = m_export_table.begin();
                Export_Table_t::const_iterator e_pos = m_export_table.find ( *o_pos );
                Export_Table_t::const_iterator e_end = m_export_table.end();

                Rev_Name_Table_t::const_iterator n_begin = m_rev_name_hash_table.begin();
                Rev_Name_Table_t::const_iterator n_pos = m_rev_name_hash_table.find ( *o_pos );
                Rev_Name_Table_t::const_iterator n_end = m_rev_name_hash_table.end();

                Name_String_Table_t::const_iterator str_begin = m_name_string_table.begin();
                Name_String_Table_t::const_iterator str_pos = m_name_string_table.find ( n_pos->second );
                Name_String_Table_t::const_iterator str_end = m_name_string_table.end();

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
        PE_Export_Directory::convert ()
        {
            io::Byte_Converter::convert ( m_export_flags );
            io::Byte_Converter::convert ( m_time_date_stamp );
            io::Byte_Converter::convert ( m_major_version );
            io::Byte_Converter::convert ( m_minor_version );
            io::Byte_Converter::convert ( m_name_rva );
            io::Byte_Converter::convert ( m_ordinal_base );
            io::Byte_Converter::convert ( m_address_table_entries );
            io::Byte_Converter::convert ( m_num_of_name_pointers );
            io::Byte_Converter::convert ( m_export_address_table_rva );
            io::Byte_Converter::convert ( m_name_pointer_rva );
            io::Byte_Converter::convert ( m_ordinal_table_rva );
        }

        void
        PE_Export_Directory::set_DLL_Name ( std::string name )
        {
            m_dll_name = name;
        }

        boost::uint32_t
        PE_Export_Directory::get_Address_Table_Entries ( void ) const
        {
            return m_address_table_entries;
        }

        boost::uint32_t
        PE_Export_Directory::get_Export_Address_Table_RVA ( void ) const
        {
            return m_export_address_table_rva;
        }

        boost::uint32_t
        PE_Export_Directory::get_Number_Of_Name_Pointers ( void ) const
        {
            return m_num_of_name_pointers;
        }

        boost::uint32_t
        PE_Export_Directory::get_Name_Pointer_RVA ( void ) const
        {
            return m_name_pointer_rva;
        }

        boost::uint32_t
        PE_Export_Directory::get_Ordinal_Table_RVA ( void ) const
        {
            return m_ordinal_table_rva;
        }

        void
        PE_Export_Directory::add_Export_Entry ( boost::uint32_t export_addr,
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

    } /* namespace wpef_module */
} /* namespace libreverse */

