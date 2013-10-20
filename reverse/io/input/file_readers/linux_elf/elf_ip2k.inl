#include <reverse/io/input/file_readers/linux_elf/elf_ip2k.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_ip2k::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_ip2k::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_IP2K_NONE"; break;
	      case 1: output = "R_IP2K_16"; break;
	      case 2: output = "R_IP2K_32"; break;
	      case 3: output = "R_IP2K_FR9"; break;
	      case 4: output = "R_IP2K_BANK"; break;
	      case 5: output = "R_IP2K_ADDR16CJP"; break;
	      case 6: output = "R_IP2K_PAGE3"; break;
	      case 7: output = "R_IP2K_LO8DATA"; break;
	      case 8: output = "R_IP2K_HI8DATA"; break;
	      case 9: output = "R_IP2K_LO8INSN"; break;
	      case 10: output = "R_IP2K_HI8INSN"; break;
	      case 11: output = "R_IP2K_PC_SKIP"; break;
	      case 12: output = "R_IP2K_TEXT"; break;
	      case 13: output = "R_IP2K_FR_OFFSET"; break;
	      case 14: output = "R_IP2K_EX8DATA"; break;
	      default:
                {
		  trace::io_error ( "Unknown ip2k relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_ip2k::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
