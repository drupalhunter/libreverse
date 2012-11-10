#include "Elf_d10v.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_d10v::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_d10v::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_D10V_NONE"; break;
            case 1: output = "R_D10V_10_PCREL_R"; break;
            case 2: output = "R_D10V_10_PCREL_L"; break;
            case 3: output = "R_D10V_16"; break;
            case 4: output = "R_D10V_18"; break;
            case 5: output = "R_D10V_18_PCREL"; break;
            case 6: output = "R_D10V_32"; break;
            case 7: output = "R_D10V_GNU_VTINHERIT"; break;
            case 8: output = "R_D10V_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::IO,
				       TraceLevel::ERROR,
				       boost::str ( boost::format ( "Unknown d10v relocation type: " ) % type ) );
#endif /* LIBREVERSE_DEBUG */


                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_d10v::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
