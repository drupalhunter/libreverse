#include <reverse/io/input/file_readers/linux_elf/elf_sparc.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_sparc::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_sparc::get_Type" );

	    std::string output = "";

	    switch (type)
	      {

                /* Relocation types.  */
	      case 0: output = "R_SPARC_NONE"; break;
	      case 1: output = "R_SPARC_8"; break;
	      case 2: output = "R_SPARC_16"; break;
	      case 3: output = "R_SPARC_32"; break;
	      case 4: output = "R_SPARC_DISP8"; break;
	      case 5: output = "R_SPARC_DISP16"; break;
	      case 6: output = "R_SPARC_DISP32"; break;
	      case 7: output = "R_SPARC_WDISP30"; break;
	      case 8: output = "R_SPARC_WDISP22"; break;
	      case 9: output = "R_SPARC_HI22"; break;
	      case 10: output = "R_SPARC_22"; break;
	      case 11: output = "R_SPARC_13"; break;
	      case 12: output = "R_SPARC_LO10"; break;
	      case 13: output = "R_SPARC_GOT10"; break;
	      case 14: output = "R_SPARC_GOT13"; break;
	      case 15: output = "R_SPARC_GOT22"; break;
	      case 16: output = "R_SPARC_PC10"; break;
	      case 17: output = "R_SPARC_PC22"; break;
	      case 18: output = "R_SPARC_WPLT30"; break;
	      case 19: output = "R_SPARC_COPY"; break;
	      case 20: output = "R_SPARC_GLOB_DAT"; break;
	      case 21: output = "R_SPARC_JMP_SLOT"; break;
	      case 22: output = "R_SPARC_RELATIVE"; break;
	      case 23: output = "R_SPARC_UA32"; break;

                /* ??? These 6 relocs are new but not currently used.  For binary
                   compatibility in the sparc64-elf toolchain, we leave them out.
                   A non-binary upward compatible change is expected for sparc64-elf.  */
#ifndef SPARC64_OLD_RELOCS
                /* ??? New relocs on the UltraSPARC.  Not sure what they're for yet.  */
	      case 24: output = "R_SPARC_PLT32"; break;
	      case 25: output = "R_SPARC_HIPLT22"; break;
	      case 26: output = "R_SPARC_LOPLT10"; break;
	      case 27: output = "R_SPARC_PCPLT32"; break;
	      case 28: output = "R_SPARC_PCPLT22"; break;
	      case 29: output = "R_SPARC_PCPLT10"; break;
#endif

                /* v9 relocs */
	      case 30: output = "R_SPARC_10"; break;
	      case 31: output = "R_SPARC_11"; break;
	      case 32: output = "R_SPARC_64"; break;
	      case 33: output = "R_SPARC_OLO10"; break;
	      case 34: output = "R_SPARC_HH22"; break;
	      case 35: output = "R_SPARC_HM10"; break;
	      case 36: output = "R_SPARC_LM22"; break;
	      case 37: output = "R_SPARC_PC_HH22"; break;
	      case 38: output = "R_SPARC_PC_HM10"; break;
	      case 39: output = "R_SPARC_PC_LM22"; break;
	      case 40: output = "R_SPARC_WDISP16"; break;
	      case 41: output = "R_SPARC_WDISP19"; break;
	      case 42: output = "R_SPARC_UNUSED_42"; break;
	      case 43: output = "R_SPARC_7"; break;
	      case 44: output = "R_SPARC_5"; break;
	      case 45: output = "R_SPARC_6"; break;
	      case 46: output = "R_SPARC_DISP64"; break;
	      case 47: output = "R_SPARC_PLT64"; break;
	      case 48: output = "R_SPARC_HIX22"; break;
	      case 49: output = "R_SPARC_LOX10"; break;
	      case 50: output = "R_SPARC_H44"; break;
	      case 51: output = "R_SPARC_M44"; break;
	      case 52: output = "R_SPARC_L44"; break;
	      case 53: output = "R_SPARC_REGISTER"; break;
	      case 54: output = "R_SPARC_UA64"; break;
	      case 55: output = "R_SPARC_UA16"; break;

	      case 56: output = "R_SPARC_TLS_GD_HI22"; break;
	      case 57: output = "R_SPARC_TLS_GD_LO10"; break;
	      case 58: output = "R_SPARC_TLS_GD_ADD"; break;
	      case 59: output = "R_SPARC_TLS_GD_CALL"; break;
	      case 60: output = "R_SPARC_TLS_LDM_HI22"; break;
	      case 61: output = "R_SPARC_TLS_LDM_LO10"; break;
	      case 62: output = "R_SPARC_TLS_LDM_ADD"; break;
	      case 63: output = "R_SPARC_TLS_LDM_CALL"; break;
	      case 64: output = "R_SPARC_TLS_LDO_HIX22"; break;
	      case 65: output = "R_SPARC_TLS_LDO_LOX10"; break;
	      case 66: output = "R_SPARC_TLS_LDO_ADD"; break;
	      case 67: output = "R_SPARC_TLS_IE_HI22"; break;
	      case 68: output = "R_SPARC_TLS_IE_LO10"; break;
	      case 69: output = "R_SPARC_TLS_IE_LD"; break;
	      case 70: output = "R_SPARC_TLS_IE_LDX"; break;
	      case 71: output = "R_SPARC_TLS_IE_ADD"; break;
	      case 72: output = "R_SPARC_TLS_LE_HIX22"; break;
	      case 73: output = "R_SPARC_TLS_LE_LOX10"; break;
	      case 74: output = "R_SPARC_TLS_DTPMOD32"; break;
	      case 75: output = "R_SPARC_TLS_DTPMOD64"; break;
	      case 76: output = "R_SPARC_TLS_DTPOFF32"; break;
	      case 77: output = "R_SPARC_TLS_DTPOFF64"; break;
	      case 78: output = "R_SPARC_TLS_TPOFF32"; break;
	      case 79: output = "R_SPARC_TLS_TPOFF64"; break;
  
                //EMPTY_RELOC  (R_SPARC_max_std)

	      case 250: output = "R_SPARC_GNU_VTINHERIT"; break;
	      case 251: output = "R_SPARC_GNU_VTENTRY"; break;
	      case 252: output = "R_SPARC_REV32"; break;

	      default:
                {
		  trace::io_data ( "Unknown Sparc type: %1%", type );

		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_sparc::get_Type" );

	    return output;
	  }

 	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
