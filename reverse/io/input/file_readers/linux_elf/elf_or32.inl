#include "Elf_or32.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_or32::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_or32::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_OR32_NONE"; break;
            case 1: output = "R_OR32_32"; break;
            case 2: output = "R_OR32_16"; break;
            case 3: output = "R_OR32_8"; break;
            case 4: output = "R_OR32_CONST"; break;
            case 5: output = "R_OR32_CONSTH"; break;
            case 6: output = "R_OR32_JUMPTARG"; break;
            case 7: output = "R_OR32_GNU_VTENTRY"; break;
            case 8: output = "R_OR32_GNU_VTINHERIT"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown or32 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_or32::get_Type" );
#endif /* LIBREVERSE_DEBUG */

        return output;
    }
} /* namespace elf_module */  
} /* namespace libreverse */
