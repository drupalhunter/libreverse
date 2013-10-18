#include <reverse/io/input/file_readers/linux_elf/elf_m32r.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {


	  inline std::string
	  elf_m32r::get_type (boost::uint32_t type)
	  {

	    trace::io_detail ( "Entering Elf_m32r::get_Type" );

	    std::string output = "";

	    switch (type)
	      {
	      case 0:
                {
		  output = "R_M32R_NONE";
		  break;
                }
	      case 1:
                {
		  output = "R_M32R_16";
		  break;
                }
	      case 2:
                {
		  output = "R_M32R_32";
		  break;
                }
	      case 3:
                {
		  output = "R_M32R_24";
		  break;
                }
	      case 4:
                {
		  output = "R_M32R_10_PCREL";
		  break;
                }
	      case 5:
                {
		  output = "R_M32R_18_PCREL";
		  break;
                }
	      case 6:
                {
		  output = "R_M32R_26_PCREL";
		  break;
                }
	      case 7:
                {
		  output = "R_M32R_HI16_ULO";
		  break;
                }
	      case 8:
                {
		  output = "R_M32R_HI16_SLO";
		  break;
                }
	      case 9:
                {
		  output = "R_M32R_LO16";
		  break;
                }
	      case 10:
                {
		  output = "R_M32R_SDA16";
		  break;
                }
	      case 11:
                {
		  output = "R_M32R_GNU_VTINHERIT";
		  break;
                }
	      case 12:
                {
		  output = "R_M32R_GNU_VTENTRY";
		  break;
                }
	      default:
                {

		  trace::io_error ( "Unknown m32r relocation type: %1%", type );
		  
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_m32r::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
