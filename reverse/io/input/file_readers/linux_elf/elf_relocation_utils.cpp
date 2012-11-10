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

#include "Elf_Relocation_Utils.h"
#include "Elf_arm.h"
#include "Elf_avr.h"
#include "Elf_m32r.h"
#include "Elf_ix86.h"
#include "Elf_m68hc11.h"
#include "Elf_m68k.h"
#include "Elf_i960.h"
#include "Elf_v850.h"
#include "Elf_d10v.h"
#include "Elf_d30v.h"
#include "Elf_dlx.h"
#include "Elf_sh.h"
#include "Elf_mn10300.h"
#include "Elf_mn10200.h"
#include "Elf_fr30.h"
#include "Elf_frv.h"
#include "Elf_arc.h"
#include "Elf_mcore.h"
#include "Elf_mips.h"
#include "Elf_ia64.h"
#include "Elf_vax.h"
#include "Elf_mmix.h"
#include "Elf_msp430.h"
#include "Elf_ppc64.h"
#include "Elf_alpha.h"
#include "Elf_h8.h"
#include "Elf_cris.h"
#include "Elf_i860.h"
#include "Elf_x86_64.h"
#include "Elf_i370.h"
#include "Elf_or32.h"
#include "Elf_s390.h"
#include "Elf_sparc.h"
#include "Elf_ppc.h"
#include "Elf_hppa.h"
#include "Elf_pj.h"
#include "Elf_xstormy16.h"
#include "Elf_ip2k.h"
#include "Elf_iq2000.h"
#include "Elf_xtensa.h"

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
        Elf_Relocation_Utils::get_Section_Type_Name ( boost::uint16_t machine_value,
						      boost::uint8_t reloc_type,
						      boost::uint8_t bitsize  )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Elf_Relocation::get_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


            std::stringstream result;

            switch ( machine_value )
            {
                default:
                    result << "";
                    break;


                case Elf_Common::EM_M32R:
                case Elf_Common::EM_CYGNUS_M32R:
                    result << Elf_m32r::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_386:
                case Elf_Common::EM_486:
                    result << Elf_ix86::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_68HC11:
                case Elf_Common::EM_68HC12:
                    result << Elf_m68hc11::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_68K:
                    result << Elf_m68k::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_960:
                    result << Elf_i960::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_AVR:
                case Elf_Common::EM_AVR_OLD:
                    result << Elf_avr::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_OLD_SPARCV9:
                case Elf_Common::EM_SPARC32PLUS:
                case Elf_Common::EM_SPARCV9:
                case Elf_Common::EM_SPARC:
                    result << Elf_sparc::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_V850:
                case Elf_Common::EM_CYGNUS_V850:
                    result << Elf_v850::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_D10V:
                case Elf_Common::EM_CYGNUS_D10V:
                    result << Elf_d10v::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_D30V:
                case Elf_Common::EM_CYGNUS_D30V:
                    result << Elf_d30v::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_DLX:
                    result << Elf_dlx::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_SH:
                    result << Elf_sh::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_MN10300:
                case Elf_Common::EM_CYGNUS_MN10300:
                    result << Elf_mn10300::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_MN10200:
                case Elf_Common::EM_CYGNUS_MN10200:
                    result << Elf_mn10200::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_FR30:
                case Elf_Common::EM_CYGNUS_FR30:
                    result << Elf_fr30::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_CYGNUS_FRV:
                    result << Elf_frv::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_MCORE:
                    result << Elf_mcore::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_MMIX:
                    result << Elf_mmix::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_MSP430:
                case Elf_Common::EM_MSP430_OLD:
                    result << Elf_msp430::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_PPC:
                    result << Elf_ppc::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_PPC64:
                    result << Elf_ppc64::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_MIPS:
                case Elf_Common::EM_MIPS_RS3_LE:
                    if ( bitsize == 32 )
                    {
                        result << Elf_mips::get_Type ( reloc_type );
                    }
                    else
                    {
                        result << Elf_mips::get_Type ( Elf_mips::ELF64_MIPS_R_TYPE ( reloc_type ) );

                        result << Elf_mips::get_Type ( Elf_mips::ELF64_MIPS_R_TYPE2 ( reloc_type ) );

                        result << Elf_mips::get_Type ( Elf_mips::ELF64_MIPS_R_TYPE3 ( reloc_type ) );
                    }
                    break;

                case Elf_Common::EM_ALPHA:
                    result << Elf_alpha::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_ARM:
                    result << Elf_arm::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_ARC:
                    result << Elf_arc::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_PARISC:
                    result << Elf_hppa::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_H8_300:
                case Elf_Common::EM_H8_300H:
                case Elf_Common::EM_H8S:
                    result << Elf_h8::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_OPENRISC:
                case Elf_Common::EM_OR32:
                    result << Elf_or32::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_PJ:
                case Elf_Common::EM_PJ_OLD:
                    result << Elf_pj::get_Type ( reloc_type );
                    break;
                case Elf_Common::EM_IA_64:
                    result << Elf_ia64::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_CRIS:
                    result << Elf_cris::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_860:
                    result << Elf_i860::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_X86_64:
                    result << Elf_x86_64::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_S370:
                    result << Elf_i370::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_S390_OLD:
                case Elf_Common::EM_S390:
                    result << Elf_s390::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_XSTORMY16:
                    result << Elf_xstormy16::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_VAX:
                    result << Elf_vax::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_IP2K:
                case Elf_Common::EM_IP2K_OLD:
                    result << Elf_ip2k::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_IQ2000:
                    result << Elf_iq2000::get_Type ( reloc_type );
                    break;

                case Elf_Common::EM_XTENSA_OLD:
                case Elf_Common::EM_XTENSA:
                    result << Elf_xtensa::get_Type ( reloc_type );
                    break;
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Elf_Relocation::get_Section_Type_Name" );
#endif /* LIBREVERSE_DEBUG */


            return result.str();
        }

    } /* namespace elf_module */
} /* namespace libreverse */
