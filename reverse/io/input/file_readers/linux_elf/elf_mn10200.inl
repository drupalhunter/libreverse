#include <reverse/io/input/file_readers/linux_elf/elf_mn10200.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_mn10200::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_mn10200::get_Type" );

	    std::string output;

	    switch(type)
	      {
	      case 0: output = "R_MN10200_NONE"; break;
	      case 1: output = "R_MN10200_32"; break;
	      case 2: output = "R_MN10200_16"; break;
	      case 3: output = "R_MN10200_8"; break;
	      case 4: output = "R_MN10200_24"; break;
	      case 5: output = "R_MN10200_PCREL8"; break;
	      case 6: output = "R_MN10200_PCREL16"; break;
	      case 7: output = "R_MN10200_PCREL24"; break;
	      default:
		{
		  trace::io_error ( "Unknown mn10200 type: %1%", type );
		  output = "unknown";
		}
	      }

	    trace::io_detail ( "Exiting Elf_mn10200::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

