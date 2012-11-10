#include "Elf_arc.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_arc::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_arc::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_ARC_NONE"; break;
            case 1: output = "R_ARC_32"; break;
            case 2: output = "R_ARC_B26"; break;
            case 3: output = "R_ARC_B22_PCREL"; break;
            default:
	      {

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::ERROR,
				     boost::str ( boost::format ( "Unknown arc relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

		output = "unknown";
	      }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                            "Exiting Elf_arc::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
