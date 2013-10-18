/*  Elf_Symbol_32.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOLS_32_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOLS_32_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Symbol_32
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct elf_symbol_32 {

	    /*!
	     * \brief This member holds an index into the object file's symbol
	     * string table, which holds the character representations of the
	     * symbol names. If the value is non-zero, it represents a string
	     * table index that gives the symbol name. Otherwise, the symbol
	     * table entry has no name. (Elf)
	     */
	    Elf32_Word st_name;

	    /*!
	     * \brief This member gives the value of the associated
	     * symbol. Depending on the context, this may be an absolute value,
	     * and address. (Elf)
	     */
	    Elf32_Addr st_value;

	    /*!
	     * \brief This member holds the data object's size in the number of
	     *  bytes. This member holds 0 if the symbol has no size or an
	     *  unknown size. (Elf)
	     */
	    Elf32_Word st_size;

	    /*!
	     * \brief This member specifies the symbol's type and binding
	     * attributes. (Elf)
	     */
	    boost::uint8_t st_info;

	    /*! \brief No defined meaning, 0 */
	    boost::uint8_t st_other;

	    /*!
	     * \brief Every symbol table entry is "defined" in relation to some
	     * section; this member holds the relevant seciton header table
	     * index. (Elf)
	     */
	    Elf32_Half st_shndx;

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   reverse::io::input::file_readers::linux_elf::elf_symbol_32,
			   (Elf32_Word, st_name)
			   (Elf32_Addr, st_value)
			   (Elf32_Word, st_size)
			   (boost::uint8_t, st_info)
			   (boost::uint8_t, st_other)
			   (Elf32_Half, st_shndx)
			   )


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOLS_32_HPP_INCLUDED
