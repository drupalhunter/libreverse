/*  Elf_Relocation_64.cpp

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

#include "Elf_Relocation_64.h"
#include "Elf_Relocation_Utils.h"
#include "Elf_File_Header_64.h"

#include "io/Byte_Converter.h"

#include <iomanip>
#include <sstream>
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

    Elf_Relocation_64::Elf_Relocation_64 ( elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
      : r_offset ( 0 ),
	r_info ( 0 ),
	m_symbol_table_index ( 0 ),
	m_reloc_type ( 0 ),
	m_file_hdr ( file_hdr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Relocation_64 constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Relocation_64::convert ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Relocation_64::convert" );
#endif /* LIBREVERSE_DEBUG */


      io::Byte_Converter::convert ( r_offset );
      io::Byte_Converter::convert ( r_info );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Relocation_64::convert" );
#endif /* LIBREVERSE_DEBUG */


    }

    std::string
    Elf_Relocation_64::to_String() const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Relocation_64::to_String" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      output << boost::format ( "0x%1% " ) %
	boost::io::group ( std::setfill ( '0' ), std::hex, std::setw ( 16 ), r_offset );

      output << boost::format ( "0x%1% " ) %
	boost::io::group ( std::setfill ( '0' ), std::hex, std::setw ( 16 ), r_info );

      output << Elf_Relocation_Utils::get_Section_Type_Name ( m_file_hdr->get_Machine_Value(),
							      m_reloc_type,
							      static_cast<boost::uint8_t>(64) );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Relocation_64::to_String" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    boost::uint64_t
    Elf_Relocation_64::get_Symbol_Token_Index ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Relocation_64::get_Symbol_Token_Index" );
#endif /* LIBREVERSE_DEBUG */


      return m_symbol_table_index;
    }
  } /* namespace elf_module */
} /* namespace libreverse */
