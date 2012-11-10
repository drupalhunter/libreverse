#include "Elf_xstormy16.h"
#include <iostream>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_xstormy16::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_xstormy16::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_XSTORMY16_NONE"; break;

            case 1: output = "R_XSTORMY16_32"; break;
            case 2: output = "R_XSTORMY16_16"; break;
            case 3: output = "R_XSTORMY16_8"; break;
            case 4: output = "R_XSTORMY16_PC32"; break;
            case 5: output = "R_XSTORMY16_PC16"; break;
            case 6: output = "R_XSTORMY16_PC8"; break;

            case 7: output = "R_XSTORMY16_REL_12"; break;
            case 8: output = "R_XSTORMY16_24"; break;
            case 9: output = "R_XSTORMY16_FPTR16"; break;

            case 10: output = "R_XSTORMY16_LO16"; break;
            case 11: output = "R_XSTORMY16_HI16"; break;
            case 12: output = "R_XSTORMY16_12"; break;

            case 128: output = "R_XSTORMY16_GNU_VTINHERIT"; break;
            case 129: output = "R_XSTORMY16_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown xstorym16 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_xstormy16::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
