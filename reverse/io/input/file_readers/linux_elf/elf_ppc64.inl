#include "Elf_ppc64.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_ppc64::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_ppc64::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
            case 0: output = "R_PPC64_NONE"; break;
            case 1: output = "R_PPC64_ADDR32"; break;
            case 2: output = "R_PPC64_ADDR24"; break;
            case 3: output = "R_PPC64_ADDR16"; break;
            case 4: output = "R_PPC64_ADDR16_LO"; break;
            case 5: output = "R_PPC64_ADDR16_HI"; break;
            case 6: output = "R_PPC64_ADDR16_HA"; break;
            case 7: output = "R_PPC64_ADDR14"; break;
            case 8: output = "R_PPC64_ADDR14_BRTAKEN"; break;
            case 9: output = "R_PPC64_ADDR14_BRNTAKEN"; break;
            case 10: output = "R_PPC64_REL24"; break;
            case 11: output = "R_PPC64_REL14"; break;
            case 12: output = "R_PPC64_REL14_BRTAKEN"; break;
            case 13: output = "R_PPC64_REL14_BRNTAKEN"; break;
            case 14: output = "R_PPC64_GOT16"; break;
            case 15: output = "R_PPC64_GOT16_LO"; break;
            case 16: output = "R_PPC64_GOT16_HI"; break;
            case 17: output = "R_PPC64_GOT16_HA"; break;
                /* 18 unused.  32-bit reloc is R_PPC_PLTREL24.  */
            case 19: output = "R_PPC64_COPY"; break;
            case 20: output = "R_PPC64_GLOB_DAT"; break;
            case 21: output = "R_PPC64_JMP_SLOT"; break;
            case 22: output = "R_PPC64_RELATIVE"; break;
                /* 23 unused.  32-bit reloc is R_PPC_LOCAL24PC.  */
            case 24: output = "R_PPC64_UADDR32"; break;
            case 25: output = "R_PPC64_UADDR16"; break;
            case 26: output = "R_PPC64_REL32"; break;
            case 27: output = "R_PPC64_PLT32"; break;
            case 28: output = "R_PPC64_PLTREL32"; break;
            case 29: output = "R_PPC64_PLT16_LO"; break;
            case 30: output = "R_PPC64_PLT16_HI"; break;
            case 31: output = "R_PPC64_PLT16_HA"; break;
                /* 32 unused.  32-bit reloc is R_PPC_SDAREL16.  */
            case 33: output = "R_PPC64_SECTOFF"; break;
            case 34: output = "R_PPC64_SECTOFF_LO"; break;
            case 35: output = "R_PPC64_SECTOFF_HI"; break;
            case 36: output = "R_PPC64_SECTOFF_HA"; break;
            case 37: output = "R_PPC64_REL30"; break;
            case 38: output = "R_PPC64_ADDR64"; break;
            case 39: output = "R_PPC64_ADDR16_HIGHER"; break;
            case 40: output = "R_PPC64_ADDR16_HIGHERA"; break;
            case 41: output = "R_PPC64_ADDR16_HIGHEST"; break;
            case 42: output = "R_PPC64_ADDR16_HIGHESTA"; break;
            case 43: output = "R_PPC64_UADDR64"; break;
            case 44: output = "R_PPC64_REL64"; break;
            case 45: output = "R_PPC64_PLT64"; break;
            case 46: output = "R_PPC64_PLTREL64"; break;
            case 47: output = "R_PPC64_TOC16"; break;
            case 48: output = "R_PPC64_TOC16_LO"; break;
            case 49: output = "R_PPC64_TOC16_HI"; break;
            case 50: output = "R_PPC64_TOC16_HA"; break;
            case 51: output = "R_PPC64_TOC"; break;
            case 52: output = "R_PPC64_PLTGOT16"; break;
            case 53: output = "R_PPC64_PLTGOT16_LO"; break;
            case 54: output = "R_PPC64_PLTGOT16_HI"; break;
            case 55: output = "R_PPC64_PLTGOT16_HA"; break;

                /* The following relocs were added in the 64-bit PowerPC ELF ABI
                   revision 1.2. */
            case 56: output = "R_PPC64_ADDR16_DS"; break;
            case 57: output = "R_PPC64_ADDR16_LO_DS"; break;
            case 58: output = "R_PPC64_GOT16_DS"; break;
            case 59: output = "R_PPC64_GOT16_LO_DS"; break;
            case 60: output = "R_PPC64_PLT16_LO_DS"; break;
            case 61: output = "R_PPC64_SECTOFF_DS"; break;
            case 62: output = "R_PPC64_SECTOFF_LO_DS"; break;
            case 63: output = "R_PPC64_TOC16_DS"; break;
            case 64: output = "R_PPC64_TOC16_LO_DS"; break;
            case 65: output = "R_PPC64_PLTGOT16_DS"; break;
            case 66: output = "R_PPC64_PLTGOT16_LO_DS"; break;

                /* Relocs added to support TLS.  PowerPC64 ELF ABI revision 1.5.  */
            case 67: output = "R_PPC64_TLS"; break;
            case 68: output = "R_PPC64_DTPMOD64"; break;
            case 69: output = "R_PPC64_TPREL16"; break;
            case 70: output = "R_PPC64_TPREL16_LO"; break;
            case 71: output = "R_PPC64_TPREL16_HI"; break;
            case 72: output = "R_PPC64_TPREL16_HA"; break;
            case 73: output = "R_PPC64_TPREL64"; break;
            case 74: output = "R_PPC64_DTPREL16"; break;
            case 75: output = "R_PPC64_DTPREL16_LO"; break;
            case 76: output = "R_PPC64_DTPREL16_HI"; break;
            case 77: output = "R_PPC64_DTPREL16_HA"; break;
            case 78: output = "R_PPC64_DTPREL64"; break;
            case 79: output = "R_PPC64_GOT_TLSGD16"; break;
            case 80: output = "R_PPC64_GOT_TLSGD16_LO"; break;
            case 81: output = "R_PPC64_GOT_TLSGD16_HI"; break;
            case 82: output = "R_PPC64_GOT_TLSGD16_HA"; break;
            case 83: output = "R_PPC64_GOT_TLSLD16"; break;
            case 84: output = "R_PPC64_GOT_TLSLD16_LO"; break;
            case 85: output = "R_PPC64_GOT_TLSLD16_HI"; break;
            case 86: output = "R_PPC64_GOT_TLSLD16_HA"; break;
            case 87: output = "R_PPC64_GOT_TPREL16_DS"; break;
            case 88: output = "R_PPC64_GOT_TPREL16_LO_DS"; break;
            case 89: output = "R_PPC64_GOT_TPREL16_HI"; break;
            case 90: output = "R_PPC64_GOT_TPREL16_HA"; break;
            case 91: output = "R_PPC64_GOT_DTPREL16_DS"; break;
            case 92: output = "R_PPC64_GOT_DTPREL16_LO_DS"; break;
            case 93: output = "R_PPC64_GOT_DTPREL16_HI"; break;
            case 94: output = "R_PPC64_GOT_DTPREL16_HA"; break;
            case 95: output = "R_PPC64_TPREL16_DS"; break;
            case 96: output = "R_PPC64_TPREL16_LO_DS"; break;
            case 97: output = "R_PPC64_TPREL16_HIGHER"; break;
            case 98: output = "R_PPC64_TPREL16_HIGHERA"; break;
            case 99: output = "R_PPC64_TPREL16_HIGHEST"; break;
            case 100: output = "R_PPC64_TPREL16_HIGHESTA"; break;
            case 101: output = "R_PPC64_DTPREL16_DS"; break;
            case 102: output = "R_PPC64_DTPREL16_LO_DS"; break;
            case 103: output = "R_PPC64_DTPREL16_HIGHER"; break;
            case 104: output = "R_PPC64_DTPREL16_HIGHERA"; break;
            case 105: output = "R_PPC64_DTPREL16_HIGHEST"; break;
            case 106: output = "R_PPC64_DTPREL16_HIGHESTA"; break;

                /* These are GNU extensions to enable C++ vtable garbage collection.  */
            case 253: output = "R_PPC64_GNU_VTINHERIT"; break;
            case 254: output = "R_PPC64_GNU_VTENTRY"; break;
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown ppc64 relocation type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_ppc64::get_Type" );
#endif /* LIBREVERSE_DEBUG */

    
        return output;

    }

    inline bool Elf_ppc64::IS_PPC64_TLS_RELOC (boost::uint32_t value)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_ppc64::IS_PPC64_TLS_RELOC" );
#endif /* LIBREVERSE_DEBUG */


        return ((value >= 67) && (value <= 106));
    }

} /* namespace elf_module */
} /* namespace libreverse */
