/*  PE_Resource_Entry.cpp

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

#include "PE_Resource_Entry.hpp"
#include "Section_Flags.hpp"
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.hpp"
#include <sstream>

namespace reverse
{
    namespace wpef_module
    {

        PE_Resource_Entry::PE_Resource_Entry()
                :  m_name ( 0 ),
                m_offset_to_data ( 0 )
        {}

        std::string PE_Resource_Entry::to_String ( void )
        {
            std::stringstream output_str;

            output_str << "PE Resource Entry Section:" << std::endl;

            output_str << boost::format ( "  Name:                 %1X" ) %
            m_name
            << std::endl;

            output_str << boost::format ( "  Offset to data:       %1X" ) %
            m_offset_to_data
            << std::endl;

            return output_str.str();

        }

        void PE_Resource_Entry::convert ()
        {
            io::Byte_Converter::convert ( m_name );
            io::Byte_Converter::convert ( m_offset_to_data );
        }

    } /* namespace wpef_module */
} /* namespace reverse */

