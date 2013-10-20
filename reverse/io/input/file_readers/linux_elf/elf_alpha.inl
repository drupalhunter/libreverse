#include <reverse/io/input/file_readers/linux_elf/elf_alpha.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {


	  inline std::string
	  elf_alpha::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_alpha::get_Type" );

	    std::string output;

            switch (type)
	      {
		/* No reloc */
	      case 0: output = "R_ALPHA_NONE"; break;

		/* Direct 32 bit */
	      case 1: output = "R_ALPHA_REFLONG"; break;

		/* Direct 64 bit */
	      case 2: output = "R_ALPHA_REFQUAD"; break;

		/* GP relative 32 bit */
	      case 3: output = "R_ALPHA_GPREL32"; break;

		/* GP relative 16 bit w/optimization */
	      case 4: output = "R_ALPHA_LITERAL"; break;

		/* Optimization hint for LITERAL */
	      case 5: output = "R_ALPHA_LITUSE"; break;

		/* Add displacement to GP */
	      case 6: output = "R_ALPHA_GPDISP"; break;

		/* PC+4 relative 23 bit shifted */
	      case 7: output = "R_ALPHA_BRADDR"; break;

		/* PC+4 relative 16 bit shifted */
	      case 8: output = "R_ALPHA_HINT"; break;

		/* PC relative 16 bit */
	      case 9: output = "R_ALPHA_SREL16"; break;

		/* PC relative 32 bit */
	      case 10: output = "R_ALPHA_SREL32"; break;

		/* PC relative 64 bit */
	      case 11: output = "R_ALPHA_SREL64"; break;


		/* Skip 12 - 16; deprecated ECOFF relocs.  */

		/* GP relative 32 bit, high 16 bits */
	      case 17: output = "R_ALPHA_GPRELHIGH"; break;

		/* GP relative 32 bit, low 16 bits */
	      case 18: output = "R_ALPHA_GPRELLOW"; break;

		/* GP relative 16 bit */
	      case 19: output = "R_ALPHA_GPREL16"; break;


		/* Skip 20 - 23; deprecated ECOFF relocs.  */

		/* These relocations are specific to shared libraries.  */
		/* Copy symbol at runtime */
	      case 24: output = "R_ALPHA_COPY"; break;

		/* Create GOT entry */
	      case 25: output = "R_ALPHA_GLOB_DAT"; break;

		/* Create PLT entry */
	      case 26: output = "R_ALPHA_JMP_SLOT"; break;

		/* Adjust by program base */
	      case 27: output = "R_ALPHA_RELATIVE"; break;

		/* Like BRADDR, but assert that the source and target object file
		   share the same GP value, and adjust the target address for
		   STO_ALPHA_STD_GPLOAD.  */

	      case 28: output = "R_ALPHA_BRSGP"; break;


		/* Thread-Local Storage.  */

	      case 29: output = "R_ALPHA_TLSGD"; break;
	      case 30: output = "R_ALPHA_TLSLDM"; break;
	      case 31: output = "R_ALPHA_DTPMOD64"; break;
	      case 32: output = "R_ALPHA_GOTDTPREL"; break;
	      case 33: output = "R_ALPHA_DTPREL64"; break;
	      case 34: output = "R_ALPHA_DTPRELHI"; break;
	      case 35: output = "R_ALPHA_DTPRELLO"; break;
	      case 36: output = "R_ALPHA_DTPREL16"; break;
	      case 37: output = "R_ALPHA_GOTTPREL"; break;
	      case 38: output = "R_ALPHA_TPREL64"; break;
	      case 39: output = "R_ALPHA_TPRELHI"; break;
	      case 40: output = "R_ALPHA_TPRELLO"; break;
	      case 41: output = "R_ALPHA_TPREL16"; break;
	      default:
		{
		  trace::io_error ( "Unknown alpha relocation type: %1%", type );
		  output = "unknown";
		}
	      }

	    trace::io_detail ( "Exiting Elf_alpha::get_Type" );

            return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

