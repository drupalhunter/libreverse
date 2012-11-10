/*  Segment_Command_64.cpp

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

#include "Segment_Command_64.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace libreverse
{
    namespace mach_module
    {

        Segment_Command_64::Segment_Command_64 ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_segname ( MAX_NAME_SIZE ),
                m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_vmaddr ( 0 ),
                m_vmsize ( 0 ),
                m_fileoff ( 0 ),
                m_filesize ( 0 ),
                m_maxprot ( 0 ),
                m_initprot ( 0 ),
                m_nsects ( 0 ),
                m_flags ( 0 )
        {}

        void
        Segment_Command_64::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
                io::Byte_Converter::convert ( m_vmaddr );
                io::Byte_Converter::convert ( m_vmsize );
                io::Byte_Converter::convert ( m_fileoff );
                io::Byte_Converter::convert ( m_filesize );
                io::Byte_Converter::convert ( m_maxprot );
                io::Byte_Converter::convert ( m_initprot );
                io::Byte_Converter::convert ( m_nsects );
                io::Byte_Converter::convert ( m_flags );
            }
        }

        std::string
        Segment_Command_64::to_String ()
        {
            std::stringstream output;

            output << "Segment Command (64-bit):" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << boost::format ( "  Virtual Memory Address: %1$X" ) % m_vmaddr << std::endl
            << boost::format ( "  Virtual Memory Size: %1%" ) % m_vmsize << std::endl
            << boost::format ( "  Offset: 0x%1$X" ) % m_fileoff << std::endl
            << boost::format ( "  Filesize: %1%" ) % m_filesize << std::endl
            << boost::format ( "  Max Protection: 0x%1$X" ) % m_maxprot << std::endl
            << boost::format ( "  Initial Protection: 0x%1$X" ) % m_initprot << std::endl
            << boost::format ( "  Number of Sections: %1%" ) % m_nsects << std::endl
            << boost::format ( "  Flags: %1$X" ) % m_flags;

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace libreverse */
