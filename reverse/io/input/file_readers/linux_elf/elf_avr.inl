#include <reverse/io/input/file_readers/linux_elf/elf_avr.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_avr::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_avr::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_AVR_NONE"; break;
	      case 1: output = "R_AVR_32"; break;
	      case 2: output = "R_AVR_7_PCREL"; break;
	      case 3: output = "R_AVR_13_PCREL"; break;
	      case 4: output = "R_AVR_16"; break;
	      case 5: output = "R_AVR_16_PM"; break;
	      case 6: output = "R_AVR_LO8_LDI"; break;
	      case 7: output = "R_AVR_HI8_LDI"; break;
	      case 8: output = "R_AVR_HH8_LDI"; break;
	      case 9: output = "R_AVR_LO8_LDI_NEG"; break;
	      case 10: output = "R_AVR_HI8_LDI_NEG"; break;
	      case 11: output = "R_AVR_HH8_LDI_NEG"; break;
	      case 12: output = "R_AVR_LO8_LDI_PM"; break;
	      case 13: output = "R_AVR_HI8_LDI_PM"; break;
	      case 14: output = "R_AVR_HH8_LDI_PM"; break;
	      case 15: output = "R_AVR_LO8_LDI_PM_NEG"; break;
	      case 16: output = "R_AVR_HI8_LDI_PM_NEG"; break;
	      case 17: output = "R_AVR_HH8_LDI_PM_NEG"; break;
	      case 18: output = "R_AVR_CALL"; break;
	      default:
		{

		  trace::io_error ( "Unknown AVR relocation type: %1%", type );

		  output = "unknown";
		}
	      }

	    trace::io_detail ( "Exiting Elf_avr::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
