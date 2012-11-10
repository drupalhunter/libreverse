/*  Elf_Program_Header_64.h

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

#ifndef ELF_PROGRAM_HEADER_64_H
#define ELF_PROGRAM_HEADER_64_H

#include "io/input/File_Readers/Base_Header.h"
#include "io/IO_Types.h"
#include <string>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Program_Header_64
     * \date 2003
     * \author Stephen Torri
     *
     * (Elf) = Executable and Linkable Format specification
     */
    class Elf_Program_Header_64 : public header::Base_Header {

        friend class Elf_File;

    public:

        /*!
         * \brief Constructor
         * \param e_machine Target architecture
         */
        Elf_Program_Header_64 ( boost::uint16_t e_machine );

        /*!
         * \brief Convert the bit order of the stored data if host and
         * data endian types differ
         */
        virtual void convert ();

        /*!
         * \brief Return the data of this header in a format style
         * \return String representation of data
         * The format style was taken from the readelf source code
         */
        std::string to_String (void) const;

        /*!
         * \brief Get the human readable strings from the header
         * \return String output of header
         */
        void get_Text_String ( io_types::Text_Data::data_type* output );

        boost::uint32_t get_Type ( void ) const;

        /*! \brief If the address for a data is contained within this
          program header we return TRUE. Otherwise FALSE.
        */
        bool in_Range ( boost::uint64_t addr ) const;

        /*! \brief Get result of p_vaddr - p_offset */
        boost::uint64_t get_Address_Offset (void) const;

        boost::uint64_t get_Virtual_Address (void) const;

    private:

        /*!
         * \brief This member tells what kind of segment this array element
         * described or how to interpret the array element's
         * information. Type values and their meanings appear below. (Elf)
         */
        boost::uint32_t p_type;

        /*!
         * \brief This member gives the offset from the beginning of the
         * file at which the first byte of the segment resides. (Elf)
         */
        boost::uint64_t p_offset;

        /*!
         * \brief This member gives the virtual address at which the first
         * byte of the segment resides in memory.
         */
        boost::uint64_t p_vaddr;

        /*!
         * \brief On systems for which physical addressing is relevant, this
         * member is reserved for the segment's physical address. Because
         * System V ignores physical addressing for application programs,
         * this member has unspecified contents for executable files and
         * shared objects. (Elf)
         */
        boost::uint64_t p_paddr;

        /*!
         * \brief This member gives the number of bytes in the file image of
         * the segment; it may be zero. (Elf)
         */
        boost::uint64_t p_filesz;

        /*!
         * \brief This member gives the number of bytes in the memory image
         * of the segment; it may be zero. (Elf)
         */
        boost::uint64_t p_memsz;

        /*!
         * \brief This member gives the flags relevant to the segment. (Elf)
         */
        boost::uint64_t p_flags;

        /*!
         * \brief This member gives the value to which the segments are
         * aligned in memory and in the file. Values 0 and 1 mean no
         * alignment is required. Otherwise, p_align should be positive,
         * integral power of 2, and p_vaddr should equal p_offset modulo
         * p_align. (Elf)
         */
        boost::uint64_t p_align;

        //----------------------------------------
        //      ELF HEADER helper variables
        //----------------------------------------

        /*! \brief Machine architecture */
        boost::uint16_t m_e_machine;

    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_PROGRAM_HEADER_64_H */
