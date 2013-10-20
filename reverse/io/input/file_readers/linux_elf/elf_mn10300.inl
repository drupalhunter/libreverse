#include <reverse/io/input/file_readers/linux_elf/elf_mn10300.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_mn10300::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_mn10300::get_Type" );

	    std::string output;

	    switch (type)
	      {
                /* Relocations.  */
	      case 0: output = "R_MN10300_NONE"; break;
	      case 1: output = "R_MN10300_32"; break;
	      case 2: output = "R_MN10300_16"; break;
	      case 3: output = "R_MN10300_8"; break;
	      case 4: output = "R_MN10300_PCREL32"; break;
	      case 5: output = "R_MN10300_PCREL16"; break;
	      case 6: output = "R_MN10300_PCREL8"; break;
	      case 7: output = "R_MN10300_GNU_VTINHERIT"; break;
	      case 8: output = "R_MN10300_GNU_VTENTRY"; break;
	      case 9: output = "R_MN10300_24"; break;
	      default:
                {
		  trace::io_error ( "Unknown mn10300 relocation type: ", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_mn10300::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
