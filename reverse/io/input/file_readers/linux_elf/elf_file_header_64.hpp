/*  Elf_File_Header_64.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_HEADER_64_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_HEADER_64_HPP_INCLUDED

#include <string>

#include <reverse/io/input/file_readers/linux_elf/elf_eident_header.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>


namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  /*!
	   * \class Elf_File_Header_64
	   * \date 2003
	   * \author Stephen Torri
	   *
	   * A major thanks to Eric Youngdale and Nick Clifton for the nice readelf utility.
	   * All functions take and modified from readelf are noted with a message in
	   * their description.
	   *
	   * ----------------------------------------------------------------------------
	   * readelf.c -- display contents of an ELF format file
	   *  Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.
	   *
	   *  Originally developed by Eric Youngdale <eric@andante.jic.com>
	   *   Modifications by Nick Clifton <nickc@redhat.com>
	   *
	   *  This file is part of GNU Binutils.
	   *-----------------------------------------------------------------------------
	   */
	  struct elf_file_header_64
	  {
	    elf_eident_header base;
      
	    /*! \brief  Object file type */
	    Elf32_Half e_type;
      
	    /*! \brief Required architecture for the file */
	    Elf32_Half e_machine;
      
	    /*! \brief ELF version for the file */
	    Elf32_Word e_version;

	    /*!
	     * \brief This memeber gives the virtual address to which the system
	     * first transfer control. If the file has no associated entry
	     * point, this member holds zero. [Elf Format]
	     */
	    boost::uint64_t e_entry;

	    /*! \brief  Program header table's file offset in bytes */
	    boost::uint64_t e_phoff;

	    /*! \brief  Section header table's file offset in bytes */
	    boost::uint64_t e_shoff;
      
	    /*! \brief  Processor-specific flags associated with the file */
	    boost::uint32_t e_flags;
	    
	    /*! \brief  ELF header size in bytes */
	    boost::uint16_t e_ehsize;
	    
	    /*! \brief  Program header table entry size */
	    boost::uint16_t e_phentsize;
	    
	    /*!
	     * \brief This members holds the number of entries in the program
	     * header table (bytes).
	     */
	    boost::uint16_t e_phnum;

	    /*! \brief  Section header table entry size (bytes) */
	    boost::uint16_t e_shentsize;

	    /*! \brief  Section header table entry count */
	    boost::uint16_t e_shnum;
      
	    /*!
	     * \brief Section header string table index of the entry associated
	     * with the section name string table.
	     */
	    boost::uint16_t e_shstrndx;
	    
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
			   struct reverse::io::input::file_readers::linux_elf::elf_file_header_64,
			   ( struct reverse::io::input::file_readers::linux_elf::elf_eident_header, base )
			   ( boost::uint16_t, e_type )
			   ( boost::uint16_t, e_machine )
			   ( boost::uint32_t, e_version )
			   ( boost::uint64_t, e_entry )
			   ( boost::uint64_t, e_phoff )
			   ( boost::uint64_t, e_shoff )
			   ( boost::uint32_t, e_flags )
			   ( boost::uint16_t, e_ehsize )
			   ( boost::uint16_t, e_phentsize )
			   ( boost::uint16_t, e_phnum )
			   ( boost::uint16_t, e_shentsize )
			   ( boost::uint16_t, e_shnum )
			   ( boost::uint16_t, e_shstrndx )
			   )

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_HEADER_64_HPP_INCLUDED
