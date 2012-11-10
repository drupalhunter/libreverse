#include "Elf_avr.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    std::string
    Elf_avr::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_avr::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_AVR_NONE"; break;
            case 1: output = "R_AVR_32"; break;
            case 2: output = "R_AVR_7_PCREL"; break;
            case 3: output = "R_AVR_13_PCREL"; break;
            case 4: output = "R_AVR_16"; break;
            case 5: output = "R_AVR_16_PM"; break;
            case 6: output = "R_AVR_LO8_LDI"; break;
            case 7: output = "R_AVR_HI8_LDI"; break;
            case 8: output = "R_AVR_HH8_LDI"; break;
            case 9: output = "R_AVR_LO8_LDI_NEG"; break;
            case 10: output = "R_AVR_HI8_LDI_NEG"; break;
            case 11: output = "R_AVR_HH8_LDI_NEG"; break;
            case 12: output = "R_AVR_LO8_LDI_PM"; break;
            case 13: output = "R_AVR_HI8_LDI_PM"; break;
            case 14: output = "R_AVR_HH8_LDI_PM"; break;
            case 15: output = "R_AVR_LO8_LDI_PM_NEG"; break;
            case 16: output = "R_AVR_HI8_LDI_PM_NEG"; break;
            case 17: output = "R_AVR_HH8_LDI_PM_NEG"; break;
            case 18: output = "R_AVR_CALL"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown AVR relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */


                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_avr::get_Type" );
#endif /* LIBREVERSE_DEBUG */

    
        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
