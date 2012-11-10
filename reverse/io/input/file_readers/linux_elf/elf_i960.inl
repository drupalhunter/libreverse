#include "Elf_i960.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_i960::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_i960::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {

            case 0: output = "R_960_NONE"; break;

            case 1: output = "R_960_12"; break;

            case 2: output = "R_960_32"; break;

            case 3: output = "R_960_IP24"; break;

            case 4: output = "R_960_SUB"; break;

            case 5: output = "R_960_OPTCALL"; break;

            case 6: output = "R_960_OPTCALLX"; break;

            case 7: output = "R_960_OPTCALLXA"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown i960 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "Unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_i960::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;

    }
} /* namespace elf_module */
} /* namespace libreverse */
