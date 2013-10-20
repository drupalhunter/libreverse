#include <reverse/io/input/file_readers/linux_elf/elf_i960.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_i960::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_i960::get_Type" );

	    std::string output;
	    
	    switch (type)
	      {
		
	      case 0: output = "R_960_NONE"; break;

	      case 1: output = "R_960_12"; break;

	      case 2: output = "R_960_32"; break;

	      case 3: output = "R_960_IP24"; break;

	      case 4: output = "R_960_SUB"; break;

	      case 5: output = "R_960_OPTCALL"; break;

	      case 6: output = "R_960_OPTCALLX"; break;

	      case 7: output = "R_960_OPTCALLXA"; break;
	      default:
                {
		  trace::io_error ( "Unknown i960 relocation type: %1%", type );
		  output = "Unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_i960::get_Type" );

	    return output;

	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

