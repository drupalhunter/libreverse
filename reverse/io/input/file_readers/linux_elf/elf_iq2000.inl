#include "Elf_iq2000.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace elf_module {

    inline std::string
    Elf_iq2000::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_iq2000::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_IQ2000_NONE"; break;
            case 1: output = "R_IQ2000_16"; break;
            case 2: output = "R_IQ2000_32"; break;
            case 3: output = "R_IQ2000_26"; break;
            case 4: output = "R_IQ2000_PC16"; break;
            case 5: output = "R_IQ2000_HI16"; break;
            case 6: output = "R_IQ2000_LO16"; break;
            case 7: output = "R_IQ2000_OFFSET_16"; break;
            case 8: output = "R_IQ2000_OFFSET_21"; break;
            case 9: output = "R_IQ2000_UHI16"; break;
            case 10: output = "R_IQ2000_32_DEBUG"; break;
            case 200: output = "R_IQ2000_GNU_VTINHERIT"; break;
            case 201: output = "R_IQ2000_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown iq2000 relocation type: %1%" ) % type ) );
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
