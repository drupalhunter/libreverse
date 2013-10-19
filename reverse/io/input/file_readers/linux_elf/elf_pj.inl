#include <reverse/io/input/file_readers/linux_elf/elf_pj.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_pj::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_pj::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_PJ_NONE"; break;
	      case 1: output = "R_PJ_DATA_DIR32"; break;
	      case 2: output = "R_PJ_CODE_REL32"; break;
	      case 3: output = "R_PJ_CODE_REL16"; break; 
	      case 6: output = "R_PJ_CODE_DIR32"; break;
	      case 7: output = "R_PJ_CODE_DIR16"; break;  
	      case 13: output = "R_PJ_CODE_LO16"; break;
	      case 14: output = "R_PJ_CODE_HI16"; break;
	      case 15: output = "R_PJ_GNU_VTINHERIT"; break;
	      case 16: output = "R_PJ_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown pj relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_pj::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
