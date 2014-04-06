/*  Thread_Command.cpp

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

#include "Thread_Command.h"
#include "errors/Internal_Exception.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace reverse
{
    namespace mach_module
    {

        Thread_Command::Thread_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_flavor ( 0 ),
                m_count ( 0 )
        {}

        void
        Thread_Command::add_CPU_State ( mach_types::CPU_Thread_State::ptr_t cpu )
        {
            if ( ! cpu )
            {
                throw errors::Internal_Exception ( errors::Internal_Exception::null_pointer );
            }

            m_cpu = cpu;
        }

        void
        Thread_Command::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                io::Byte_Converter::convert ( m_cmd );
                io::Byte_Converter::convert ( m_cmdsize );
                io::Byte_Converter::convert ( m_flavor );
                io::Byte_Converter::convert ( m_count );
                m_cpu->convert ( need_convert );
            }
        }

        std::string
        Thread_Command::to_String ( void )
        {
            std::stringstream output;

            output << "Thread Command:" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << boost::format ( "  Flavor: %1%" ) % m_flavor << std::endl
            << boost::format ( "  Count: %1%" ) % m_count << std::endl
            << m_cpu->to_String();

            return output.str();
        }
    } /* namespace mach_module */
} /* namespace reverse */
