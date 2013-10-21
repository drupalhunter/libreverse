/*  Elf_Version_Need_Aux.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_NEED_AUX_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_NEED_AUX_HPP_INCLUDED

#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_Version_Need_Aux
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct elf_version_need_aux {

	    /*! \brief Hash of dependency name */
	    boost::uint32_t vna_hash;

	    /*! \brief Flags (VER_FLG_*). */
	    boost::uint16_t vna_flags;

	    /*! \brief Unused */
	    boost::uint16_t vna_other;
	    
	    /*! \brief String table offset to version name. */
	    boost::uint32_t vna_name;
	    
	    /*! \brief Offset to next vernaux. */
	    boost::uint32_t vna_next;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_version_need_aux,
			   ( boost::uint32_t, vna_hash )
			   ( boost::uint16_t, vna_flags )
			   ( boost::uint16_t, vna_other )
			   ( boost::uint32_t, vna_name )
			   ( boost::uint32_t, vna_next )
			   )


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_NEED_AUX_HPP_INCLUDED
