#include <reverse/io/input/file_readers/linux_elf/elf_vax.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_vax::get_type (boost::uint32_t const& type)
	  {
	    trace::io_detail ( "Entering Elf_vax::get_Type" );

	    std::string output = "";

	    switch (type)
	      {
                /* No reloc */
	      case 0: output = "R_VAX_NONE"; break;
                /* Direct 32 bit  */
	      case 1: output = "R_VAX_32"; break;
                /* Direct 16 bit  */
	      case 2: output = "R_VAX_16"; break;
                /* Direct 8 bit  */
	      case 3: output = "R_VAX_8"; break;
                /* PC relative 32 bit */
	      case 4: output = "R_VAX_PC32"; break;
                /* PC relative 16 bit */
	      case 5: output = "R_VAX_PC16"; break;
                /* PC relative 8 bit */
	      case 6: output = "R_VAX_PC8"; break;
                /* 32 bit PC relative GOT entry */
	      case 7: output = "R_VAX_GOT32"; break;
                /* 32 bit PC relative PLT address */
	      case 13: output = "R_VAX_PLT32"; break;
                /* Copy symbol at runtime */
	      case 19: output = "R_VAX_COPY"; break;
                /* Create GOT entry */
	      case 20: output = "R_VAX_GLOB_DAT"; break;
                /* Create PLT entry */
	      case 21: output = "R_VAX_JMP_SLOT"; break;
                /* Adjust by program base */
	      case 22: output = "R_VAX_RELATIVE"; break;

                /* These are GNU extensions to enable C++ vtable garbage
                   collection.  */
	      case 23: output = "R_VAX_GNU_VTINHERIT"; break;
  
	      case 24: output = "R_VAX_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown vax relocation type: %1%", type );
		  output = "unknown";
                }

	      }

	    trace::io_detail ( "Exiting Elf_vax::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

