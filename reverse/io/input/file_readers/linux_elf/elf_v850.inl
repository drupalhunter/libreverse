#include <reverse/io/input/file_readers/linux_elf/elf_v850.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_v850::get_type ( boost::uint32_t type )
	  {
	    trace::io_detail ( "Entering Elf_v850::get_Type" );

	    std::string output;

	    switch (type)
	      {
	      case 0: output = "R_V850_NONE"; break;
	      case 1: output = "R_V850_9_PCREL"; break;
	      case 2: output = "R_V850_22_PCREL"; break;
	      case 3: output = "R_V850_HI16_S"; break;
	      case 4: output = "R_V850_HI16"; break;
	      case 5: output = "R_V850_LO16"; break;
	      case 6: output = "R_V850_32"; break;
	      case 7: output = "R_V850_16"; break;
	      case 8: output = "R_V850_8"; break;
	      case 9: output = " R_V850_SDA_16_16_OFFSET"; break;		/* For ld.b, st.b, set1, clr1, not1, tst1, movea, movhi */
	      case 10: output = " R_V850_SDA_15_16_OFFSET"; break;		/* For ld.w, ld.h, ld.hu, st.w, st.h */
	      case 11: output = " R_V850_ZDA_16_16_OFFSET"; break;		/* For ld.b, st.b, set1, clr1, not1, tst1, movea, movhi */
	      case 12: output = " R_V850_ZDA_15_16_OFFSET"; break;		/* For ld.w, ld.h, ld.hu, st.w, st.h */
	      case 13: output = " R_V850_TDA_6_8_OFFSET"; break;		/* For sst.w, sld.w */
	      case 14: output = " R_V850_TDA_7_8_OFFSET"; break;		/* For sst.h, sld.h */
	      case 15: output = " R_V850_TDA_7_7_OFFSET"; break;		/* For sst.b, sld.b */
	      case 16: output = " R_V850_TDA_16_16_OFFSET"; break;		/* For set1, clr1, not1, tst1, movea, movhi */
	      case 17: output = " R_V850_TDA_4_5_OFFSET"; break;		/* For sld.hu */
	      case 18: output = " R_V850_TDA_4_4_OFFSET"; break;		/* For sld.bu */
	      case 19: output = " R_V850_SDA_16_16_SPLIT_OFFSET"; break;	/* For ld.bu */
	      case 20: output = " R_V850_ZDA_16_16_SPLIT_OFFSET"; break;	/* For ld.bu */
	      case 21: output = " R_V850_CALLT_6_7_OFFSET"; break;		/* For callt */
	      case 22: output = " R_V850_CALLT_16_16_OFFSET"; break;	/* For callt */
	      case 23: output = "R_V850_GNU_VTINHERIT"; break;
	      case 24: output = "R_V850_GNU_VTENTRY"; break;
	      case 25: output = "R_V850_LONGCALL"; break;
	      case 26: output = "R_V850_LONGJUMP"; break;
	      case 27: output = "R_V850_ALIGN"; break;
	      default:
                {
		  trace::io_error ( "Unknown v850 relocation type: %1%", type );
		  output = "unknown";
                }
	      }

	    trace::io_detail ( "Exiting Elf_v850::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

