/*  Mach_Header_64.cpp

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

#include "Mach_Header_64.h"
#include <boost/format.hpp>
#include <sstream>
#include <string>
#include "io/Output.h"
#include "io/Byte_Converter.h"
#include "CPU_Type.h"

namespace reverse
{
    namespace mach_module
    {

        //--------------------------------------
        //        64-bit Mach_Header_64
        //--------------------------------------
        Mach_Header_64::Mach_Header_64()
                : m_magic ( 0 ),
                m_cputype ( CPU_Type::CPU_TYPE_ANY ),
                m_cpusubtype ( 0 ),
                m_filetype ( 0 ),
                m_ncmds ( 0 ),
                m_sizeofcmds ( 0 ),
                m_flags ( 0 ),
                m_reserved ( 0 )
        {}

        std::string
        Mach_Header_64::to_String ( void )
        {
            std::stringstream output;

            output << "Mach_Header_64" << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Magic: %1$8X" ) % m_magic << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "CPU type: %1$8X" ) % m_cputype << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "CPU sub-type: %1$8X" ) % m_cpusubtype << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "File type: %1$8X" ) % m_filetype << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Command count: %1$d ( %2$8X )" ) % m_ncmds % m_ncmds << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Command size: %1$d ( %2$8X )" ) % m_sizeofcmds % m_sizeofcmds << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Flags: %1$d ( %2$8X )" ) % m_flags % m_flags << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Reserved: %1$d ( %2$8X )" ) % m_reserved % m_reserved << std::endl;

            return output.str();
        }

        bool
        Mach_Header_64::is_Mach_File ( void ) const
        {
            bool result = false;

            if ( ( m_magic == MH_MAGIC_64 ) ||
                    ( m_magic == MH_CIGAM_64 ) )
            {
                result = true;
            }

            return result;
        }

        void
        Mach_Header_64::convert ( void )
        {
            io::Byte_Converter::convert ( m_magic );
            io::Byte_Converter::convert ( m_cputype );
            io::Byte_Converter::convert ( m_cpusubtype );
            io::Byte_Converter::convert ( m_filetype );
            io::Byte_Converter::convert ( m_ncmds );
            io::Byte_Converter::convert ( m_sizeofcmds );
            io::Byte_Converter::convert ( m_flags );
            io::Byte_Converter::convert ( m_reserved );
        }

        bool
        Mach_Header_64::needs_Convert ( void ) const
        {
            bool result = true;

            if ( m_magic == MH_MAGIC_64 )
            {
                result = false;
            }

            return result;
        }

        boost::uint32_t
        Mach_Header_64::get_Magic ( void ) const
        {
            return m_magic;
        }

        boost::uint32_t
        Mach_Header_64::get_CPU_Type ( void ) const
        {
            return m_cputype;
        }

        boost::uint32_t
        Mach_Header_64::get_CPU_SubType ( void ) const
        {
            return m_cpusubtype;
        }

        boost::uint32_t
        Mach_Header_64::get_File_Type ( void ) const
        {
            return m_filetype;
        }

        boost::uint32_t
        Mach_Header_64::get_Load_Command_Count ( void ) const
        {
            return m_ncmds;
        }

        boost::uint32_t
        Mach_Header_64::get_Load_Command_Size ( void ) const
        {
            return m_sizeofcmds;
        }

        boost::uint32_t
        Mach_Header_64::get_Flags ( void ) const
        {
            return m_flags;
        }

        boost::uint32_t
        Mach_Header_64::get_Reserved ( void ) const
        {
            return m_reserved;
        }

    } /* namespace mach_module */
} /* namespace reverse */
