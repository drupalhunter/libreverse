/*  Dylinker_Command.cpp

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

#include "Dylinker_Command.h"
#include "LC_Str.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace mach_module
    {

        Dylinker_Command::Dylinker_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_name ( new LC_Str() )
        {}

        void
        Dylinker_Command::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
                m_name->convert ( need_convert );
            }
        }

                std::string
        Dylinker_Command::to_String ( void )
        {
            std::stringstream output;

            output << "Dylinker Command:" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << m_name->to_String();

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace reverse */
