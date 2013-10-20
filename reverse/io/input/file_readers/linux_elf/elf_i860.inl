#include <reverse/io/input/file_readers/linux_elf/elf_i860.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string 
	  elf_i860::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_i680::get_Type" );

	    std::string output;

	    switch (type)
	      {
                /* No reloc */
	      case 0x00: output = "R_860_NONE"; break;
                /* S+A  */
	      case 0x01: output = "R_860_32"; break;
                /* No calculation */
	      case 0x02: output = "R_860_COPY"; break;
                /* S, Create GOT entry */
	      case 0x03: output = "R_860_GLOB_DAT"; break;
                /* S+A, Create PLT entry */
	      case 0x04: output = "R_860_JUMP_SLOT"; break;
                /* B+A, Adj by program base */
	      case 0x05: output = "R_860_RELATIVE"; break;
                /* (S+A-P) >> 2 */
	      case 0x30: output = "R_860_PC26"; break; 
                /* (L+A-P) >> 2 */
	      case 0x31: output = "R_860_PLT26"; break;
                /* (S+A-P) >> 2 */
	      case 0x32: output = "R_860_PC16"; break;
                /* S+A */
	      case 0x40: output = "R_860_LOW0"; break;
                /* S+A */
	      case 0x42: output = "R_860_SPLIT0"; break;       
                /* S+A */
	      case 0x44: output = "R_860_LOW1"; break;
                /* S+A */
	      case 0x46: output = "R_860_SPLIT1"; break;
                /* S+A */
	      case 0x48: output = "R_860_LOW2"; break;
                /* S+A */
	      case 0x4A: output = "R_860_SPLIT2"; break;
                /* S+A */
	      case 0x4C: output = "R_860_LOW3"; break;
                /* G */
	      case 0x50: output = "R_860_LOGOT0"; break;
                /* G */
	      case 0x52: output = "R_860_SPGOT0"; break;
                /* G */
	      case 0x54: output = "R_860_LOGOT1"; break;
                /* G */
	      case 0x56: output = "R_860_SPGOT1"; break;
                /* O */
	      case 0x60: output = "R_860_LOGOTOFF0"; break;
                /* O */
	      case 0x62: output = "R_860_SPGOTOFF0"; break;
                /* O */
	      case 0x64: output = "R_860_LOGOTOFF1"; break;
                /* O */
	      case 0x66: output = "R_860_SPGOTOFF1"; break;
                /* O */
	      case 0x68: output = "R_860_LOGOTOFF2"; break;
                /* O */
	      case 0x6C: output = "R_860_LOGOTOFF3"; break;
                /* (S+A-P) >> 2 */
	      case 0x70: output = "R_860_LOPC"; break;
                /* hiadj(S+A) */
	      case 0x80: output = "R_860_HIGHADJ"; break;
                /* hiadj(G) */
	      case 0x90: output = "R_860_HAGOT"; break;
                /* hiadj(O) */
	      case 0xA0: output = "R_860_HAGOTOFF"; break;
                /* hiadj((S+A-P) >> 2) */
	      case 0xB0: output = "R_860_HAPC"; break;
                /* (S+A) >> 16 */
	      case 0xC0: output = "R_860_HIGH"; break;
                /* G >> 16 */
	      case 0xD0: output = "R_860_HIGOT"; break;
                /* O */
	      case 0xE0: output = "R_860_HIGOTOFF"; break;
	      default:
                {
		  trace::io_detail ( "Unknown i860 relocation type: %1%", type );
		  output = "unknown";
                }

	      }

	    trace::io_detail ( "Entering Elf_i680::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

