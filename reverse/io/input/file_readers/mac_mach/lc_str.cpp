/*  LC_Str.cpp

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

#include "LC_Str.h"
#include "io/Byte_Converter.h"
#include <boost/format.hpp>
#include <sstream>

namespace reverse
{
    namespace mach_module
    {

        LC_Str::LC_Str()
                : m_offset ( 0 ),
                m_text ( "" )
        {}

        void
        LC_Str::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_offset );
            }
        }

        std::string
        LC_Str::to_String (void)
        {
            std::stringstream output;

            output << "    LC_Str" << std::endl
            << boost::format ("    Offset: 0x%1$X" ) % m_offset << std::endl
            << boost::format ("    Text: %1% " ) % m_text;

            return output.str();
        }

    } /* namespace mach_module */
} /* namespace reverse */
