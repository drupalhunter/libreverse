#include "Elf_mn10300.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_mn10300::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_mn10300::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
                /* Relocations.  */
            case 0: output = "R_MN10300_NONE"; break;
            case 1: output = "R_MN10300_32"; break;
            case 2: output = "R_MN10300_16"; break;
            case 3: output = "R_MN10300_8"; break;
            case 4: output = "R_MN10300_PCREL32"; break;
            case 5: output = "R_MN10300_PCREL16"; break;
            case 6: output = "R_MN10300_PCREL8"; break;
            case 7: output = "R_MN10300_GNU_VTINHERIT"; break;
            case 8: output = "R_MN10300_GNU_VTENTRY"; break;
            case 9: output = "R_MN10300_24"; break;
            default:
                {
#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::IO,
				       TraceLevel::ERROR,
				       boost::str ( boost::format ( "Unknown mn10300 relocation type: " ) % type ) ) ;
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_mn10300::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
