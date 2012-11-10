#include "Elf_arm.h"

#include <string>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline const boost::uint32_t
    Elf_arm::EF_ARM_EABI_VERSION ( boost::uint32_t flags )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_arc::EF_ARM_EABI_VERSION" );
#endif /* LIBREVERSE_DEBUG */

      return (flags & EF_ARM_EABIMASK);
    }

    inline std::string
    Elf_arm::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_arc::get_Type" );
#endif /* LIBREVERSE_DEBUG */

      std::string output = "";

      switch (type)
	{
	case 0: output = "R_ARM_NONE"; break;
	case 1: output = "R_ARM_PC24"; break;
	case 2: output = "R_ARM_ABS32"; break;
	case 3: output = "R_ARM_REL32"; break;
#ifdef OLD_ARM_ABI
	case 4: output = "R_ARM_ABS8"; break;
	case 5: output = "R_ARM_ABS16"; break;
	case 6: output = "R_ARM_ABS12"; break;
	case 7: output = "R_ARM_THM_ABS5"; break;
	case 8: output = "R_ARM_THM_PC22"; break;
	case 9: output = "R_ARM_SBREL32"; break;
	case 10: output = "R_ARM_AMP_VCALL9"; break;

	  /* Cygnus extension to abi: Thumb unconditional branch.  */
	case 11: output = "R_ARM_THM_PC11"; break;

	  /* Cygnus extension to abi: Thumb conditional branch.  */
	case 12: output = "R_ARM_THM_PC9"; break;
	case 13: output = "R_ARM_GNU_VTINHERIT"; break;
	case 14: output = "R_ARM_GNU_VTENTRY"; break;
#else /* not OLD_ARM_ABI */
	case 4: output = "R_ARM_PC13"; break;
	case 5: output = "R_ARM_ABS16"; break;
	case 6: output = "R_ARM_ABS12"; break;
	case 7: output = "R_ARM_THM_ABS5"; break;
	case 8: output = "R_ARM_ABS8"; break;
	case 9: output = "R_ARM_SBREL32"; break;
	case 10: output = "R_ARM_THM_PC22"; break;
	case 11: output = "R_ARM_THM_PC8"; break;
	case 12: output = "R_ARM_AMP_VCALL9"; break;
	case 13: output = "R_ARM_SWI24"; break;
	case 14: output = "R_ARM_THM_SWI8"; break;
	case 15: output = "R_ARM_XPC25"; break;
	case 16: output = "R_ARM_THM_XPC22"; break;
#endif /* not OLD_ARM_ABI */
	case 20: output = "R_ARM_COPY"; break;   /* Copy symbol at runtime.  */
	case 21: output = "R_ARM_GLOB_DAT"; break;   /* Create GOT entry.  */
	case 22: output = "R_ARM_JUMP_SLOT"; break;   /* Create PLT entry.  */
	case 23: output = "R_ARM_RELATIVE"; break;   /* Adjust by program base.  */
	case 24: output = "R_ARM_GOTOFF"; break;   /* 32 bit offset to GOT.  */

	  /* 32 bit PC relative offset to GOT.  */
	case 25: output = "R_ARM_GOTPC"; break;

	  /* 32 bit GOT entry.  */
	case 26: output = "R_ARM_GOT32"; break;

	  /* 32 bit PLT address.  */
	case 27: output = "R_ARM_PLT32"; break;
#ifdef OLD_ARM_ABI
	case 28: output = "FIRST_INVALID_RELOC"; break;
	case 249: output = "LAST_INVALID_RELOC"; break;
#else /* not OLD_ARM_ABI */
	case 28: output = "FIRST_INVALID_RELOC1"; break;
	case 31: output = "LAST_INVALID_RELOC1"; break;
	case 32: output = "R_ARM_ALU_PCREL7_0"; break;
	case 33: output = "R_ARM_ALU_PCREL15_8"; break;
	case 34: output = "R_ARM_ALU_PCREL23_15"; break;
	case 35: output = "R_ARM_LDR_SBREL11_0"; break;
	case 36: output = "R_ARM_ALU_SBREL19_12"; break;
	case 37: output = "R_ARM_ALU_SBREL27_20"; break;
	case 38: output = "FIRST_INVALID_RELOC2"; break;
	case 39: output = "LAST_INVALID_RELOC2"; break;
	case 100: output = "R_ARM_GNU_VTENTRY"; break;
	case 101: output = "R_ARM_GNU_VTINHERIT"; break;

	  /* Cygnus extension to abi: Thumb unconditional branch.  */
	case 102: output = "R_ARM_THM_PC11"; break;

	  /* Cygnus extension to abi: Thumb conditional branch.  */
	case 103: output = "R_ARM_THM_PC9"; break;
	case 104: output = "FIRST_INVALID_RELOC3"; break;
	case 248: output = "LAST_INVALID_RELOC3"; break;
	case 249: output = "R_ARM_RXPC25"; break;
#endif /* not OLD_ARM_ABI */
	case 250: output = "R_ARM_RSBREL32"; break;
	case 251: output = "R_ARM_THM_RPC22"; break;
	case 252: output = "R_ARM_RREL32"; break;
	case 253: output = "R_ARM_RABS32"; break;
	case 254: output = "R_ARM_RPC24"; break;
	case 255: output = "R_ARM_RBASE"; break;
	default:
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::ERROR,
				 boost::str ( boost::format ( "Unknown arm relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

	    output = "unknown";
	  }
	}

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_arc::get_Type" );
#endif /* LIBREVERSE_DEBUG */

      return output;
    }
  } /* namespace elf_module */
} /* namespace libreverse */
