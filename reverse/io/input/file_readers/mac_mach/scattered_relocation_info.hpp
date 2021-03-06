/*  Scattered_Relocation_Info.h

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

#ifndef SCATTERED_RELOCATION_INFO_H
#define SCATTERED_RELOCATION_INFO_H

#include <boost/cstdint.hpp>

namespace reverse
{
    namespace mach_module
    {

        class Scattered_Relocation_Info
        {
            public:

                /*! \brief Default Constructor */
                Scattered_Relocation_Info();

            private:

                /*! \brief If this bit is 0, this structure is actually a relocation_info (page 51) structure. */
                bool m_r_scattered;

                /*! \brief In MH_OBJECT files, this is an offset from the start of the section to the item containing the
                 *         address requiring relocation. If the high bit of this field is clear (which you can check using
                 *         the R_SCATTERED bit mask), this structure is actually a relocation_info (page 51) structure.
                 *
                 *         In images used by the dynamic linker, this is an offset from the virtual memory address of the
                 *         data of the first segment_command (page 20) that appears in the file (not necessarily the one
                 *         with the lowest address). For images with the MH_SPLIT_SEGS flag set, this is an offset from\
                 *         the virtual memory address of data of the first read/write segment_command (page 20).
                 *
                 *         Since this field is only 24 bits long, the offset in this field can never be larger than 0x00FFFFFF,
                 *         thus limiting the size of the relocatable contents of this image to 16 megabytes.
                 */
                boost::uint32_t m_r_address;

                /*! \brief Indicates whether the item containing the address to be relocated is part of a CPU instruction
                 *         that uses PC-relative addressing.
                 *
                 *         For addresses contained in PC-relative instructions, the CPU adds the address of the instruction
                 *         to the address contained in the instruction.
                 */
                bool m_r_pcrel;

                /*! \brief Indicates the length of the item containing the address to be relocated. A value of 0 indicates
                 *         a single byte; a value of 1 indicates a 2-byte address, and a value of 2 indicates a 4-byte address.
                 */
                boost::uint8_t m_r_length;

                /*! \brief Indicates the type of relocation to be performed. Possible values for this field are shared between
                 *         this structure and the relocation_info data structure; see the description of the r_type field
                 *         in the relocation_info (page 51) data structure for more details.
                 */
                boost::uint8_t m_r_type;

                /*! \brief The address of the relocatable expression for the item in the file that needs to be updated if the
                 *         address is changed. For relocatable expressions with the difference of two section addresses,
                 *         the address from which to subtract (in mathematical terms, the minuend) is contained in the
                 *         first relocation entry and the address to subtract (the subtrahend) is contained in the second
                 *         relocation entry.
                 */
                boost::uint32_t m_r_value;

        };

    } /* namespace mach_module */

} /* namespace reverse */


#endif /* SCATTERED_RELOCATION_INFO_H */
