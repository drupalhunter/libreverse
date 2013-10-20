#include <reverse/io/input/file_readers/linux_elf/elf_d30v.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_d30v::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_d30v::get_Type" );

	    std::string output;

	    switch (type)
	      {
                /* Relocations.  */
	      case 0: output = "R_D30V_NONE"; break;
	      case 1: output = "R_D30V_6"; break;
	      case 2: output = "R_D30V_9_PCREL"; break;
	      case 3: output = "R_D30V_9_PCREL_R"; break;
	      case 4: output = "R_D30V_15"; break;
	      case 5: output = "R_D30V_15_PCREL"; break;
	      case 6: output = "R_D30V_15_PCREL_R"; break;
	      case 7: output = "R_D30V_21"; break;
	      case 8: output = "R_D30V_21_PCREL"; break;
	      case 9: output = "R_D30V_21_PCREL_R"; break;
	      case 10: output = "R_D30V_32"; break;
	      case 11: output = "R_D30V_32_PCREL"; break;
	      case 12: output = "R_D30V_32_NORMAL"; break;
                
	      default:
                {
		  trace::io_error ( "Unknown d30v relocation type: %1%", type );

		  output = "unknown";

                }
	      }

	    trace::io_detail ( "Exiting Elf_d30v::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
