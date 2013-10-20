#include <reverse/io/input/file_readers/linux_elf/elf_s390.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_s390::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_s390::get_Type" );

	    std::string output;

	    switch (type)
	      {
                /* No reloc.  */
	      case 0: output = "R_390_NONE"; break;
                /* Direct 8 bit.  */
	      case 1: output = "R_390_8"; break;
                /* Direct 12 bit.  */
	      case 2: output = "R_390_12"; break;
                /* Direct 16 bit.  */
	      case 3: output = "R_390_16"; break;
                /* Direct 32 bit.  */
	      case 4: output = "R_390_32"; break;
                /* PC relative 32 bit.  */
	      case 5: output = "R_390_PC32"; break;
                /* 12 bit GOT offset.  */
	      case 6: output = "R_390_GOT12"; break;
                /* 32 bit GOT offset.  */
	      case 7: output = "R_390_GOT32"; break;
                /* 32 bit PC relative PLT address.  */
	      case 8: output = "R_390_PLT32"; break;
                /* Copy symbol at runtime.  */
	      case 9: output = "R_390_COPY"; break;
                /* Create GOT entry.  */
	      case 10: output = "R_390_GLOB_DAT"; break;
                /* Create PLT entry.  */
	      case 11: output = "R_390_JMP_SLOT"; break;
                /* Adjust by program base.  */
	      case 12: output = "R_390_RELATIVE"; break;
                /* 32 bit offset to GOT.  */
	      case 13: output = "R_390_GOTOFF32"; break;
                /* 32 bit PC relative offset to GOT.  */
	      case 14: output = "R_390_GOTPC"; break;
                /* 16 bit GOT offset.  */
	      case 15: output = "R_390_GOT16"; break;
                /* PC relative 16 bit.  */
	      case 16: output = "R_390_PC16"; break;
                /* PC relative 16 bit shifted by 1.  */
	      case 17: output = "R_390_PC16DBL"; break;
                /* 16 bit PC rel. PLT shifted by 1.  */
	      case 18: output = "R_390_PLT16DBL"; break;
                /* PC relative 32 bit shifted by 1.  */
	      case 19: output = "R_390_PC32DBL"; break;
                /* 32 bit PC rel. PLT shifted by 1.  */
	      case 20: output = "R_390_PLT32DBL"; break;
                /* 32 bit PC rel. GOT shifted by 1.  */
	      case 21: output = "R_390_GOTPCDBL"; break;
                /* Direct 64 bit.  */
	      case 22: output = "R_390_64"; break;
                /* PC relative 64 bit.  */
	      case 23: output = "R_390_PC64"; break;
                /* 64 bit GOT offset.  */
	      case 24: output = "R_390_GOT64"; break;
                /* 64 bit PC relative PLT address.  */
	      case 25: output = "R_390_PLT64"; break;
                /* 32 bit PC rel. to GOT entry >> 1. */
	      case 26: output = "R_390_GOTENT"; break;
                /* 16 bit offset to GOT. */
	      case 27: output = "R_390_GOTOFF16"; break;
                /* 64 bit offset to GOT. */
	      case 28: output = "R_390_GOTOFF64"; break;
                /* 12 bit offset to jump slot.  */
	      case 29: output = "R_390_GOTPLT12"; break;
                /* 16 bit offset to jump slot.  */
	      case 30: output = "R_390_GOTPLT16"; break;
                /* 32 bit offset to jump slot.  */
	      case 31: output = "R_390_GOTPLT32"; break;
                /* 64 bit offset to jump slot.  */
	      case 32: output = "R_390_GOTPLT64"; break;
                /* 32 bit rel. offset to jump slot.  */
	      case 33: output = "R_390_GOTPLTENT"; break;
                /* 16 bit offset from GOT to PLT. */
	      case 34: output = "R_390_PLTOFF16"; break;
                /* 32 bit offset from GOT to PLT. */
	      case 35: output = "R_390_PLTOFF32"; break;
                /* 16 bit offset from GOT to PLT. */
	      case 36: output = "R_390_PLTOFF64"; break;
                /* Tag for load insn in TLS code. */
	      case 37: output = "R_390_TLS_LOAD"; break;
                /* Tag for function call in general dynamic TLS code.  */
	      case 38: output = "R_390_TLS_GDCALL"; break;
                /* Tag for function call in local dynamic TLS code.  */
	      case 39: output = "R_390_TLS_LDCALL"; break;
                /* Direct 32 bit for general dynamic thread local data.  */
	      case 40: output = "R_390_TLS_GD32"; break;
                /* Direct 64 bit for general dynamic thread local data.  */
	      case 41: output = "R_390_TLS_GD64"; break;
                /* 12 bit GOT offset for static TLS block offset.  */
	      case 42: output = "R_390_TLS_GOTIE12"; break;
                /* 32 bit GOT offset for static TLS block offset.  */
	      case 43: output = "R_390_TLS_GOTIE32"; break;
                /* 64 bit GOT offset for static TLS block offset.  */
	      case 44: output = "R_390_TLS_GOTIE64"; break;
                /* Direct 32 bit for local dynamic thread local data in LD
                   code.  */
	      case 45: output = "R_390_TLS_LDM32"; break;
                /* Direct 64 bit for local dynamic thread local data in LD
                   code.  */
	      case 46: output = "R_390_TLS_LDM64"; break;
                /* 32 bit address of GOT entry for negated static TLS block
                   offset.  */
	      case 47: output = "R_390_TLS_IE32"; break;
                /* 64 bit address of GOT entry for negated static TLS block
                   offset.  */
	      case 48: output = "R_390_TLS_IE64"; break;
                /* 32 bit rel. offset to GOT entry for negated static TLS
                   block offset.  */
	      case 49: output = "R_390_TLS_IEENT"; break;
                /* 32 bit negated offset relative to static TLS block.  */
	      case 50: output = "R_390_TLS_LE32"; break;
                /* 64 bit negated offset relative to static TLS block.  */
	      case 51: output = "R_390_TLS_LE64"; break;
                /* 32 bit offset relative to TLS block.  */
	      case 52: output = "R_390_TLS_LDO32"; break;
                /* 64 bit offset relative to TLS block. ID of module
                   containing symbol.  */
	      case 53: output = "R_390_TLS_LDO64"; break;
	      case 54: output = "R_390_TLS_DTPMOD"; break;
                /* Offset in TLS block.  */
	      case 55: output = "R_390_TLS_DTPOFF"; break;
                /* Negate offset in static TLS block.  */
	      case 56: output = "R_390_TLS_TPOFF"; break;
                /* These are GNU extensions to enable C++ vtable garbage
                   collection.  */
	      case 250: output = "R_390_GNU_VTINHERIT"; break;
	      case 251: output = "R_390_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown s390 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_s390::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

