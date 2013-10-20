#include <reverse/io/input/file_readers/linux_elf/elf_d10v.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_d10v::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_d10v::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_D10V_NONE"; break;
	      case 1: output = "R_D10V_10_PCREL_R"; break;
	      case 2: output = "R_D10V_10_PCREL_L"; break;
	      case 3: output = "R_D10V_16"; break;
	      case 4: output = "R_D10V_18"; break;
	      case 5: output = "R_D10V_18_PCREL"; break;
	      case 6: output = "R_D10V_32"; break;
	      case 7: output = "R_D10V_GNU_VTINHERIT"; break;
	      case 8: output = "R_D10V_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown d10v relocation type: ", type );

		  output = "unknown";
                }
	      }
	
	    trace::io_detail ( "Exiting Elf_d10v::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

