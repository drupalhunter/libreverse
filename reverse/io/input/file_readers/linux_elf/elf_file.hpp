
/*  Elf_File_T.h

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

#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include "io/IO_Types.h"
#include "io/File.h"
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "Elf_Header_Eident.h"
#include "Elf_File_Header_32.h"
#include "Elf_File_Header_64.h"
#include "Elf_Program_Header_32.h"
#include "Elf_Program_Header_64.h"
#include "Elf_Section_Header_32.h"
#include "Elf_Section_Header_64.h"
#include "Elf_Symbol_32.h"
#include "Elf_Symbol_64.h"
#include "Elf_Relocation_Add_32.h"
#include "Elf_Relocation_Add_64.h"
#include "Elf_Relocation_32.h"
#include "Elf_Relocation_64.h"

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_File
     *
     * \brief Elf_File contains all the elf specific functionality to
     * read binary data from a target file.
     *
     * \date 2004
     */
    class Elf_File
    {
    public:

        /*! \brief Narrow? (Copy Constructor?)
         *  \param f_ref Reference to the File object to copy
         */
        Elf_File ( io_types::File_ID::const_ptr_t filename );

        bool init (void);

        void seek ( boost::uint32_t offset );

        data_types::Memory_Map::ptr_t subset ( boost::uint32_t length );

        /* Read eident header from file */
        void read_Elf_Header_Eident ( elf_types::Elf_Header_Eident::ptr_t& obj );

        /* Read program header */
        void read_Elf_Program_Header ( elf_types::Elf_Program_Header_32::ptr_t& obj );

        /* Read program header */
        void read_Elf_Program_Header ( elf_types::Elf_Program_Header_64::ptr_t& obj );

        /* Read file header */
        void read_Elf_File_Header ( elf_types::Elf_File_Header_32::ptr_t& obj );

        /* Read file header */
        void read_Elf_File_Header ( elf_types::Elf_File_Header_64::ptr_t& obj );

        /* Read section header */
        void read_Elf_Section_Header ( elf_types::Elf_Section_Header_32::ptr_t& obj );

        /* Read section header */
        void read_Elf_Section_Header ( elf_types::Elf_Section_Header_64::ptr_t& obj );

        /* Read symbol */
        void read_Elf_Symbol ( elf_types::Elf_Symbol_32::ptr_t& obj );

        /* Read symbol */
        void read_Elf_Symbol ( elf_types::Elf_Symbol_64::ptr_t& obj );

        /* Read 32-bit relocation_add */
        void read_Elf_Relocation_Add  ( elf_types::Elf_Relocation_Add_32::ptr_t& obj );

        /* Read 64-bit relocation_add */
        void read_Elf_Relocation_Add ( elf_types::Elf_Relocation_Add_64::ptr_t& obj );

        /* Read 32-bit relocation */
        void read_Elf_Relocation ( elf_types::Elf_Relocation_32::ptr_t& obj );

        /* Read 64-bit relocation */
        void read_Elf_Relocation ( elf_types::Elf_Relocation_64::ptr_t& obj );

	boost::uint32_t size ( void ) const;

    private:

        io::File m_file;
    };
} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_FILE_H_ */
