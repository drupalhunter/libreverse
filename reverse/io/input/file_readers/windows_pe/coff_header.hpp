/*  Coff_Header.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_COFF_HEADER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_COFF_HEADER_HPP_INCLUDED

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


	  class coff_header : public io::input::base_header {
	  public:

	    friend class pe_file;

	    /*!
	     * \brief Default Constructor
	     */
	    coff_header();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~coff_header(){}

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void);

	    /*!
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();

	    boost::uint16_t get_section_header_count (void) const;

	    boost::uint16_t get_optional_header_size (void) const;

	    bool is_valid () const;

	    boost::uint16_t get_machine_number (void) const;

	    boost::uint32_t get_time_stamp_number (void) const;

	    boost::uint32_t get_symbol_table_pointer (void) const;

	    boost::uint32_t get_number_of_symbols (void) const;

	    boost::uint16_t get_characteristic_value (void) const;

	    bool is_executable (void) const;

	  private:

	    /*!
	     * \brief Returns the machine name
	     * \return String representation of machine name
	     */
	    std::string get_machine_name (void);

	    /*!
	     * \brief Returns a string representing the characteristics
	     * \return String representing the characteristics
	     */
	    std::string get_characteristics_string (void);

	    /* MS_PE_COFF: The number that identifies the type of target
	       machine. */
	    boost::uint16_t m_machine;

	    /* MS_PE_COFF: The number of sections. This indicates the size
	       of the section table, which immediately follows the
	       headers. */
	    boost::uint16_t m_number_of_sections;

	    /* MS_PE_COFF: The low 32-bits of the number of seconds since
	       00:00 January 1, 1970 ( a C run-time value ), that indicates
	       when the file was created. */
	    boost::uint32_t m_time_date_stamp;

	    /* MS_PE_COFF: The file offset of the COFF symbol table, or zero
	       if no COFF symbol table is present.  This value should be
	       zero for an image because COFF debugging information is
	       deprecated. */
	    boost::uint32_t m_pointer_to_symbol_table;

	    /* MS_PE_COFF: The number of entries in the symbol table.  This
	       data can be used to locate the string table, which
	       immediately follows the symbol table. This value should be
	       zero for an image because COFF debugging information is
	       deprecated.
	    */
	    boost::uint32_t m_number_of_symbols;

	    /* MS_PE_COFF: The size of the optional header, which is
	       required for executable files but not for object files. This
	       value should be zero for an object file. */
	    boost::uint16_t m_size_of_optional_header;

	    /* MS_PE_COFF: The flags that indicate the attributes of the
	       file.
	    */
	    boost::uint16_t m_characteristics;
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_COFF_HEADER_HPP_INCLUDED
