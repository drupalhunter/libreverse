/*  UUID_Command.cpp

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

#include "UUID_Command.h"
#include "io/Byte_Converter.h"
#include <boost/format.hpp>
#include <sstream>

namespace reverse
{
    namespace mach_module
    {

        const boost::uint8_t UUID_Command::MAX_SIZE = 16;

        UUID_Command::UUID_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_uuid ( MAX_SIZE )
        {}

        void
        UUID_Command::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
            }
        }

        std::string
        UUID_Command::to_String ( void )
        {
            std::stringstream output;

            output << "UUID Command:" << std::endl
            << boost::format ( "  command id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  command size: %1%" ) % m_cmdsize;

            return output.str();
        }

    } /* namespace mach_module */
} /* namespace reverse */
