/*  Elf_Symbol_64.cpp

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

#include "Elf_Symbol_64.h"

#include "io/Byte_Converter.h"

#include <boost/format.hpp>
#include <iomanip>
#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    Elf_Symbol_64::Elf_Symbol_64 ( boost::uint16_t e_machine )
        : st_name (0),
          st_value (0),
          st_size (0),
          st_info (0),
          st_other (0),
          st_shndx (0),
          m_symbol_name (""),
          m_symbol_binding (0),
          m_symbol_type (0),
          m_e_machine (e_machine)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Symbol constructor" );
#endif /* LIBREVERSE_DEBUG */
    }

    void Elf_Symbol_64::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol::convert" );
#endif /* LIBREVERSE_DEBUG */


	io::Byte_Converter::convert (st_name);
	io::Byte_Converter::convert (st_shndx);
	io::Byte_Converter::convert (st_value);
	io::Byte_Converter::convert (st_size);


#ifdef LIBREVERSE_DEBUG    
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol::convert" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Symbol_64::set_symbol_info ( boost::uint8_t binding,
				     boost::uint8_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol::set_symbol_info" );
#endif /* LIBREVERSE_DEBUG */


        st_info = ((binding << 4) + (type & 0xF));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol::set_symbol_info" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Elf_Symbol_64::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        output_str << boost::format("0x%1% ") %
	  boost::io::group (std::setfill('0'), std::hex, std::setw(8), st_value)
                   << " " << m_symbol_name;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output_str.str();
    }

    boost::uint32_t
    Elf_Symbol_64::get_String_Token_Index (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Symbol::get_String_Token_Index" );
#endif /* LIBREVERSE_DEBUG */

        return st_name;
    }

    void
    Elf_Symbol_64::set_Symbol_Name ( std::string name )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol::set_Symbol_Name" );
#endif /* LIBREVERSE_DEBUG */


        m_symbol_name = name;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol::set_Symbol_Name" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Elf_Symbol_64::get_Name (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Symbol::get_Name" );
#endif /* LIBREVERSE_DEBUG */

        return m_symbol_name;
    }

    boost::uint64_t
    Elf_Symbol_64::get_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Symbol::get_Value" );
#endif /* LIBREVERSE_DEBUG */

        return st_value;
    }

    boost::uint8_t
    Elf_Symbol_64::get_Symbol_Type_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Symbol::get_Symbol_Type_Value" );
#endif /* LIBREVERSE_DEBUG */

        return m_symbol_type;
    }

    boost::uint16_t
    Elf_Symbol_64::get_Index (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Symbol::get_Index" );
#endif /* LIBREVERSE_DEBUG */

        return st_shndx;
    }
} /* namespace elf_module */
} /* namespace libreverse */
