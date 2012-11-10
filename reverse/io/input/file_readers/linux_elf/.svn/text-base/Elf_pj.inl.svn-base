#include "Elf_pj.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_pj::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_pj::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_PJ_NONE"; break;
            case 1: output = "R_PJ_DATA_DIR32"; break;
            case 2: output = "R_PJ_CODE_REL32"; break;
            case 3: output = "R_PJ_CODE_REL16"; break; 
            case 6: output = "R_PJ_CODE_DIR32"; break;
            case 7: output = "R_PJ_CODE_DIR16"; break;  
            case 13: output = "R_PJ_CODE_LO16"; break;
            case 14: output = "R_PJ_CODE_HI16"; break;
            case 15: output = "R_PJ_GNU_VTINHERIT"; break;
            case 16: output = "R_PJ_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown pj relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_pj::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
