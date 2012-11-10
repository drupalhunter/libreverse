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

#ifndef ELF_SYMBOLS_32_H
#define ELF_SYMBOLS_32_H

#include "io/input/File_Readers/Base_Header.h"

#include <string>

namespace libreverse { namespace elf_module {

    /*!
     * \class Elf_Symbol_32
     * \date 2003
     * \author Stephen Torri
     */
    class Elf_Symbol_32 : public header::Base_Header {

    friend class Elf_File;

    public:

      Elf_Symbol_32 ( boost::uint16_t e_machine );

      /*!
       * \brief Return the data of this header in a format style
       * \return String representation of data
       * The format style was taken from the readelf source code
       */
      std::string to_String (void) const;

      /*!
       * \brief Convert bit ordering
       * \param host_endian Host bit ordering
       * \param data_endian Data bit ordering
       * Convert the bit ordering from the target file bit ordering
       * to the host system. If the host system and the target file
       * match this is a no-op.
       */
      virtual void convert ();
        
      void set_symbol_info ( boost::uint8_t binding,
			     boost::uint8_t type );

      /* TODO: We need to convert these
	 const boost::uint32_t elf_r_sym (i)		((i) >> 8)
	 #define ELF32_R_TYPE(i)		((i) & 0xff)
	 #define ELF32_R_INFO(s,t)	(((s) << 8) + ((t) & 0xff))
      */

      boost::uint32_t get_String_Token_Index (void) const;

      void set_Symbol_Name ( std::string name );

      std::string get_Name (void) const;

      boost::uint32_t get_Value (void) const;

      boost::uint8_t get_Symbol_Type_Value (void) const;

      boost::uint16_t get_Index (void) const;

    private:

      /*!
       * \brief This member holds an index into the object file's symbol
       * string table, which holds the character representations of the
       * symbol names. If the value is non-zero, it represents a string
       * table index that gives the symbol name. Otherwise, the symbol
       * table entry has no name. (Elf)
       */
      boost::uint32_t st_name;

      /*!
       * \brief This member gives the value of the associated
       * symbol. Depending on the context, this may be an absolute value,
       * and address. (Elf)
       */
      boost::uint32_t st_value;

      /*!
       * \brief This member holds the data object's size in the number of
       *  bytes. This member holds 0 if the symbol has no size or an
       *  unknown size. (Elf)
       */
      boost::uint32_t st_size;

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
      boost::uint16_t st_shndx;

      /********************
       * Helper variables
       ********************/
      std::string m_symbol_name;

      boost::uint8_t m_symbol_binding;

      boost::uint8_t m_symbol_type;

    private:
      /********************
       * Helper variables
       ********************/
      boost::uint16_t m_e_machine;

    };

  } /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_SYMBOLS_32_H */
