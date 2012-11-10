/*  Elf_File_Header_32.cpp

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

#include "Elf_File_Header_32.h"
#include "Elf_File_Header_Utils.h"

#include <sstream>
#include <boost/format.hpp>

#include "io/Byte_Converter.h"
#include "errors/File_Reader_Exception.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace elf_module
  {

    Elf_File_Header_32::Elf_File_Header_32()
      : e_ident ( new Elf_Header_Eident() ),
	e_type ( 0 ),
	e_machine ( 0 ),
	e_version ( 0 ),
	e_entry ( 0 ),
	e_phoff ( 0 ),
	e_shoff ( 0 ),
	e_flags ( 0 ),
	e_ehsize ( 0 ),
	e_phentsize ( 0 ),
	e_phnum ( 0 ),
	e_shentsize ( 0 ),
	e_shnum ( 0 ),
	e_shstrndx ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Elf_File_Header_32::~Elf_File_Header_32()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_File_Header_32::convert ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_File_Header_32::convert" );
#endif /* LIBREVERSE_DEBUG */


      io::Byte_Converter::convert ( e_type );
      io::Byte_Converter::convert ( e_machine );
      io::Byte_Converter::convert ( e_version );
      io::Byte_Converter::convert ( e_entry );
      io::Byte_Converter::convert ( e_phoff );
      io::Byte_Converter::convert ( e_shoff );
      io::Byte_Converter::convert ( e_flags );
      io::Byte_Converter::convert ( e_ehsize );
      io::Byte_Converter::convert ( e_phentsize );
      io::Byte_Converter::convert ( e_phnum );
      io::Byte_Converter::convert ( e_shentsize );
      io::Byte_Converter::convert ( e_shnum );
      io::Byte_Converter::convert ( e_shstrndx );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_File_Header_32::convert" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Elf_File_Header_32::needs_Convert ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_File_Header_32::needs_Convert" );
#endif /* LIBREVERSE_DEBUG */


      bool need_convert = false;

      unsigned char EndianTest[2] = { 1, 0 };

      // TRUE = host supports little-endian
      // FALSE = host supports big-endian
      bool system_little_endian = true;

      if ( * ( short* ) ( EndianTest ) == 0x10 )
	{
	  system_little_endian = false;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "System is little endian = %1$X" )
					% static_cast<boost::uint16_t>(system_little_endian) ) );
#endif /* LIBREVERSE_DEBUG */


      if ( system_little_endian != e_ident->is_Little_Endian() )
	{
	  need_convert = true;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DATA,
			   boost::str ( boost::format ( "Needs convert = %1$X" ) % static_cast<boost::uint16_t>(need_convert) ) );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_File_Header_32::needs_Convert" );
#endif /* LIBREVERSE_DEBUG */


      return need_convert;
    }

    std::string
    Elf_File_Header_32::get_File_Type_Meta () const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_File_Type_Meta" );
#endif /* LIBREVERSE_DEBUG */


      return Elf_File_Header_Utils::get_File_Type_Meta ( e_type );
    }

    boost::uint16_t
    Elf_File_Header_32::get_File_Type_Value () const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_File_Type_Value" );
#endif /* LIBREVERSE_DEBUG */


      return e_type;
    }

    std::string
    Elf_File_Header_32::get_Arch_Type () const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_File_Header_32::get_Arch_Type" );
#endif /* LIBREVERSE_DEBUG */


      return Elf_File_Header_Utils::get_Arch_Name ( e_machine );
    }

    std::string
    Elf_File_Header_32::to_String ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_File_Header_32::to_String" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output_str;

      output_str << e_ident->to_String();

      output_str << boost::format ( "  Type:                              %1$s (0x%2$X)" )
	% Elf_File_Header_Utils::get_File_Type_Name ( e_type )
	% e_type
		 << std::endl
		 << "  Machine:                           "
		 << Elf_File_Header_Utils::get_Machine_Name ( e_machine ) << std::endl;

      output_str << boost::format ( "  Version:                           %1%" ) %
	boost::io::group ( std::hex, std::showbase, e_version ) << std::endl;

      output_str << boost::format ( "  Entry point address:               %1%" ) %
	boost::io::group ( std::hex, std::showbase, e_entry ) << std::endl;

      output_str << "  Start of program headers:          "
		 << e_phoff << " (bytes into file)" << std::endl;
      output_str << "  Start of section headers:          "
		 << e_shoff << " (bytes into file)" << std::endl;
      output_str << boost::format ( "  Flags:                             0x%1%%2%" ) %
	boost::io::group ( std::hex,
			   std::showbase,
			   e_flags ) %
	Elf_File_Header_Utils::get_Machine_Flags ( e_flags, e_machine ) << std::endl;

      output_str << "  Size of this header:               "
		 << e_ehsize << " (bytes)" << std::endl;
      output_str << "  Size of program headers table:     "
		 << e_phentsize << " (bytes)" << std::endl;
      output_str << "  Number of program headers:         "
		 << e_phnum << std::endl;
      output_str << "  Size of section headers:           "
		 << e_shentsize << " (bytes)" << std::endl;
      output_str << "  Number of section headers:         " << e_shnum << std::endl;
      output_str << "  Section header string table index: "
		 << e_shstrndx << std::endl;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_File_Header_32::to_String" );
#endif /* LIBREVERSE_DEBUG */


      return output_str.str();
    }

    void
    Elf_File_Header_32::get_Text_String ( io_types::Text_Data::data_type* output ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_File_Header_32::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


      output->push_back ( e_ident->to_String() );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_File_Header_32::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */

    }


    boost::uint16_t
    Elf_File_Header_32::get_Section_Header_Count ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Section_Header_Count" );
#endif /* LIBREVERSE_DEBUG */


      return e_shnum;
    }

    boost::uint16_t
    Elf_File_Header_32::get_Program_Header_Count ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Program_Header_Count" );
#endif /* LIBREVERSE_DEBUG */

      return e_phnum;
    }

    boost::uint32_t
    Elf_File_Header_32::get_Section_Header_Offset ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Section_Header_Offset" );
#endif /* LIBREVERSE_DEBUG */


      return e_shoff;
    }

    boost::uint16_t
    Elf_File_Header_32::get_Machine_Value ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Machine_Value" );
#endif /* LIBREVERSE_DEBUG */


      return e_machine;
    }

    boost::uint16_t
    Elf_File_Header_32::get_String_Token_Index ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_String_Token_Index" );
#endif /* LIBREVERSE_DEBUG */


      return e_shstrndx;
    }

    boost::uint32_t
    Elf_File_Header_32::get_Program_Header_Offset ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Program_Header_Offset" );
#endif /* LIBREVERSE_DEBUG */


      return e_phoff;
    }

    elf_types::Elf_Header_Eident::ptr_t
    Elf_File_Header_32::get_Eident ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Eident" );
#endif /* LIBREVERSE_DEBUG */


      return e_ident;
    }

    boost::uint32_t
    Elf_File_Header_32::get_Entry ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_File_Header_32::get_Entry" );
#endif /* LIBREVERSE_DEBUG */


      return e_entry;
    }
  } /* namespace elf_module */
} /* namespace libreverse */
