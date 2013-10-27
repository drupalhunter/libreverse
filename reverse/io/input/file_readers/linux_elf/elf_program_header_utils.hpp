/*  Elf_Program_Header_Utils.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_UTILS_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_UTILS_HPP

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Program_Header_Utils
	   * \date 2008
	   * \author Stephen Torri
	   *
	   * (Elf) = Executable and Linkable Format specification
	   */
	  class elf_program_header_utils
	  {
	  public:

	    static std::string get_segment_type ( boost::uint32_t type_value,
						  boost::uint16_t machine_arch );

	    static std::string get_mips_segment_type ( boost::uint32_t type_value );

	    static std::string get_parisc_segment_type ( boost::uint32_t type_value );

	    static std::string get_ia64_segment_type ( boost::uint32_t type_value );

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_UTILS_HPP
