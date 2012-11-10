/*  DOS_Relocation_Header.cpp

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

#include "DOS_Relocation_Header.h"
#include "io/Byte_Converter.h"
#include <iomanip>
#include <sstream>
#include <boost/format.hpp>

namespace libreverse
{
    namespace wpef_module
    {

        DOS_Relocation_Header::DOS_Relocation_Header()
                : m_offset ( 0 ),
                m_segment ( 0 )
        {}

        void DOS_Relocation_Header::convert ()
        {
            io::Byte_Converter::convert ( m_offset );
            io::Byte_Converter::convert ( m_segment );
        }

        boost::uint32_t const
        DOS_Relocation_Header::get_size ()
        {
            boost::uint32_t size = 32;
            return size;
        }

        std::string DOS_Relocation_Header::to_String ()
        {
            std::stringstream output_str;

            output_str
            << boost::format ( "DOS Relocation Header:   Offset: 0x%1%  Segment: 0x%2%" ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 4 ),
                               m_offset ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 4 ),
                               m_segment );

            return output_str.str();

        }

    } /* namespace wpef_module */
} /* namespace libreverse */
