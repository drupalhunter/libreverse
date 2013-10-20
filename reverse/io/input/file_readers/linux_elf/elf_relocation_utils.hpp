/*  Elf_Relocation_Utils.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_UTILS_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_UTILS_HPP_INCLUDED

#include <string>
#include <boost/cstdint.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class elf_relocation_utils {
	  public:
	    
	    /*!
	     * \brief Return type name
	     * \param machine_value CPU of the target
	     * \param reloc_type Relocation type
	     * \return String representation of section header type
	     */
	    static std::string get_section_type_name ( boost::uint16_t machine_value,
						       boost::uint8_t reloc_type,
						       boost::uint8_t bitsize );
	    
	  };
	  
	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_RELOCATION_UTILS_HPP_INCLUDED
