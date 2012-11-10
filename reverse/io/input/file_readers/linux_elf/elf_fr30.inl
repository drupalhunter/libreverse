#include "Elf_fr30.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_fr30::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_fr30::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_FR30_NONE"; break;
            case 1: output = "R_FR30_8"; break;
            case 2: output = "R_FR30_20"; break;
            case 3: output = "R_FR30_32"; break;
            case 4: output = "R_FR30_48"; break;
            case 5: output = "R_FR30_6_IN_4"; break;
            case 6: output = "R_FR30_8_IN_8"; break;
            case 7: output = "R_FR30_9_IN_8"; break;
            case 8: output = "R_FR30_10_IN_8"; break;
            case 9: output = "R_FR30_9_PCREL"; break;
            case 10: output = "R_FR30_12_PCREL"; break;
            case 11: output = "R_FR30_GNU_VTINHERIT"; break;
            case 12: output = "R_FR30_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown fr30 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_fr30::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
