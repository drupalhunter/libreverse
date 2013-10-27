/*  Elf_Program_Header_T.cpp

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

#include <reverse/io/input/file_readers/linux_elf/elf_program_header_utils.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mips.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_hppa.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ia64.hpp>
#include <reverse/trace.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_program_header_utils::get_segment_type ( boost::uint32_t type_value,
						       boost::uint16_t machine_arch )
	  {
	    trace::io_detail ( "entering elf_program_header::get_segment_type" );

	    std::string output;

	    switch ( type_value )
	      {
	      case elf_common::PT_NULL:         output = "NULL"; break;
	      case elf_common::PT_LOAD:         output = "LOAD"; break;
	      case elf_common::PT_DYNAMIC:      output = "DYNAMIC"; break;
	      case elf_common::PT_INTERP:       output = "INTERP"; break;
	      case elf_common::PT_NOTE:         output = "NOTE"; break;
	      case elf_common::PT_SHLIB:        output = "SHLIB"; break;
	      case elf_common::PT_PHDR:         output = "PHDR"; break;
	      case elf_common::PT_TLS:          output = "TLS"; break;
	      case elf_common::PT_GNU_EH_FRAME: output = "GNU_EH_FRAME"; break;
	      case elf_common::PT_GNU_STACK:    output = "STACK"; break;
	      case elf_common::PT_GNU_RELRO:    output = "RELRO"; break;
	      case elf_common::PT_PAX_FLAGS:    output = "PAX_FLAGS"; break;
	      case elf_common::PT_SUNWBSS:      output = "SUNWBSS"; break;
	      case elf_common::PT_SUNWSTACK:    output = "SUNWSTACK"; break;

	      default:
		if ( ( type_value >= elf_common::PT_LOPROC ) && ( type_value <= elf_common::PT_HIPROC ) )
		  {
		    std::string type;
		    switch ( machine_arch )
		      {
		      case elf_common::EM_MIPS:
		      case elf_common::EM_MIPS_RS3_LE:
			{
			  type = elf_program_header_utils::get_mips_segment_type ( type_value );
			  break;
			}
		      case elf_common::EM_PARISC:
			{
			  type = elf_program_header_utils::get_parisc_segment_type ( type_value );
			  break;
			}
		      case elf_common::EM_IA_64:
			{
			  type = elf_program_header_utils::get_ia64_segment_type ( type_value );
			  break;
			}
		      default:
			break;
		      }

		    if ( ! type.empty() )
		      {
			output = type;
		      }
		    else
		      {
			output = boost::str ( boost::format ( "LOPROC+%1%" ) % ( type_value - elf_common::PT_LOPROC ) );
		      }
		  }
		else if ( ( type_value >= elf_common::PT_LOOS ) && ( type_value <= elf_common::PT_HIOS ) )
		  {
		    std::string type;

		    switch ( machine_arch )
		      {
		      case elf_common::EM_PARISC:
			type = elf_program_header_utils::get_parisc_segment_type ( type_value );
			break;
		      case elf_common::EM_IA_64:
			type = elf_program_header_utils::get_ia64_segment_type ( type_value );
			break;
		      default:
			break;
		      }

		    if ( ! type.empty() )
		      {
			output = type;
		      }
		    else
		      {
			output = boost::str ( boost::format ( "LOOS+%1%" ) % ( type_value - elf_common::PT_LOOS ) );
		      }
		  }
		else
		  {
		    output = boost::str ( boost::format ( "<unknown>: %1%" ) % type_value );
		  }
	      }

	    trace::io_detail ( "exiting elf_program_header::get_segment_type" );

	    return output;
	  }

	  std::string
	  elf_program_header_utils::get_mips_segment_type ( boost::uint32_t type_value )
	  {
	    trace::io_detail ( "entering elf_program_header::get_mips_segment_type" );

	    std::string output;

	    switch ( type_value )
	      {
	      case elf_mips::PT_MIPS_REGINFO: output = "REGINFO"; break;
	      case elf_mips::PT_MIPS_RTPROC:  output = "RTPROC"; break;
	      case elf_mips::PT_MIPS_OPTIONS: output = "OPTIONS"; break;
	      default: break;
	      }

	    trace::io_detail ( "exiting elf_program_header::get_mips_segment_type" );

	    return output;
	  }

	  std::string
	  elf_program_header_utils::get_parisc_segment_type ( boost::uint32_t type_value )
	  {
	    trace::io_detail ( "entering elf_program_header::get_parisc_segment_type" );

	    std::string output;

	    switch ( type_value )
	      {
	      case elf_hppa::PT_HP_TLS:       output = "HP_TLS"; break;
	      case elf_hppa::PT_HP_CORE_NONE:     output = "HP_CORE_NONE"; break;
	      case elf_hppa::PT_HP_CORE_VERSION:  output = "HP_CORE_VERSION"; break;
	      case elf_hppa::PT_HP_CORE_KERNEL:   output = "HP_CORE_KERNEL"; break;
	      case elf_hppa::PT_HP_CORE_COMM:     output = "HP_CORE_COMM"; break;
	      case elf_hppa::PT_HP_CORE_PROC:     output = "HP_CORE_PROC"; break;
	      case elf_hppa::PT_HP_CORE_LOADABLE: output = "HP_CORE_LOADABLE"; break;
	      case elf_hppa::PT_HP_CORE_STACK:    output = "HP_CORE_STACK"; break;
	      case elf_hppa::PT_HP_CORE_SHM:      output = "HP_CORE_SHM"; break;
	      case elf_hppa::PT_HP_CORE_MMF:      output = "HP_CORE_MMF"; break;
	      case elf_hppa::PT_HP_PARALLEL:      output = "HP_PARALLEL"; break;
	      case elf_hppa::PT_HP_FASTBIND:      output = "HP_FASTBIND"; break;
	      case elf_hppa::PT_PARISC_ARCHEXT:   output = "PARISC_ARCHEXT"; break;
	      case elf_hppa::PT_PARISC_UNWIND:    output = "PARISC_UNWIND"; break;
	      default: break;
	      }

	    trace::io_detail ( "Exiting Elf_Program_Header::get_parisc_segment_type" );

	    return output;
	  }

	  std::string
	  elf_program_header_utils::get_ia64_segment_type ( boost::uint32_t type_value )
	  {
	    trace::io_detail ( "entering elf_program_header::get_ia64_segment_type" );

	    std::string output;

	    switch ( type_value )
	      {
	      case elf_ia64::PT_IA_64_ARCHEXT:      output = "IA_64_ARCHEXT"; break;
	      case elf_ia64::PT_IA_64_UNWIND:   output = "IA_64_UNWIND"; break;
	      case elf_hppa::PT_HP_TLS:         output = "HP_TLS"; break;
	      case elf_ia64::PT_IA_64_HP_OPT_ANOT: output = "HP_OPT_ANNOT"; break;
	      case elf_ia64::PT_IA_64_HP_HSL_ANOT: output = "HP_HSL_ANNOT"; break;
	      case elf_ia64::PT_IA_64_HP_STACK:     output = "HP_STACK"; break;
	      default:
		break;
	      }

	    trace::io_detail ( "exiting elf_program_header::get_ia64_segment_type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

