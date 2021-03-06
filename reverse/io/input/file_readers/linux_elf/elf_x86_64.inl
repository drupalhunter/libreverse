#include <reverse/io/input/file_readers/linux_elf/elf_x86_64.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_x86_64::get_type (boost::uint32_t const& type)
	  {
	    trace::io_detail ( "Entering Elf_x86_64::get_Type" );

	    std::string output;

	    switch (type)
	      {
                /* No reloc */
	      case 0: output = "R_X86_64_NONE"; break;
                /* Direct 64 bit  */
	      case 1: output = "R_X86_64_64"; break;
                /* PC relative 32 bit signed */
	      case 2: output = "R_X86_64_PC32"; break;
                /* 32 bit GOT entry */
	      case 3: output = "R_X86_64_GOT32"; break;
                /* 32 bit PLT address */
	      case 4: output = "R_X86_64_PLT32"; break;
                /* Copy symbol at runtime */
	      case 5: output = "R_X86_64_COPY"; break;
                /* Create GOT entry */
	      case 6: output = "R_X86_64_GLOB_DAT"; break;
                /* Create PLT entry */
	      case 7: output = "R_X86_64_JUMP_SLOT"; break;
                /* Adjust by program base */
	      case 8: output = "R_X86_64_RELATIVE"; break;
                /* 32 bit signed pc relative offset to GOT */
	      case 9: output = "R_X86_64_GOTPCREL"; break;
                /* Direct 32 bit zero extended */
	      case 10: output = "R_X86_64_32"; break;
                /* Direct 32 bit sign extended */
	      case 11: output = "R_X86_64_32S"; break;
                /* Direct 16 bit zero extended */
	      case 12: output = "R_X86_64_16"; break;
                /* 16 bit sign extended pc relative*/
	      case 13: output = "R_X86_64_PC16"; break;
                /* Direct 8 bit sign extended */
	      case 14: output = "R_X86_64_8"; break;
                /* 8 bit sign extended pc relative*/
	      case 15: output = "R_X86_64_PC8"; break;
                /* ID of module containing symbol */
	      case 16: output = "R_X86_64_DTPMOD64"; break;
                /* Offset in TLS block */
	      case 17: output = "R_X86_64_DTPOFF64"; break;
                /* Offset in initial TLS block */
	      case 18: output = "R_X86_64_TPOFF64"; break;
                /* PC relative offset to GD GOT block */
	      case 19: output = "R_X86_64_TLSGD"; break;
                /* PC relative offset to LD GOT block */
	      case 20: output = "R_X86_64_TLSLD"; break;
                /* Offset in TLS block */
	      case 21: output = "R_X86_64_DTPOFF32"; break;
                /* PC relative offset to IE GOT entry */
	      case 22: output = "R_X86_64_GOTTPOFF"; break;
                /* Offset in initial TLS block */
	      case 23: output = "R_X86_64_TPOFF32"; break;
                /* GNU C++ hack  */
	      case 250: output = "R_X86_64_GNU_VTINHERIT"; break;
                /* GNU C++ hack  */
	      case 251: output = "R_X86_64_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown x86-64 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_x86_64::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

