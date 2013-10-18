
/*  Elf_File_Header_Utils.cpp

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

#include <reverse/errors/file_reader_exception.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_file_header_utils.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_hppa.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_mips.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_sparc.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ia64.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_m32r.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_m68k.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_ppc.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_v850.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_pj.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_arm.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_vax.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_file_header_utils::get_file_type_name ( boost::uint16_t e_type )
	  {

	    trace::io_detail ( "Entering Elf_File_Header_Utils::get_File_Type_Name" );

            std::stringstream result;

            switch ( e_type )
	      {
	      case Elf_Common::ET_NONE:
		result << "NONE (None)";
		break;
	      case Elf_Common::ET_REL:
		result << "REL (Relocatable file)";
		break;
	      case Elf_Common::ET_EXEC:
		result << "EXEC (Executable file)";
		break;
	      case Elf_Common::ET_DYN:
		result << "DYN (Shared object file)";
		break;
	      case Elf_Common::ET_CORE:
		result << "CORE (Core file)";
		break;
	      default:
		/* Old check test for ET_HIPROC as well. The problem with this
		 * is that the limit of a boost::uint16_t is the value 0xFFFF. This
		 * was the value of ET_HIPROC. So the test for the high limit
		 * was always true.
		 */
		if ( e_type >= Elf_Common::ET_LOPROC )
		  {
		    result << boost::format ( "Processor Specific: (%1%)" ) % e_type;
		  }
		else if ( ( e_type >= Elf_Common::ET_LOOS ) &&
			  ( e_type <= Elf_Common::ET_HIOS ) )
		  {
		    result << boost::format ( "OS Specific: (%1%)" ) % e_type;
		  }
		else
		  {
		    result << boost::format ( "<unknown>: %1%" ) % e_type;
		  }
	      }

	    trace::io_detail ( "Exiting Elf_File_Header_Utils::get_File_Type_Name" );

            return result.str();
	  }

	  std::string
	  Elf_File_Header_Utils::get_File_Type_Meta ( boost::uint16_t e_type )
	  {

	    trace::io_detail ( "Entering Elf_File_Header_Utils::get_File_Type_Meta" );

            std::string result = "";

            switch ( e_type )
	      {
	      case Elf_Common::ET_NONE:
		result = "elf:none";
		break;
	      case Elf_Common::ET_REL:
		result = "elf:relocatable_object";
		break;
	      case Elf_Common::ET_EXEC:
		result = "elf:executable";
		break;
	      case Elf_Common::ET_DYN:
		result = "elf:dynamically_linked_library";
		break;
	      case Elf_Common::ET_CORE:
		result = "elf:core_file";
		break;
	      default:
		result = "elf:unknown";
	      }

	    trace::io_detail ( "Exiting Elf_File_Header_Utils::get_File_Type_Meta" );

            return result;
	  }

	  std::string
	  Elf_File_Header_Utils::get_Arch_Name ( boost::uint16_t e_machine )
	  {

	    trace::io_detail ( "Entering Elf_File_Header_Utils::get_Arch_Name" );

            std::string value = "";

            switch ( e_machine )
	      {
	      case Elf_Common::EM_SPARC:
		{
		  value = "sun:sparc_v";
		  break;
		}
	      case Elf_Common::EM_386:
		{
		  value = "intel:i386";
		  break;
                }
	      default:
                {

		  trace::io_error ( "The architecture for the file was %1%",
				    Elf_File_Header_Utils::get_Machine_Name ( e_machine ) );

		  throw errors::file_reader_exception ( errors::file_reader_exception::unsupported_arch_type );
                }
	      }

	    trace::io_detail ( "Exiting Elf_File_Header_Utils::get_Arch_Name" );

            return value;
	  }

	  std::string
	  Elf_File_Header_Utils::get_Machine_Name ( boost::uint16_t e_machine )
	  {

	    trace::io_detail ( "Entering Elf_File_Header_Utils::get_Machine_Name" );

            std::stringstream result;

            switch ( e_machine )
	      {
	      case Elf_Common::EM_NONE:
		result << "None";
		break;
	      case Elf_Common::EM_M32:
		result << "WE32100";
		break;
	      case Elf_Common::EM_SPARC:
		result << "Sparc";
		break;
	      case Elf_Common::EM_386:
		result << "Intel 80386";
		break;
	      case Elf_Common::EM_68K:
		result << "MC68000";
		break;
	      case Elf_Common::EM_88K:
		result << "MC88000";
		break;
	      case Elf_Common::EM_486:
		result << "Intel 80486";
		break;
	      case Elf_Common::EM_860:
		result << "Intel 80860";
		break;
	      case Elf_Common::EM_MIPS:
		result << "MIPS R3000";
		break;
	      case Elf_Common::EM_S370:
		result << "IBM System/370";
		break;
	      case Elf_Common::EM_MIPS_RS3_LE:
		result << "MIPS R4000 big-endian";
		break;
	      case Elf_Common::EM_OLD_SPARCV9:
		result << "Sparc v9 (old)";
		break;
	      case Elf_Common::EM_PARISC:
		result << "HPPA";
		break;
	      case Elf_Common::EM_PPC_OLD:
		result << "Power PC (old)";
		break;
	      case Elf_Common::EM_SPARC32PLUS:
		result << "Sparc v8+" ;
		break;
	      case Elf_Common::EM_960:
		result << "Intel 90860";
		break;
	      case Elf_Common::EM_PPC:
		result << "PowerPC";
		break;
	      case Elf_Common::EM_PPC64:
		result << "PowerPC64";
		break;
	      case Elf_Common::EM_V800:
		result << "NEC V800";
		break;
	      case Elf_Common::EM_FR20:
		result << "Fujitsu FR20";
		break;
	      case Elf_Common::EM_RH32:
		result << "TRW RH32";
		break;
	      case Elf_Common::EM_MCORE:
		result << "MCORE";
		break;
	      case Elf_Common::EM_ARM:
		result << "ARM";
		break;
	      case Elf_Common::EM_OLD_ALPHA:
		result << "Digital Alpha (old)";
		break;
	      case Elf_Common::EM_SH:
		result << "Renesas / SuperH SH";
		break;
	      case Elf_Common::EM_SPARCV9:
		result << "Sparc v9";
		break;
	      case Elf_Common::EM_TRICORE:
		result << "Siemens Tricore";
		break;
	      case Elf_Common::EM_ARC:
		result << "ARC";
		break;
	      case Elf_Common::EM_H8_300:
		result << "Renesas H8/300";
		break;
	      case Elf_Common::EM_H8_300H:
		result << "Renesas H8/300H";
		break;
	      case Elf_Common::EM_H8S:
		result << "Renesas H8S";
		break;
	      case Elf_Common::EM_H8_500:
		result << "Renesas H8/500";
		break;
	      case Elf_Common::EM_IA_64:
		result << "Intel IA-64";
		break;
	      case Elf_Common::EM_MIPS_X:
		result << "Stanford MIPS-X";
		break;
	      case Elf_Common::EM_COLDFIRE:
		result << "Motorola Coldfire";
		break;
	      case Elf_Common::EM_68HC12:
		result << "Motorola M68HC12";
		break;
	      case Elf_Common::EM_ALPHA:
		result << "Alpha";
		break;
	      case Elf_Common::EM_CYGNUS_D10V:
	      case Elf_Common::EM_D10V:
		result << "d10v";
		break;
	      case Elf_Common::EM_CYGNUS_D30V:
	      case Elf_Common::EM_D30V:
		result << "d30v";
		break;
	      case Elf_Common::EM_CYGNUS_M32R:
	      case Elf_Common::EM_M32R:
		result << "Renesas M32R (formerly Mitsubishi M32r)";
		break;
	      case Elf_Common::EM_CYGNUS_V850:
	      case Elf_Common::EM_V850:
		result << "NEC v850";
		break;
	      case Elf_Common::EM_CYGNUS_MN10300:
	      case Elf_Common::EM_MN10300:
		result << "mn10300";
		break;
	      case Elf_Common::EM_CYGNUS_MN10200:
	      case Elf_Common::EM_MN10200:
		result << "mn10200";
		break;
	      case Elf_Common::EM_CYGNUS_FR30:
	      case Elf_Common::EM_FR30:
		result << "Fujitsu FR30";
		break;
	      case Elf_Common::EM_CYGNUS_FRV:
		result << "Fujitsu FR-V";
		break;
	      case Elf_Common::EM_PJ_OLD:
	      case Elf_Common::EM_PJ:
		result << "picoJava";
		break;
	      case Elf_Common::EM_MMA:
		result << "Fujitsu Multimedia Accelerator";
		break;
	      case Elf_Common::EM_PCP:
		result << "Siemens PCP";
		break;
	      case Elf_Common::EM_NCPU:
		result << "Sony nCPU embedded RISC processor";
		break;
	      case Elf_Common::EM_NDR1:
		result << "Denso NDR1 microprocesspr";
		break;
	      case Elf_Common::EM_STARCORE:
		result << "Motorola Star*Core processor";
		break;
	      case Elf_Common::EM_ME16:
		result << "Toyota ME16 processor";
		break;
	      case Elf_Common::EM_ST100:
		result << "STMicroelectronics ST100 processor";
		break;
	      case Elf_Common::EM_TINYJ:
		result << "Advanced Logic Corp. TinyJ embedded processor";
		break;
	      case Elf_Common::EM_FX66:
		result << "Siemens FX66 microcontroller";
		break;
	      case Elf_Common::EM_ST9PLUS:
		result << "STMicroelectronics ST9+ 8/16 bit microcontroller";
		break;
	      case Elf_Common::EM_ST7:
		result << "STMicroelectronics ST7 8-bit microcontroller";
		break;
	      case Elf_Common::EM_68HC16:
		result << "Motorola MC68HC16 Microcontroller";
		break;
	      case Elf_Common::EM_68HC11:
		result << "Motorola MC68HC11 Microcontroller";
		break;
	      case Elf_Common::EM_68HC08:
		result << "Motorola MC68HC08 Microcontroller";
		break;
	      case Elf_Common::EM_68HC05:
		result << "Motorola MC68HC05 Microcontroller";
		break;
	      case Elf_Common::EM_SVX:
		result << "Silicon Graphics SVx";
		break;
	      case Elf_Common::EM_ST19:
		result << "STMicroelectronics ST19 8-bit microcontroller";
		break;
	      case Elf_Common::EM_VAX:
		result << "Digital VAX";
		break;
	      case Elf_Common::EM_AVR_OLD:
	      case Elf_Common::EM_AVR:
		result << "Atmel AVR 8-bit microcontroller";
		break;
	      case Elf_Common::EM_CRIS:
		result << "Axis Communications 32-bit embedded processor";
		break;
	      case Elf_Common::EM_JAVELIN:
		result << "Infineon Technologies 32-bit embedded cpu";
		break;
	      case Elf_Common::EM_FIREPATH:
		result << "Element 14 64-bit DSP processor";
		break;
	      case Elf_Common::EM_ZSP:
		result << "LSI Logic's 16-bit DSP processor";
		break;
	      case Elf_Common::EM_MMIX:
		result << "Donald Knuth's educational 64-bit processor";
		break;
	      case Elf_Common::EM_HUANY:
		result << "Harvard Universitys's machine-independent object format";
		break;
	      case Elf_Common::EM_PRISM:
		result << "Vitesse Prism";
		break;
	      case Elf_Common::EM_X86_64:
		result << "Advanced Micro Devices X86-64";
		break;
	      case Elf_Common::EM_S390_OLD:
	      case Elf_Common::EM_S390:
		result << "IBM S/390";
		break;
	      case Elf_Common::EM_XSTORMY16:
		result << "Sanyo Xstormy16 CPU core";
		break;
	      case Elf_Common::EM_OPENRISC:
	      case Elf_Common::EM_OR32:
		result << "OpenRISC";
		break;
	      case Elf_Common::EM_DLX:
		result << "OpenDLX";
		break;
	      case Elf_Common::EM_IP2K_OLD:
	      case Elf_Common::EM_IP2K:
		result << "Ubicom IP2xxx 8-bit microcontrollers";
		break;
	      case Elf_Common::EM_IQ2000:
		result << "Vitesse IQ2000";
		break;
	      case Elf_Common::EM_XTENSA_OLD:
	      case Elf_Common::EM_XTENSA:
		result << "Tensilica Xtensa Processor";
		break;
	      default:
		result << boost::format ( "<unknown>: %1%" ) % e_machine;
	      }

	    trace::io_detail ( "Exiting Elf_File_Header_Utils::get_Machine_Name" );

            return result.str();
	  }

	  std::string
	  Elf_File_Header_Utils::decode_ARM_Machine_Flags ( boost::uint32_t e_flags )
	  {

	    trace::io_detail ( "Entering Elf_File_Header_Utils::decode_ARM_Machine_Flags" );

            std::stringstream result;
            boost::uint32_t eabi;
            bool unknown_abi = false;

            eabi = Elf_arm::EF_ARM_EABI_VERSION ( e_flags );
            e_flags &= ~ Elf_arm::EF_ARM_EABIMASK;

            /* Handle "generic" ARM flags.  */
            if ( e_flags & Elf_arm::EF_ARM_RELEXEC )
	      {
                result <<", relocatable executable";
                e_flags &= ~ Elf_arm::EF_ARM_RELEXEC;
	      }

            if ( e_flags & Elf_arm::EF_ARM_HASENTRY )
	      {
                result << ", has entry point";
                e_flags &= ~ Elf_arm::EF_ARM_HASENTRY;
	      }

            /* Now handle EABI specific flags.  */
            switch ( eabi )
	      {
	      default:
                {
		  result << ", <unrecognized EABI>";
		  if ( e_flags )
                    {
		      unknown_abi = true;
                    }
		  break;
                }
	      case Elf_arm::EF_ARM_EABI_VER1:
                {
		  result << ", Version1 EABI";

		  if ( e_flags & Elf_arm::EF_ARM_SYMSARESORTED )
                    {
		      result << ", sorted symbol tables";
                    }
		  else
                    {
		      unknown_abi = true;
                    }

		  break;
                }
	      case Elf_arm::EF_ARM_EABI_VER2:
                {
		  result << ", Version2 EABI";

		  /* Conflicts with EF_ARM_INTERWORK.  */
		  if ( e_flags & Elf_arm::EF_ARM_SYMSARESORTED )
                    {
		      result << ", sorted symbol tables";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_DYNSYMSUSESEGIDX )
                    {
		      result << ", dynamic symbols use segment index";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_MAPSYMSFIRST )
                    {
		      result << ", mapping symbols precede others";
                    }
		  if ( e_flags & ~ ( Elf_arm::EF_ARM_SYMSARESORTED |
				     Elf_arm::EF_ARM_DYNSYMSUSESEGIDX |
				     Elf_arm::EF_ARM_MAPSYMSFIRST ) )
                    {
		      unknown_abi = true;
                    }

		  break;
                }
	      case Elf_arm::EF_ARM_EABI_UNKNOWN:
                {
		  result << ", GNU EABI";

		  if ( e_flags & Elf_arm::EF_ARM_INTERWORK )
                    {
		      result << ", interworking enabled";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_APCS_26 )
                    {
		      result << ", uses APCS/26";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_APCS_FLOAT )
                    {
		      result << ", uses APCS/float";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_PIC )
                    {
		      result << ", position independent";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_ALIGN8 )
                    {
		      result << ", 8 bit structure alignment";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_NEW_ABI )
                    {
		      result << ", uses new ABI";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_OLD_ABI )
                    {
		      result << ", uses old ABI";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_SOFT_FLOAT )
                    {
		      result << ", software FP";
                    }
		  if ( e_flags & Elf_arm::EF_ARM_MAVERICK_FLOAT )
                    {
		      result << ", Maverick FP";
                    }


		  if ( e_flags & ~ ( Elf_arm::EF_ARM_INTERWORK |
				     Elf_arm::EF_ARM_APCS_26 |
				     Elf_arm::EF_ARM_APCS_FLOAT |
				     Elf_arm::EF_ARM_PIC |
				     Elf_arm::EF_ARM_ALIGN8 |
				     Elf_arm::EF_ARM_NEW_ABI |
				     Elf_arm::EF_ARM_OLD_ABI |
				     Elf_arm::EF_ARM_SOFT_FLOAT |
				     Elf_arm::EF_ARM_MAVERICK_FLOAT ) )
                    {
		      unknown_abi = true;
                    }
		  break;
                }
	      }

            if ( unknown_abi )
	      {
                result << ", <unknown>";
	      }

	    trace::io_detail ( "Exiting Elf_File_Header_Utils::decode_ARM_Machine_Flags" );

            return result.str();
	  }

	  std::string
	  Elf_File_Header_Utils::get_Machine_Flags ( boost::uint32_t e_flags,
						     boost::uint16_t e_machine )
	  {

	    trace::io_detail ( "Entering Elf_File_Header_Utils::get_Machine_Flags" );

            std::stringstream result;

            if ( e_flags )
	      {
                switch ( e_machine )
		  {
		  default:
		    break;

		  case Elf_Common::EM_ARM:
		    result << decode_ARM_Machine_Flags ( e_flags );
		    break;

		  case Elf_Common::EM_68K:
		    if ( e_flags & Elf_m68k::EF_CPU32 )
		      {
			result << ", cpu32";
		      }

		    if ( e_flags & Elf_m68k::EF_M68000 )
		      {
			result << ", m68000";
		      }
		    break;

		  case Elf_Common::EM_PPC:
		    if ( e_flags & Elf_ppc::EF_PPC_EMB )
		      {
			result << ", emb";
		      }

		    if ( e_flags & Elf_ppc::EF_PPC_RELOCATABLE )
		      {
			result << ", relocatable";
		      }

		    if ( e_flags & Elf_ppc::EF_PPC_RELOCATABLE_LIB )
		      {
			result << ", relocatable-lib";
		      }
		    break;

		  case Elf_Common::EM_V850:
		  case Elf_Common::EM_CYGNUS_V850:
		    switch ( e_flags & Elf_v850::EF_V850_ARCH )
		      {
		      case Elf_v850::E_V850E_ARCH:
			result << ", v850e";
			break;
		      case Elf_v850::E_V850_ARCH:
			result << ", v850";
			break;
		      default:
			result << ", unknown v850 architecture variant";
			break;
		      }
		    break;

		  case Elf_Common::EM_M32R:
		  case Elf_Common::EM_CYGNUS_M32R:
		    if ( ( e_flags & Elf_m32r::EF_M32R_ARCH ) == Elf_m32r::E_M32R_ARCH )
		      result << ", m32r";

		    break;

		  case Elf_Common::EM_MIPS:
		  case Elf_Common::EM_MIPS_RS3_LE:
		    if ( e_flags & Elf_mips::EF_MIPS_NOREORDER )
		      {
			result << ", noreorder";
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_PIC )
		      {
			result << ", pic";
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_CPIC )
		      {
			result << ", cpic";
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_UCODE )
		      {
			result << ", ugen_reserved";
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_ABI2 )
		      {
			result << ", abi2";
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_OPTIONS_FIRST )
		      {
			result << ", odk first";
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_32BITMODE )
		      {
			result << ", 32bitmode";
		      }

		    switch ( ( e_flags & Elf_mips::EF_MIPS_MACH ) )
		      {
		      case Elf_mips::E_MIPS_MACH_3900: result << ", 3900"; break;
		      case Elf_mips::E_MIPS_MACH_4010: result << ", 4010"; break;
		      case Elf_mips::E_MIPS_MACH_4100: result << ", 4100"; break;
		      case Elf_mips::E_MIPS_MACH_4111: result << ", 4111"; break;
		      case Elf_mips::E_MIPS_MACH_4120: result << ", 4120"; break;
		      case Elf_mips::E_MIPS_MACH_4650: result << ", 4650"; break;
		      case Elf_mips::E_MIPS_MACH_5400: result << ", 5400"; break;
		      case Elf_mips::E_MIPS_MACH_5500: result << ", 5500"; break;
		      case Elf_mips::E_MIPS_MACH_SB1:  result << ", sb1";  break;
		      case 0:
			/* We simply ignore the field in this case to avoid confusion:
			   MIPS ELF does not specify Elf_mips::EF_MIPS_MACH, it is a GNU
			   extension.  */
			break;
		      default: result << ", unknown CPU"; break;
		      }

		    switch ( ( e_flags & Elf_mips::EF_MIPS_ABI ) )
		      {
		      case Elf_mips::E_MIPS_ABI_O32: result << ", o32"; break;
		      case Elf_mips::E_MIPS_ABI_O64: result << ", o64"; break;
		      case Elf_mips::E_MIPS_ABI_EABI32: result << ", eabi32"; break;
		      case Elf_mips::E_MIPS_ABI_EABI64: result << ", eabi64"; break;
		      case 0:
			/* We simply ignore the field in this case to avoid confusion:
			   MIPS ELF does not specify Elf_mips::EF_MIPS_ABI, it is a GNU extension.
			   This means it is likely to be an o32 file, but not for
			   sure.  */
			break;
		      default: result << ", unknown ABI"; break;
		      }

		    if ( e_flags & Elf_mips::EF_MIPS_ARCH_ASE_MDMX )
		      result << ", mdmx";

		    if ( e_flags & Elf_mips::EF_MIPS_ARCH_ASE_M16 )
		      result << ", mips16";

		    switch ( ( e_flags & Elf_mips::EF_MIPS_ARCH ) )
		      {
		      case Elf_mips::E_MIPS_ARCH_1: result << ", mips1"; break;
		      case Elf_mips::E_MIPS_ARCH_2: result << ", mips2"; break;
		      case Elf_mips::E_MIPS_ARCH_3: result << ", mips3"; break;
		      case Elf_mips::E_MIPS_ARCH_4: result << ", mips4"; break;
		      case Elf_mips::E_MIPS_ARCH_5: result << ", mips5"; break;
		      case Elf_mips::E_MIPS_ARCH_32: result << ", mips32"; break;
		      case Elf_mips::E_MIPS_ARCH_32R2: result << ", mips32r2"; break;
		      case Elf_mips::E_MIPS_ARCH_64: result << ", mips64"; break;
		      default: result << ", unknown ISA"; break;
		      }

		    break;

		  case Elf_Common::EM_SPARCV9:
		    if ( e_flags & Elf_sparc::EF_SPARC_32PLUS )
		      result << ", v8+";

		    if ( e_flags & Elf_sparc::EF_SPARC_SUN_US1 )
		      result << ", ultrasparcI";

		    if ( e_flags & Elf_sparc::EF_SPARC_SUN_US3 )
		      result << ", ultrasparcIII";

		    if ( e_flags & Elf_sparc::EF_SPARC_HAL_R1 )
		      result << ", halr1";

		    if ( e_flags & Elf_sparc::EF_SPARC_LEDATA )
		      result << ", ledata";

		    if ( ( e_flags & Elf_sparc::EF_SPARCV9_MM ) == Elf_sparc::EF_SPARCV9_TSO )
		      result << ", tso";

		    if ( ( e_flags & Elf_sparc::EF_SPARCV9_MM ) == Elf_sparc::EF_SPARCV9_PSO )
		      result << ", pso";

		    if ( ( e_flags & Elf_sparc::EF_SPARCV9_MM ) == Elf_sparc::EF_SPARCV9_RMO )
		      result << ", rmo";
		    break;

		  case Elf_Common::EM_PARISC:
		    switch ( e_flags & Elf_hppa::EF_PARISC_ARCH )
		      {
		      case Elf_hppa::EFA_PARISC_1_0:
			result << ", PA-RISC 1.0";
			break;
		      case Elf_hppa::EFA_PARISC_1_1:
			result << ", PA-RISC 1.1";
			break;
		      case Elf_hppa::EFA_PARISC_2_0:
			result << ", PA-RISC 2.0";
			break;
		      default:
			break;
		      }
		    if ( e_flags & Elf_hppa::EF_PARISC_TRAPNIL )
		      result << ", trapnil";
		    if ( e_flags & Elf_hppa::EF_PARISC_EXT )
		      result << ", ext";
		    if ( e_flags & Elf_hppa::EF_PARISC_LSB )
		      result << ", lsb";
		    if ( e_flags & Elf_hppa::EF_PARISC_WIDE )
		      result << ", wide";
		    if ( e_flags & Elf_hppa::EF_PARISC_NO_KABP )
		      result << ", no kabp";
		    if ( e_flags & Elf_hppa::EF_PARISC_LAZYSWAP )
		      result << ", lazyswap";
		    break;

		  case Elf_Common::EM_PJ:
		  case Elf_Common::EM_PJ_OLD:
		    if ( ( e_flags & Elf_pj::EF_PICOJAVA_NEWCALLS ) ==
			 Elf_pj::EF_PICOJAVA_NEWCALLS )
		      result << ", new calling convention";

		    if ( ( e_flags & Elf_pj::EF_PICOJAVA_GNUCALLS ) ==
			 Elf_pj::EF_PICOJAVA_GNUCALLS )
		      result << ", gnu calling convention";
		    break;

		  case Elf_Common::EM_IA_64:
		    if ( ( e_flags & Elf_ia64::EF_IA_64_ABI64 ) )
		      result << ", 64-bit";
		    else
		      result << ", 32-bit";
		    if ( ( e_flags & Elf_ia64::EF_IA_64_REDUCEDFP ) )
		      result << ", reduced fp model";
		    if ( ( e_flags & Elf_ia64::EF_IA_64_NOFUNCDESC_CONS_GP ) )
		      result << ", no function descriptors, constant gp";
		    else if ( ( e_flags & Elf_ia64::EF_IA_64_CONS_GP ) )
		      result << ", constant gp";
		    if ( ( e_flags & Elf_ia64::EF_IA_64_ABSOLUTE ) )
		      result << ", absolute";
		    break;

		  case Elf_Common::EM_VAX:
		    if ( ( e_flags & Elf_vax::EF_VAX_NONPIC ) )
		      result << ", non-PIC";
		    if ( ( e_flags & Elf_vax::EF_VAX_DFLOAT ) )
		      result << ", D-Float";
		    if ( ( e_flags & Elf_vax::EF_VAX_GFLOAT ) )
		      result << ", G-Float";
		    break;
		  }
	      }

	    trace::io_detail ( "Exiting Elf_File_Header_Utils::get_Machine_Flags" );

            return result.str();
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

