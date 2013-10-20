#include <reverse/io/input/file_readers/linux_elf/elf_ix86.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_ix86::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_ix86::get_Type" );

	    std::string output;
	    
	    switch (type)
	      {
                /* No reloc */
	      case 0: output = "R_386_NONE"; break;

                /* Direct 32 bit  */
	      case 1: output = "R_386_32"; break;

                /* PC relative 32 bit */
	      case 2: output = "R_386_PC32"; break;

                /* 32 bit GOT entry */
	      case 3: output = "R_386_GOT32"; break;

                /* 32 bit PLT address */
	      case 4: output = "R_386_PLT32"; break;

                /* Copy symbol at runtime */
	      case 5: output = "R_386_COPY"; break;

                /* Create GOT entry */
	      case 6: output = "R_386_GLOB_DAT"; break;

                /* Create PLT entry */
	      case 7: output = "R_386_JUMP_SLOT"; break;

                /* Adjust by program base */
	      case 8: output = "R_386_RELATIVE"; break;

                /* 32 bit offset to GOT */
	      case 9: output = "R_386_GOTOFF"; break;

                /* 32 bit PC relative offset to GOT */
	      case 10: output = "R_386_GOTPC"; break;

                /* Used by Sun */
	      case 11: output = "R_386_32PLT"; break;

	      case 12: output = "FIRST_INVALID_RELOC"; break;
	      case 13: output = "LAST_INVALID_RELOC"; break; 
	      case 14: output = "R_386_TLS_TPOFF"; break;
     
	      case 15: output = "R_386_TLS_IE"; break;
	      case 16: output = "R_386_TLS_GOTIE"; break;
	      case 17: output = "R_386_TLS_LE"; break;
	      case 18: output = "R_386_TLS_GD"; break;
	      case 19: output = "R_386_TLS_LDM"; break;
	      case 20: output = "R_386_16"; break;
	      case 21: output = "R_386_PC16"; break;
	      case 22: output = "R_386_8"; break;
	      case 23: output = "R_386_PC8"; break;
        
	      case 24: output = "R_386_TLS_GD_32"; break;
        
	      case 25: output = "R_386_TLS_GD_PUSH"; break;
     
	      case 26: output = "R_386_TLS_GD_CALL"; break;
     
	      case 27: output = "R_386_TLS_GD_POP"; break;
     
	      case 28: output = "R_386_TLS_LDM_32"; break;
     
	      case 29: output = "R_386_TLS_LDM_PUSH"; break;
     
	      case 30: output = "R_386_TLS_LDM_CALL"; break;
     
	      case 31: output = "R_386_TLS_LDM_POP"; break;
     
	      case 32: output = "R_386_TLS_LDO_32"; break;
     
	      case 33: output = "R_386_TLS_IE_32"; break;
     
	      case 34: output = "R_386_TLS_LE_32"; break;
     
	      case 35: output = "R_386_TLS_DTPMOD32"; break;
     
	      case 36: output = "R_386_TLS_DTPOFF32"; break;
     
	      case 37: output = "R_386_TLS_TPOFF32"; break;

                /* These are GNU extensions to enable C++ vtable garbage collection.  */
     
	      case 250: output = "R_386_GNU_VTINHERIT"; break;
     
	      case 251: output = "R_386_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown ix86 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_ix86::get_Type" );
    
	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

