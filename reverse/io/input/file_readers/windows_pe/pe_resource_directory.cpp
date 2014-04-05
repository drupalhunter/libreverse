/*  PE_Resource_Directory.cpp

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

#include "PE_Resource_Directory.h"
#include "PE_Resource_Data_Entry.h"
#include "PE_Resource_Integer_Types.h"
#include "Section_Flags.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include "io/Output.h"
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace reverse
{
    namespace wpef_module
    {

        boost::uint8_t const PE_Resource_Directory::TYPE_LEVEL = 0;
        boost::uint8_t const PE_Resource_Directory::NAME_LEVEL = 1;
        boost::uint8_t const PE_Resource_Directory::LANGUAGE_LEVEL = 2;

        PE_Resource_Directory::PE_Resource_Directory ( boost::uint8_t level )
                :  m_characteristics ( 0 ),
                m_time_date_stamp ( 0 ),
                m_major_version ( 0 ),
                m_minor_version ( 0 ),
                m_num_of_name_entries ( 0 ),
                m_num_of_id_entries ( 0 ),
                m_name ( "" ),
                m_id ( 0 ),
                m_level ( level )
        {}

        std::string PE_Resource_Directory::to_String ( void )
        {
            std::stringstream output_str;

            output_str << io::Output::indent ( m_level * 2 )
            << "PE Resource Directory Section (";

            if ( m_level == NAME_LEVEL )
            {
                output_str << PE_Resource_Integer_Types::get_String_Name ( m_id );
            }
            else
            {
                if ( m_name.empty() )
                {
                    output_str << "ID:" << m_id;
                }
                else
                {
                    output_str << m_name;
                }
            }

            output_str << ")" << std::endl;

            output_str << io::Output::indent ( m_level * 2 )
            << boost::format ( "  Characteristics:         %1X" ) % m_characteristics
            << std::endl;

            boost::posix_time::ptime epoch
            ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_time_date_stamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << io::Output::indent ( m_level * 2 )
            << "  Time stamp (seconds): "
            << boost::posix_time::to_simple_string ( creation_date )
            << std::endl;

            output_str << io::Output::indent ( m_level * 2 )
            << boost::format ( "  Version:             %1d.%1d" ) % m_major_version % m_minor_version
            << std::endl;

            output_str << io::Output::indent ( m_level * 2 )
            << boost::format ( "  Number of Names:     %1d" ) % m_num_of_name_entries
            << std::endl;

            output_str << io::Output::indent ( m_level * 2 )
            << boost::format ( "  Number of Ids:       %1d" ) % m_num_of_id_entries
            << std::endl;

            for ( Children_List_t::const_iterator pos = m_children.begin();
                    pos != m_children.end();
                    pos++ )
            {
                output_str << ( *pos )->to_String() << std::endl;
            }

            for ( wpef_types::PE_Resource_Directory::Data_List_t::const_iterator pos = m_data.begin();
                    pos != m_data.end();
                    pos++ )
            {
                output_str << ( *pos )->to_String() << std::endl;
            }

            return output_str.str();

        }

        void
        PE_Resource_Directory::convert ()
        {
            io::Byte_Converter::convert ( m_characteristics );
            io::Byte_Converter::convert ( m_time_date_stamp );
            io::Byte_Converter::convert ( m_major_version );
            io::Byte_Converter::convert ( m_minor_version );
            io::Byte_Converter::convert ( m_num_of_name_entries );
            io::Byte_Converter::convert ( m_num_of_id_entries );
        }

        void
        PE_Resource_Directory::add_Directory ( wpef_types::PE_Resource_Directory::ptr_t dir_ptr )
        {
            m_children.push_back ( dir_ptr );
        }

        void
        PE_Resource_Directory::add_Data ( wpef_types::PE_Resource_Data_Entry::ptr_t data_ptr )
        {
            m_data.push_back ( data_ptr );
        }

        boost::uint16_t
        PE_Resource_Directory::get_Number_Of_Name_Entries () const
        {
            return m_num_of_name_entries;
        }

        boost::uint16_t
        PE_Resource_Directory::get_Number_Of_Id_Entries () const
        {
            return m_num_of_id_entries;
        }

        void
        PE_Resource_Directory::set_Name ( std::string name )
        {
            m_name = name;
        }

        void
        PE_Resource_Directory::set_ID ( boost::uint32_t id )
        {
            m_id = id;
        }

        boost::uint8_t
        PE_Resource_Directory::get_Level ( void ) const
        {
            return m_level;
        }

        wpef_types::PE_Resource_Directory::Data_List_t::const_iterator
        PE_Resource_Directory::get_Data_Begin ( void ) const
        {
            return m_data.begin();
        }

        wpef_types::PE_Resource_Directory::Data_List_t::const_iterator
        PE_Resource_Directory::get_Data_End ( void ) const
        {
            return m_data.end();
        }

    } /* namespace wpef_module */
} /* namespace reverse */

