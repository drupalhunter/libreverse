/*  Elf_Section_Header_32.cpp

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

#include "Elf_Section_Header_32.h"
#include "io/Byte_Converter.h"
#include "Elf_Common.h"
#include "Elf_mips.h"
#include "Elf_hppa.h"
#include "Elf_ia64.h"

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

    Elf_Section_Header_32::Elf_Section_Header_32 ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32 constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Elf_Section_Header_32::Elf_Section_Header_32 ( boost::uint16_t e_machine )
      : m_e_machine ( e_machine )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32 constructor (uint16)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Section_Header_32::convert ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_32::convert" );
#endif /* LIBREVERSE_DEBUG */


      io::Byte_Converter::convert ( sh_name );
      io::Byte_Converter::convert ( sh_type );
      io::Byte_Converter::convert ( sh_link );
      io::Byte_Converter::convert ( sh_info );
      io::Byte_Converter::convert ( sh_flags );
      io::Byte_Converter::convert ( sh_offset );
      io::Byte_Converter::convert ( sh_size );
      io::Byte_Converter::convert ( sh_addralign );
      io::Byte_Converter::convert ( sh_entsize );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_32::convert" );
#endif /* LIBREVERSE_DEBUG */


    }

    std::string
    Elf_Section_Header_32::to_String() const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_32::to_String" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      result << boost::format ( " %1$-17s %2$08X %3$08X %4$08X %5$08X 2**%6$X" )
	% m_str_name
	% sh_addr
	% sh_offset
	% sh_size
	% sh_info
	% sh_addralign;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_32::to_String" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    void
    Elf_Section_Header_32::get_Text_String ( io_types::Text_Data::data_type* ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_32::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


      // ADD text if we are a sh_type == SHT_PROGBITS and SHF_ALLOC + SHF_WRITE


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_32::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Elf_Section_Header_32::get_Section_Name_Index() const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Section_Name_Index" );
#endif /* LIBREVERSE_DEBUG */


      return sh_name;
    }

    boost::uint32_t
    Elf_Section_Header_32::get_Section_Size ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Section_Size" );
#endif /* LIBREVERSE_DEBUG */

	
      return sh_size;
    }

    void
    Elf_Section_Header_32::set_Section_String_Name ( std::string name )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_32::set_Section_String_Name" );
#endif /* LIBREVERSE_DEBUG */


      m_str_name = name;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_32::set_Section_String_Name" );
#endif /* LIBREVERSE_DEBUG */


    }

    std::string
    Elf_Section_Header_32::get_Section_String_Name ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Section_String_Name" );
#endif /* LIBREVERSE_DEBUG */


      return m_str_name;
    }

    boost::uint32_t
    Elf_Section_Header_32::get_Section_Offset ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Section_Offset" );
#endif /* LIBREVERSE_DEBUG */


      return sh_offset;
    }

    boost::uint32_t
    Elf_Section_Header_32::get_Section_Type ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Section_Type" );
#endif /* LIBREVERSE_DEBUG */


      return sh_type;
    }

    boost::uint32_t
    Elf_Section_Header_32::get_Next_Section_Index ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Next_Section_Index" );
#endif /* LIBREVERSE_DEBUG */


      return sh_link;
    }

    boost::uint32_t
    Elf_Section_Header_32::get_Section_Token_Size ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Section_Header_32::get_Section_Token_Size" );
#endif /* LIBREVERSE_DEBUG */


      return sh_entsize;
    }
  } /* namespace elf_module */
} /* namespace libreverse */
