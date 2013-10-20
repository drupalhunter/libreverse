/*  Elf_i370.h

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

/*

  i370 ELF support for BFD.
  Copyright 2000, 2002 Free Software Foundation, Inc.

  This file is part of BFD, the Binary File Descriptor library.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.

  This file holds definitions specific to the i370 ELF ABI.  Note
  that most of this is not actually implemented by BFD.
*/

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_I370_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_I370_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_i370 {
	  public:

	    /*
	      i370 relocations
          
	      Note that there is really just one relocation that we currently
	      support (and only one that we seem to need, at the moment), and
	      that is the 31-bit address relocation.  Note that the 370/390
	      only supports a 31-bit (2GB) address space.
	    */

	    static inline std::string get_type ( boost::uint32_t type );

	    /* Processor specific section headers, sh_type field */
        
	    /* Link editor is to sort the entries in this section based on the
	       address specified in the associated symbol table entry.  */
	    static const boost::uint32_t SHT_ORDERED = elf_common::SHT_HIPROC;
    
	    /* i370 -mrelocatable flag */
	    static const boost::uint32_t EF_I370_RELOCATABLE =	0x00010000;

	    /* i370 -mrelocatable-lib flag */
	    static const boost::uint32_t EF_I370_RELOCATABLE_LIB = 0x00008000;

	    /* Processor specific section flags, sh_flags field */

	    /* Link editor is to exclude this section from executable and
	       shared objects that it builds when those objects are not to be
	       furhter relocated.  */
	    static const boost::uint32_t SHF_EXCLUDE = 0x80000000;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_i370.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_I370_HPP_INCLUDED
