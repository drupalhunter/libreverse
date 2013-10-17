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

#include <reverse/io/byte_converter.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_section_header_utils.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mips.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_hppa.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ia64.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <sstream>
#include <iomanip>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_section_header_utils::get_flags ( boost::uint64_t sh_flags )
	  {

	    trace::io_detail ( "Entering Elf_Section_Header_Utils::get_flags" );

	    std::stringstream result;

	    while ( sh_flags )
	      {
		boost::uint64_t flag;

		flag = sh_flags & - sh_flags;
		sh_flags &= ~ flag;

		switch ( flag )
		  {
		  case elf_common::SHF_WRITE:
		    result << "W"; break;
		  case elf_common::SHF_ALLOC:
		    result << "A"; break;
		  case elf_common::SHF_EXECINSTR:
		    result << "X"; break;
		  case elf_common::SHF_MERGE:
		    result << "M"; break;
		  case elf_common::SHF_STRINGS:
		    result << "S"; break;
		  case elf_common::SHF_INFO_LINK:
		    result << "I"; break;
		  case elf_common::SHF_LINK_ORDER:
		    result << "L"; break;
		  case elf_common::SHF_OS_NONCONFORMING:
		    result << "O"; break;
		  case elf_common::SHF_GROUP:
		    result << "G"; break;
		  case elf_common::SHF_TLS:
		    result << "T"; break;
		  default:
		    if ( flag & elf_common::SHF_MASKOS )
		      {
			result << "o";
			sh_flags &= ~ elf_common::SHF_MASKOS;
		      }
		    else if ( flag & elf_common::SHF_MASKPROC )
		      {
			result << "p";
			sh_flags &= ~ elf_common::SHF_MASKPROC;
		      }
		    else
		      result << "x";
		    break;
		  }
	      }

	    trace::io_detail ( "Exiting Elf_Section_Header_Utils::get_flags" );

	    return result.str();
	  }

	  std::string
	  elf_section_header_utils::get_section_type_name ( boost::uint32_t sh_type,
							    boost::uint16_t e_machine )
	  {

	    trace::io_detail ( "Entering Elf_Section_Header_Utils::get_Section_Type_Name" );

	    std::stringstream result;

	    switch ( sh_type )
	      {
	      case elf_common::SHT_NULL:      result << "NULL"; break;
	      case elf_common::SHT_PROGBITS:          result << "PROGBITS"; break;
	      case elf_common::SHT_SYMTAB:        result << "SYMTAB"; break;
	      case elf_common::SHT_STRTAB:        result << "STRTAB"; break;
	      case elf_common::SHT_RELA:      result << "RELA"; break;
	      case elf_common::SHT_HASH:      result << "HASH"; break;
	      case elf_common::SHT_DYNAMIC:       result << "DYNAMIC"; break;
	      case elf_common::SHT_NOTE:      result << "NOTE"; break;
	      case elf_common::SHT_NOBITS:        result << "NOBITS"; break;
	      case elf_common::SHT_REL:               result << "REL"; break;
	      case elf_common::SHT_SHLIB:     result << "SHLIB"; break;
	      case elf_common::SHT_DYNSYM:        result << "DYNSYM"; break;
	      case elf_common::SHT_INIT_ARRAY:            result << "INIT_ARRAY"; break;
	      case elf_common::SHT_FINI_ARRAY:            result << "FINI_ARRAY"; break;
	      case elf_common::SHT_PREINIT_ARRAY: result << "PREINIT_ARRAY"; break;
	      case elf_common::SHT_GROUP:     result << "GROUP"; break;
	      case elf_common::SHT_SYMTAB_SHNDX:  result << "SYMTAB SECTION INDICIES"; break;
	      case elf_common::SHT_GNU_verdef:            result << "VERDEF"; break;
	      case elf_common::SHT_GNU_verneed:           result << "VERNEED"; break;
	      case elf_common::SHT_GNU_versym:            result << "VERSYM"; break;
	      case 0x6ffffff0:                        result << "VERSYM"; break;
	      case 0x6ffffffc:                        result << "VERDEF"; break;
	      case 0x7ffffffd:                        result << "AUXILIARY"; break;
	      case 0x7fffffff:                        result << "FILTER"; break;
	      case elf_common::SHT_GNU_LIBLIST:           result << "GNU_LIBLIST"; break;

	      default:
		if ( ( sh_type >= elf_common::SHT_LOPROC ) && ( sh_type <= elf_common::SHT_HIPROC ) )
		  {
		    switch ( e_machine )
		      {
		      case elf_common::EM_MIPS:
		      case elf_common::EM_MIPS_RS3_LE:
			result << elf_section_header_utils::get_mips_section_type_name ( sh_type );
			break;
		      case elf_common::EM_PARISC:
			result << elf_section_header_utils::get_parisc_section_type_name ( sh_type );
			break;
		      case elf_common::EM_IA_64:
			result << elf_section_header_utils::get_ia64_section_type_name ( sh_type );
			break;
		      default:
			result << boost::format ( "LOPROC+%x" ) % ( sh_type - elf_common::SHT_LOPROC );
			break;
		      }
		  }
		else if ( ( sh_type >= elf_common::SHT_LOOS ) && ( sh_type <= elf_common::SHT_HIOS ) )
		  {
		    result << boost::format ( "LOOS+%x" ) % ( sh_type - elf_common::SHT_LOOS );
		  }
		else if ( ( sh_type >= elf_common::SHT_LOUSER ) && ( sh_type <= elf_common::SHT_HIUSER ) )
		  {
		    result << boost::format ( "LOUSER+%x" ) % ( sh_type - elf_common::SHT_LOUSER );
		  }
		else
		  {
		    result << boost::format ( "<unknown>: %x" ) % sh_type;
		  }
	      }

	    trace::io_detail ( "Exiting Elf_Section_Header_Utils::get_Section_Type_Name" );

	    return result.str();
	  }

	  std::string
	  elf_section_header_utils::get_mips_section_type_name ( boost::uint32_t sh_type )
	  {

	    trace::io_detail ( "Entering Elf_Section_Header_Utils::get_Mips_Section_Type_Name" );

	    std::stringstream result;

	    switch ( sh_type )
	      {
	      case elf_mips::SHT_MIPS_LIBLIST:       result << "MIPS_LIBLIST"; break;
	      case elf_mips::SHT_MIPS_MSYM:            result << "MIPS_MSYM"; break;
	      case elf_mips::SHT_MIPS_CONFLICT:      result << "MIPS_CONFLICT"; break;
	      case elf_mips::SHT_MIPS_GPTAB:       result << "MIPS_GPTAB"; break;
	      case elf_mips::SHT_MIPS_UCODE:       result << "MIPS_UCODE"; break;
	      case elf_mips::SHT_MIPS_DEBUG:       result << "MIPS_DEBUG"; break;
	      case elf_mips::SHT_MIPS_REGINFO:       result << "MIPS_REGINFO"; break;
	      case elf_mips::SHT_MIPS_PACKAGE:       result << "MIPS_PACKAGE"; break;
	      case elf_mips::SHT_MIPS_PACKSYM:       result << "MIPS_PACKSYM"; break;
	      case elf_mips::SHT_MIPS_RELD:            result << "MIPS_RELD"; break;
	      case elf_mips::SHT_MIPS_IFACE:       result << "MIPS_IFACE"; break;
	      case elf_mips::SHT_MIPS_CONTENT:       result << "MIPS_CONTENT"; break;
	      case elf_mips::SHT_MIPS_OPTIONS:       result << "MIPS_OPTIONS"; break;
	      case elf_mips::SHT_MIPS_SHDR:            result << "MIPS_SHDR"; break;
	      case elf_mips::SHT_MIPS_FDESC:       result << "MIPS_FDESC"; break;
	      case elf_mips::SHT_MIPS_EXTSYM:      result << "MIPS_EXTSYM"; break;
	      case elf_mips::SHT_MIPS_DENSE:       result << "MIPS_DENSE"; break;
	      case elf_mips::SHT_MIPS_PDESC:       result << "MIPS_PDESC"; break;
	      case elf_mips::SHT_MIPS_LOCSYM:      result << "MIPS_LOCSYM"; break;
	      case elf_mips::SHT_MIPS_AUXSYM:      result << "MIPS_AUXSYM"; break;
	      case elf_mips::SHT_MIPS_OPTSYM:      result << "MIPS_OPTSYM"; break;
	      case elf_mips::SHT_MIPS_LOCSTR:      result << "MIPS_LOCSTR"; break;
	      case elf_mips::SHT_MIPS_LINE:            result << "MIPS_LINE"; break;
	      case elf_mips::SHT_MIPS_RFDESC:      result << "MIPS_RFDESC"; break;
	      case elf_mips::SHT_MIPS_DELTASYM:      result << "MIPS_DELTASYM"; break;
	      case elf_mips::SHT_MIPS_DELTAINST:     result << "MIPS_DELTAINST"; break;
	      case elf_mips::SHT_MIPS_DELTACLASS:    result << "MIPS_DELTACLASS"; break;
	      case elf_mips::SHT_MIPS_DWARF:       result << "MIPS_DWARF"; break;
	      case elf_mips::SHT_MIPS_DELTADECL:     result << "MIPS_DELTADECL"; break;
	      case elf_mips::SHT_MIPS_SYMBOL_LIB:    result << "MIPS_SYMBOL_LIB"; break;
	      case elf_mips::SHT_MIPS_EVENTS:      result << "MIPS_EVENTS"; break;
	      case elf_mips::SHT_MIPS_TRANSLATE:     result << "MIPS_TRANSLATE"; break;
	      case elf_mips::SHT_MIPS_PIXIE:       result << "MIPS_PIXIE"; break;
	      case elf_mips::SHT_MIPS_XLATE:       result << "MIPS_XLATE"; break;
	      case elf_mips::SHT_MIPS_XLATE_DEBUG:   result << "MIPS_XLATE_DEBUG"; break;
	      case elf_mips::SHT_MIPS_WHIRL:       result << "MIPS_WHIRL"; break;
	      case elf_mips::SHT_MIPS_EH_REGION:     result << "MIPS_EH_REGION"; break;
	      case elf_mips::SHT_MIPS_XLATE_OLD:     result << "MIPS_XLATE_OLD"; break;
	      case elf_mips::SHT_MIPS_PDR_EXCEPTION: result << "MIPS_PDR_EXCEPTION"; break;
	      default:
		result << "<unknown> ";
		break;
	      }
	    
	    trace::io_detail ( "Exiting Elf_Section_Header_Utils::get_Mips_Section_Type_Name" );

	    return result.str();
	  }

	  std::string
	  elf_section_header_utils::get_parisc_section_type_name ( boost::uint32_t sh_type )
	  {

	    trace::io_detail ( "Entering Elf_Section_Header_Utils::get_Parisc_Section_Type_Name" );

	    std::stringstream result;

	    switch ( sh_type )
	      {
	      case elf_hppa::SHT_PARISC_EXT:
		{
		  result << "PARISC_EXT";
		  break;
		}
	      case elf_hppa::SHT_PARISC_UNWIND:
		{
		  result << "PARISC_UNWIND";
		  break;
		}
	      case elf_hppa::SHT_PARISC_DOC:
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

	    trace::io_detail ( "Exiting Elf_Section_Header_Utils::get_Mips_Section_Type_Name" );

	    return result.str();
	  }

	  std::string
	  elf_section_header_utils::get_ia64_section_type_name ( boost::uint32_t sh_type )
	  {
	    trace::io_detail ( "Entering Elf_Section_Header_Utils::get_Ia64_Section_Type_Name" );

	    std::stringstream result;

	    /* If the top 8 bits are 0x78 the next 8 are the os/abi ID. */
	    if ( ( sh_type & 0xFF000000 ) == elf_ia64::SHT_IA_64_LOPSREG )
	      {
		result << elf_section_header_utils::get_osabi_name ( ( sh_type & 0x00FF0000 ) >> 16 );
	      }
	    else
	      {
		switch ( sh_type )
		  {
		  case elf_ia64::SHT_IA_64_EXT:
		    {
		      result << "IA_64_EXT";
		      break;
		    }
		  case elf_ia64::SHT_IA_64_UNWIND:
		    {
		      result << "IA_64_UNWIND";
		      break;
		    }
		  case elf_ia64::SHT_IA_64_PRIORITY_INIT:
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

	    trace::io_detail ( "Exiting Elf_Section_Header_Utils::get_Ia64_Section_Type_Name" );

	    return result.str();
	  }

	  std::string
	  elf_section_header_utils::get_osabi_name ( boost::uint32_t osabi )
	  {

	    trace::io_detail ( "Entering Elf_Section_Header_Utils::get_Osabi_Name" );

	    std::stringstream result;

	    switch ( osabi )
	      {
	      case elf_common::ELFOSABI_NONE:     result << "UNIX - System V";
	      case elf_common::ELFOSABI_HPUX:     result << "UNIX - HP-UX";
	      case elf_common::ELFOSABI_NETBSD:       result << "UNIX - NetBSD";
	      case elf_common::ELFOSABI_LINUX:        result << "UNIX - Linux";
	      case elf_common::ELFOSABI_HURD:     result << "GNU/Hurd";
	      case elf_common::ELFOSABI_SOLARIS:    result << "UNIX - Solaris";
	      case elf_common::ELFOSABI_AIX:      result << "UNIX - AIX";
	      case elf_common::ELFOSABI_IRIX:     result << "UNIX - IRIX";
	      case elf_common::ELFOSABI_FREEBSD:    result << "UNIX - FreeBSD";
	      case elf_common::ELFOSABI_TRU64:        result << "UNIX - TRU64";
	      case elf_common::ELFOSABI_MODESTO:    result << "Novell - Modesto";
	      case elf_common::ELFOSABI_OPENBSD:    result << "UNIX - OpenBSD";
	      case elf_common::ELFOSABI_OPENVMS:    result << "VMS - OpenVMS";
	      case elf_common::ELFOSABI_NSK:      result << "HP - Non-Stop Kernel";
	      case elf_common::ELFOSABI_AROS:     result << "Amiga Research OS";
	      case elf_common::ELFOSABI_STANDALONE: result << "Standalone App";
	      case elf_common::ELFOSABI_ARM:      result << "ARM";
	      default:
		result << boost::format ( "<unknown: %x>" ) % osabi;
	      }

	    trace::io_detail ( "Exiting Elf_Section_Header_Utils::get_Osabi_Name" );

	    return result.str();
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
