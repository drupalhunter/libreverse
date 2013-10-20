#include <reverse/io/input/file_readers/linux_elf/elf_xtensa.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_xtensa::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_xtensa::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_XTENSA_NONE"; break;
	      case 1: output = "R_XTENSA_32"; break;
	      case 2: output = "R_XTENSA_RTLD"; break;
	      case 3: output = "R_XTENSA_GLOB_DAT"; break;
	      case 4: output = "R_XTENSA_JMP_SLOT"; break;
	      case 5: output = "R_XTENSA_RELATIVE"; break;
	      case 6: output = "R_XTENSA_PLT"; break;
	      case 8: output = "R_XTENSA_OP0"; break;
	      case 9: output = "R_XTENSA_OP1"; break;
	      case 10: output = "R_XTENSA_OP2"; break; 
	      case 11: output = "R_XTENSA_ASM_EXPAND"; break;
	      case 12: output = "R_XTENSA_ASM_SIMPLIFY"; break;
	      case 15: output = "R_XTENSA_GNU_VTINHERIT"; break;
	      case 16: output = "R_XTENSA_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown xtensa relocation type: %1%", type );
		  output = "unknown";
                }

	      }

	    trace::io_detail ( "Exiting Elf_xtensa::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

