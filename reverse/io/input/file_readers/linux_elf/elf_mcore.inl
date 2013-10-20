#include <reverse/io/input/file_readers/linux_elf/elf_mcore.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_mcore::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_iq2000::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_MCORE_NONE"; break;
	      case 1: output = "R_MCORE_ADDR32"; break;
	      case 2: output = "R_MCORE_PCRELIMM8BY4"; break;
	      case 3: output = "R_MCORE_PCRELIMM11BY2"; break;
	      case 4: output = "R_MCORE_PCRELIMM4BY2"; break;
	      case 5: output = "R_MCORE_PCREL32"; break;
	      case 6: output = "R_MCORE_PCRELJSR_IMM11BY2"; break;
	      case 7: output = "R_MCORE_GNU_VTINHERIT"; break;
	      case 8: output = "R_MCORE_GNU_VTENTRY"; break;
	      case 9: output = "R_MCORE_RELATIVE"; break;
	      case 10: output = "R_MCORE_COPY"; break;
	      case 11: output = "R_MCORE_GLOB_DAT"; break;
	      case 12: output = "R_MCORE_JUMP_SLOT"; break;
	      default:
                {
		  trace::io_error ( "Unknown mcore relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_iq2000::get_Type" );

	    return output;
	  }


	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

