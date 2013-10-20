#include <reverse/io/input/file_readers/linux_elf/elf_sh.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_sh::get_type (boost::uint32_t type)
	  {
	    trace::io_detail ( "Entering Elf_sh::get_Type" );

	    std::string output;

	    /* Relocations.  */
	    /* Relocations 25ff are GNU extensions.  25..33 are used for
	       relaxation and use the same constants as COFF uses.  */
	    switch (type)
	      {
	      case 0: output = "R_SH_NONE"; break;
	      case 1: output = "R_SH_DIR32"; break;
	      case 2: output = "R_SH_REL32"; break;
	      case 3: output = "R_SH_DIR8WPN"; break;
	      case 4: output = "R_SH_IND12W"; break;
	      case 5: output = "R_SH_DIR8WPL"; break;
	      case 6: output = "R_SH_DIR8WPZ"; break;
	      case 7: output = "R_SH_DIR8BP"; break;
	      case 8: output = "R_SH_DIR8W"; break;
	      case 9: output = "R_SH_DIR8L"; break;
	      case 10: output = "R_SH_FIRST_INVALID_RELOC"; break;
	      case 24: output = "R_SH_LAST_INVALID_RELOC"; break;
	      case 25: output = "R_SH_SWITCH16"; break;
	      case 26: output = "R_SH_SWITCH32"; break;
	      case 27: output = "R_SH_USES"; break;
	      case 28: output = "R_SH_COUNT"; break;
	      case 29: output = "R_SH_ALIGN"; break;
	      case 30: output = "R_SH_CODE"; break;
	      case 31: output = "R_SH_DATA"; break;
	      case 32: output = "R_SH_LABEL"; break;
	      case 33: output = "R_SH_SWITCH8"; break;
	      case 34: output = "R_SH_GNU_VTINHERIT"; break;
	      case 35: output = "R_SH_GNU_VTENTRY"; break;
	      case 36: output = "R_SH_LOOP_START"; break;
	      case 37: output = "R_SH_LOOP_END"; break;
	      case 38: output = "R_SH_FIRST_INVALID_RELOC_2"; break;
	      case 44: output = "R_SH_LAST_INVALID_RELOC_2"; break;
	      case 45: output = "R_SH_DIR5U"; break;
	      case 46: output = "R_SH_DIR6U"; break;
	      case 47: output = "R_SH_DIR6S"; break;
	      case 48: output = "R_SH_DIR10S"; break;
	      case 49: output = "R_SH_DIR10SW"; break;
	      case 50: output = "R_SH_DIR10SL"; break;
	      case 51: output = "R_SH_DIR10SQ"; break;
	      case 52: output = "R_SH_FIRST_INVALID_RELOC_3"; break;
	      case 143: output = "R_SH_LAST_INVALID_RELOC_3"; break;
	      case 144: output = "R_SH_TLS_GD_32"; break;
	      case 145: output = "R_SH_TLS_LD_32"; break;
	      case 146: output = "R_SH_TLS_LDO_32"; break;
	      case 147: output = "R_SH_TLS_IE_32"; break;
	      case 148: output = "R_SH_TLS_LE_32"; break;
	      case 149: output = "R_SH_TLS_DTPMOD32"; break;
	      case 150: output = "R_SH_TLS_DTPOFF32"; break;
	      case 151: output = "R_SH_TLS_TPOFF32"; break;
	      case 152: output = "R_SH_FIRST_INVALID_RELOC_4"; break;
	      case 159: output = "R_SH_LAST_INVALID_RELOC_4"; break;
	      case 160: output = "R_SH_GOT32"; break;
	      case 161: output = "R_SH_PLT32"; break;
	      case 162: output = "R_SH_COPY"; break;
	      case 163: output = "R_SH_GLOB_DAT"; break;
	      case 164: output = "R_SH_JMP_SLOT"; break;
	      case 165: output = "R_SH_RELATIVE"; break;
	      case 166: output = "R_SH_GOTOFF"; break;
	      case 167: output = "R_SH_GOTPC"; break;
	      case 168: output = "R_SH_GOTPLT32"; break;
	      case 169: output = "R_SH_GOT_LOW16"; break;
	      case 170: output = "R_SH_GOT_MEDLOW16"; break;
	      case 171: output = "R_SH_GOT_MEDHI16"; break;
	      case 172: output = "R_SH_GOT_HI16"; break;
	      case 173: output = "R_SH_GOTPLT_LOW16"; break;
	      case 174: output = "R_SH_GOTPLT_MEDLOW16"; break;
	      case 175: output = "R_SH_GOTPLT_MEDHI16"; break;
	      case 176: output = "R_SH_GOTPLT_HI16"; break;
	      case 177: output = "R_SH_PLT_LOW16"; break;
	      case 178: output = "R_SH_PLT_MEDLOW16"; break;
	      case 179: output = "R_SH_PLT_MEDHI16"; break;
	      case 180: output = "R_SH_PLT_HI16"; break;
	      case 181: output = "R_SH_GOTOFF_LOW16"; break;
	      case 182: output = "R_SH_GOTOFF_MEDLOW16"; break;
	      case 183: output = "R_SH_GOTOFF_MEDHI16"; break;
	      case 184: output = "R_SH_GOTOFF_HI16"; break;
	      case 185: output = "R_SH_GOTPC_LOW16"; break;
	      case 186: output = "R_SH_GOTPC_MEDLOW16"; break;
	      case 187: output = "R_SH_GOTPC_MEDHI16"; break;
	      case 188: output = "R_SH_GOTPC_HI16"; break;
	      case 189: output = "R_SH_GOT10BY4"; break;
	      case 190: output = "R_SH_GOTPLT10BY4"; break;
	      case 191: output = "R_SH_GOT10BY8"; break;
	      case 192: output = "R_SH_GOTPLT10BY8"; break;
	      case 193: output = "R_SH_COPY64"; break;
	      case 194: output = "R_SH_GLOB_DAT64"; break;
	      case 195: output = "R_SH_JMP_SLOT64"; break;
	      case 196: output = "R_SH_RELATIVE64"; break;
	      case 197: output = "R_SH_FIRST_INVALID_RELOC_5"; break;
	      case 241: output = "R_SH_LAST_INVALID_RELOC_5"; break;
	      case 242: output = "R_SH_SHMEDIA_CODE"; break;
	      case 243: output = "R_SH_PT_16"; break;
	      case 244: output = "R_SH_IMMS16"; break;
	      case 245: output = "R_SH_IMMU16"; break;
	      case 246: output = "R_SH_IMM_LOW16"; break;
	      case 247: output = "R_SH_IMM_LOW16_PCREL"; break;
	      case 248: output = "R_SH_IMM_MEDLOW16"; break;
	      case 249: output = "R_SH_IMM_MEDLOW16_PCREL"; break;
	      case 250: output = "R_SH_IMM_MEDHI16"; break;
	      case 251: output = "R_SH_IMM_MEDHI16_PCREL"; break;
	      case 252: output = "R_SH_IMM_HI16"; break;
	      case 253: output = "R_SH_IMM_HI16_PCREL"; break;
	      case 254: output = "R_SH_64"; break;
	      case 255: output = "R_SH_64_PCREL"; break;
	      default:
                {
		  trace::io_error ( "Unknown sh relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_sh::get_Type" );

	    return output;
	  }

	  inline bool elf_sh::EF_SH_HAS_FP (boost::uint8_t flags)
	  {
	    trace::io_detail ( "Inside Elf_sh::EF_SH_HAS_FP" );
      
	    bool result = false;
      
	    if (flags & 8)
	      {
		result = true;
	      }
      
	    return result;
	  }

	  inline bool elf_sh::EF_SH_HAS_DSP (boost::uint8_t flags)
	  {
	    trace::io_detail ( "Inside Elf_sh::EF_SH_HAS_DSP" );

	    bool result = false;

	    if (flags & 4)
	      {
                result = true;
	      }

	    return result;
	  }
  
	  inline boost::uint8_t
	  elf_sh::EF_SH_MERGE_MACH (boost::uint8_t mach1, boost::uint8_t mach2)
	  {
	    trace::io_detail ( "Entering Elf_sh::EF_SH_MERGE_MACH" );

	    boost::uint8_t result = 0;

	    if ((mach1 == EF_SH3) ||
		((mach1 == EF_SH_UNKNOWN) && (mach2 == EF_SH_DSP)) ||
		((mach1 == EF_SH_DSP) && (mach2 == EF_SH3)) ||
		(mach2 == EF_SH_UNKNOWN))
	      {
                result = EF_SH3_DSP;
	      }
	    else if (((mach1 < EF_SH3) && (mach2 == EF_SH_UNKNOWN)) ||
		     ((mach2 < EF_SH3) && (mach1 == EF_SH_UNKNOWN)))
	      {
                result = EF_SH3;
	      }
	    else if ((mach1 == EF_SH2E) && EF_SH_HAS_FP (mach2))
	      {
                result = mach2;
	      }
	    else if ((mach2 == EF_SH2E) && EF_SH_HAS_FP (mach1))
	      {
                result = mach1;
	      }
	    else if (((mach1 == EF_SH2E) && (mach2 == EF_SH_UNKNOWN)) ||
		     ((mach2 == EF_SH2E) && (mach1 == EF_SH_UNKNOWN)))
	      {
                result = EF_SH2E;
	      }
	    else if (((mach1 == EF_SH3E) && (mach2 == EF_SH_UNKNOWN)) ||
		     ((mach2 == EF_SH3E) && (mach1 == EF_SH_UNKNOWN)))
	      {
                result = EF_SH4;
	      }
	    else if (mach1 == EF_SH2E)
	      {
                result = 7;
	      }
	    // If mach1 == EF_SH2E then we return 7 or use mach1 value
	    // in comparison. (x = 7 or mach1)
	    //
	    // If mach2 == EF_SH2E then we return 7 or use mach2 value
	    // in comparison. (y = 7 or mach2)
	    //
	    // If x > y then return mach1 else return mach2
	    else {
	      boost::uint8_t lh_val = 7;
	      boost::uint8_t rh_val = 7;
	      result = mach2;

	      if (mach1 == EF_SH2E)
                {
		  lh_val = mach1;
                }
	      if (mach2 == EF_SH2E)
                {
		  rh_val = mach2;
                }
	      if (lh_val > rh_val)
                {
		  result = mach1;
                }
	    }

	    trace::io_detail ( "Exiting Elf_sh::EF_SH_MERGE_MACH" );

	    return result;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
