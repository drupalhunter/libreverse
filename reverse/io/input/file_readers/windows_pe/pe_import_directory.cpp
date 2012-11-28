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

#include <reverse/io/input/file_readers/windows_pe/pe_import_directory.hpp>
#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iomanip>
#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

        pe_import_directory::pe_import_directory()
                : m_import_lookup_table ( 0 ),
                m_timestamp ( 0 ),
                m_forwarder_chain ( 0 ),
                m_name_rva ( 0 ),
                m_import_address_table ( 0 ),
                m_name ( "" )
        {}

        boost::uint32_t
        pe_import_directory::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        std::string
        pe_import_directory::to_string ( void ) const
        {
            std::stringstream output_str;

            output_str << "pe import directory:" << std::endl;

            output_str << boost::format ( "  import lookup table:              %1x" ) %
            m_import_lookup_table
            << std::endl;

            boost::posix_time::ptime epoch
            ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_timestamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << boost::format ( "  time & date:              %1%" ) %
            boost::posix_time::to_simple_string ( creation_date )
            << std::endl;

            output_str << boost::format ( "  forwarder chain:          %1x" ) %
            m_forwarder_chain
            << std::endl;

            output_str << boost::format ( "  name rva:                 %1% (%2%)" ) %
            boost::io::group ( std::hex,
                               m_name_rva ) %
            m_name
            << std::endl;

            output_str << boost::format ( "  import address table:     %1x" ) %
            m_import_address_table
            << std::endl;

            if ( ! m_import_dll_list.empty() )
            {
                output_str << "   functions" << std::endl;

                for ( dll_list_t::const_iterator pos = m_import_dll_list.begin();
                        pos != m_import_dll_list.end();
                        pos++ )
                {
                    output_str << boost::format ( "     %1x %2s" )
                    % ( *pos ).first
                    % ( *pos ).second
                    << std::endl;
                }
            }

            if ( ! m_ordinal_list.empty() )
            {
                output_str << std::endl << "   ordinals" << std::endl;

                for ( ordinal_list_t::const_iterator pos = m_ordinal_list.begin();
                        pos != m_ordinal_list.end();
                        pos++ )
                {
                    output_str << "     " << ( *pos ) << std::endl;
                }
            }

            return output_str.str();

        }

        void
        pe_import_directory::convert ()
        {
            io::byte_converter::convert ( m_import_lookup_table );
            io::byte_converter::convert ( m_timestamp );
            io::byte_converter::convert ( m_forwarder_chain );
            io::byte_converter::convert ( m_name_rva );
            io::byte_converter::convert ( m_import_address_table );
        }

        void
        pe_import_directory::set_dll_name ( std::string name )
        {
            m_name = name;
        }

        void
        pe_import_directory::add_function_name ( boost::uint16_t hint,
                std::string name )
        {
            m_import_dll_list.push_back ( std::make_pair ( hint, name ) );
        }

        boost::uint32_t
        pe_import_directory::get_import_lookup_table ( void ) const
        {
            return m_import_lookup_table;
        }

        boost::uint32_t
        pe_import_directory::get_name_rva ( void ) const
        {
            return m_name_rva;
        }

        boost::uint32_t
        pe_import_directory::get_import_address_table ( void ) const
        {
            return m_import_address_table;
        }

        bool const
        pe_import_directory::is_null ( void ) const
        {
            return ( m_import_lookup_table == 0 ) &&
                   ( m_timestamp == 0 ) &&
                   ( m_forwarder_chain == 0 ) &&
                   ( m_name_rva == 0 ) &&
                   ( m_import_address_table == 0 );
        }

        void
        pe_import_directory::add_ordinal ( boost::uint32_t val )
        {
            m_ordinal_list.push_back ( val );
        }

        boost::uint32_t
        pe_import_directory::get_timestamp ( void ) const
        {
            return m_timestamp;
        }

        boost::uint32_t
        pe_import_directory::get_forwarder_chain ( void ) const
        {
            return m_forwarder_chain;
        }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


