#include "Elf_m68hc11.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline const bool Elf_m68hc11::EF_M68HC11_CAN_MERGE_MACH ( boost::uint8_t mach1,
                                                               boost::uint8_t mach2 )
    {
        return ((EF_M68HC11_MACH (mach1) == EF_M68HC11_MACH (mach2))
                || (EF_M68HC11_MACH (mach1) == EF_M68HC11_GENERIC)
                || (EF_M68HC11_MACH (mach2) == EF_M68HC11_GENERIC));
    }

    inline const boost::uint8_t Elf_m68hc11::EF_M68HC11_MACH (boost::uint8_t mach)
    {
        return (mach & EF_M68HC11_MACH_MASK);
    }

    /* Relocation types.  */
    inline std::string Elf_m68hc11::get_Type ( boost::uint32_t type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_m68hc11::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_M68HC11_NONE"; break;
            case 1: output = "R_M68HC11_8"; break;
            case 2: output = "R_M68HC11_HI8"; break;
            case 3: output = "R_M68HC11_LO8"; break;
            case 4: output = "R_M68HC11_PCREL_8"; break;
            case 5: output = "R_M68HC11_16"; break;
            case 6: output = "R_M68HC11_32"; break;
            case 7: output = "R_M68HC11_3B"; break;
            case 8: output = "R_M68HC11_PCREL_16"; break;

                /* These are GNU extensions to enable C++ vtable garbage
                   collection.  */
  
            case 9: output = "R_M68HC11_GNU_VTINHERIT"; break;
            case 10: output = "R_M68HC11_GNU_VTENTRY"; break;
            case 11: output = "R_M68HC11_24"; break;
            case 12: output = "R_M68HC11_LO16"; break;
            case 13: output = "R_M68HC11_PAGE"; break;
                
                /* GNU extension for linker relaxation.  Mark beginning of a
                   jump instruction (any form).  */
  
            case 20: output = "R_M68HC11_RL_JUMP"; break;

                /* Mark beginning of Gcc relaxation group instruction.  */
  
            case 21: output = "R_M68HC11_RL_GROUP"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown m68hc11 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_m68hc11::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
