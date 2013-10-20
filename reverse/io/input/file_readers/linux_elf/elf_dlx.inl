#include <reverse/io/input/file_readers/linux_elf/elf_dlx.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_dlx::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_dlx::get_Type" );
	    std::string output;

	    switch(type)
	      {
	      case 0: output = "R_DLX_NONE"; break;
	      case 1: output = "R_DLX_RELOC_8"; break;
	      case 2: output = "R_DLX_RELOC_16"; break;
	      case 3: output = "R_DLX_RELOC_32"; break;
	      case 4: output = "R_DLX_GNU_VTINHERIT"; break;
	      case 5: output = "R_DLX_GNU_VTENTRY"; break;
	      case 6: output = "R_DLX_RELOC_16_HI"; break;
	      case 7: output = "R_DLX_RELOC_16_LO"; break;
	      case 8: output = "R_DLX_RELOC_16_PCREL"; break;
	      case 9: output = "R_DLX_RELOC_26_PCREL"; break;
	      default:

		{
		  trace::io_error ( "Unknown dlx relocaltion type: %1%", type );
		  output = "unknown";
		}
	      }

	    trace::io_detail ( "Exiting Elf_dlx::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

