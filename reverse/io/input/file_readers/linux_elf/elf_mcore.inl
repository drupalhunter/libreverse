#include "Elf_mcore.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_mcore::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_iq2000::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_MCORE_NONE"; break;
            case 1: output = "R_MCORE_ADDR32"; break;
            case 2: output = "R_MCORE_PCRELIMM8BY4"; break;
            case 3: output = "R_MCORE_PCRELIMM11BY2"; break;
            case 4: output = "R_MCORE_PCRELIMM4BY2"; break;
            case 5: output = "R_MCORE_PCREL32"; break;
            case 6: output = "R_MCORE_PCRELJSR_IMM11BY2"; break;
            case 7: output = "R_MCORE_GNU_VTINHERIT"; break;
            case 8: output = "R_MCORE_GNU_VTENTRY"; break;
            case 9: output = "R_MCORE_RELATIVE"; break;
            case 10: output = "R_MCORE_COPY"; break;
            case 11: output = "R_MCORE_GLOB_DAT"; break;
            case 12: output = "R_MCORE_JUMP_SLOT"; break;
            default:
                {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown mcore relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_iq2000::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
