/*  Elf_Symbol_Info.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOL_INFO_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOL_INFO_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Symbol_Info
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct elf_symbol_info {

	    /*! \brief Symbol info section item: Define */
	    boost::uint16_t si_boundto;

	    /*! \brief Symbol info section flags: Define */
	    boost::uint16_t si_flags;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse


BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_program_header_32,
			   ( boost::uint16_t, si_boundto )
			   ( boost::uint16_t, si_flags )
			   )

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SYMBOL_INFO_HPP_INCLUDED
