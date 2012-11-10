/*  Elf_Program_Header_32.cpp

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

#include "Elf_Program_Header_32.h"
#include "Elf_Program_Header_Utils.h"
#include "Elf_Common.h"

#include "io/Byte_Converter.h"

#include <sstream>
#include <iomanip>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
    namespace elf_module
    {

        Elf_Program_Header_32::Elf_Program_Header_32 ( boost::uint16_t e_machine )
	  : m_e_machine ( e_machine )
        {

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Elf_Program_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

        }

        void
        Elf_Program_Header_32::convert ()
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Elf_Program_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


            io::Byte_Converter::convert ( p_type );
            io::Byte_Converter::convert ( p_offset );
            io::Byte_Converter::convert ( p_vaddr );
            io::Byte_Converter::convert ( p_paddr );
            io::Byte_Converter::convert ( p_filesz );
            io::Byte_Converter::convert ( p_memsz );
            io::Byte_Converter::convert ( p_flags );
            io::Byte_Converter::convert ( p_align );


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Elf_Program_Header::convert" );
#endif /* LIBREVERSE_DEBUG */

        }

        std::string
	Elf_Program_Header_32::to_String ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Elf_Program_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


            std::stringstream output_str;

            // PRINT: type
            output_str << boost::format ( "  %|-15| " ) % Elf_Program_Header_Utils::get_segment_type ( p_type, m_e_machine );

            output_str << boost::format ( "0x%1%   " ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 6 ),
                               p_offset );

            output_str << boost::format ( "0x%1%   " ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 8 ),
                               p_vaddr );

            output_str << boost::format ( "0x%1%   " ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 8 ),
                               p_paddr );

            output_str << boost::format ( "0x%1%  " ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 5 ),
                               p_filesz );

            output_str << boost::format ( "0x%1%    " ) %
            boost::io::group ( std::setfill ( '0' ),
                               std::hex,
                               std::setw ( 5 ),
                               p_memsz );

            if ( p_flags & Elf_Common::PF_R )
            {
                output_str << "R";
            }
            else
            {
                output_str << " ";
            }

            if ( p_flags & Elf_Common::PF_W )
            {
                output_str << "W";
            }
            else
            {
                output_str << " ";
            }

            if ( p_flags & Elf_Common::PF_X )
            {
                output_str << "E";
            }
            else
            {
                output_str << " ";
            }

            output_str << boost::format ( "  0x%|-5|" ) %
	      boost::io::group ( std::hex, p_align );


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Elf_Program_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


            return output_str.str();
        }

        void
        Elf_Program_Header_32::get_Text_String ( io_types::Text_Data::data_type* )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Elf_Section_Header::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


            // ADD text if we are a sh_type == SHT_PROGBITS and SHF_ALLOC + SHF_WRITE


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Elf_Section_Header::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */

        }


        boost::uint32_t
        Elf_Program_Header_32::get_Type ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Elf_Program_Header::get_Type" );
#endif /* LIBREVERSE_DEBUG */


            return p_type;
        }

        bool
        Elf_Program_Header_32::in_Range ( boost::uint32_t addr ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Elf_Program_Header::in_Range" );
#endif /* LIBREVERSE_DEBUG */


            return ( addr >= p_vaddr ) && ( addr <= p_vaddr + p_filesz );
        }

        boost::uint32_t
        Elf_Program_Header_32::get_Address_Offset ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Elf_Program_Header::get_Address_Offset" );
#endif /* LIBREVERSE_DEBUG */


            return p_vaddr - p_offset;
        }

        boost::uint32_t
        Elf_Program_Header_32::get_Virtual_Address ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Elf_Program_Header::get_Virtual_Address" );
#endif /* LIBREVERSE_DEBUG */


            return p_vaddr;
        }

        boost::uint32_t
        Elf_Program_Header_32::get_Memory_Size ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Elf_Program_Header::get_Memory_Size" );
#endif /* LIBREVERSE_DEBUG */


            return p_memsz;
        }
    } /* namespace elf_module */
} /* namespace libreverse */
