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

#include "Elf_Program_Header_Utils.h"
#include "Elf_Common.h"
#include "Elf_mips.h"
#include "Elf_hppa.h"
#include "Elf_ia64.h"

#include "io/Byte_Converter.h"

#include <boost/format.hpp>
#include <sstream>

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
    Elf_Program_Header_Utils::get_segment_type ( boost::uint32_t type_value,
						 boost::uint16_t machine_arch )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Program_Header::get_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream result;

      switch ( type_value )
	{
	case Elf_Common::PT_NULL:           result << "NULL"; break;
	case Elf_Common::PT_LOAD:           result << "LOAD"; break;
	case Elf_Common::PT_DYNAMIC:      result << "DYNAMIC"; break;
	case Elf_Common::PT_INTERP: result << "INTERP"; break;
	case Elf_Common::PT_NOTE:           result << "NOTE"; break;
	case Elf_Common::PT_SHLIB:  result << "SHLIB"; break;
	case Elf_Common::PT_PHDR:           result << "PHDR"; break;
	case Elf_Common::PT_TLS:            result << "TLS"; break;
	case Elf_Common::PT_GNU_EH_FRAME: result << "GNU_EH_FRAME"; break;
	case Elf_Common::PT_GNU_STACK:    result << "STACK"; break;
	case Elf_Common::PT_GNU_RELRO:    result << "RELRO"; break;
	case Elf_Common::PT_PAX_FLAGS:    result << "PAX_FLAGS"; break;
	case Elf_Common::PT_SUNWBSS:      result << "SUNWBSS"; break;
	case Elf_Common::PT_SUNWSTACK:    result << "SUNWSTACK"; break;

	default:
	  if ( ( type_value >= Elf_Common::PT_LOPROC ) && ( type_value <= Elf_Common::PT_HIPROC ) )
	    {
	      std::string type;
	      switch ( machine_arch )
		{
		case Elf_Common::EM_MIPS:
		case Elf_Common::EM_MIPS_RS3_LE:
		  {
		    type = Elf_Program_Header_Utils::get_mips_segment_type ( type_value );
		    break;
		  }
		case Elf_Common::EM_PARISC:
		  {
		    type = Elf_Program_Header_Utils::get_parisc_segment_type ( type_value );
		    break;
		  }
		case Elf_Common::EM_IA_64:
		  {
		    type = Elf_Program_Header_Utils::get_ia64_segment_type ( type_value );
		    break;
		  }
		default:
		  break;
		}

	      if ( ! type.empty() )
		{
		  result << type;
		}
	      else
		{
		  result << boost::format ( "LOPROC+%1%" ) % ( type_value - Elf_Common::PT_LOPROC );
		}
	    }
	  else if ( ( type_value >= Elf_Common::PT_LOOS ) && ( type_value <= Elf_Common::PT_HIOS ) )
	    {
	      std::string type;

	      switch ( machine_arch )
		{
		case Elf_Common::EM_PARISC:
		  type = Elf_Program_Header_Utils::get_parisc_segment_type ( type_value );
		  break;
		case Elf_Common::EM_IA_64:
		  type = Elf_Program_Header_Utils::get_ia64_segment_type ( type_value );
		  break;
		default:
		  break;
		}

	      if ( ! type.empty() )
		{
		  result << type;
		}
	      else
		{
		  result << boost::format ( "LOOS+%1%" ) % ( type_value - Elf_Common::PT_LOOS );
		}
	    }
	  else
	    {
	      result << boost::format ( "<unknown>: %1%" ) % type_value;
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Program_Header::get_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      return result.str();
    }

    std::string
    Elf_Program_Header_Utils::get_mips_segment_type ( boost::uint32_t type_value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Program_Header::get_mips_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      switch ( type_value )
	{
	case Elf_mips::PT_MIPS_REGINFO: output << "REGINFO"; break;
	case Elf_mips::PT_MIPS_RTPROC:  output << "RTPROC"; break;
	case Elf_mips::PT_MIPS_OPTIONS: output << "OPTIONS"; break;
	default: break;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Program_Header::get_mips_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Program_Header_Utils::get_parisc_segment_type ( boost::uint32_t type_value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Program_Header::get_parisc_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      switch ( type_value )
	{
	case Elf_hppa::PT_HP_TLS:       output << "HP_TLS"; break;
	case Elf_hppa::PT_HP_CORE_NONE:     output << "HP_CORE_NONE"; break;
	case Elf_hppa::PT_HP_CORE_VERSION:  output << "HP_CORE_VERSION"; break;
	case Elf_hppa::PT_HP_CORE_KERNEL:   output << "HP_CORE_KERNEL"; break;
	case Elf_hppa::PT_HP_CORE_COMM:     output << "HP_CORE_COMM"; break;
	case Elf_hppa::PT_HP_CORE_PROC:     output << "HP_CORE_PROC"; break;
	case Elf_hppa::PT_HP_CORE_LOADABLE: output << "HP_CORE_LOADABLE"; break;
	case Elf_hppa::PT_HP_CORE_STACK:    output << "HP_CORE_STACK"; break;
	case Elf_hppa::PT_HP_CORE_SHM:      output << "HP_CORE_SHM"; break;
	case Elf_hppa::PT_HP_CORE_MMF:      output << "HP_CORE_MMF"; break;
	case Elf_hppa::PT_HP_PARALLEL:      output << "HP_PARALLEL"; break;
	case Elf_hppa::PT_HP_FASTBIND:      output << "HP_FASTBIND"; break;
	case Elf_hppa::PT_PARISC_ARCHEXT:   output << "PARISC_ARCHEXT"; break;
	case Elf_hppa::PT_PARISC_UNWIND:    output << "PARISC_UNWIND"; break;
	default: break;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Program_Header::get_parisc_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Program_Header_Utils::get_ia64_segment_type ( boost::uint32_t type_value )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Program_Header::get_ia64_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      std::stringstream output;

      switch ( type_value )
	{
	case Elf_ia64::PT_IA_64_ARCHEXT:      output << "IA_64_ARCHEXT"; break;
	case Elf_ia64::PT_IA_64_UNWIND:   output << "IA_64_UNWIND"; break;
	case Elf_hppa::PT_HP_TLS:         output << "HP_TLS"; break;
	case Elf_ia64::PT_IA_64_HP_OPT_ANOT: output << "HP_OPT_ANNOT"; break;
	case Elf_ia64::PT_IA_64_HP_HSL_ANOT: output << "HP_HSL_ANNOT"; break;
	case Elf_ia64::PT_IA_64_HP_STACK:     output << "HP_STACK"; break;
	default:
	  break;
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Program_Header::get_ia64_segment_type" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

  } /* namespace elf_module */
} /* namespace libreverse */
