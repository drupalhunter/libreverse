/*  PE_Resource_Directory_Entry.cpp

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

#include "PE_Resource_Directory_Entry.h"
#include "Section_Flags.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace wpef_module
    {

        boost::uint8_t const PE_Resource_Directory_Entry::NAME = 0;
        boost::uint8_t const PE_Resource_Directory_Entry::ID = 1;

        PE_Resource_Directory_Entry::PE_Resource_Directory_Entry ( boost::uint8_t type )
                :  m_name ( 0 ),
                m_rva ( 0 ),
                m_type ( type )
        {}

        std::string
        PE_Resource_Directory_Entry::to_String ( void )
        {
            std::stringstream output_str;

            output_str << "PE Resource Directory_Entry Section:" << std::endl;

            output_str << boost::format ( "  Name:                 %1X" ) %
            m_name
            << std::endl;

            output_str << boost::format ( "  Offset to data:       %1X" ) %
            m_rva
            << std::endl;

            return output_str.str();

        }

        void PE_Resource_Directory_Entry::convert ()
        {
            io::Byte_Converter::convert ( m_name );
            io::Byte_Converter::convert ( m_rva );
        }

        boost::uint32_t
        PE_Resource_Directory_Entry::get_Name_Offset ( void ) const
        {
            return m_name;
        }

        boost::uint32_t
        PE_Resource_Directory_Entry::get_Offset ( void ) const
        {
            return m_rva;
        }

        boost::uint32_t
        PE_Resource_Directory_Entry::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        boost::uint8_t
        PE_Resource_Directory_Entry::get_Type ( void ) const
        {
            return m_type;
        }

        bool
        PE_Resource_Directory_Entry::is_Directory_Bit_Set ( void ) const
        {
            boost::uint32_t val = ( ( m_rva & 0x80000000 ) >> 31 );
            return ( val == 1 );
        }

    } /* namespace wpef_module */
} /* namespace reverse */

