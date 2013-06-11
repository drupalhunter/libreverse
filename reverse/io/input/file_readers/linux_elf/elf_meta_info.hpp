/*  Elf_meta_info.h

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
#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_META_INFO_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_META_INFO_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_meta_info {
	  public:

	    static const std::string FILE_TYPE_32BIT;
	    static const std::string FILE_TYPE_64BIT;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_META_INFO_HPP_INCLUDED
