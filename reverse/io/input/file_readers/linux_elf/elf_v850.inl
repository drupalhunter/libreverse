#include "Elf_v850.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_v850::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_v850::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

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

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::IO,
				       TraceLevel::DETAIL,
				       boost::str ( boost::format ( "Unknown v850 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_v850::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
