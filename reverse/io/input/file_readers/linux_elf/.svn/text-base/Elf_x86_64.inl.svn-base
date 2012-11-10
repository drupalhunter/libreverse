#include "Elf_x86_64.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_x86_64::get_Type (boost::uint32_t const& type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_x86_64::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
                /* No reloc */
            case 0: output = "R_X86_64_NONE"; break;
                /* Direct 64 bit  */
            case 1: output = "R_X86_64_64"; break;
                /* PC relative 32 bit signed */
            case 2: output = "R_X86_64_PC32"; break;
                /* 32 bit GOT entry */
            case 3: output = "R_X86_64_GOT32"; break;
                /* 32 bit PLT address */
            case 4: output = "R_X86_64_PLT32"; break;
                /* Copy symbol at runtime */
            case 5: output = "R_X86_64_COPY"; break;
                /* Create GOT entry */
            case 6: output = "R_X86_64_GLOB_DAT"; break;
                /* Create PLT entry */
            case 7: output = "R_X86_64_JUMP_SLOT"; break;
                /* Adjust by program base */
            case 8: output = "R_X86_64_RELATIVE"; break;
                /* 32 bit signed pc relative offset to GOT */
            case 9: output = "R_X86_64_GOTPCREL"; break;
                /* Direct 32 bit zero extended */
            case 10: output = "R_X86_64_32"; break;
                /* Direct 32 bit sign extended */
            case 11: output = "R_X86_64_32S"; break;
                /* Direct 16 bit zero extended */
            case 12: output = "R_X86_64_16"; break;
                /* 16 bit sign extended pc relative*/
            case 13: output = "R_X86_64_PC16"; break;
                /* Direct 8 bit sign extended */
            case 14: output = "R_X86_64_8"; break;
                /* 8 bit sign extended pc relative*/
            case 15: output = "R_X86_64_PC8"; break;
                /* ID of module containing symbol */
            case 16: output = "R_X86_64_DTPMOD64"; break;
                /* Offset in TLS block */
            case 17: output = "R_X86_64_DTPOFF64"; break;
                /* Offset in initial TLS block */
            case 18: output = "R_X86_64_TPOFF64"; break;
                /* PC relative offset to GD GOT block */
            case 19: output = "R_X86_64_TLSGD"; break;
                /* PC relative offset to LD GOT block */
            case 20: output = "R_X86_64_TLSLD"; break;
                /* Offset in TLS block */
            case 21: output = "R_X86_64_DTPOFF32"; break;
                /* PC relative offset to IE GOT entry */
            case 22: output = "R_X86_64_GOTTPOFF"; break;
                /* Offset in initial TLS block */
            case 23: output = "R_X86_64_TPOFF32"; break;
                /* GNU C++ hack  */
            case 250: output = "R_X86_64_GNU_VTINHERIT"; break;
                /* GNU C++ hack  */
            case 251: output = "R_X86_64_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown x86-64 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_x86_64::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
