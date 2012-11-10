/*  Elf_File_Header_64.h

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

#ifndef ELF_FILE_HEADER_64_H
#define ELF_FILE_HEADER_64_H

#include <string>
#include "Elf_Header_Eident.h"
#include "io/input/File_Readers/Base_Header.h"
#include "io/input/File_Readers/File_Reader.h"

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_File_Header_64
     * \date 2003
     * \author Stephen Torri
     *
     * A major thanks to Eric Youngdale and Nick Clifton for the nice readelf utility.
     * All functions take and modified from readelf are noted with a message in
     * their description.
     *
     * ----------------------------------------------------------------------------
     * readelf.c -- display contents of an ELF format file
     *  Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.
     *
     *  Originally developed by Eric Youngdale <eric@andante.jic.com>
     *   Modifications by Nick Clifton <nickc@redhat.com>
     *
     *  This file is part of GNU Binutils.
     *-----------------------------------------------------------------------------
     */
    class Elf_File_Header_64 : public libreverse::header::Base_Header {
    public:

        friend class Elf_File;

        /* Functions */

        /*!
         * \brief Default Constructor
         */
        Elf_File_Header_64();

        /*!
         * \brief Default Destructor
         */
        virtual ~Elf_File_Header_64();

        /*!
         * \brief Convert the bit order of the stored data if host and data
         * endian types differ
         */
        virtual void convert ();

        bool needs_Convert();

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void);

        /*!
         * \brief Find human reable strings in file header
         */
        virtual void get_Text_String ( io_types::Text_Data::data_type* output );

        std::string get_File_Type_Meta () const;

        /*!
         * \brief Returns the e_type value
         *
         * \return Value of target file type
         */
        boost::uint16_t get_File_Type_Value (void) const;

        /*!
         * \brief Returns the string representation of the cpu
         * architecutre of the target file (e_machine)
         *
         * \return String representation of the cpu architecture of the
         * target file
         *
         */
        std::string get_Arch_Type (void) const;

        boost::uint16_t get_Program_Header_Count (void) const;

        boost::uint64_t get_Program_Header_Offset(void) const;

        boost::uint16_t get_Section_Header_Count (void) const;

        boost::uint64_t get_Section_Header_Offset(void) const;

        boost::uint16_t get_Machine_Value (void) const;

        boost::uint16_t get_String_Token_Index (void) const;

        elf_types::Elf_Header_Eident::ptr_t get_Eident (void) const;

        boost::uint64_t get_Entry (void) const;

    private:

        /* Data */

        /*! \brief  ELF "magic number".
         *
         * The initial bytes mark the file as an object file and provide
         * machine-indepenedent data with which to decode and interpret the
         * file's contents.[ELF Format]
         */
        elf_types::Elf_Header_Eident::ptr_t e_ident;

        /*! \brief  Object file type */
        boost::uint16_t e_type;

        /*! \brief Required architecture for the file */
        boost::uint16_t e_machine;

        /*! \brief ELF version for the file */
        boost::uint32_t e_version;

        /*!
         * \brief This memeber gives the virtual address to which the system
         * first transfer control. If the file has no associated entry
         * point, this member holds zero. [Elf Format]
         */
        boost::uint64_t e_entry;

        /*! \brief  Program header table's file offset in bytes */
        boost::uint64_t e_phoff;

        /*! \brief  Section header table's file offset in bytes */
        boost::uint64_t e_shoff;

        /*! \brief  Processor-specific flags associated with the file */
        boost::uint32_t e_flags;

        /*! \brief  ELF header size in bytes */
        boost::uint16_t e_ehsize;

        /*! \brief  Program header table entry size */
        boost::uint16_t e_phentsize;

        /*!
         * \brief This members holds the number of entries in the program
         * header table (bytes).
         */
        boost::uint16_t e_phnum;

        /*! \brief  Section header table entry size (bytes) */
        boost::uint16_t e_shentsize;

        /*! \brief  Section header table entry count */
        boost::uint16_t e_shnum;

        /*!
         * \brief Section header string table index of the entry associated
         * with the section name string table.
         */
        boost::uint16_t e_shstrndx;

        /* Constants */
        static const boost::uint8_t EI_NIDENT;

        /* Functions */
    };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_FILE_HEADER_64_H */
