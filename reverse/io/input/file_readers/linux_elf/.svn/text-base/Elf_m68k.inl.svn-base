#include "Elf_m68k.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_m68k::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_m68k::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch(type)
            {
                /* No reloc */
            case 0: output = "R_68K_NONE"; break;

                /* Direct 32 bit  */
            case 1: output = "R_68K_32"; break;

                /* Direct 16 bit  */
            case 2: output = "R_68K_16"; break;

                /* Direct 8 bit  */
            case 3: output = "R_68K_8"; break;

                /* PC relative 32 bit */
            case 4: output = "R_68K_PC32"; break;

                /* PC relative 16 bit */
            case 5: output = "R_68K_PC16"; break;

                /* PC relative 8 bit */
            case 6: output = "R_68K_PC8"; break;

                /* 32 bit PC relative GOT entry */
            case 7: output = "R_68K_GOT32"; break;

                /* 16 bit PC relative GOT entry */
            case 8: output = "R_68K_GOT16"; break;

                /* 8 bit PC relative GOT entry */
            case 9: output = "R_68K_GOT8"; break;

                /* 32 bit GOT offset */
            case 10: output = "R_68K_GOT32O"; break;

                /* 16 bit GOT offset */
            case 11: output = "R_68K_GOT16O"; break;

                /* 8 bit GOT offset */
            case 12: output = "R_68K_GOT8O"; break;

                /* 32 bit PC relative PLT address */
            case 13: output = "R_68K_PLT32"; break;

                /* 16 bit PC relative PLT address */
            case 14: output = "R_68K_PLT16"; break;

                /* 8 bit PC relative PLT address */
            case 15: output = "R_68K_PLT8"; break;

                /* 32 bit PLT offset */
            case 16: output = "R_68K_PLT32O"; break;

                /* 16 bit PLT offset */
            case 17: output = "R_68K_PLT16O"; break;

                /* 8 bit PLT offset */
            case 18: output = "R_68K_PLT8O"; break;

                /* Copy symbol at runtime */
            case 19: output = "R_68K_COPY"; break;

                /* Create GOT entry */
            case 20: output = "R_68K_GLOB_DAT"; break;

                /* Create PLT entry */
            case 21: output = "R_68K_JMP_SLOT"; break;

                /* Adjust by program base */
            case 22: output = "R_68K_RELATIVE"; break;

                /* These are GNU extensions to enable C++ vtable garbage collection.  */
       
            case 23: output = "R_68K_GNU_VTINHERIT"; break;
            case 24: output = "R_68K_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
			     boost::str ( boost::format ( "Unknown m86k relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_m68k::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

} /* namespace elf_module */
} /* namespace libreverse */
