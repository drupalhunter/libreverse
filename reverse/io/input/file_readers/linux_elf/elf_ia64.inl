#include "Elf_ia64.h"

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    inline std::string
    Elf_ia64::get_Type (boost::uint32_t type)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_ia64::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        std::string output = "";

        switch (type)
            {
                /* none */
            case 0x00: output = "R_IA64_NONE"; break;

                /* symbol + addend, add imm14 */
            case 0x21: output = "R_IA64_IMM14"; break;

                /* symbol + addend, add imm22 */
            case 0x22: output = "R_IA64_IMM22"; break;

                /* symbol + addend, mov imm64 */
            case 0x23: output = "R_IA64_IMM64"; break;

                /* symbol + addend, data4 MSB */
            case 0x24: output = "R_IA64_DIR32MSB"; break;

                /* symbol + addend, data4 LSB */
            case 0x25: output = "R_IA64_DIR32LSB"; break;

                /* symbol + addend, data8 MSB */
            case 0x26: output = "R_IA64_DIR64MSB"; break;

                /* symbol + addend, data8 LSB */
            case 0x27: output = "R_IA64_DIR64LSB"; break;

                /* @gprel(sym+add), add imm22 */
            case 0x2a: output = "R_IA64_GPREL22"; break;
                /* @gprel(sym+add), mov imm64 */
            case 0x2b: output = "R_IA64_GPREL64I"; break;
                /* @gprel(sym+add), data4 MSB */
            case 0x2c: output = "R_IA64_GPREL32MSB"; break;
                /* @gprel(sym+add), data4 LSB */
            case 0x2d: output = "R_IA64_GPREL32LSB"; break;
                /* @gprel(sym+add), data8 MSB */
            case 0x2e: output = "R_IA64_GPREL64MSB"; break;
                /* @gprel(sym+add), data8 LSB */
            case 0x2f: output = "R_IA64_GPREL64LSB"; break;

                /* @ltoff(sym+add), add imm22 */
            case 0x32: output = "R_IA64_LTOFF22"; break;
                /* @ltoff(sym+add), mov imm64 */
            case 0x33: output = "R_IA64_LTOFF64I"; break;

                /* @pltoff(sym+add), add imm22 */
            case 0x3a: output = "R_IA64_PLTOFF22"; break;
                /* @pltoff(sym+add), mov imm64 */
            case 0x3b: output = "R_IA64_PLTOFF64I"; break;
                /* @pltoff(sym+add), data8 MSB */
            case 0x3e: output = "R_IA64_PLTOFF64MSB"; break;
                /* @pltoff(sym+add), data8 LSB */
            case 0x3f: output = "R_IA64_PLTOFF64LSB"; break;

                /* @fptr(sym+add), mov imm64 */
            case 0x43: output = "R_IA64_FPTR64I"; break;
                /* @fptr(sym+add), data4 MSB */
            case 0x44: output = "R_IA64_FPTR32MSB"; break;
                /* @fptr(sym+add), data4 LSB */
            case 0x45: output = "R_IA64_FPTR32LSB"; break;
                /* @fptr(sym+add), data8 MSB */
            case 0x46: output = "R_IA64_FPTR64MSB"; break;
                /* @fptr(sym+add), data8 LSB */
            case 0x47: output = "R_IA64_FPTR64LSB"; break;

                /* @pcrel(sym+add), brl */
            case 0x48: output = "R_IA64_PCREL60B"; break;
                /* @pcrel(sym+add), ptb, call */
            case 0x49: output = "R_IA64_PCREL21B"; break;
                /* @pcrel(sym+add), chk.s */
            case 0x4a: output = "R_IA64_PCREL21M"; break;
                /* @pcrel(sym+add), fchkf */
            case 0x4b: output = "R_IA64_PCREL21F"; break;
                /* @pcrel(sym+add), data4 MSB */
            case 0x4c: output = "R_IA64_PCREL32MSB"; break;
                /* @pcrel(sym+add), data4 LSB */
            case 0x4d: output = "R_IA64_PCREL32LSB"; break;
                /* @pcrel(sym+add), data8 MSB */
            case 0x4e: output = "R_IA64_PCREL64MSB"; break;
                /* @pcrel(sym+add), data8 LSB */
            case 0x4f: output = "R_IA64_PCREL64LSB"; break;

                /* @ltoff(@fptr(s+a)), imm22 */
            case 0x52: output = "R_IA64_LTOFF_FPTR22"; break;
                /* @ltoff(@fptr(s+a)), imm64 */
            case 0x53: output = "R_IA64_LTOFF_FPTR64I"; break;
                /* @ltoff(@fptr(s+a)), 4 MSB */
            case 0x54: output = "R_IA64_LTOFF_FPTR32MSB"; break;
                /* @ltoff(@fptr(s+a)), 4 LSB */
            case 0x55: output = "R_IA64_LTOFF_FPTR32LSB"; break;
                /* @ltoff(@fptr(s+a)), 8 MSB */
            case 0x56: output = "R_IA64_LTOFF_FPTR64MSB"; break;
                /* @ltoff(@fptr(s+a)), 8 LSB */
            case 0x57: output = "R_IA64_LTOFF_FPTR64LSB"; break;

                /* @segrel(sym+add), data4 MSB */
            case 0x5c: output = "R_IA64_SEGREL32MSB"; break;
                /* @segrel(sym+add), data4 LSB */
            case 0x5d: output = "R_IA64_SEGREL32LSB"; break;
                /* @segrel(sym+add), data8 MSB */
            case 0x5e: output = "R_IA64_SEGREL64MSB"; break;
                /* @segrel(sym+add), data8 LSB */
            case 0x5f: output = "R_IA64_SEGREL64LSB"; break;

                /* @secrel(sym+add), data4 MSB */
            case 0x64: output = "R_IA64_SECREL32MSB"; break;
                /* @secrel(sym+add), data4 LSB */
            case 0x65: output = "R_IA64_SECREL32LSB"; break;
                /* @secrel(sym+add), data8 MSB */
            case 0x66: output = "R_IA64_SECREL64MSB"; break;
                /* @secrel(sym+add), data8 LSB */
            case 0x67: output = "R_IA64_SECREL64LSB"; break;

                /* data 4 + REL */
            case 0x6c: output = "R_IA64_REL32MSB"; break;
                /* data 4 + REL */
            case 0x6d: output = "R_IA64_REL32LSB"; break;
                /* data 8 + REL */
            case 0x6e: output = "R_IA64_REL64MSB"; break;
                /* data 8 + REL */
            case 0x6f: output = "R_IA64_REL64LSB"; break;

                /* symbol + addend, data4 MSB */
            case 0x74: output = "R_IA64_LTV32MSB"; break;
                /* symbol + addend, data4 LSB */
            case 0x75: output = "R_IA64_LTV32LSB"; break;
                /* symbol + addend, data8 MSB */
            case 0x76: output = "R_IA64_LTV64MSB"; break;
                /* symbol + addend, data8 LSB */
            case 0x77: output = "R_IA64_LTV64LSB"; break;

                /* @pcrel(sym+add), ptb, call */
            case 0x79: output = "R_IA64_PCREL21BI"; break;
                /* @pcrel(sym+add), imm22 */
            case 0x7a: output = "R_IA64_PCREL22"; break;
                /* @pcrel(sym+add), imm64 */
            case 0x7b: output = "R_IA64_PCREL64I"; break;

                /* dynamic reloc, imported PLT, MSB */
            case 0x80: output = "R_IA64_IPLTMSB"; break;
                /* dynamic reloc, imported PLT, LSB */
            case 0x81: output = "R_IA64_IPLTLSB"; break;
                /* dynamic reloc, data copy */
            case 0x84: output = "R_IA64_COPY"; break;
                /* LTOFF22, relaxable.  */
            case 0x86: output = "R_IA64_LTOFF22X"; break;
                /* Use of LTOFF22X.  */
            case 0x87: output = "R_IA64_LDXMOV"; break;

                /* @tprel(sym+add), add imm14 */
            case 0x91: output = "R_IA64_TPREL14"; break;
                /* @tprel(sym+add), add imm22 */
            case 0x92: output = "R_IA64_TPREL22"; break;
                /* @tprel(sym+add), add imm64 */
            case 0x93: output = "R_IA64_TPREL64I"; break;
                /* @tprel(sym+add), data8 MSB */
            case 0x96: output = "R_IA64_TPREL64MSB"; break;
                /* @tprel(sym+add), data8 LSB */
            case 0x97: output = "R_IA64_TPREL64LSB"; break;

                /* @ltoff(@tprel(s+a)), add imm22 */
            case 0x9a: output = "R_IA64_LTOFF_TPREL22"; break;

                /* @dtpmod(sym+add), data8 MSB */
            case 0xa6: output = "R_IA64_DTPMOD64MSB"; break;
                /* @dtpmod(sym+add), data8 LSB */
            case 0xa7: output = "R_IA64_DTPMOD64LSB"; break;
                /* @ltoff(@dtpmod(s+a)), imm22 */
            case 0xaa: output = "R_IA64_LTOFF_DTPMOD22"; break;

                /* @dtprel(sym+add), imm14 */
            case 0xb1: output = "R_IA64_DTPREL14"; break;
                /* @dtprel(sym+add), imm22 */
            case 0xb2: output = "R_IA64_DTPREL22"; break;
                /* @dtprel(sym+add), imm64 */
            case 0xb3: output = "R_IA64_DTPREL64I"; break;
                /* @dtprel(sym+add), data4 MSB */
            case 0xb4: output = "R_IA64_DTPREL32MSB"; break;
                /* @dtprel(sym+add), data4 LSB */
            case 0xb5: output = "R_IA64_DTPREL32LSB"; break;
                /* @dtprel(sym+add), data8 MSB */
            case 0xb6: output = "R_IA64_DTPREL64MSB"; break;
                /* @dtprel(sym+add), data8 LSB */
            case 0xb7: output = "R_IA64_DTPREL64LSB"; break;

                /* @ltoff(@dtprel(s+a)), imm22 */
            case 0xba: output = "R_IA64_LTOFF_DTPREL22"; break;

                // This one is odd since it has the value as the same as the
                // R_IA64_LTOFF_DTPREL22
                //FAKE_RELOC (R_IA64_MAX_RELOC_CODE, 0xba)
            default:
                {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::ERROR,
			     boost::str ( boost::format ( "Unknown ia64 type: %1%" ) % type ) );
#endif /* LIBREVERSE_DEBUG */

                    output = "unknown";
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_ia64::get_Type" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }
} /* namespace elf_module */
} /* namespace libreverse */
