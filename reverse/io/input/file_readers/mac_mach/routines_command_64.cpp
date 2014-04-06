/*  Routines_Command_64.cpp

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

#include "Routines_Command_64.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace mach_module
    {

        Routines_Command_64::Routines_Command_64 ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_init_address ( 0 ),
                m_init_module ( 0 ),
                m_reserved1 ( 0 ),
                m_reserved2 ( 0 ),
                m_reserved3 ( 0 ),
                m_reserved4 ( 0 ),
                m_reserved5 ( 0 ),
                m_reserved6 ( 0 )
        {}

        void
        Routines_Command_64::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
                io::Byte_Converter::convert ( m_init_address );
                io::Byte_Converter::convert ( m_init_module );
                io::Byte_Converter::convert ( m_reserved1 );
                io::Byte_Converter::convert ( m_reserved2 );
                io::Byte_Converter::convert ( m_reserved3 );
                io::Byte_Converter::convert ( m_reserved4 );
                io::Byte_Converter::convert ( m_reserved5 );
                io::Byte_Converter::convert ( m_reserved6 );
            }
        }

        std::string
        Routines_Command_64::to_String ( void )
        {
            std::stringstream output;

            output << "Routines Command (64-bit):" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << boost::format ( "  m_init_address: %1$X" ) % m_init_address << std::endl
            << boost::format ( "  m_init_module: %1%" ) % m_init_module << std::endl
            << boost::format ( "  m_reserved1: %1%" ) % m_reserved1 << std::endl
            << boost::format ( "  m_reserved2: %1%" ) % m_reserved2 << std::endl
            << boost::format ( "  m_reserved3: %1%" ) % m_reserved3 << std::endl
            << boost::format ( "  m_reserved4: %1%" ) % m_reserved4 << std::endl
            << boost::format ( "  m_reserved5: %1%" ) % m_reserved5 << std::endl
            << boost::format ( "  m_reserved6: %1%" ) % m_reserved6;

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace reverse */
