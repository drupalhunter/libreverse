#include <reverse/io/input/file_readers/linux_elf/elf_xstormy16.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_xstormy16::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_xstormy16::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_XSTORMY16_NONE"; break;

	      case 1: output = "R_XSTORMY16_32"; break;
	      case 2: output = "R_XSTORMY16_16"; break;
	      case 3: output = "R_XSTORMY16_8"; break;
	      case 4: output = "R_XSTORMY16_PC32"; break;
	      case 5: output = "R_XSTORMY16_PC16"; break;
	      case 6: output = "R_XSTORMY16_PC8"; break;

	      case 7: output = "R_XSTORMY16_REL_12"; break;
	      case 8: output = "R_XSTORMY16_24"; break;
	      case 9: output = "R_XSTORMY16_FPTR16"; break;

	      case 10: output = "R_XSTORMY16_LO16"; break;
	      case 11: output = "R_XSTORMY16_HI16"; break;
	      case 12: output = "R_XSTORMY16_12"; break;

	      case 128: output = "R_XSTORMY16_GNU_VTINHERIT"; break;
	      case 129: output = "R_XSTORMY16_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown xstorym16 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_xstormy16::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

