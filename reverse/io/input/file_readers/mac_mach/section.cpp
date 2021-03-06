/*  Section.cpp

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

#include "Section.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace mach_module
    {

        Section::Section ()
                : m_sectname ( "" ),
                m_segname ( "" ),
                m_addr ( 0 ),
                m_size ( 0 ),
                m_offset ( 0 ),
                m_align ( 0 ),
                m_reloff ( 0 ),
                m_nreloc ( 0 ),
                m_flags ( 0 ),
                m_reserved1 ( 0 ),
                m_reserved2 ( 0 )
        {}

        void
        Section::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_addr );
                io::Byte_Converter::convert ( m_size );
                io::Byte_Converter::convert ( m_offset );
                io::Byte_Converter::convert ( m_align );
                io::Byte_Converter::convert ( m_reloff );
                io::Byte_Converter::convert ( m_nreloc );
                io::Byte_Converter::convert ( m_flags );
                io::Byte_Converter::convert ( m_reserved1 );
                io::Byte_Converter::convert ( m_reserved2 );
            }
        }

        std::string
        Section::to_String ()
        {
            std::stringstream output;

            output << "Section Command:" << std::endl
            << boost::format ( "  Name: %1%" ) % m_sectname << std::endl
            << boost::format ( "  Segment Name: %1%" ) % m_segname << std::endl
            << boost::format ( "  Virtual Memory Address: 0x%1$X" ) % m_addr << std::endl
            << boost::format ( "  Virtual Memory Size: 0x%1$X" ) % m_size << std::endl
            << boost::format ( "  Offset: 0x%1$X" ) % m_offset << std::endl
            << boost::format ( "  Align: 0x%1$X" ) % m_align << std::endl
            << boost::format ( "  Relocation (File offset): 0x%1$X" ) % m_reloff << std::endl
            << boost::format ( "  Number of relocations: %1%" ) % m_nreloc << std::endl
            << boost::format ( "  Flags: %1$X" ) % m_flags << std::endl
            << boost::format ( "  m_reserved1: %1%" ) % m_reserved1 << std::endl
            << boost::format ( "  m_reserved2: %1%" ) % m_reserved2;

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace reverse */
