
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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_UTILS_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_UTILS_HPP_INCLUDED

#include <boost/cstdint.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Section_Header_Utils
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class Elf_Section_Header_Utils {

	  public:

	    //----------------------------------------
	    //      ELF HEADER helper functions
	    //----------------------------------------
	    /*!
	     * \brief Return header flags
	     * \return String representation of flags
	     */
	    static std::string get_flags ( boost::uint64_t sh_flags );

	    /*!
	     * \brief Return type name
	     * \return String representation of section header type
	     */
	    static std::string get_section_type_name ( boost::uint32_t sh_type,
						       boost::uint16_t e_machine );

	    /*!
	     * \brief Return MIPS type name
	     * \return String representation of section header type
	     */
	    static std::string get_mips_section_type_name ( boost::uint32_t sh_type );

	    /*!
	     * \brief Return PARISC type name
	     * \return String representation of section header type
	     */
	    static std::string get_parisc_section_type_name ( boost::uint32_t sh_type );

	    /*!
	     * \brief Return ia64 type name
	     * \return String representation of section header type
	     */
	    static std::string get_ia64_section_type_name ( boost::uint32_t sh_type );

	    /*!
	     * \brief Return osabi name
	     * \return String representation of the osabi name
	     */
	    static std::string get_osabi_name ( boost::uint32_t osabi );

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_UTILS_HPP_INCLUDED
