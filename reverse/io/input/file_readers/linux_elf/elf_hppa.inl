#include <reverse/io/input/file_readers/linux_elf/elf_hppa.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  inline std::string
	  elf_hppa::get_type (boost::uint32_t const type)
	  {
	    trace::io_detail ( "Entering Elf_hppa::get_Type" );

	    std::string output = "";

	    switch (type)
	      {
                /* No reloc */
	      case 0: output = "R_PARISC_NONE"; break;

                /*32-bit word symbol + addend*/
	      case 1: output = "R_PARISC_DIR32"; break;

                /*long immediate (7) LR(symbol, addend) */
	      case 2: output = "R_PARISC_DIR21L"; break;

                /*branch external (19) RR(symbol, addend) */
	      case 3: output = "R_PARISC_DIR17R"; break;

                /*branch external (19) symbol + addend*/
	      case 4: output = "R_PARISC_DIR17F"; break;

                /*load/store (1) RR(symbol, addend) */
	      case 6: output = "R_PARISC_DIR14R"; break;

                /*load/store (1) symbol, addend */
	      case 7: output = "R_PARISC_DIR14F"; break;

                /* PC-relative relocation types
                   Typically used for calls.
                   Note PCREL17C and PCREL17F differ only in overflow handling.
                   PCREL17C never reports a relocation error.

                   When supporting argument relocations, function calls must be
                   accompanied by parameter relocation information.This information is
                   carried in the ten high-order bits of the addend field.The remaining
                   22 bits of of the addend field are sign-extended to form the Addend.

                   Note the code to build argument relocations depends on the
                   addend being zero.A consequence of this limitation is GAS
                   can not perform relocation reductions for function symbols.*/

                /*op & branch (17) symbol - PC - 8 + addend*/
	      case 8: output = "R_PARISC_PCREL12F"; break;

                /*32-bit word symbol - PC - 8 + addend*/
	      case 9: output = "R_PARISC_PCREL32"; break;

                /*long immediate (7) L(symbol - PC - 8 + addend) */
	      case 10: output = "R_PARISC_PCREL21L"; break;

                /*branch external (19) R(symbol - PC - 8 + addend) */
	      case 11: output = "R_PARISC_PCREL17R"; break;

                /*branch (20) symbol - PC - 8 + addend*/
	      case 12: output = "R_PARISC_PCREL17F"; break;

                /*branch (20) symbol - PC - 8 + addend*/
	      case 13: output = "R_PARISC_PCREL17C"; break;

                /*load/store (1) R(symbol - PC - 8 + addend) */
	      case 14: output = "R_PARISC_PCREL14R"; break;

                /*load/store (1) symbol - PC - 8 + addend*/
	      case 15: output = "R_PARISC_PCREL14F"; break;


                /* DP-relative relocation types.*/
                /*long immediate (7) LR(symbol - GP, addend)*/
	      case 18: output = "R_PARISC_DPREL21L"; break;

                /*load/store mod. comp. (2)RR(symbol - GP, addend)*/
	      case 19: output = "R_PARISC_DPREL14WR"; break;

                /*load/store doubleword (3)RR(symbol - GP, addend)*/
	      case 20: output = "R_PARISC_DPREL14DR"; break;

                /*load/store (1) RR(symbol - GP, addend)*/
	      case 22: output = "R_PARISC_DPREL14R"; break;

                /*load/store (1) symbol - GP + addend */
	      case 23: output = "R_PARISC_DPREL14F"; break;


                /* Data linkage table (DLT) relocation types

		   SOM DLT_REL fixup requests are used to for static data references
		   from position-independent code within shared libraries.They are
		   similar to the GOT relocation types in some SVR4 implementations.*/

                /*long immediate (7) LR(symbol - GP, addend) */
	      case 26: output = "R_PARISC_DLTREL21L"; break;

                /*load/store (1) RR(symbol - GP, addend) */
	      case 30: output = "R_PARISC_DLTREL14R"; break;

                /*load/store (1) symbol - GP + addend*/
	      case 31: output = "R_PARISC_DLTREL14F"; break;


                /* DLT indirect relocation types*/
                /*long immediate (7) L(ltoff(symbol + addend)) */
	      case 34: output = "R_PARISC_DLTIND21L"; break;

                /*load/store (1) R(ltoff(symbol + addend)) */
	      case 38: output = "R_PARISC_DLTIND14R"; break;

                /*load/store (1) ltoff(symbol + addend)*/
	      case 39: output = "R_PARISC_DLTIND14F"; break;


                /* Base relative relocation types.Ugh.These imply lots of state */
                /*none no reloc; base := sym */
	      case 40: output = "R_PARISC_SETBASE"; break;

                /*32-bit wordsymbol - SECT + addend*/
	      case 41: output = "R_PARISC_SECREL32"; break;

                /*long immediate (7) LR(symbol - base, addend) */
	      case 42: output = "R_PARISC_BASEREL21L"; break;

                /*branch external (19) RR(symbol - base, addend) */
	      case 43: output = "R_PARISC_BASEREL17R"; break;

                /*branch external (19) symbol - base + addend*/
	      case 44: output = "R_PARISC_BASEREL17F"; break;

                /*load/store (1) RR(symbol - base, addend) */
	      case 46: output = "R_PARISC_BASEREL14R"; break;

                /*load/store (1) symbol - base, addend */
	      case 47: output = "R_PARISC_BASEREL14F"; break;


                /* Segment relative relocation types.*/
                /*none no relocation; SB := sym*/
	      case 48: output = "R_PARISC_SEGBASE"; break;

                /*32-bit wordsymbol - SB + addend */
	      case 49: output = "R_PARISC_SEGREL32"; break;


                /* Offsets from the PLT.*/
                /*long immediate (7) LR(pltoff(symbol), addend) */
	      case 50: output = "R_PARISC_PLTOFF21L"; break;

                /*load/store (1) RR(pltoff(symbol), addend) */
	      case 54: output = "R_PARISC_PLTOFF14R"; break;

                /*load/store (1) pltoff(symbol) + addend*/
	      case 55: output = "R_PARISC_PLTOFF14F"; break;


                /*32-bit wordltoff(fptr(symbol+addend)) */
	      case 57: output = "R_PARISC_LTOFF_FPTR32"; break;

                /*long immediate (7) L(ltoff(fptr(symbol+addend)))*/
	      case 58: output = "R_PARISC_LTOFF_FPTR21L"; break;

                /*load/store (1) R(ltoff(fptr(symbol+addend)))*/
	      case 62: output = "R_PARISC_LTOFF_FPTR14R"; break;


                /*64-bit doublewordfptr(symbol+addend) */
	      case 64: output = "R_PARISC_FPTR64"; break;


                /* Plabel relocation types.*/ 
                /*32-bit word fptr(symbol) */
	      case 65: output = "R_PARISC_PLABEL32"; break;

                /*long immediate (7) L(fptr(symbol))*/
	      case 66: output = "R_PARISC_PLABEL21L"; break;

                /*load/store (1) R(fptr(symbol))*/
	      case 70: output = "R_PARISC_PLABEL14R"; break;


                /* PCREL relocations.*/
                /*64-bit doublewordsymbol - PC - 8 + addend */
	      case 72: output = "R_PARISC_PCREL64"; break;

                /*branch & link (21) symbol - PC - 8 + addend */
	      case 73: output = "R_PARISC_PCREL22C"; break;

                /*branch & link (21) symbol - PC - 8 + addend */
	      case 74: output = "R_PARISC_PCREL22F"; break;

                /*load/store mod. comp. (2)R(symbol - PC - 8 + addend)*/
	      case 75: output = "R_PARISC_PCREL14WR"; break;

                /*load/store doubleword (3)R(symbol - PC - 8 + addend)*/
	      case 76: output = "R_PARISC_PCREL14DR"; break;

                /*load/store (1) symbol - PC - 8 + addend */
	      case 77: output = "R_PARISC_PCREL16F"; break;

                /*load/store mod. comp. (2)symbol - PC - 8 + addend */
	      case 78: output = "R_PARISC_PCREL16WF"; break;

                /*load/store doubleword (3)symbol - PC - 8 + addend */
	      case 79: output = "R_PARISC_PCREL16DF"; break;


                /*64-bit doublewordsymbol + addend*/
	      case 80: output = "R_PARISC_DIR64"; break;

                /*64-bit doublewordRR(symbol, addend) */
	      case 81: output = "R_PARISC_DIR64WR"; break;

                /*64-bit doublewordRR(symbol, addend) */
	      case 82: output = "R_PARISC_DIR64DR"; break;

                /*load/store mod. comp. (2)RR(symbol, addend) */
	      case 83: output = "R_PARISC_DIR14WR"; break;

                /*load/store doubleword (3)RR(symbol, addend) */
	      case 84: output = "R_PARISC_DIR14DR"; break;

                /*load/store (1) symbol + addend*/
	      case 85: output = "R_PARISC_DIR16F"; break;

                /*load/store mod. comp. (2)symbol + addend*/
	      case 86: output = "R_PARISC_DIR16WF"; break;

                /*load/store doubleword (3)symbol + addend*/
	      case 87: output = "R_PARISC_DIR16DF"; break;

                /*64-bit doublewordsymbol - GP + addend */
	      case 88: output = "R_PARISC_GPREL64"; break;

                /*load/store mod. comp. (2)RR(symbol - GP, addend) */
	      case 91: output = "R_PARISC_DLTREL14WR"; break;

                /*load/store doubleword (3)RR(symbol - GP, addend) */
	      case 92: output = "R_PARISC_DLTREL14DR"; break;

                /*load/store (1) symbol - GP + addend*/
	      case 93: output = "R_PARISC_GPREL16F"; break;

                /*load/store mod. comp. (2)symbol - GP + addend*/
	      case 94: output = "R_PARISC_GPREL16WF"; break;

                /*load/store doubleword (3)symbol - GP + addend*/
	      case 95: output = "R_PARISC_GPREL16DF"; break;


                /*64-bit doublewordltoff(symbol + addend)*/
	      case 96: output = "R_PARISC_LTOFF64"; break;

                /*load/store mod. comp. (2)R(ltoff(symbol + addend)) */
	      case 99: output = "R_PARISC_DLTIND14WR"; break;

                /*load/store doubleword (3)R(ltoff(symbol + addend)) */
	      case 100: output = "R_PARISC_DLTIND14DR"; break;

                /*load/store (1) ltoff(symbol + addend)*/
	      case 101: output = "R_PARISC_LTOFF16F"; break;

                /*load/store mod. comp. (2)ltoff(symbol + addend)*/
	      case 102: output = "R_PARISC_LTOFF16WF"; break;

                /*load/store doubleword (3)ltoff(symbol + addend)*/
	      case 103: output = "R_PARISC_LTOFF16DF"; break;


                /*64-bit doublewordsymbol - SECT + addend */
	      case 104: output = "R_PARISC_SECREL64"; break;

                /*load/store mod. comp. (2)RR(symbol - base, addend) */
	      case 107: output = "R_PARISC_BASEREL14WR"; break;

                /*load/store doubleword (3)RR(symbol - base, addend) */
	      case 108: output = "R_PARISC_BASEREL14DR"; break;


                /*64-bit doublewordsymbol - SB + addend */
	      case 112: output = "R_PARISC_SEGREL64"; break;

                /*load/store mod. comp. (2)RR(pltoff(symbol), addend) */
	      case 115: output = "R_PARISC_PLTOFF14WR"; break;

                /*load/store doubleword (3)RR(pltoff(symbol), addend) */
	      case 116: output = "R_PARISC_PLTOFF14DR"; break;

                /*load/store (1) pltoff(symbol) + addend*/
	      case 117: output = "R_PARISC_PLTOFF16F"; break;

                /*load/store mod. comp. (2)pltoff(symbol) + addend*/
	      case 118: output = "R_PARISC_PLTOFF16WF"; break;

                /*load/store doubleword (3)pltoff(symbol) + addend*/
	      case 119: output = "R_PARISC_PLTOFF16DF"; break;


                /*64-bit doublewordltoff(fptr(symbol+addend)) */
	      case 120: output = "R_PARISC_LTOFF_FPTR64"; break;

                /*load/store mod. comp. (2)R(ltoff(fptr(symbol+addend)))*/
	      case 123: output = "R_PARISC_LTOFF_FPTR14WR"; break;

                /*load/store doubleword (3)R(ltoff(fptr(symbol+addend)))*/
	      case 124: output = "R_PARISC_LTOFF_FPTR14DR"; break;

                /*load/store (1) ltoff(fptr(symbol+addend)) */
	      case 125: output = "R_PARISC_LTOFF_FPTR16F"; break;

                /*load/store mod. comp. (2)ltoff(fptr(symbol+addend)) */
	      case 126: output = "R_PARISC_LTOFF_FPTR16WF"; break;

                /*load/store doubleword (3)ltoff(fptr(symbol+addend)) */
	      case 127: output = "R_PARISC_LTOFF_FPTR16DF"; break;


                /*data Dynamic relocations only */
	      case 128: output = "R_PARISC_COPY"; break;

                /*plt */
	      case 129: output = "R_PARISC_IPLT"; break;

                /*plt */
	      case 130: output = "R_PARISC_EPLT"; break;


                /*32-bit wordsymbol - TP + addend*/
	      case 153: output = "R_PARISC_TPREL32"; break;

                /*long immediate (7) LR(symbol - TP, addend) */
	      case 154: output = "R_PARISC_TPREL21L"; break;

                /*load/store (1) RR(symbol - TP, addend) */
	      case 158: output = "R_PARISC_TPREL14R"; break;


                /*long immediate (7) L(ltoff(symbol - TP + addend)) */
	      case 162: output = "R_PARISC_LTOFF_TP21L"; break;

                /*load/store (1) R(ltoff(symbol - TP + addend)) */
	      case 166: output = "R_PARISC_LTOFF_TP14R"; break;

                /*load/store (1) ltoff(symbol - TP + addend)*/
	      case 167: output = "R_PARISC_LTOFF_TP14F"; break;


                /*64-bit wordsymbol - TP + addend*/
	      case 216: output = "R_PARISC_TPREL64"; break;

                /*load/store mod. comp. (2)RR(symbol - TP, addend) */
	      case 219: output = "R_PARISC_TPREL14WR"; break;

                /*load/store doubleword (3)RR(symbol - TP, addend) */
	      case 220: output = "R_PARISC_TPREL14DR"; break;

                /*load/store (1) symbol - TP + addend*/
	      case 221: output = "R_PARISC_TPREL16F"; break;

                /*load/store mod. comp. (2)symbol - TP + addend*/
	      case 222: output = "R_PARISC_TPREL16WF"; break;

                /*load/store doubleword (3)symbol - TP + addend*/
	      case 223: output = "R_PARISC_TPREL16DF"; break;


                /*64-bit doublewordltoff(symbol - TP + addend)*/
	      case 224: output = "R_PARISC_LTOFF_TP64"; break;

                /*load/store mod. comp. (2)R(ltoff(symbol - TP + addend)) */
	      case 227: output = "R_PARISC_LTOFF_TP14WR"; break;

                /*load/store doubleword (3)R(ltoff(symbol - TP + addend)) */
	      case 228: output = "R_PARISC_LTOFF_TP14DR"; break;

                /*load/store (1) ltoff(symbol - TP + addend)*/
	      case 229: output = "R_PARISC_LTOFF_TP16F"; break;

                /*load/store mod. comp. (2)ltoff(symbol - TP + addend)*/
	      case 230: output = "R_PARISC_LTOFF_TP16WF"; break;

                /*load/store doubleword (3)ltoff(symbol - TP + addend)*/
	      case 231: output = "R_PARISC_LTOFF_TP16DF"; break;

	      case 232: output = "R_PARISC_GNU_VTENTRY"; break;
	      case 233: output = "R_PARISC_GNU_VTINHERIT"; break;

	      default:
                {

		  trace::io_error ( "Unknown hppa relocation type: %1%", type );

		  output = "unknown";

                }

	      }

	    trace::io_detail ( "Exiting Elf_hppa::get_Type" );

	    return output;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

