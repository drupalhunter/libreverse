/*  Symtab_Command.cpp

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

#include "Symtab_Command.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace mach_module
    {

        Symtab_Command::Symtab_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_symoff ( 0 ),
                m_nsyms ( 0 ),
                m_stroff ( 0 ),
                m_strsize ( 0 )
        {}

        void
        Symtab_Command::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
                io::Byte_Converter::convert ( m_symoff );
                io::Byte_Converter::convert ( m_nsyms );
                io::Byte_Converter::convert ( m_stroff );
                io::Byte_Converter::convert ( m_strsize );
            }
        }

        std::string
       Symtab_Command::to_String ( void )
        {
            std::stringstream output;

            output << "Symtab Command:" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << boost::format ( "  Symbol Offset: 0x%1$X" ) % m_symoff << std::endl
            << boost::format ( "  Number of Symbols: %1%" ) % m_nsyms << std::endl
            << boost::format ( "  Stroff: 0x%1$X" ) % m_stroff << std::endl
            << boost::format ( "  Strsize: %1%" ) % m_strsize << std::endl;

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace reverse */
