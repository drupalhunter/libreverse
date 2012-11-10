#include "Elf_ppc.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_ppc::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_ppc::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type) 
            {
            case 0: output = "R_PPC_NONE"; break;
            case 1: output = "R_PPC_ADDR32"; break;
            case 2: output = "R_PPC_ADDR24"; break;
            case 3: output = "R_PPC_ADDR16"; break;
            case 4: output = "R_PPC_ADDR16_LO"; break;
            case 5: output = "R_PPC_ADDR16_HI"; break;
            case 6: output = "R_PPC_ADDR16_HA"; break;
            case 7: output = "R_PPC_ADDR14"; break;
            case 8: output = "R_PPC_ADDR14_BRTAKEN"; break;
            case 9: output = "R_PPC_ADDR14_BRNTAKEN"; break;
            case 10: output = "R_PPC_REL24"; break;
            case 11: output = "R_PPC_REL14"; break;
            case 12: output = "R_PPC_REL14_BRTAKEN"; break;
            case 13: output = "R_PPC_REL14_BRNTAKEN"; break;
            case 14: output = "R_PPC_GOT16"; break;
            case 15: output = "R_PPC_GOT16_LO"; break;
            case 16: output = "R_PPC_GOT16_HI"; break;
            case 17: output = "R_PPC_GOT16_HA"; break;
            case 18: output = "R_PPC_PLTREL24"; break;
            case 19: output = "R_PPC_COPY"; break;
            case 20: output = "R_PPC_GLOB_DAT"; break;
            case 21: output = "R_PPC_JMP_SLOT"; break;
            case 22: output = "R_PPC_RELATIVE"; break;
            case 23: output = "R_PPC_LOCAL24PC"; break;
            case 24: output = "R_PPC_UADDR32"; break;
            case 25: output = "R_PPC_UADDR16"; break;
            case 26: output = "R_PPC_REL32"; break;
            case 27: output = "R_PPC_PLT32"; break;
            case 28: output = "R_PPC_PLTREL32"; break;
            case 29: output = "R_PPC_PLT16_LO"; break;
            case 30: output = "R_PPC_PLT16_HI"; break;
            case 31: output = "R_PPC_PLT16_HA"; break;
            case 32: output = "R_PPC_SDAREL16"; break;
            case 33: output = "R_PPC_SECTOFF"; break;
            case 34: output = "R_PPC_SECTOFF_LO"; break;
            case 35: output = "R_PPC_SECTOFF_HI"; break;
            case 36: output = "R_PPC_SECTOFF_HA"; break;
            case 37: output = "R_PPC_ADDR30"; break;

                /* Relocs added to support TLS.  */
            case 67: output = "R_PPC_TLS"; break;
            case 68: output = "R_PPC_DTPMOD32"; break;
            case 69: output = "R_PPC_TPREL16"; break;
            case 70: output = "R_PPC_TPREL16_LO"; break;
            case 71: output = "R_PPC_TPREL16_HI"; break;
            case 72: output = "R_PPC_TPREL16_HA"; break;
            case 73: output = "R_PPC_TPREL32"; break;
            case 74: output = "R_PPC_DTPREL16"; break;
            case 75: output = "R_PPC_DTPREL16_LO"; break;
            case 76: output = "R_PPC_DTPREL16_HI"; break;
            case 77: output = "R_PPC_DTPREL16_HA"; break;
            case 78: output = "R_PPC_DTPREL32"; break;
            case 79: output = "R_PPC_GOT_TLSGD16"; break;
            case 80: output = "R_PPC_GOT_TLSGD16_LO"; break;
            case 81: output = "R_PPC_GOT_TLSGD16_HI"; break;
            case 82: output = "R_PPC_GOT_TLSGD16_HA"; break;
            case 83: output = "R_PPC_GOT_TLSLD16"; break;
            case 84: output = "R_PPC_GOT_TLSLD16_LO"; break;
            case 85: output = "R_PPC_GOT_TLSLD16_HI"; break;
            case 86: output = "R_PPC_GOT_TLSLD16_HA"; break;
            case 87: output = "R_PPC_GOT_TPREL16"; break;
            case 88: output = "R_PPC_GOT_TPREL16_LO"; break;
            case 89: output = "R_PPC_GOT_TPREL16_HI"; break;
            case 90: output = "R_PPC_GOT_TPREL16_HA"; break;
            case 91: output = "R_PPC_GOT_DTPREL16"; break;
            case 92: output = "R_PPC_GOT_DTPREL16_LO"; break;
            case 93: output = "R_PPC_GOT_DTPREL16_HI"; break;
            case 94: output = "R_PPC_GOT_DTPREL16_HA"; break;

                /* The remaining relocs are from the Embedded ELF ABI, and are not
                   in the SVR4 ELF ABI.  */
            case 101: output = "R_PPC_EMB_NADDR32"; break;
            case 102: output = "R_PPC_EMB_NADDR16"; break;
            case 103: output = "R_PPC_EMB_NADDR16_LO"; break;
            case 104: output = "R_PPC_EMB_NADDR16_HI"; break;
            case 105: output = "R_PPC_EMB_NADDR16_HA"; break;
            case 106: output = "R_PPC_EMB_SDAI16"; break;
            case 107: output = "R_PPC_EMB_SDA2I16"; break;
            case 108: output = "R_PPC_EMB_SDA2REL"; break;
            case 109: output = "R_PPC_EMB_SDA21"; break;
            case 110: output = "R_PPC_EMB_MRKREF"; break;
            case 111: output = "R_PPC_EMB_RELSEC16"; break;
            case 112: output = "R_PPC_EMB_RELST_LO"; break;
            case 113: output = "R_PPC_EMB_RELST_HI"; break;
            case 114: output = "R_PPC_EMB_RELST_HA"; break;
            case 115: output = "R_PPC_EMB_BIT_FLD"; break;
            case 116: output = "R_PPC_EMB_RELSDA"; break;

                /* These are GNU extensions to enable C++ vtable garbage collection.  */
            case 253: output = "R_PPC_GNU_VTINHERIT"; break;
            case 254: output = "R_PPC_GNU_VTENTRY"; break;

                /* This is a phony reloc to handle any old fashioned TOC16 references
                   that may still be in object files.  */
            case 255: output = "R_PPC_TOC16"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown ppc relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_ppc::get_Type" );
#endif /* LIBREVERSE_DEBUG */

    
        return output;
    }


    inline bool
    Elf_ppc::is_PPC_TLS_Reloc (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_ppc::is_PPC_TLS_Reloc" );
#endif /* LIBREVERSE_DEBUG */


        return ((type >= 67) && (type <= 94));
    }

} /* namespace elf_module */
} /* namespace libreverse */
