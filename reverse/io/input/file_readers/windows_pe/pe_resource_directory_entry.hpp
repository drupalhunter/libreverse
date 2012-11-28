/*  PE_Resource_Directory_Entry.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_RESOURCE_DIRECTORY_ENTRY_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_RESOURCE_DIRECTORY_ENTRY_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class pe_resource_directory_entry : public io::input::base_header {
	  public:

	    friend class pe_file;

	    //-------------------------------
	    //     IDENTIFIER TYPES
	    //-------------------------------
	    static boost::uint8_t const name;
	    static boost::uint8_t const id;

	    /*!
	     * \brief Default Constructor
	     */
	    pe_resource_directory_entry ( boost::uint8_t type );

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~pe_resource_directory_entry(){}

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void);

	    /*!
	     * \brief convert the bit order of the stored data
	     */
	    virtual void convert ();

	    virtual boost::uint32_t get_size (void) const;

	    boost::uint32_t get_name_offset (void) const;

	    boost::uint32_t get_offset (void) const;

	    boost::uint8_t get_type (void) const;

	    bool is_directory_bit_set (void) const;

	  private:

	    /* MS_PE_COFF: The address of a string that gives the Type,
	       Name, or Language ID entry, depending on level of table.
	    */
	    boost::uint32_t m_name;

	    /* MS_PE_COFF: High bit = 0 => Address of a Resource Data
	       entry (a leaf).  High bit = 1 ==> The lower 31 bits are the
	       address of another resource directory table (the next level
	       down).
	    */
	    boost::uint32_t m_rva;

	    boost::uint8_t m_type;
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_RESOURCE_DIRECTORY_ENTRY_HPP_INCLUDED
