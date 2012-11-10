#include "Elf_h8.h"

#include <iostream>


#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_h8::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_h8::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
                /* Relocations 59..63 are GNU extensions.  */
            case 0: output = "R_H8_NONE"; break;
            case 1: output = "R_H8_DIR32"; break;
            case 2: output = "R_H8_DIR32_28"; break;
            case 3: output = "R_H8_DIR32_24"; break;
            case 4: output = "R_H8_DIR32_16"; break;
            case 6: output = "R_H8_DIR32U"; break;
            case 7: output = "R_H8_DIR32U_28"; break;
            case 8: output = "R_H8_DIR32U_24"; break;
            case 9: output = "R_H8_DIR32U_20"; break;
            case 10: output = "R_H8_DIR32U_16"; break;
            case 11: output = "R_H8_DIR24"; break;
            case 12: output = "R_H8_DIR24_20"; break;
            case 13: output = "R_H8_DIR24_16"; break;
            case 14: output = "R_H8_DIR24U"; break;
            case 15: output = "R_H8_DIR24U_20"; break;
            case 16: output = "R_H8_DIR24U_16"; break;
            case 17: output = "R_H8_DIR16"; break;
            case 18: output = "R_H8_DIR16U"; break;
            case 19: output = "R_H8_DIR16S_32"; break;
            case 20: output = "R_H8_DIR16S_28"; break;
            case 21: output = "R_H8_DIR16S_24"; break;
            case 22: output = "R_H8_DIR16S_20"; break;
            case 23: output = "R_H8_DIR16S"; break;
            case 24: output = "R_H8_DIR8"; break;
            case 25: output = "R_H8_DIR8U"; break;
            case 26: output = "R_H8_DIR8Z_32"; break;
            case 27: output = "R_H8_DIR8Z_28"; break;
            case 28: output = "R_H8_DIR8Z_24"; break;
            case 29: output = "R_H8_DIR8Z_20"; break;
            case 30: output = "R_H8_DIR8Z_16"; break;
            case 31: output = "R_H8_PCREL16"; break;
            case 32: output = "R_H8_PCREL8"; break;
            case 33: output = "R_H8_BPOS"; break;
            case 34: output = "R_H8_FIRST_INVALID_DIR_RELOC"; break;
            case 58: output = "R_H8_LAST_INVALID_DIR_RELOC"; break;
            case 59: output = "R_H8_DIR16A8"; break;
            case 60: output = "R_H8_DIR16R8"; break;
            case 61: output = "R_H8_DIR24A8"; break;
            case 62: output = "R_H8_DIR24R8"; break;
            case 63: output = "R_H8_DIR32A16"; break;
            case 65: output = "R_H8_ABS32"; break;
            case 127: output = "R_H8_ABS32A16"; break;
            case 128: output = "R_H8_SYM"; break;
            case 129: output = "R_H8_OPneg"; break;
            case 130: output = "R_H8_OPadd"; break;
            case 131: output = "R_H8_OPsub"; break;
            case 132: output = "R_H8_OPmul"; break;
            case 133: output = "R_H8_OPdiv"; break;
            case 134: output = "R_H8_OPshla"; break;
            case 135: output = "R_H8_OPshra"; break;
            case 136: output = "R_H8_OPsctsize"; break;
            case 137: output = "R_H8_OPhword"; break;
            case 138: output = "R_H8_OPlword"; break;
            case 139: output = "R_H8_OPhigh"; break;
            case 140: output = "R_H8_OPlow"; break;
            case 141: output = "R_H8_OPscttop"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown h8 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_h8::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
