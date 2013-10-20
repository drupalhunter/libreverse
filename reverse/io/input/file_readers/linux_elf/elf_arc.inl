#include <reverse/io/input/file_readers/linux_elf/elf_arc.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_arc::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_arc::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_ARC_NONE"; break;
	      case 1: output = "R_ARC_32"; break;
	      case 2: output = "R_ARC_B26"; break;
	      case 3: output = "R_ARC_B22_PCREL"; break;
	      default:
		{
		  trace::io_error ( "Unknown arc relocation type: %1%", type );
		  output = "unknown";
		}
	      }

	    trace::io_detail ( "Exiting Elf_arc::get_Type" );
	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

