/*  elf_parser.hpp

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PARSER_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PARSER_GRAMMAR_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_file_32.hpp>

namespace reverse {
namespace io {
namespace input {
namespace file_readers {
namespace linux_elf {

/*!
 * \brief elf_parser contains all the elf specific functionality to
 * read binary data from a target file.
 *
 * \date 2004
 */
class elf_parser {
public:

     /*! \brief Narrow? (Copy Constructor?)
      *  \param f_ref Reference to the File object to copy
      */
     bool read ( char const* iter,
                 char const* end,
                 elf_file_32& output
               );

     /* Read eident header from file */
     bool read_elf_header_eident ( char const* iter,
                                   char const* end,
                                   elf_eident_header& elf_eident_header_obj );

     /* Read program header (32-bit) */
     bool read_elf_program_header ( char const* iter,
                                   char const* end,
				   elf_program_header_32& program_header_obj );

// 	    /* Read program header */
// 	    void read_Elf_Program_Header ( elf_types::Elf_Program_Header_64::ptr_t& obj );
//
// 	    /* Read file header */
// 	    void read_Elf_File_Header ( elf_types::Elf_File_Header_32::ptr_t& obj );
//
// 	    /* Read file header */
// 	    void read_Elf_File_Header ( elf_types::Elf_File_Header_64::ptr_t& obj );
//
// 	    /* Read section header */
// 	    void read_Elf_Section_Header ( elf_types::Elf_Section_Header_32::ptr_t& obj );
//
// 	    /* Read section header */
// 	    void read_Elf_Section_Header ( elf_types::Elf_Section_Header_64::ptr_t& obj );
//
// 	    /* Read symbol */
// 	    void read_Elf_Symbol ( elf_types::Elf_Symbol_32::ptr_t& obj );
//
// 	    /* Read symbol */
// 	    void read_Elf_Symbol ( elf_types::Elf_Symbol_64::ptr_t& obj );
//
// 	    /* Read 32-bit relocation_add */
// 	    void read_Elf_Relocation_Add  ( elf_types::Elf_Relocation_Add_32::ptr_t& obj );
//
// 	    /* Read 64-bit relocation_add */
// 	    void read_Elf_Relocation_Add ( elf_types::Elf_Relocation_Add_64::ptr_t& obj );
//
// 	    /* Read 32-bit relocation */
// 	    void read_Elf_Relocation ( elf_types::Elf_Relocation_32::ptr_t& obj );
//
// 	    /* Read 64-bit relocation */
// 	    void read_Elf_Relocation ( elf_types::Elf_Relocation_64::ptr_t& obj );
//
// 	    boost::uint32_t size ( void ) const;
//
// 	  private:
//
// 	    io::File m_file;
};

} // namespace linux_elf
} // namespace file_readers
} // namespace input
} //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PARSER_GRAMMAR_HPP
