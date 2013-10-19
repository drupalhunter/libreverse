/*  Elf_Note.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_NOTE_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_NOTE_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Note
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct Elf_Note
	  {
	    /*! \brief Size of entry's owner string */
	    Elf32_Word m_namesz;

	    /*! \brief  Size of the note descriptor */
	    Elf32_Word  m_descsz;

	    /*! \brief Interpretation of the descriptor */
	    Elf32_Word m_type;

	    /*! \brief Start of the name+desc data */
	    std::string m_name;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_note,
			   ( Elf32_Word, m_namesz )
			   ( Elf32_Word, m_descsz )
			   ( Elf32_Word, m_type )
			   ( std::string, m_name )

#endif // REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_NOTE_HPP_INCLUDED 
