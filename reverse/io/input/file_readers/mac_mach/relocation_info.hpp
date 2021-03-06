/*  Relocation_Info.h

   Copyright (C) 2008 Stephen Torri

   This file is part of Libreverse.

   Libreverse is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   Libreverse is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

#ifndef RELOCATION_INFO_H
#define RELOCATION_INFO_H

#include <boost/cstdint.hpp>

namespace reverse { namespace mach_module {

  class Relocation_Info {
  public:

    /*! Default Constructor */
    Relocation_Info();

  private:

    /*! \brief In MH_OBJECT files, this is an offset from the start of the section to the item containing the
     *         address requiring relocation. If the high bit of this field is set (which you can check using the
     *         R_SCATTERED bit mask), the relocation_info structure is actually a scattered_relocation_info (page 54) structure.
     *
     *         In images used by the dynamic linker, this is an offset from the virtual memory address of the
     *         data of the first segment_command (page 20) that appears in the file (not necessarily the one
     *         with the lowest address). For images with the MH_SPLIT_SEGS flag set, this is an offset from
     *         the virtual memory address of data of the first read/write segment_command (page 20).
     */
    boost::uint32_t m_r_address;

    /*! \brief Indicates either an index into the symbol table (when the r_extern field is set to 1) or a section
     *         number (when the r_extern field is set to 0). As previously mentioned, sections are ordered
     *         from 1 to 255 in the order in which they appear in the LC_SEGMENT load commands. This field
     *         is set to R_ABS for relocation entries for absolute symbols, which need no relocation.
     */
    boost::uint32_t m_r_symbolnum;

    /*! \brief Indicates whether the item containing the address to be relocated is part of a CPU instruction
     *         that uses PC-relative addressing.
     *
     *         For addresses contained in PC-relative instructions, the CPU adds the address of the instruction
     *         to the address contained in the instruction.
     */
    bool m_r_pcrel;

    /*! \brief Indicates the length of the item containing the address to be relocated. The following table lists
     *         r_length values and the corresponding address length.
     *
     * Value    Address length
     *   0        1 byte
     *   1        2 bytes
     *   2        4 bytes
     *   3        4 bytes. See description for the PPC_RELOC_BR14 r_type in scattered_relocation_info (page 54).
     */
    boost::uint8_t m_r_length;

    /*! \brief Indicates whether the r_symbolnum field is an index into the symbol table (1) or a section
     *         number (0).
     */
    bool m_r_extern;

    /*! \brief For the x86 environment, the r_type field may contain any of these values:
     *
     * - GENERIC_RELOC_VANILLA—A generic relocation entry for both addresses contained in data
     *   and addresses contained in CPU instructions.
     * - GENERIC_RELOC_PAIR—The second relocation entry of a pair.
     * - GENERIC_RELOC_SECTDIFF—A relocation entry for an item that contains the difference of
     *   two section addresses. This is generally used for position-independent code generation.
     *   GENERIC_RELOC_SECTDIFF contains the address from which to subtract; it must be followed
     *   by a GENERIC_RELOC_PAIR containing the address to subtract.
     * - GENERIC_RELOC_LOCAL_SECTDIFF—Similar to GENERIC_RELOC_SECTDIFF except that this
     *   entry refers specifically to the address in this item. If the address is that of a globally visible
     *   coalesced symbol, this relocation entry does not change if the symbol is overridden. This
     *   is used to associate stack unwinding information with the object code this relocation entry
     *   describes.
     * - GENERIC_RELOC_PB_LA_PTR—A relocation entry for a prebound lazy pointer. This is always
     *   a scattered relocation entry. The r_value field contains the non-prebound value of the
     *   lazy pointer.
     *
     * For the x86-64 environment, the r_type field may contain any of these values:
     * - X86_64_RELOC_BRANCH—A CALL/JMP instruction with 32-bit displacement.
     * - X86_64_RELOC_GOT_LOAD—A MOVQ load of a GOT entry.
     * - X86_64_RELOC_GOT—Other GOT references.
     * - X86_64_RELOC_SIGNED—Signed 32-bit displacement.
     * - X86_64_RELOC_UNSIGNED—Absolute address.
     * - X86_64_RELOC_SUBTRACTOR—Must be followed by a X86_64_RELOC_UNSIGNED relocation.
     *
     * For PowerPC environments, the r_type field is usually PPC_RELOC_VANILLA for addresses
     * contained in data. Relocation entries for addresses contained in CPU instructions are described
     * by other r_type values:
     * - PPC_RELOC_PAIR—The second relocation entry of a pair. A PPC_RELOC_PAIR entry must
     *   follow each of the other relocation entry types, except for PPC_RELOC_VANILLA,
     *   PPC_RELOC_BR14, PPC_RELOC_BR24, and PPC_RELOC_PB_LA_PTR.
     * - PPC_RELOC_BR14—The instruction contains a 14-bit branch displacement. If the r_length
     *   is 3, the branch was statically predicted by setting or clearing the Y bit depending on the
     *   sign of the displacement or the opcode.
     * - PPC_RELOC_BR24—The instruction contains a 24-bit branch displacement.
     * - PPC_RELOC_HI16—The instruction contains the high 16 bits of a relocatable expression.
     *   The next relocation entry must be a PPC_RELOC_PAIR specifying the low 16 bits of the
     *   expression in the low 16 bits of the r_value field.
     * - PPC_RELOC_LO16—The instruction contains the low 16 bits of an address. The next relocation
     *   entry must be a PPC_RELOC_PAIR specifying the high 16 bits of the expression in the low
     *   (not the high) 16 bits of the r_value field.
     * - PPC_RELOC_HA16—Same as the PPC_RELOC_HI16 except the low 16 bits and the high 16
     *   bits are added together with the low 16 bits sign-extended first. This means if bit 15 of the
     *   low 16 bits is set, the high 16 bits stored in the instruction are adjusted.
     * - PPC_RELOC_LO14—Same as PPC_RELOC_LO16 except that the low 2 bits are not stored in
     *   the CPU instruction and are always 0. PPC_RELOC_LO14 is used in 64-bit load/store
     *   instructions.
     * - PPC_RELOC_SECTDIFF—A relocation entry for an item that contains the difference of two
     *   section addresses. This is generally used for position-independent code generation.
     * - PPC_RELOC_SECTDIFF contains the address from which to subtract; it must be followed by
     *   a PPC_RELOC_PAIR containing the section address to subtract.
     * - PPC_RELOC_LOCAL_SECTDIFF—Similar to PPC_RELOC_SECTDIFF except that this entry
     *   refers specifically to the address in this item. If the address is that of a globally visible
     *   coalesced symbol, this relocation entry does not change if the symbol is overridden. This
     *   is used to associate stack unwinding information with the object code this relocation entry
     *   describes
     * - PPC_RELOC_PB_LA_PTR—A relocation entry for a prebound lazy pointer. This is always a
     *   scattered relocation entry. The r_value field contains the non-prebound value of the lazy
     *   pointer.
     * - PPC_RELOC_HI16_SECTDIFF—Section difference form of PPC_RELOC_HI16.
     * - PPC_RELOC_LO16_SECTDIFF—Section difference form of PPC_RELOC_LO16.
     * - PPC_RELOC_HA16_SECTDIFF—Section difference form of PPC_RELOC_HA16.
     * - PPC_RELOC_JBSR—A relocation entry for the assembler synthetic opcode jbsr, which is
     *   a 24-bit branch-and-link instruction using a branch island. The branch displacement is
     *   assembled to the branch island address and the relocation entry indicates the actual target
     *   symbol. If the linker is able to make the branch reach the actual target symbol, it does.
     *   Otherwise, the branch is relocated to the branch island.
     * - PPC_RELOC_LO14_SECTDIFF—Section difference form of PPC_RELOC_LO14.
     */
    boost::uint8_t m_r_type;

  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* RELOCATION_INFO_H */
