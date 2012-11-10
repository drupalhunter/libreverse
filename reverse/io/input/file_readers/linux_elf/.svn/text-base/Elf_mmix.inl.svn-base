#include "Elf_mmix.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_mmix::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_mmix::get_Type" );
#endif /* LIBREVERSE_DEBUG */

        std::string output = "";

        switch (type)
            {
            case 0: output = "R_MMIX_NONE"; break;

                /* Standard absolute relocations.  */
            case 1: output = "R_MMIX_8"; break;
            case 2: output = "R_MMIX_16"; break;
            case 3: output = "R_MMIX_24"; break;
            case 4: output = "R_MMIX_32"; break;
            case 5: output = "R_MMIX_64"; break;

                /* Standard relative relocations.  */
            case 6: output = "R_MMIX_PC_8"; break;
            case 7: output = "R_MMIX_PC_16"; break;
            case 8: output = "R_MMIX_PC_24"; break;
            case 9: output = "R_MMIX_PC_32"; break;
            case 10: output = "R_MMIX_PC_64"; break;

                /* GNU extensions for C++ vtables.  */
            case 11: output = "R_MMIX_GNU_VTINHERIT"; break;
            case 12: output = "R_MMIX_GNU_VTENTRY"; break;

                /* A GETA instruction.  */
            case 13: output = "R_MMIX_GETA"; break;
            case 14: output = "R_MMIX_GETA_1"; break;
            case 15: output = "R_MMIX_GETA_2"; break;
            case 16: output = "R_MMIX_GETA_3"; break;

                /* A conditional branch instruction.  */
            case 17: output = "R_MMIX_CBRANCH"; break;
            case 18: output = "R_MMIX_CBRANCH_J"; break;
            case 19: output = "R_MMIX_CBRANCH_1"; break;
            case 20: output = "R_MMIX_CBRANCH_2"; break;
            case 21: output = "R_MMIX_CBRANCH_3"; break;

                /* A PUSHJ instruction.  */
            case 22: output = "R_MMIX_PUSHJ"; break;
            case 23: output = "R_MMIX_PUSHJ_1"; break;
            case 24: output = "R_MMIX_PUSHJ_2"; break;
            case 25: output = "R_MMIX_PUSHJ_3"; break;

                /* A JMP instruction.  */
            case 26: output = "R_MMIX_JMP"; break;
            case 27: output = "R_MMIX_JMP_1"; break;
            case 28: output = "R_MMIX_JMP_2"; break;
            case 29: output = "R_MMIX_JMP_3"; break;

                /* A relative address such as in a GETA or a branch.  */
            case 30: output = "R_MMIX_ADDR19"; break;

                /* A relative address such as in a JMP (only).  */
            case 31: output = "R_MMIX_ADDR27"; break;

                /* A general register or a number 0..255.  */
            case 32: output = "R_MMIX_REG_OR_BYTE"; break;

                /* A general register. */
            case 33: output = "R_MMIX_REG"; break;

                /* A global register and an offset, the global register (allocated at
                   link time) contents plus the offset made equivalent to the relocation
                   expression at link time.  The relocation must point at the Y field of
                   an instruction.  */
            case 34: output = "R_MMIX_BASE_PLUS_OFFSET"; break;

                /* A LOCAL assertion.  */
            case 35: output = "R_MMIX_LOCAL"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown mmix relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_mmix::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
