/*  Elf_Reader_64.h

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

#ifndef ELF_READER_64_H
#define ELF_READER_64_H

#include "Elf_Types.h"
#include "io/IO_Types.h"
#include "io/input/File_Readers/File_Reader.h"
#include <string>

namespace libreverse
{
    namespace elf_module
    {

        /*!
         * \class Elf_Reader_64
         * \date 2003
         * \author Stephen Torri
         */
        class Elf_Reader_64 : public io::File_Reader
        {
            public:

                /*!
                 * \brief Default Constructor
                 * \param target_file The file to be used for decompiling
                 */
                Elf_Reader_64 ( io_types::File_ID::const_ptr_t target_file );

                /*!
                 * \brief Default Destructor
                 */
                virtual ~Elf_Reader_64();

                /*! \brief Elf_Header reference for this reader */
                elf_types::Elf_Header_64::ptr_t get_Header ( void );

                virtual bool support_File_Type ( void );

                virtual void read_Headers ( void );

                virtual data_types::Memory_Map::ptr_t get_Memory_Map ( void );

                virtual std::string to_String ( void );

                virtual io_types::Text_Data::data_type get_Text_Strings ( void );

                virtual io_types::Text_Data::data_type get_UTF16_Strings ( void );

                /*---------------
                 *   Functions
                 *---------------*/

                /*!
                 * \brief Get the Elf File Header from the file
                 */
                void read_File_Header ( void );

                /*!
                 * \brief Get the Elf Program Headers from the file
                 */
                void read_Program_Headers ( void );

                /*!
                 * \brief Return the File Type of the target file
                 */
                virtual std::string get_File_Type ( void );

                /* !\brief Return the Architecture Type of the target file */
                std::string get_Arch_Type ( void );

                /* !\brief Return the offset for a section header */
                std::string get_Section_Offset ( std::string name );

                /* !\brief Return the offset for a section length */
                std::string get_Section_Length ( std::string name );

                /*!
                 * \brief Return the Entry Point of the target file
                 */
                std::string get_Entry_Point ( void );

                /*!
                 * \brief Return the Base Address of the target file
                 */
                std::string get_Base_Address ( void );

                /*!
                 * \brief Get the Section Headers from the file
                 */
                void read_Section_Headers ( void );

                /*!
                 * \brief Get the Dynamic Headers from the file
                 */
                void read_Dynamic_Headers ( void );

                /*!
                 * \brief Get the Symbols from the Symbols Token of the file
                 */
                void read_Symbol_Token ( void );

                /*!
                 * \brief Get the Relocation Headers from the file
                 */
                void read_Relocations ( void );

                /*!
                 * \brief Get the Relocation headers (SHT_REL)
                 */
                void read_Relocation_Headers ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
                                               elf_types::Elf_File_Header_64::const_ptr_t file_hdr );

                /*!
                 * \brief Get the Relocation Addend headers (SHT_RELA)
                 */
                void read_Relocation_Addend_Headers ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
                                                      elf_types::Elf_File_Header_64::const_ptr_t file_hdr );

                /*!
                 * \brief Get the Relocation symbols
                 */
                void read_Relocation_Symbols ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
                                               elf_types::Elf_File_Header_64::const_ptr_t file_hdr );

                virtual std::string get_Section_String ( std::string name ) const;

                virtual std::string get_String_Name ( boost::uint32_t index ) const;

                void set_Symbol_Name ( elf_types::Elf_Symbol_64::ptr_t symbol_ptr );

            private:

                /*---------------
                 *   Variables
                 *---------------*/
                /*! \brief Elf File handle */
                elf_types::Elf_File::ptr_t m_elf_file;

                /*! \brief Conversion of data read is required */
                bool m_convert;

                elf_types::Elf_Header_64::ptr_t m_elf_data;

                data_types::Memory_Map::ptr_t m_string_table_ptr;
        };

    } /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_READER_64_H */
