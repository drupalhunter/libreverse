#include <reverse/io/input/file_readers/linux_elf/elf_or32.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {


	  inline std::string
	  elf_or32::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_or32::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_OR32_NONE"; break;
	      case 1: output = "R_OR32_32"; break;
	      case 2: output = "R_OR32_16"; break;
	      case 3: output = "R_OR32_8"; break;
	      case 4: output = "R_OR32_CONST"; break;
	      case 5: output = "R_OR32_CONSTH"; break;
	      case 6: output = "R_OR32_JUMPTARG"; break;
	      case 7: output = "R_OR32_GNU_VTENTRY"; break;
	      case 8: output = "R_OR32_GNU_VTINHERIT"; break;
	      default:
                {
		  trace::io_error ( "Unknown or32 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_or32::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

