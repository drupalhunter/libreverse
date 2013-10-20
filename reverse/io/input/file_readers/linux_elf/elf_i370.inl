#include <reverse/io/input/file_readers/linux_elf/elf_i370.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_i370::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_i370::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_I370_NONE"; break;
            case 1: output = "R_I370_ADDR31"; break;
            case 2: output = "R_I370_ADDR32"; break;
            case 3: output = "R_I370_ADDR16"; break; 
            case 4: output = "R_I370_REL31"; break;
            case 5: output = "R_I370_REL32"; break;  
            case 6: output = "R_I370_ADDR12"; break;
            case 7: output = "R_I370_REL12"; break;
            case 8: output = "R_I370_ADDR8"; break;
            case 9: output = "R_I370_REL8"; break;
            case 10: output = "R_I370_COPY"; break;
            case 11: output = "R_I370_RELATIVE"; break;
            default:
                {
		  trace::io_error ( "Unknown i370 relocation type: %1%", type );
		  output = "unknown";
                }
            }

	    trace::io_detail ( "Exiting Elf_i370::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
