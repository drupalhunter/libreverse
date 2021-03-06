/*  Elf_Header_64.h

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

#ifndef ELF_HEADER_64_H
#define ELF_HEADER_64_H

#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include "Elf_File_Header_64.h"
#include "Elf_Program_Header_64.h"
#include "Elf_Section_Header_64.h"
#include "Elf_Dynamic_Header_64.h"
#include "Elf_Relocation_64.h"
#include "Elf_Relocation_Add_64.h"
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace reverse { namespace elf_module {

    /*!
     * \class Elf_Header_64
     * \date 2003
     * \author Stephen Torri
     */
    class Elf_Header_64 : public header::Base_Header {

    public:

      /*!
       * \brief Default Constructor
       */
      Elf_Header_64();

      /*!
       * \brief Default Destructor
       */
      virtual ~Elf_Header_64();

      /*!
       * \brief Initialize Elf_Header
       */
      virtual void init (void);

      /*!
       * \brief Convert the bit ordering from the target file bit ordering
       * to the host system.
       */
      virtual void convert ();

      /*!
       * \brief String representation of Elf Header
       * \return String output of header
       */
      std::string to_String (void);

      /*!
       * \brief Get the human readable strings from the header
       * \return String output of header
       */
      void get_Text_String ( io_types::Text_Data::data_type* output ) const;

      elf_types::Elf_File_Header_64::const_ptr_t get_File_Header (void) const;

      void set_File_Header ( elf_types::Elf_File_Header_64::ptr_t hdr );

      bool is_File_Header_Set (void) const;

      elf_types::Elf_Section_Header_64::const_ptr_t get_Section_Header ( boost::uint16_t index ) const;

      elf_types::Elf_Section_Header_64::const_ptr_t get_Section_Header ( std::string name ) const;

      elf_types::Elf_Header_64::Section_Header_Map_t::const_iterator get_Section_Header_Begin (void) const;

      elf_types::Elf_Header_64::Section_Header_Map_t::const_iterator get_Section_Header_End (void) const;

      elf_types::Elf_Program_Header_64::const_ptr_t get_Program_Header ( boost::uint32_t addr ) const;

      boost::uint64_t get_Base_Address (void) const;

      void push_Back_Section_Header ( elf_types::Elf_Section_Header_64::const_ptr_t sec );

      void push_Back_Program_Header ( elf_types::Elf_Program_Header_64::const_ptr_t sec );

      void push_Back_Symbol ( elf_types::Elf_Symbol_64::const_ptr_t sec);

      elf_types::Elf_Symbol_64::const_ptr_t get_Symbol (boost::uint64_t index);

      void push_Back_Relocation_Header ( elf_types::Elf_Relocation_64::const_ptr_t rel );

      void push_Back_Relocation_Add_Header ( elf_types::Elf_Relocation_Add_64::const_ptr_t rel );

      bool has_Section_Headers (void) const;

      bool has_Program_Headers (void) const;

      bool has_Symbols (void) const;

      std::string get_Program_Header_String (void) const;

      /* NOTE: Possibly we can remove this function */
      std::string get_Symbol_Token_String ( char const* string_table ) const;

      std::string get_Relocation_String (void) const;

      std::string get_Relocation_Add_String (void) const;

    private:

      /* Variables */

      /*! \brief Elf File Header */
      elf_types::Elf_File_Header_64::ptr_t m_file_hdr;

      bool m_base_address_set;

      boost::uint64_t m_base_address;

      elf_types::Elf_Header_64::Program_Header_List_t m_prg_hdrs;
      elf_types::Elf_Header_64::Program_Header_List_t m_instruction_prg_hdrs;

      elf_types::Elf_Header_64::Section_Header_Map_t m_sec_hdrs;
      elf_types::Elf_Header_64::Section_Header_Index_List_t m_sec_hdr_index;

      /*! \brief Dynamic Header */
      elf_types::Elf_Dynamic_Header_64::ptr_t m_dyn_hdr;

      /*! \brief Symbol table */
      elf_types::Elf_Header_64::Symbol_List_t m_symbol_table;

      /*! \brief Relocations */
      elf_types::Elf_Header_64::Relocation_List_t m_relocs;

      elf_types::Elf_Header_64::Relocation_Add_List_t m_relocs_add;

    };

  } /* namespace elf_module */
} /* namespace reverse */

#endif /* ELF_HEADER_64_H */
