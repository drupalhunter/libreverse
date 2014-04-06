/*  Sub_Library_Command.cpp

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

#include "Sub_Library_Command.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>
#include "LC_Str.h"

namespace reverse
{
    namespace mach_module
    {

        Sub_Library_Command::Sub_Library_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize )
        {}

        void
        Sub_Library_Command::convert ( bool )
        {}

        std::string
        Sub_Library_Command::to_String ( void )
        {
            std::stringstream output;

            output << "Sub Library Command:" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << m_sub_library->to_String();

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace reverse */
