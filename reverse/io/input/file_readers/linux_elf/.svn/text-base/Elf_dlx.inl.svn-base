#include "Elf_dlx.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_dlx::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_dlx::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch(type)
            {
            case 0: output = "R_DLX_NONE"; break;
            case 1: output = "R_DLX_RELOC_8"; break;
            case 2: output = "R_DLX_RELOC_16"; break;
            case 3: output = "R_DLX_RELOC_32"; break;
            case 4: output = "R_DLX_GNU_VTINHERIT"; break;
            case 5: output = "R_DLX_GNU_VTENTRY"; break;
            case 6: output = "R_DLX_RELOC_16_HI"; break;
            case 7: output = "R_DLX_RELOC_16_LO"; break;
            case 8: output = "R_DLX_RELOC_16_PCREL"; break;
            case 9: output = "R_DLX_RELOC_26_PCREL"; break;
            default:

                {
#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::IO,
				       TraceLevel::ERROR,
				       boost::str ( boost::format ( "Unknown dlx relocaltion type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_dlx::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
