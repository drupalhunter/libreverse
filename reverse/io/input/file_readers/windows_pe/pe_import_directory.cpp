/*  PE_Import_Directory.cpp

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

#include "PE_Import_Directory.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace libreverse
{
    namespace wpef_module
    {

        PE_Import_Directory::PE_Import_Directory()
                : m_import_lookup_table ( 0 ),
                m_timestamp ( 0 ),
                m_forwarder_chain ( 0 ),
                m_name_rva ( 0 ),
                m_import_address_table ( 0 ),
                m_name ( "" )
        {}

        boost::uint32_t
        PE_Import_Directory::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        std::string
        PE_Import_Directory::to_String ( void ) const
        {
            std::stringstream output_str;

            output_str << "PE Import Directory:" << std::endl;

            output_str << boost::format ( "  Import Lookup Table:              %1X" ) %
            m_import_lookup_table
            << std::endl;

            boost::posix_time::ptime epoch
            ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_timestamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << boost::format ( "  Time & Date:              %1%" ) %
            boost::posix_time::to_simple_string ( creation_date )
            << std::endl;

            output_str << boost::format ( "  Forwarder Chain:          %1X" ) %
            m_forwarder_chain
            << std::endl;

            output_str << boost::format ( "  Name RVA:                 %1% (%2%)" ) %
            boost::io::group ( std::hex,
                               m_name_rva ) %
            m_name
            << std::endl;

            output_str << boost::format ( "  Import Address Table:     %1X" ) %
            m_import_address_table
            << std::endl;

            if ( ! m_import_dll_list.empty() )
            {
                output_str << "   Functions" << std::endl;

                for ( DLL_List_t::const_iterator pos = m_import_dll_list.begin();
                        pos != m_import_dll_list.end();
                        pos++ )
                {
                    output_str << boost::format ( "     %1X %2s" )
                    % ( *pos ).first
                    % ( *pos ).second
                    << std::endl;
                }
            }

            if ( ! m_ordinal_list.empty() )
            {
                output_str << std::endl << "   Ordinals" << std::endl;

                for ( Ordinal_List_t::const_iterator pos = m_ordinal_list.begin();
                        pos != m_ordinal_list.end();
                        pos++ )
                {
                    output_str << "     " << ( *pos ) << std::endl;
                }
            }

            return output_str.str();

        }

        void
        PE_Import_Directory::convert ()
        {
            io::Byte_Converter::convert ( m_import_lookup_table );
            io::Byte_Converter::convert ( m_timestamp );
            io::Byte_Converter::convert ( m_forwarder_chain );
            io::Byte_Converter::convert ( m_name_rva );
            io::Byte_Converter::convert ( m_import_address_table );
        }

        void
        PE_Import_Directory::set_DLL_Name ( std::string name )
        {
            m_name = name;
        }

        void
        PE_Import_Directory::add_Function_Name ( boost::uint16_t hint,
                std::string name )
        {
            m_import_dll_list.push_back ( std::make_pair ( hint, name ) );
        }

        boost::uint32_t
        PE_Import_Directory::get_Import_Lookup_Table ( void ) const
        {
            return m_import_lookup_table;
        }

        boost::uint32_t
        PE_Import_Directory::get_Name_RVA ( void ) const
        {
            return m_name_rva;
        }

        boost::uint32_t
        PE_Import_Directory::get_Import_Address_Table ( void ) const
        {
            return m_import_address_table;
        }

        bool const
        PE_Import_Directory::is_Null ( void ) const
        {
            return ( m_import_lookup_table == 0 ) &&
                   ( m_timestamp == 0 ) &&
                   ( m_forwarder_chain == 0 ) &&
                   ( m_name_rva == 0 ) &&
                   ( m_import_address_table == 0 );
        }

        void
        PE_Import_Directory::add_Ordinal ( boost::uint32_t val )
        {
            m_ordinal_list.push_back ( val );
        }

        boost::uint32_t
        PE_Import_Directory::get_Timestamp ( void ) const
        {
            return m_timestamp;
        }

        boost::uint32_t
        PE_Import_Directory::get_Forwarder_Chain ( void ) const
        {
            return m_forwarder_chain;
        }
    } /* namespace wpef_module */
} /* namespace libreverse */

