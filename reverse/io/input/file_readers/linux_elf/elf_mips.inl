#include <reverse/io/input/file_readers/linux_elf/elf_mips.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline boost::uint32_t
	  elf_mips::elf64_mips_r_ssym (boost::uint64_t input)
	  {
	    trace::io_detail ( "entering elf_mips::elf64_mips_r_ssym" );

	    boost::uint32_t result = static_cast<boost::uint32_t>((input >> 24) & 0xff);

	    trace::io_detail ( "exiting elf_mips::elf64_mips_r_ssym" );

	    return result;
	  }

	  inline boost::uint32_t
	  elf_mips::elf64_mips_r_type3 (boost::uint64_t input)
	  {
	    trace::io_detail ( "entering elf_mips::elf64_mips_r_type3" );

	    boost::uint32_t result = static_cast<boost::uint32_t>((input >> 16) & 0xff);

	    trace::io_detail ( "exiting elf_mips::elf64_mips_r_type3" );

	    return result;
	  }

	  inline boost::uint32_t
	  elf_mips::elf64_mips_r_type2 (boost::uint64_t input)
	  {
	    trace::io_detail ( "entering elf_mips::elf32_mips_r_type2" );

	    boost::uint32_t result = static_cast<boost::uint32_t>((input >> 8) & 0xff);

	    trace::io_detail ( "exiting elf_mips::elf32_mips_r_type2" );

	    return result;
	  }

	  inline boost::uint32_t
	  elf_mips::elf64_mips_r_type (boost::uint64_t input)
	  {
	    trace::io_detail ( "entering elf_mips::elf64_mips_r_type" );

	    boost::uint32_t result = static_cast<boost::uint32_t>(input & 0xff);
	
	    trace::io_detail ( "exiting elf_mips::elf64_mips_r_type" );

	    return result;
	  }

	  inline std::string
	  elf_mips::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "entering elf_mips::get_type" );

	    std::string output = "";


	    switch (type)
	      {
	      case 0: output = "R_MIPS_NONE"; break;
	      case 1: output = "R_MIPS_16"; break;

                /* In Elf 64: alias R_MIPS_ADD */
	      case 2: output = "R_MIPS_32"; break;

                /* In Elf 64: alias R_MIPS_REL */
	      case 3: output = "R_MIPS_REL32"; break;
	      case 4: output = "R_MIPS_26"; break;
	      case 5: output = "R_MIPS_HI16"; break;
	      case 6: output = "R_MIPS_LO16"; break;

                /* In Elf 64: alias R_MIPS_GPREL */
	      case 7: output = "R_MIPS_GPREL16"; break;
	      case 8: output = "R_MIPS_LITERAL"; break;

                /* In Elf 64: alias R_MIPS_GOT */
	      case 9: output = "R_MIPS_GOT16"; break;
	      case 10: output = "R_MIPS_PC16"; break;

                /* In Elf 64: alias R_MIPS_CALL */
	      case 11: output = "R_MIPS_CALL16"; break;
	      case 12: output = "R_MIPS_GPREL32"; break;

                /* The remaining relocs are defined on Irix, although they are not
                   in the MIPS ELF ABI.  */
	      case 13: output = "R_MIPS_UNUSED1"; break;
	      case 14: output = "R_MIPS_UNUSED2"; break;
	      case 15: output = "R_MIPS_UNUSED3"; break;
	      case 16: output = "R_MIPS_SHIFT5"; break;
	      case 17: output = "R_MIPS_SHIFT6"; break;
	      case 18: output = "R_MIPS_64"; break;
	      case 19: output = "R_MIPS_GOT_DISP"; break;
	      case 20: output = "R_MIPS_GOT_PAGE"; break;
	      case 21: output = "R_MIPS_GOT_OFST"; break;
	      case 22: output = "R_MIPS_GOT_HI16"; break;
	      case 23: output = "R_MIPS_GOT_LO16"; break;
	      case 24: output = "R_MIPS_SUB"; break;
	      case 25: output = "R_MIPS_INSERT_A"; break;
	      case 26: output = "R_MIPS_INSERT_B"; break;
	      case 27: output = "R_MIPS_DELETE"; break;
	      case 28: output = "R_MIPS_HIGHER"; break;
	      case 29: output = "R_MIPS_HIGHEST"; break;
	      case 30: output = "R_MIPS_CALL_HI16"; break;
	      case 31: output = "R_MIPS_CALL_LO16"; break;
	      case 32: output = "R_MIPS_SCN_DISP"; break;
	      case 33: output = "R_MIPS_REL16"; break;
	      case 34: output = "R_MIPS_ADD_IMMEDIATE"; break;
	      case 35: output = "R_MIPS_PJUMP"; break;
	      case 36: output = "R_MIPS_RELGOT"; break;
	      case 37: output = "R_MIPS_JALR"; break;
	      case 38: output = "R_MIPS_max"; break;

                /* These relocs are used for the mips16.  */
	      case 100: output = "R_MIPS16_26"; break;
	      case 101: output = "R_MIPS16_GPREL"; break;

                /* These are GNU extensions to handle embedded-pic.  */
	      case 248: output = "R_MIPS_PC32"; break;
	      case 249: output = "R_MIPS_PC64"; break;
	      case 250: output = "R_MIPS_GNU_REL16_S2"; break;
	      case 251: output = "R_MIPS_GNU_REL_LO16"; break;
	      case 252: output = "R_MIPS_GNU_REL_HI16"; break;

                /* These are GNU extensions to enable C++ vtable garbage
                   collection.  */
	      case 253: output = "R_MIPS_GNU_VTINHERIT"; break;
	      case 254: output = "R_MIPS_GNU_VTENTRY"; break;
	      default:
                {
		  trace::io_error ( "Unknown mips relocation type: %1%", type );

		  output = "unknown";
                }  
	      }

	    trace::io_detail ( "Exiting Elf_mips::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

