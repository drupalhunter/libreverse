#include <reverse/io/input/file_readers/linux_elf/elf_fr30.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_fr30::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_fr30::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_FR30_NONE"; break;
	      case 1: output = "R_FR30_8"; break;
	      case 2: output = "R_FR30_20"; break;
	      case 3: output = "R_FR30_32"; break;
	      case 4: output = "R_FR30_48"; break;
	      case 5: output = "R_FR30_6_IN_4"; break;
	      case 6: output = "R_FR30_8_IN_8"; break;
	      case 7: output = "R_FR30_9_IN_8"; break;
	      case 8: output = "R_FR30_10_IN_8"; break;
	      case 9: output = "R_FR30_9_PCREL"; break;
	      case 10: output = "R_FR30_12_PCREL"; break;
	      case 11: output = "R_FR30_GNU_VTINHERIT"; break;
	      case 12: output = "R_FR30_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown fr30 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_fr30::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

