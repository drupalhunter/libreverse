
/*  Elf_Section_Header_64.h

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

#ifndef ELF_SECTION_HEADER_64_H
#define ELF_SECTION_HEADER_64_H

#include "io/IO_Types.h"
#include "io/input/File_Readers/Base_Header.h"
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

namespace libreverse { namespace elf_module {

  /*!
   * \class Elf_Section_Header
   * \date 2003
   * \author Stephen Torri
   */
  class Elf_Section_Header_64 : public header::Base_Header {

      friend class Elf_File;

  public:

    /*!
     * \brief Default Constructor
     */
    Elf_Section_Header_64 (void);

    /*!
     * \brief Constructor
     * \param e_machine Target architecture
     */
    Elf_Section_Header_64 (boost::uint16_t e_machine);

    /*!
     * \brief Convert the bit ordering from the target file bit ordering
     * to the host system.
     */
    virtual void convert ();

    /*!
     * \brief Convert the header data into a string representation
     * \return String representation of header data
     */
    virtual std::string to_String (void) const;

      /*!
       * \brief Get the human readable strings from the header
       * \return String output of header
       */
    void get_Text_String ( io_types::Text_Data::data_type* output ) const;

    boost::uint32_t get_Section_Name_Index(void) const;

    boost::uint64_t get_Section_Size(void) const;

    boost::uint64_t get_Section_Offset(void) const;

    void set_Section_String_Name ( std::string name );

    std::string get_Section_String_Name (void) const;

    boost::uint32_t get_Section_Type (void) const;

    boost::uint32_t get_Next_Section_Index (void) const;

    boost::uint64_t get_Section_Token_Size (void) const;

  private:

    //----------------------------------------
    //            ELF HEADER variables
    //----------------------------------------

    /*! \brief Section name, index in string tbl */
    boost::uint32_t sh_name;

    /*! \brief Type of section */
    boost::uint32_t sh_type;

    /*! \brief Miscellaneous section attributes */
    boost::uint64_t sh_flags;

    /*! \brief Section virtual addr at execution */
    boost::uint64_t sh_addr;

    /*! \brief Section file offset */
    boost::uint64_t sh_offset;

    /*! \brief Size of section in bytes */
    boost::uint64_t sh_size;

    /*! \brief Index of another section */
    boost::uint32_t sh_link;

    /*! \brief Additional section information */
    boost::uint32_t sh_info;

    /*! \brief Section alignment */
    boost::uint64_t sh_addralign;

    /*! \brief Entry size if section holds table */
    boost::uint64_t sh_entsize;

    //----------------------------------------
    //      ELF HEADER helper variables
    //----------------------------------------
    /*! \brief String name of header */
    std::string m_str_name;

    /*! \brief Machine architecture */
    boost::uint16_t m_e_machine;

  };

} /* namespace elf_module */
} /* namespace libreverse */

#endif /* ELF_SECTION_HEADER_64_H */
