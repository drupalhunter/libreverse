#include "Elf_xtensa.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_xtensa::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_xtensa::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_XTENSA_NONE"; break;
            case 1: output = "R_XTENSA_32"; break;
            case 2: output = "R_XTENSA_RTLD"; break;
            case 3: output = "R_XTENSA_GLOB_DAT"; break;
            case 4: output = "R_XTENSA_JMP_SLOT"; break;
            case 5: output = "R_XTENSA_RELATIVE"; break;
            case 6: output = "R_XTENSA_PLT"; break;
            case 8: output = "R_XTENSA_OP0"; break;
            case 9: output = "R_XTENSA_OP1"; break;
            case 10: output = "R_XTENSA_OP2"; break; 
            case 11: output = "R_XTENSA_ASM_EXPAND"; break;
            case 12: output = "R_XTENSA_ASM_SIMPLIFY"; break;
            case 15: output = "R_XTENSA_GNU_VTINHERIT"; break;
            case 16: output = "R_XTENSA_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown xtensa relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_xtensa::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
