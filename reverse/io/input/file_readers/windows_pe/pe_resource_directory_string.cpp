/*  PE_Resource_Directory_String.cpp

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

#include "PE_Resource_Directory_String.h"
#include "Section_Flags.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace libreverse
{
    namespace wpef_module
    {

        PE_Resource_Directory_String::PE_Resource_Directory_String ()
                :  m_size ( 0 )
        {}

        std::string
        PE_Resource_Directory_String::to_String ( void )
        {
            std::stringstream output_str;

            output_str << "PE Resource Directory String:" << std::endl;

            output_str << boost::format ( "  Size:       %1X" ) %
            m_size
            << std::endl;

            output_str << boost::format ( "  Text:       %1%" ) %
            this->get_String() << std::endl;

            return output_str.str();

        }

        void PE_Resource_Directory_String::convert ()
        {
            io::Byte_Converter::convert ( m_size );
        }

        boost::uint32_t
        PE_Resource_Directory_String::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        std::string
        PE_Resource_Directory_String::get_String ( void )
        {
            return m_text;
        }
    } /* namespace wpef_module */
} /* namespace libreverse */

