#include "Elf_i370.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_i370::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_i370::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_I370_NONE"; break;
            case 1: output = "R_I370_ADDR31"; break;
            case 2: output = "R_I370_ADDR32"; break;
            case 3: output = "R_I370_ADDR16"; break; 
            case 4: output = "R_I370_REL31"; break;
            case 5: output = "R_I370_REL32"; break;  
            case 6: output = "R_I370_ADDR12"; break;
            case 7: output = "R_I370_REL12"; break;
            case 8: output = "R_I370_ADDR8"; break;
            case 9: output = "R_I370_REL8"; break;
            case 10: output = "R_I370_COPY"; break;
            case 11: output = "R_I370_RELATIVE"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown i370 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_i370::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
