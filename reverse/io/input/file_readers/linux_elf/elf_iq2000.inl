#include <reverse/io/input/file_readers/linux_elf/elf_iq2000.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_iq2000::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_iq2000::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_IQ2000_NONE"; break;
	      case 1: output = "R_IQ2000_16"; break;
	      case 2: output = "R_IQ2000_32"; break;
	      case 3: output = "R_IQ2000_26"; break;
	      case 4: output = "R_IQ2000_PC16"; break;
	      case 5: output = "R_IQ2000_HI16"; break;
	      case 6: output = "R_IQ2000_LO16"; break;
	      case 7: output = "R_IQ2000_OFFSET_16"; break;
	      case 8: output = "R_IQ2000_OFFSET_21"; break;
	      case 9: output = "R_IQ2000_UHI16"; break;
	      case 10: output = "R_IQ2000_32_DEBUG"; break;
	      case 200: output = "R_IQ2000_GNU_VTINHERIT"; break;
	      case 201: output = "R_IQ2000_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown iq2000 relocation type: %1%", type );
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

