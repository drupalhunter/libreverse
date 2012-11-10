/*  Elf_Relocation_64.h

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

#ifndef ELF_RELOCATION_64_H
#define ELF_RELOCATION_64_H

#include "Elf_Types.h"
#include "io/Type_Mapper.h"
#include "io/input/File_Readers/Base_Header.h"
#include <vector>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Relocation_64
     * \date 2003
     * \author Stephen Torri
     */
    class Elf_Relocation_64 : public header::Base_Header {

        friend class Elf_File;

    public:

        Elf_Relocation_64 ( elf_types::Elf_File_Header_64::const_ptr_t file_hdr );

        /*!
         * \brief Convert the bit ordering from the target file bit ordering
         * to the host system.
         */
        virtual void convert ();

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void) const;

        /*!
         * \brief Return type name
         * \return String representation of section header type
         */
        std::string get_Section_Type_Name (void) const;

        /*!
         * \brief Return the index of the associated symbol in the symbol
         * table
         *
         * \return Bit size of header
         */
        boost::uint64_t get_Symbol_Token_Index (void) const;

    private:

        /*!
         * \brief This member gives the location at which to apply the
         * relocation action. For a relocatable file, the value is the byte
         * offset from the beginning of the section to the storage unit
         * affected by the relocation. For an executable file or a shared
         * object, the value is the virtual address of the storage unit
         * affected by the relocation. (Elf)
         */
        boost::uint64_t r_offset;

        /*!
         * \brief This member gives both the symbol table index with respect
         * to which the relocation must be made, and the type of relocation
         * to apply. (Elf)
         */

        /*
          Comment take from readelf.c:

          In little-endian objects, r_info isn't really a 64-bit
          little-endian value: it has a 32-bit little-endian symbol index
          followed by four individual byte fields.  Reorder INFO
          accordingly.

          Note take from Executable and Linkable Format (ELF) manual:

          This member gives both the symbol table index with respect to
          which the relocation must be made, and the type of relocation to
          apply. For example, a call instruction's relocation entry would
          hold the symbol table index of the function being called. If the
          index is STN_UNDEF, the undefined symbol index, the relocation
          uses 0 as the symbol value.  Relocation types are
          processor-specific. When the text refers to a relocation entry s
          relocation type or symbol table index, it means the result of
          applying ELF32_R_TYPE or ELF32_R_SYM, respectively, to the entry
          s r_info member.
        */
        boost::uint64_t r_info;

        /********************
         * Helper variables
         ********************/
        boost::uint64_t m_symbol_table_index;

        boost::uint64_t m_reloc_type;

        /*!
         * \brief Keep track of the File Header
         */
        elf_types::Elf_File_Header_64::const_ptr_t m_file_hdr;

    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_RELOCATION_64_H */
