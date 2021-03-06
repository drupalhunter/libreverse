/*  Dysymtab_Command.cpp

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

#include "Dysymtab_Command.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace mach_module
    {

        Dysymtab_Command::Dysymtab_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_ilocalsym ( 0 ),
                m_nlocalsym ( 0 ),
                m_iextdefsym ( 0 ),
                m_nextdefsym ( 0 ),
                m_iundefsym ( 0 ),
                m_nundefsym ( 0 ),
                m_tocoff ( 0 ),
                m_ntoc ( 0 ),
                m_modtaboff ( 0 ),
                m_nmodtab ( 0 ),
                m_extrefsymoff ( 0 ),
                m_nextrefsyms ( 0 ),
                m_indirectsymoff ( 0 ),
                m_nindirectsyms ( 0 ),
                m_extreloff ( 0 ),
                m_nextrel ( 0 ),
                m_localref ( 0 ),
                m_nlocrel ( 0 )
        {}

        void
        Dysymtab_Command::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
                io::Byte_Converter::convert ( m_ilocalsym );
                io::Byte_Converter::convert ( m_nlocalsym );
                io::Byte_Converter::convert ( m_iextdefsym );
                io::Byte_Converter::convert ( m_nextdefsym );
                io::Byte_Converter::convert ( m_iundefsym );
                io::Byte_Converter::convert ( m_nundefsym );
                io::Byte_Converter::convert ( m_tocoff );
                io::Byte_Converter::convert ( m_ntoc );
                io::Byte_Converter::convert ( m_modtaboff );
                io::Byte_Converter::convert ( m_nmodtab );
                io::Byte_Converter::convert ( m_extrefsymoff );
                io::Byte_Converter::convert ( m_nextrefsyms );
                io::Byte_Converter::convert ( m_indirectsymoff );
                io::Byte_Converter::convert ( m_nindirectsyms );
                io::Byte_Converter::convert ( m_extreloff );
                io::Byte_Converter::convert ( m_nextrel );
                io::Byte_Converter::convert ( m_localref );
                io::Byte_Converter::convert ( m_nlocrel );
            }
        }

        std::string
        Dysymtab_Command::to_String ( void )
        {
            std::stringstream output;

            output << "  Dysymtab Command" << std::endl
            << boost::format ( "  Command id:   %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command size: %1% " ) % m_cmdsize << std::endl
            << boost::format ( "  m_ilocalsym: 0x%1$X" ) % m_ilocalsym << std::endl
            << boost::format ( "  m_nlocalsym: %1%" ) % m_nlocalsym << std::endl
            << boost::format ( "  m_iextdefsym: 0x%1$X" ) % m_iextdefsym << std::endl
            << boost::format ( "  m_nextdefsym: %1%" ) % m_nextdefsym << std::endl
            << boost::format ( "  m_iundefsym: 0x%1$X" ) % m_iundefsym << std::endl
            << boost::format ( "  m_nundefsym: %1%" ) % m_nundefsym << std::endl
            << boost::format ( "  m_tocoff: 0x%1$X" ) % m_tocoff << std::endl
            << boost::format ( "  m_ntoc: %1%" ) % m_ntoc << std::endl
            << boost::format ( "  m_modtaboff: 0x%1$X" ) % m_modtaboff << std::endl
            << boost::format ( "  m_nmodtab: %1%" ) % m_nmodtab << std::endl
            << boost::format ( "  m_extrefsymoff: 0x%1$X" ) % m_extrefsymoff << std::endl
            << boost::format ( "  m_nextrefsyms: %1%" ) % m_nextrefsyms << std::endl
            << boost::format ( "  m_indirectsymoff: 0x%1$X" ) % m_indirectsymoff << std::endl
            << boost::format ( "  m_nindirectsyms: %1%" ) % m_nindirectsyms << std::endl
            << boost::format ( "  m_extreloff: 0x%1$X" ) % m_extreloff << std::endl
            << boost::format ( "  m_nextrel: %1%" ) % m_nextrel << std::endl
            << boost::format ( "  m_localref: 0x%1$X" ) % m_localref << std::endl
            << boost::format ( "  m_nlocrel: %1%" ) % m_nlocrel;

            return output.str();
        }

    } /* namespace mach_module */
} /* namespace reverse */
