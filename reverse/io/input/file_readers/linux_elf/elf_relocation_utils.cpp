/*  Elf_Relocation_T.cpp

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

#include <reverse/io/input/file_readers/linux_elf/elf_relocation_utils.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_arm.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_avr.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_m32r.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ix86.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_m68hc11.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_m68k.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_i960.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_v850.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_d10v.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_d30v.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_dlx.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_sh.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mn10300.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mn10200.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_fr30.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_frv.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_arc.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mcore.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mips.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ia64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_vax.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mmix.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_msp430.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ppc64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_alpha.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_h8.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_cris.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_i860.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_x86_64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_i370.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_or32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_s390.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_sparc.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ppc.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_hppa.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_pj.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_xstormy16.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ip2k.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_iq2000.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_xtensa.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_relocation_utils::get_section_type_name ( boost::uint16_t machine_value,
							boost::uint8_t reloc_type,
							boost::uint8_t bitsize  )
	  {
	    trace::io_detail ( "Entering Elf_Relocation::get_Section_Type_Name" );

            std::string output;

            switch ( machine_value )
	      {
	      default:
		output = "";
		break;


	      case elf_common::EM_M32R:
	      case elf_common::EM_CYGNUS_M32R:
		output = elf_m32r::get_type ( reloc_type );
		break;

	      case elf_common::EM_386:
	      case elf_common::EM_486:
		output = elf_ix86::get_type ( reloc_type );
		break;

	      case elf_common::EM_68HC11:
	      case elf_common::EM_68HC12:
		output = elf_m68hc11::get_type ( reloc_type );
		break;

	      case elf_common::EM_68K:
		output = elf_m68k::get_type ( reloc_type );
		break;

	      case elf_common::EM_960:
		output = elf_i960::get_type ( reloc_type );
		break;

	      case elf_common::EM_AVR:
	      case elf_common::EM_AVR_OLD:
		output = elf_avr::get_type ( reloc_type );
		break;

	      case elf_common::EM_OLD_SPARCV9:
	      case elf_common::EM_SPARC32PLUS:
	      case elf_common::EM_SPARCV9:
	      case elf_common::EM_SPARC:
		output = elf_sparc::get_type ( reloc_type );
		break;

	      case elf_common::EM_V850:
	      case elf_common::EM_CYGNUS_V850:
		output = elf_v850::get_type ( reloc_type );
		break;

	      case elf_common::EM_D10V:
	      case elf_common::EM_CYGNUS_D10V:
		output = elf_d10v::get_type ( reloc_type );
		break;

	      case elf_common::EM_D30V:
	      case elf_common::EM_CYGNUS_D30V:
		output = elf_d30v::get_type ( reloc_type );
		break;

	      case elf_common::EM_DLX:
		output = elf_dlx::get_type ( reloc_type );
		break;

	      case elf_common::EM_SH:
		output = elf_sh::get_type ( reloc_type );
		break;

	      case elf_common::EM_MN10300:
	      case elf_common::EM_CYGNUS_MN10300:
		output = elf_mn10300::get_type ( reloc_type );
		break;

	      case elf_common::EM_MN10200:
	      case elf_common::EM_CYGNUS_MN10200:
		output = elf_mn10200::get_type ( reloc_type );
		break;

	      case elf_common::EM_FR30:
	      case elf_common::EM_CYGNUS_FR30:
		output = elf_fr30::get_type ( reloc_type );
		break;

	      case elf_common::EM_CYGNUS_FRV:
		output = elf_frv::get_type ( reloc_type );
		break;

	      case elf_common::EM_MCORE:
		output = elf_mcore::get_type ( reloc_type );
		break;

	      case elf_common::EM_MMIX:
		output = elf_mmix::get_type ( reloc_type );
		break;

	      case elf_common::EM_MSP430:
	      case elf_common::EM_MSP430_OLD:
		output = elf_msp430::get_type ( reloc_type );
		break;

	      case elf_common::EM_PPC:
		output = elf_ppc::get_type ( reloc_type );
		break;

	      case elf_common::EM_PPC64:
		output = elf_ppc64::get_type ( reloc_type );
		break;

	      case elf_common::EM_MIPS:
	      case elf_common::EM_MIPS_RS3_LE:
		if ( bitsize == 32 )
		  {
		    output = elf_mips::get_type ( reloc_type );
		  }
		else
		  {
		    output = elf_mips::get_type ( elf_mips::elf64_mips_r_type ( reloc_type ) );

		    output = elf_mips::get_type ( elf_mips::elf64_mips_r_type2 ( reloc_type ) );

		    output = elf_mips::get_type ( elf_mips::elf64_mips_r_type3 ( reloc_type ) );
		  }
		break;

	      case elf_common::EM_ALPHA:
		output = elf_alpha::get_type ( reloc_type );
		break;

	      case elf_common::EM_ARM:
		output = elf_arm::get_type ( reloc_type );
		break;

	      case elf_common::EM_ARC:
		output = elf_arc::get_type ( reloc_type );
		break;

	      case elf_common::EM_PARISC:
		output = elf_hppa::get_type ( reloc_type );
		break;

	      case elf_common::EM_H8_300:
	      case elf_common::EM_H8_300H:
	      case elf_common::EM_H8S:
		output = elf_h8::get_type ( reloc_type );
		break;

	      case elf_common::EM_OPENRISC:
	      case elf_common::EM_OR32:
		output = elf_or32::get_type ( reloc_type );
		break;

	      case elf_common::EM_PJ:
	      case elf_common::EM_PJ_OLD:
		output = elf_pj::get_type ( reloc_type );
		break;
	      case elf_common::EM_IA_64:
		output = elf_ia64::get_type ( reloc_type );
		break;

	      case elf_common::EM_CRIS:
		output = elf_cris::get_type ( reloc_type );
		break;

	      case elf_common::EM_860:
		output = elf_i860::get_type ( reloc_type );
		break;

	      case elf_common::EM_X86_64:
		output = elf_x86_64::get_type ( reloc_type );
		break;

	      case elf_common::EM_S370:
		output = elf_i370::get_type ( reloc_type );
		break;

	      case elf_common::EM_S390_OLD:
	      case elf_common::EM_S390:
		output = elf_s390::get_type ( reloc_type );
		break;

	      case elf_common::EM_XSTORMY16:
		output = elf_xstormy16::get_type ( reloc_type );
		break;

	      case elf_common::EM_VAX:
		output = elf_vax::get_type ( reloc_type );
		break;

	      case elf_common::EM_IP2K:
	      case elf_common::EM_IP2K_OLD:
		output = elf_ip2k::get_type ( reloc_type );
		break;

	      case elf_common::EM_IQ2000:
		output = elf_iq2000::get_type ( reloc_type );
		break;

	      case elf_common::EM_XTENSA_OLD:
	      case elf_common::EM_XTENSA:
		output = elf_xtensa::get_type ( reloc_type );
		break;
	      }

	    trace::io_detail ( "Exiting Elf_Relocation::get_Section_Type_Name" );

            return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
