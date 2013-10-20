#include <reverse/io/input/file_readers/linux_elf/elf_msp430.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_msp430::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_msp430::get_Type" );

	    std::string output;
	    
	    switch (type)
	      {

	      case 0: output = "R_MSP430_NONE"; break;
	      case 1: output = "R_MSP430_32"; break;
	      case 2: output = "R_MSP430_10_PCREL"; break;
	      case 3: output = "R_MSP430_16"; break;
	      case 4: output = "R_MSP430_16_PCREL"; break;
	      case 5: output = "R_MSP430_16_BYTE"; break;
	      case 6: output = "R_MSP430_16_PCREL_BYTE"; break;
	      default:
                {
		  trace::io_error ( "Unknown msp430 type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_msp430::get_Type" );
    
	    return output;
	  }


	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

