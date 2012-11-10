/*  Elf_Section_Header_Utils.cpp

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

#include "Elf_Section_Header_Utils.h"
#include "Elf_Common.h"
#include "Elf_mips.h"
#include "Elf_hppa.h"
#include "Elf_ia64.h"

#include "io/Byte_Converter.h"

#include <boost/format.hpp>
#include <sstream>
#include <iomanip>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{ 
  namespace elf_module
  {

    std::string
    Elf_Section_Header_Utils::get_Flags ( boost::uint64_t sh_flags )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_Utils::get_flags" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      while ( sh_flags )
	{
	  boost::uint64_t flag;

	  flag = sh_flags & - sh_flags;
	  sh_flags &= ~ flag;

	  switch ( flag )
	    {
	    case Elf_Common::SHF_WRITE:
	      result << "W"; break;
	    case Elf_Common::SHF_ALLOC:
	      result << "A"; break;
	    case Elf_Common::SHF_EXECINSTR:
	      result << "X"; break;
	    case Elf_Common::SHF_MERGE:
	      result << "M"; break;
	    case Elf_Common::SHF_STRINGS:
	      result << "S"; break;
	    case Elf_Common::SHF_INFO_LINK:
	      result << "I"; break;
	    case Elf_Common::SHF_LINK_ORDER:
	      result << "L"; break;
	    case Elf_Common::SHF_OS_NONCONFORMING:
	      result << "O"; break;
	    case Elf_Common::SHF_GROUP:
	      result << "G"; break;
	    case Elf_Common::SHF_TLS:
	      result << "T"; break;
	    default:
	      if ( flag & Elf_Common::SHF_MASKOS )
		{
		  result << "o";
		  sh_flags &= ~ Elf_Common::SHF_MASKOS;
		}
	      else if ( flag & Elf_Common::SHF_MASKPROC )
		{
		  result << "p";
		  sh_flags &= ~ Elf_Common::SHF_MASKPROC;
		}
	      else
		result << "x";
	      break;
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_Utils::get_flags" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    std::string
    Elf_Section_Header_Utils::get_Section_Type_Name ( boost::uint32_t sh_type,
						      boost::uint16_t e_machine )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_Utils::get_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      switch ( sh_type )
	{
	case Elf_Common::SHT_NULL:      result << "NULL"; break;
	case Elf_Common::SHT_PROGBITS:          result << "PROGBITS"; break;
	case Elf_Common::SHT_SYMTAB:        result << "SYMTAB"; break;
	case Elf_Common::SHT_STRTAB:        result << "STRTAB"; break;
	case Elf_Common::SHT_RELA:      result << "RELA"; break;
	case Elf_Common::SHT_HASH:      result << "HASH"; break;
	case Elf_Common::SHT_DYNAMIC:       result << "DYNAMIC"; break;
	case Elf_Common::SHT_NOTE:      result << "NOTE"; break;
	case Elf_Common::SHT_NOBITS:        result << "NOBITS"; break;
	case Elf_Common::SHT_REL:               result << "REL"; break;
	case Elf_Common::SHT_SHLIB:     result << "SHLIB"; break;
	case Elf_Common::SHT_DYNSYM:        result << "DYNSYM"; break;
	case Elf_Common::SHT_INIT_ARRAY:            result << "INIT_ARRAY"; break;
	case Elf_Common::SHT_FINI_ARRAY:            result << "FINI_ARRAY"; break;
	case Elf_Common::SHT_PREINIT_ARRAY: result << "PREINIT_ARRAY"; break;
	case Elf_Common::SHT_GROUP:     result << "GROUP"; break;
	case Elf_Common::SHT_SYMTAB_SHNDX:  result << "SYMTAB SECTION INDICIES"; break;
	case Elf_Common::SHT_GNU_verdef:            result << "VERDEF"; break;
	case Elf_Common::SHT_GNU_verneed:           result << "VERNEED"; break;
	case Elf_Common::SHT_GNU_versym:            result << "VERSYM"; break;
	case 0x6ffffff0:                        result << "VERSYM"; break;
	case 0x6ffffffc:                        result << "VERDEF"; break;
	case 0x7ffffffd:                        result << "AUXILIARY"; break;
	case 0x7fffffff:                        result << "FILTER"; break;
	case Elf_Common::SHT_GNU_LIBLIST:           result << "GNU_LIBLIST"; break;

	default:
	  if ( ( sh_type >= Elf_Common::SHT_LOPROC ) && ( sh_type <= Elf_Common::SHT_HIPROC ) )
	    {
	      switch ( e_machine )
		{
		case Elf_Common::EM_MIPS:
		case Elf_Common::EM_MIPS_RS3_LE:
		  result << Elf_Section_Header_Utils::get_Mips_Section_Type_Name ( sh_type );
		  break;
		case Elf_Common::EM_PARISC:
		  result << Elf_Section_Header_Utils::get_Parisc_Section_Type_Name ( sh_type );
		  break;
		case Elf_Common::EM_IA_64:
		  result << Elf_Section_Header_Utils::get_Ia64_Section_Type_Name ( sh_type );
		  break;
		default:
		  result << boost::format ( "LOPROC+%x" ) % ( sh_type - Elf_Common::SHT_LOPROC );
		  break;
		}
	    }
	  else if ( ( sh_type >= Elf_Common::SHT_LOOS ) && ( sh_type <= Elf_Common::SHT_HIOS ) )
	    {
	      result << boost::format ( "LOOS+%x" ) % ( sh_type - Elf_Common::SHT_LOOS );
	    }
	  else if ( ( sh_type >= Elf_Common::SHT_LOUSER ) && ( sh_type <= Elf_Common::SHT_HIUSER ) )
	    {
	      result << boost::format ( "LOUSER+%x" ) % ( sh_type - Elf_Common::SHT_LOUSER );
	    }
	  else
	    {
	      result << boost::format ( "<unknown>: %x" ) % sh_type;
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_Utils::get_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    std::string
    Elf_Section_Header_Utils::get_Mips_Section_Type_Name ( boost::uint32_t sh_type )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_Utils::get_Mips_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      switch ( sh_type )
	{
	case Elf_mips::SHT_MIPS_LIBLIST:       result << "MIPS_LIBLIST"; break;
	case Elf_mips::SHT_MIPS_MSYM:            result << "MIPS_MSYM"; break;
	case Elf_mips::SHT_MIPS_CONFLICT:      result << "MIPS_CONFLICT"; break;
	case Elf_mips::SHT_MIPS_GPTAB:       result << "MIPS_GPTAB"; break;
	case Elf_mips::SHT_MIPS_UCODE:       result << "MIPS_UCODE"; break;
	case Elf_mips::SHT_MIPS_DEBUG:       result << "MIPS_DEBUG"; break;
	case Elf_mips::SHT_MIPS_REGINFO:       result << "MIPS_REGINFO"; break;
	case Elf_mips::SHT_MIPS_PACKAGE:       result << "MIPS_PACKAGE"; break;
	case Elf_mips::SHT_MIPS_PACKSYM:       result << "MIPS_PACKSYM"; break;
	case Elf_mips::SHT_MIPS_RELD:            result << "MIPS_RELD"; break;
	case Elf_mips::SHT_MIPS_IFACE:       result << "MIPS_IFACE"; break;
	case Elf_mips::SHT_MIPS_CONTENT:       result << "MIPS_CONTENT"; break;
	case Elf_mips::SHT_MIPS_OPTIONS:       result << "MIPS_OPTIONS"; break;
	case Elf_mips::SHT_MIPS_SHDR:            result << "MIPS_SHDR"; break;
	case Elf_mips::SHT_MIPS_FDESC:       result << "MIPS_FDESC"; break;
	case Elf_mips::SHT_MIPS_EXTSYM:      result << "MIPS_EXTSYM"; break;
	case Elf_mips::SHT_MIPS_DENSE:       result << "MIPS_DENSE"; break;
	case Elf_mips::SHT_MIPS_PDESC:       result << "MIPS_PDESC"; break;
	case Elf_mips::SHT_MIPS_LOCSYM:      result << "MIPS_LOCSYM"; break;
	case Elf_mips::SHT_MIPS_AUXSYM:      result << "MIPS_AUXSYM"; break;
	case Elf_mips::SHT_MIPS_OPTSYM:      result << "MIPS_OPTSYM"; break;
	case Elf_mips::SHT_MIPS_LOCSTR:      result << "MIPS_LOCSTR"; break;
	case Elf_mips::SHT_MIPS_LINE:            result << "MIPS_LINE"; break;
	case Elf_mips::SHT_MIPS_RFDESC:      result << "MIPS_RFDESC"; break;
	case Elf_mips::SHT_MIPS_DELTASYM:      result << "MIPS_DELTASYM"; break;
	case Elf_mips::SHT_MIPS_DELTAINST:     result << "MIPS_DELTAINST"; break;
	case Elf_mips::SHT_MIPS_DELTACLASS:    result << "MIPS_DELTACLASS"; break;
	case Elf_mips::SHT_MIPS_DWARF:       result << "MIPS_DWARF"; break;
	case Elf_mips::SHT_MIPS_DELTADECL:     result << "MIPS_DELTADECL"; break;
	case Elf_mips::SHT_MIPS_SYMBOL_LIB:    result << "MIPS_SYMBOL_LIB"; break;
	case Elf_mips::SHT_MIPS_EVENTS:      result << "MIPS_EVENTS"; break;
	case Elf_mips::SHT_MIPS_TRANSLATE:     result << "MIPS_TRANSLATE"; break;
	case Elf_mips::SHT_MIPS_PIXIE:       result << "MIPS_PIXIE"; break;
	case Elf_mips::SHT_MIPS_XLATE:       result << "MIPS_XLATE"; break;
	case Elf_mips::SHT_MIPS_XLATE_DEBUG:   result << "MIPS_XLATE_DEBUG"; break;
	case Elf_mips::SHT_MIPS_WHIRL:       result << "MIPS_WHIRL"; break;
	case Elf_mips::SHT_MIPS_EH_REGION:     result << "MIPS_EH_REGION"; break;
	case Elf_mips::SHT_MIPS_XLATE_OLD:     result << "MIPS_XLATE_OLD"; break;
	case Elf_mips::SHT_MIPS_PDR_EXCEPTION: result << "MIPS_PDR_EXCEPTION"; break;
	default:
	  result << "<unknown> ";
	  break;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_Utils::get_Mips_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    std::string
    Elf_Section_Header_Utils::get_Parisc_Section_Type_Name ( boost::uint32_t sh_type )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_Utils::get_Parisc_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      switch ( sh_type )
	{
	case Elf_hppa::SHT_PARISC_EXT:
	  {
	    result << "PARISC_EXT";
	    break;
	  }
	case Elf_hppa::SHT_PARISC_UNWIND:
	  {
	    result << "PARISC_UNWIND";
	    break;
	  }
	case Elf_hppa::SHT_PARISC_DOC:
	  {
	    result << "PARISC_DOC";
	    break;
	  }
	default:
	  {
	    result << "<unknown>";
	    break;
	  }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_Utils::get_Mips_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    std::string
    Elf_Section_Header_Utils::get_Ia64_Section_Type_Name ( boost::uint32_t sh_type )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_Utils::get_Ia64_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      /* If the top 8 bits are 0x78 the next 8 are the os/abi ID. */
      if ( ( sh_type & 0xFF000000 ) == Elf_ia64::SHT_IA_64_LOPSREG )
	{
	  result << Elf_Section_Header_Utils::get_Osabi_Name ( ( sh_type & 0x00FF0000 ) >> 16 );
	}
      else
	{
	  switch ( sh_type )
	    {
	    case Elf_ia64::SHT_IA_64_EXT:
	      {
		result << "IA_64_EXT";
		break;
	      }
	    case Elf_ia64::SHT_IA_64_UNWIND:
	      {
		result << "IA_64_UNWIND";
		break;
	      }
	    case Elf_ia64::SHT_IA_64_PRIORITY_INIT:
	      {
		result << "IA_64_PRIORITY_INIT";
		break;
	      }
	    default:
	      {
		result << "<unknown>";
		break;
	      }
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_Utils::get_Ia64_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    std::string
    Elf_Section_Header_Utils::get_Osabi_Name ( boost::uint32_t osabi )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Section_Header_Utils::get_Osabi_Name" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      switch ( osabi )
	{
	case Elf_Common::ELFOSABI_NONE:     result << "UNIX - System V";
	case Elf_Common::ELFOSABI_HPUX:     result << "UNIX - HP-UX";
	case Elf_Common::ELFOSABI_NETBSD:       result << "UNIX - NetBSD";
	case Elf_Common::ELFOSABI_LINUX:        result << "UNIX - Linux";
	case Elf_Common::ELFOSABI_HURD:     result << "GNU/Hurd";
	case Elf_Common::ELFOSABI_SOLARIS:    result << "UNIX - Solaris";
	case Elf_Common::ELFOSABI_AIX:      result << "UNIX - AIX";
	case Elf_Common::ELFOSABI_IRIX:     result << "UNIX - IRIX";
	case Elf_Common::ELFOSABI_FREEBSD:    result << "UNIX - FreeBSD";
	case Elf_Common::ELFOSABI_TRU64:        result << "UNIX - TRU64";
	case Elf_Common::ELFOSABI_MODESTO:    result << "Novell - Modesto";
	case Elf_Common::ELFOSABI_OPENBSD:    result << "UNIX - OpenBSD";
	case Elf_Common::ELFOSABI_OPENVMS:    result << "VMS - OpenVMS";
	case Elf_Common::ELFOSABI_NSK:      result << "HP - Non-Stop Kernel";
	case Elf_Common::ELFOSABI_AROS:     result << "Amiga Research OS";
	case Elf_Common::ELFOSABI_STANDALONE: result << "Standalone App";
	case Elf_Common::ELFOSABI_ARM:      result << "ARM";
	default:
	  result << boost::format ( "<unknown: %x>" ) % osabi;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Section_Header_Utils::get_Osabi_Name" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

  } /* namespace elf_module */
} /* namespace libreverse */
