/*  PE_Resource_Data_Entry.cpp

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

#include "PE_Resource_Data_Entry.h"
#include "Section_Flags.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include "io/String_Converter.h"
#include "io/Output.h"
#include <sstream>
#include <boost/format.hpp>

using namespace reverse::io;

namespace reverse
{
    namespace wpef_module
    {

        PE_Resource_Data_Entry::PE_Resource_Data_Entry ( boost::uint8_t level )
                :  m_data_rva ( 0 ),
                m_size ( 0 ),
                m_codepage ( 0 ),
                m_reserved ( 0 ),
                m_level ( level ),
                m_data_string ( "" )
        {}

        std::string
        PE_Resource_Data_Entry::to_String ( void )
        {
            std::stringstream output_str;

            output_str << Output::indent ( m_level * 2 )
            << "PE Resource Data_Entry Section:" << std::endl
            << Output::indent ( m_level * 2 )
            << boost::format ( "  Data rva:             %1X" ) % m_data_rva << std::endl
            << Output::indent ( m_level * 2 )
            << boost::format ( "  Size:                 %1X" ) % m_size << std::endl
            << Output::indent ( m_level * 2 )
            << boost::format ( "  Codepage:             %1d" ) % m_codepage
            << std::endl << std::endl;

            output_str << "---------- BEGIN DATA ----------" << std::endl
            << m_data_string
            << "----------  END DATA  ----------" << std::endl;

            return output_str.str();

        }

        void
        PE_Resource_Data_Entry::convert ()
        {
            io::Byte_Converter::convert ( m_data_rva );
            io::Byte_Converter::convert ( m_size );
            io::Byte_Converter::convert ( m_codepage );
            io::Byte_Converter::convert ( m_reserved );
        }

        boost::uint32_t
        PE_Resource_Data_Entry::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        std::string
        PE_Resource_Data_Entry::data_To_String ( void ) const
        {
            std::vector<UChar> uchar_vector ( m_data_string.begin(),
                                              m_data_string.end() );

            return String_Converter::convert_From_UTF16_String ( uchar_vector );
        }
    } /* namespace wpef_module */
} /* namespace reverse */

