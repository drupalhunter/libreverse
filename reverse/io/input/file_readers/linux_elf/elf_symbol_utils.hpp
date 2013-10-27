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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOLS_UTILS_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOLS_UTILS_HPP

#include <boost/cstdint.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Symbol_Utils
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class elf_symbol_utils {

	  public:

	    /* These three functions disassemble and assemble a symbol table
	       st_info field, which contains the symbol binding and symbol
	       type.  The STB_ and STT_ defines identify the binding and
	       type.  */
	    static std::string get_symbol_binding ( boost::uint8_t symbol_binding );
        
	    static std::string get_symbol_type ( boost::uint8_t symbol_type,
						 boost::uint16_t e_machine );

	    static std::string get_symbol_index_type ( boost::uint16_t st_shndx );

	    /* this function disassembles and assembles a symbol's visibility
	       into the st_other field.  the stv_ defines specificy the actual
	       visibility.  */
	    static std::string get_symbol_visibility ( boost::uint8_t st_other );
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOLS_UTILS_HPP
