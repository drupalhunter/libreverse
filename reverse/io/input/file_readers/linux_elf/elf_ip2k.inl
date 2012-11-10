#include "Elf_ip2k.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_ip2k::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_ip2k::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_IP2K_NONE"; break;
            case 1: output = "R_IP2K_16"; break;
            case 2: output = "R_IP2K_32"; break;
            case 3: output = "R_IP2K_FR9"; break;
            case 4: output = "R_IP2K_BANK"; break;
            case 5: output = "R_IP2K_ADDR16CJP"; break;
            case 6: output = "R_IP2K_PAGE3"; break;
            case 7: output = "R_IP2K_LO8DATA"; break;
            case 8: output = "R_IP2K_HI8DATA"; break;
            case 9: output = "R_IP2K_LO8INSN"; break;
            case 10: output = "R_IP2K_HI8INSN"; break;
            case 11: output = "R_IP2K_PC_SKIP"; break;
            case 12: output = "R_IP2K_TEXT"; break;
            case 13: output = "R_IP2K_FR_OFFSET"; break;
            case 14: output = "R_IP2K_EX8DATA"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown ip2k relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */


                    output = "unknown";
                }

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_ip2k::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
