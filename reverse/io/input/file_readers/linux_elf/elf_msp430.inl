#include "Elf_msp430.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace elf_module {

    inline std::string
    Elf_msp430::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_msp430::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {

            case 0: output = "R_MSP430_NONE"; break;
            case 1: output = "R_MSP430_32"; break;
            case 2: output = "R_MSP430_10_PCREL"; break;
            case 3: output = "R_MSP430_16"; break;
            case 4: output = "R_MSP430_16_PCREL"; break;
            case 5: output = "R_MSP430_16_BYTE"; break;
            case 6: output = "R_MSP430_16_PCREL_BYTE"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown msp430 type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_msp430::get_Type" );
#endif /* LIBREVERSE_DEBUG */

    
        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
