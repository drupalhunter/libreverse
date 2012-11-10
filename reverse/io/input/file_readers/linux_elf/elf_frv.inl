#include "Elf_frv.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    std::string
    Elf_frv::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_frv::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_FRV_NONE"; break;
            case 1: output = "R_FRV_32"; break;
            case 2: output = "R_FRV_LABEL16"; break;
            case 3: output = "R_FRV_LABEL24"; break;
            case 4: output = "R_FRV_LO16"; break;
            case 5: output = "R_FRV_HI16"; break;
            case 6: output = "R_FRV_GPREL12"; break;
            case 7: output = "R_FRV_GPRELU12"; break;
            case 8: output = "R_FRV_GPREL32"; break;
            case 9: output = "R_FRV_GPRELHI"; break;
            case 10: output = "R_FRV_GPRELLO"; break;
            case 200: output = "R_FRV_GNU_VTINHERIT"; break;
            case 201: output = "R_FRV_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown frv relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_frv::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
