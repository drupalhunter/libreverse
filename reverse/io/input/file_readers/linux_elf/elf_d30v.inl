#include "Elf_d30v.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_d30v::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_d30v::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
                /* Relocations.  */
            case 0: output = "R_D30V_NONE"; break;
            case 1: output = "R_D30V_6"; break;
            case 2: output = "R_D30V_9_PCREL"; break;
            case 3: output = "R_D30V_9_PCREL_R"; break;
            case 4: output = "R_D30V_15"; break;
            case 5: output = "R_D30V_15_PCREL"; break;
            case 6: output = "R_D30V_15_PCREL_R"; break;
            case 7: output = "R_D30V_21"; break;
            case 8: output = "R_D30V_21_PCREL"; break;
            case 9: output = "R_D30V_21_PCREL_R"; break;
            case 10: output = "R_D30V_32"; break;
            case 11: output = "R_D30V_32_PCREL"; break;
            case 12: output = "R_D30V_32_NORMAL"; break;
                
            default:
                {

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::IO,
				       TraceLevel::ERROR,
				       boost::str ( boost::format ( "Unknown d30v relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

		  output = "unknown";

                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_d30v::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
