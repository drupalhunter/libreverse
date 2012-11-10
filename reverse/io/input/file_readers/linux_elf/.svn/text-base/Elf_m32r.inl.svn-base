#include "Elf_m32r.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_m32r::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_m32r::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0:
                {
                    output = "R_M32R_NONE";
                    break;
                }
            case 1:
                {
                    output = "R_M32R_16";
                    break;
                }
            case 2:
                {
                    output = "R_M32R_32";
                    break;
                }
            case 3:
                {
                    output = "R_M32R_24";
                    break;
                }
            case 4:
                {
                    output = "R_M32R_10_PCREL";
                    break;
                }
            case 5:
                {
                    output = "R_M32R_18_PCREL";
                    break;
                }
            case 6:
                {
                    output = "R_M32R_26_PCREL";
                    break;
                }
            case 7:
                {
                    output = "R_M32R_HI16_ULO";
                    break;
                }
            case 8:
                {
                    output = "R_M32R_HI16_SLO";
                    break;
                }
            case 9:
                {
                    output = "R_M32R_LO16";
                    break;
                }
            case 10:
                {
                    output = "R_M32R_SDA16";
                    break;
                }
            case 11:
                {
                    output = "R_M32R_GNU_VTINHERIT";
                    break;
                }
            case 12:
                {
                    output = "R_M32R_GNU_VTENTRY";
                    break;
                }
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown m32r relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_m32r::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
