/*  Fat_Arch.cpp

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

#include "Fat_Arch.h"
#include "io/Output.h"
#include "errors/IO_Exception.h"
#include "Trace.h"
#include "Reverse.h"
#include <sstream>
#include "io/Byte_Converter.h"
#include "CPU_Type.h"
#include "CPU_SubType.h"

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse
{
    namespace mach_module
    {
        Fat_Arch::Fat_Arch()
                : m_cputype ( 0 ),
                m_cpu_subtype ( 0 ),
                m_offset ( 0 ),
                m_size ( 0 ),
                m_align ( 0 )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Arch constructor" );
        }

        void
        Fat_Arch::convert ()
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Arch::convert" );

                io::Byte_Converter::convert ( m_cputype );
                io::Byte_Converter::convert ( m_cpu_subtype );
                io::Byte_Converter::convert ( m_offset );
                io::Byte_Converter::convert ( m_size );
                io::Byte_Converter::convert ( m_align );
        }

        std::string const
        Fat_Arch::to_String ( void ) const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Arch::to_String" );

            std::stringstream output;

            output << "Fat_Arch" << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "CPU Type: 0x%1$08X ( %2$d ) = %3$s" )
            % m_cputype % m_cputype % CPU_Type::get_String_Name ( m_cputype ) << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "CPU SubType: 0x%1$08X ( %2$d ) = %3$s" )
            % m_cpu_subtype % m_cpu_subtype % CPU_SubType::get_String_Name ( m_cputype, m_cpu_subtype ) << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Offset: 0x%1$08X" ) % m_offset << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Size: 0x%1$08X ( %2$d )" ) % m_size % m_size << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Align: 0x%1$08X ( %2$d )" ) % m_align % m_align << std::endl;

            return output.str();
        }

        boost::uint32_t
        Fat_Arch::get_CPU_Type ( void ) const
        {
            return m_cputype;
        }

        boost::uint32_t
        Fat_Arch::get_CPU_SubType ( void ) const
        {
            return m_cpu_subtype;
        }

        boost::uint32_t
        Fat_Arch::get_Offset ( void ) const
        {
            return m_offset;
        }

        boost::uint32_t
        Fat_Arch::get_Header_Size ( void ) const
        {
            return m_size;
        }

        boost::uint32_t
        Fat_Arch::get_Alignment ( void ) const
        {
            return m_align;
        }

        bool
        Fat_Arch::is_64bit ( void ) const
        {
            bool result = false;

            if ( ( m_cputype & CPU_Type::CPU_ARCH_MASK ) != 0 )
            {
                result = true;
            }

            return result;
        }
    } /* namespace mach_module */
} /* namespace libreverse */
