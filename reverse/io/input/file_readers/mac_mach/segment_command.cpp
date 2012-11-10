/*  Segment_Command.cpp

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

#include "Segment_Command.h"
#include "Section.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace libreverse
{
    namespace mach_module
    {

        Segment_Command::Segment_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize )
                : m_cmd ( cmd ),
                m_cmdsize ( cmdsize ),
                m_segname ( "" ),
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
        Segment_Command::convert ( bool need_convert )
        {
            if ( need_convert )
            {
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
        Segment_Command::to_String ()
        {
            std::stringstream output;

            output << "Segment Command:" << std::endl
            << boost::format ( "  Command Id: %1%" ) % m_cmd << std::endl
            << boost::format ( "  Command Size: %1%" ) % m_cmdsize << std::endl
            << boost::format ( "  Name: %1%" ) % m_segname << std::endl
            << boost::format ( "  Virtual Memory Address: 0x%1$X" ) % m_vmaddr << std::endl
            << boost::format ( "  Virtual Memory Size: 0x%1$X" ) % m_vmsize << std::endl
            << boost::format ( "  Offset: 0x%1$X" ) % m_fileoff << std::endl
            << boost::format ( "  Filesize: %1%" ) % m_filesize << std::endl
            << boost::format ( "  Max Protection: 0x%1$X" ) % m_maxprot << std::endl
            << boost::format ( "  Initial Protection: 0x%1$X" ) % m_initprot << std::endl
            << boost::format ( "  Number of Sections: %1%" ) % m_nsects << std::endl
            << boost::format ( "  Flags: %1$X" ) % m_flags;

            for ( Section_List_t::const_iterator cpos = m_sections.begin();
                    cpos != m_sections.end();
                    ++cpos )
            {
                output << ( *cpos )->to_String() << std::endl;
            }

            return output.str();
        }

        boost::uint32_t
        Segment_Command::get_Command ()
        {
            return m_cmd;
        }

        boost::uint32_t
        Segment_Command::get_Command_Size ()
        {
            return m_cmdsize;
        }

        std::string
        Segment_Command::get_Segment_Name ()
        {
            return m_segname;
        }

        boost::uint32_t
        Segment_Command::get_Virtual_Memory_Address ()
        {
            return m_vmaddr;
        }

        boost::uint32_t
        Segment_Command::get_Virtual_Memory_Size ()
        {
            return m_vmsize;
        }

        boost::uint32_t
        Segment_Command::get_File_Offset ()
        {
            return m_fileoff;
        }

        boost::uint32_t
        Segment_Command::get_File_Size ()
        {
            return m_filesize;
        }

        boost::uint32_t
        Segment_Command::get_Max_Protection ()
        {
            return m_maxprot;
        }

        boost::uint32_t
        Segment_Command::get_Init_Protection ()
        {
            return m_initprot;
        }

        boost::uint32_t
        Segment_Command::get_Section_Count ()
        {
            return m_nsects;
        }

        boost::uint32_t
        Segment_Command::get_Flags ()
        {
            return m_flags;
        }

        void
        Segment_Command::push_back ( mach_types::Section::ptr_t obj )
        {
            m_sections.push_back ( obj );
        }
    } /* namespace mach_module */
} /* namespace libreverse */
