/*  Dylib.cpp

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

#include "Dylib.h"
#include "LC_Str.h"
#include "io/Byte_Converter.h"
#include <boost/format.hpp>
#include <sstream>

namespace libreverse
{
    namespace mach_module
    {

        Dylib::Dylib ()
                : m_name ( new LC_Str() ),
                m_timestamp ( 0 ),
                m_current_version ( 0 ),
                m_compatibility_version ( 0 )
        {}

        void
        Dylib::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                m_name->convert ( need_convert );
                io::Byte_Converter::convert ( m_timestamp );
                io::Byte_Converter::convert ( m_current_version );
                io::Byte_Converter::convert ( m_compatibility_version );
            }
        }

        std::string
        Dylib::to_String ( void )
        {
            std::stringstream output;

            output << "  Dylib:" << std::endl
            << m_name->to_String() << std::endl
            << boost::format ( "    timestamp: %1%" ) % m_timestamp << std::endl
            << boost::format ( "    current version: %1%" ) % m_current_version << std::endl
            << boost::format ( "    compatibility version: %1%" ) % m_compatibility_version;

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace libreverse */
