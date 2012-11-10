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

#ifndef ELF_SYMBOLS_Utils_H
#define ELF_SYMBOLS_Utils_H

#include "io/input/File_Readers/Base_Header.h"

#include <string>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Symbol_Utils
     * \date 2003
     * \author Stephen Torri
     */
    class Elf_Symbol_Utils {

    public:

      /* These three functions disassemble and assemble a symbol table
	 st_info field, which contains the symbol binding and symbol
	 type.  The STB_ and STT_ defines identify the binding and
	 type.  */
      static std::string get_Symbol_Binding ( boost::uint8_t symbol_binding );
        
      static std::string get_Symbol_Type ( boost::uint8_t symbol_type,
					   boost::uint16_t e_machine );

      static std::string get_Symbol_Index_Type ( boost::uint16_t st_shndx );

      /* This function disassembles and assembles a symbol's visibility
	 into the st_other field.  The STV_ defines specificy the actual
	 visibility.  */
      static std::string get_Symbol_Visibility ( boost::uint8_t st_other );
    };

  } /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_SYMBOLS_Utils_H */
