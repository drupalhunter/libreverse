#include <reverse/io/input/file_readers/linux_elf/elf_frv.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_frv::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_frv::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_FRV_NONE"; break;
	      case 1: output = "R_FRV_32"; break;
	      case 2: output = "R_FRV_LABEL16"; break;
	      case 3: output = "R_FRV_LABEL24"; break;
	      case 4: output = "R_FRV_LO16"; break;
	      case 5: output = "R_FRV_HI16"; break;
	      case 6: output = "R_FRV_GPREL12"; break;
	      case 7: output = "R_FRV_GPRELU12"; break;
	      case 8: output = "R_FRV_GPREL32"; break;
	      case 9: output = "R_FRV_GPRELHI"; break;
	      case 10: output = "R_FRV_GPRELLO"; break;
	      case 200: output = "R_FRV_GNU_VTINHERIT"; break;
	      case 201: output = "R_FRV_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown frv relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_frv::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

