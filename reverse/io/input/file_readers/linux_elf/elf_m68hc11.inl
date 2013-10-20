#include <reverse/io/input/file_readers/linux_elf/elf_m68hc11.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline const bool elf_m68hc11::EF_M68HC11_CAN_MERGE_MACH ( boost::uint8_t mach1,
								     boost::uint8_t mach2 )
	  {
	    return ((EF_M68HC11_MACH (mach1) == EF_M68HC11_MACH (mach2))
		    || (EF_M68HC11_MACH (mach1) == EF_M68HC11_GENERIC)
		    || (EF_M68HC11_MACH (mach2) == EF_M68HC11_GENERIC));
	  }

	  inline const boost::uint8_t elf_m68hc11::EF_M68HC11_MACH (boost::uint8_t mach)
	  {
	    return (mach & EF_M68HC11_MACH_MASK);
	  }

	  /* Relocation types.  */
	  inline std::string elf_m68hc11::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_m68hc11::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_M68HC11_NONE"; break;
	      case 1: output = "R_M68HC11_8"; break;
	      case 2: output = "R_M68HC11_HI8"; break;
	      case 3: output = "R_M68HC11_LO8"; break;
	      case 4: output = "R_M68HC11_PCREL_8"; break;
	      case 5: output = "R_M68HC11_16"; break;
	      case 6: output = "R_M68HC11_32"; break;
	      case 7: output = "R_M68HC11_3B"; break;
	      case 8: output = "R_M68HC11_PCREL_16"; break;

                /* These are GNU extensions to enable C++ vtable garbage
                   collection.  */
  
	      case 9: output = "R_M68HC11_GNU_VTINHERIT"; break;
	      case 10: output = "R_M68HC11_GNU_VTENTRY"; break;
	      case 11: output = "R_M68HC11_24"; break;
	      case 12: output = "R_M68HC11_LO16"; break;
	      case 13: output = "R_M68HC11_PAGE"; break;
                
                /* GNU extension for linker relaxation.  Mark beginning of a
                   jump instruction (any form).  */
  
	      case 20: output = "R_M68HC11_RL_JUMP"; break;

                /* Mark beginning of Gcc relaxation group instruction.  */
  
	      case 21: output = "R_M68HC11_RL_GROUP"; break;
	      default:
                {

		  trace::io_error ( "Unknown m68hc11 relocation type: %1%", type );

		  output = "unknown";
                }

	      }

	    trace::io_detail ( "Exiting Elf_m68hc11::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

