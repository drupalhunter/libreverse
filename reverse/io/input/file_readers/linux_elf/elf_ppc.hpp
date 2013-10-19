/*  Elf_ppc.h

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
  PPC ELF support for BFD.
  Copyright 1995, 1996, 1998, 2000, 2001, 2002, 2003
  Free Software Foundation, Inc.

  By Michael Meissner, Cygnus Support, <meissner@cygnus.com>, from
  information in the System V Application Binary Interface, PowerPC
  Processor Supplement and the PowerPC Embedded Application Binary
  Interface (eabi).

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

*/

/* This file holds definitions specific to the PPC ELF ABI.  Note
   that most of this is not actually implemented by BFD.  */

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PPC_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PPC_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <string>


namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_ppc {
	  public:

	    static inline std::string get_type (boost::uint32_t type);

	    static inline bool is_ppc_tls_reloc (boost::uint32_t type);

	    /* Processor specific flags for the ELF header e_flags field.  */

	    /* PowerPC embedded flag.  */
	    static const boost::uint32_t EF_PPC_EMB = 0x80000000;

	    /* PowerPC -mrelocatable flag.  */
	    static const boost::uint32_t EF_PPC_RELOCATABLE = 0x00010000;

	    /* PowerPC -mrelocatable-lib flag.  */
	    static const boost::uint32_t EF_PPC_RELOCATABLE_LIB = 0x00008000;

	    /* Processor specific section headers, sh_type field.  */

	    /*
	      Link editor is to sort the entries in this section based on
	      the address specified in the associated symbol table
	      entry.
	    */
	    static const boost::uint32_t SHT_ORDERED = elf_common::SHT_HIPROC;


	    /* Processor specific section flags, sh_flags field.  */

	    /*
	      Link editor is to exclude this section from executable and
	      shared objects that it builds when those objects are not to
	      be furhter relocated.
	    */
	    static const boost::uint32_t SHF_EXCLUDE = 0x80000000;

	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#include "elf_ppc.inl"

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PPC_HPP_INCLUDED
