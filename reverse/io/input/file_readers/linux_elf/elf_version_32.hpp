/*  Elf_Version.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_32_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_32_HPP_INCLUDED


#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \date 2003
	   * \author Stephen Torri
	   */
	  struct elf_version_32
	  {
	    /*! \brief Version number of structure.  */
	    Elf32_Half	vd_version;
	    
	    /*! \brief Flags (VER_FLG_*).  */
	    Elf32_Half	vd_flags;
	    
	    /*! \brief Version index.  */
	    Elf32_Half	vd_ndx;
	    
	    /*! \brief Number of verdaux entries.  */
	    Elf32_Half	vd_cnt;
	    
	    /*! \brief Hash of name.  */
	    Elf32_Word vd_hash;
	    
	    /*! \brief Offset to verdaux entries.  */
	    Elf32_Word vd_aux;
	    
	    /*! \brief Offset to next verdef.  */
	    Elf32_Word vd_next;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_version_32,
			   ( Elf32_Half, vd_version )
			   ( Elf32_Half, vd_flags )
			   ( Elf32_Half, vd_ndx )
			   ( Elf32_Half, vd_cnt )
			   ( Elf32_Word, vd_hash )
			   ( Elf32_Word, vd_aux )
			   ( Elf32_Word, vd_next )
			   )

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_32_HPP_INCLUDED
