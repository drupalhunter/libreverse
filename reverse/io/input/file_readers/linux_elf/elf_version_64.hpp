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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_64_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_64_HPP_INCLUDED


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
	  struct elf_version_64
	  {
	    /*! \brief Version number of structure.  */
	    Elf64_Half	vd_version;
	    
	    /*! \brief Flags (VER_FLG_*).  */
	    Elf64_Half	vd_flags;
	    
	    /*! \brief Version index.  */
	    Elf64_Half	vd_ndx;
	    
	    /*! \brief Number of verdaux entries.  */
	    Elf64_Half	vd_cnt;
	    
	    /*! \brief Hash of name.  */
	    Elf64_Word vd_hash;
	    
	    /*! \brief Offset to verdaux entries.  */
	    Elf64_Word vd_aux;
	    
	    /*! \brief Offset to next verdef.  */
	    Elf64_Word vd_next;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_version_64,
			   ( Elf64_Half, vd_version )
			   ( Elf64_Half, vd_flags )
			   ( Elf64_Half, vd_ndx )
			   ( Elf64_Half, vd_cnt )
			   ( Elf64_Word, vd_hash )
			   ( Elf64_Word, vd_aux )
			   ( Elf64_Word, vd_next )
			   )

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_VERSION_64_HPP_INCLUDED
