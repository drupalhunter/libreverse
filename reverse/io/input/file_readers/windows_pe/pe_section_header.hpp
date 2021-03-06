/*  PE_Section_Header.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_PE_SECTION_HEADER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_PE_SECTION_HEADER_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class pe_section_header : public io::input::base_header {
	  public:

	    friend class pe_file;

	    static const boost::uint32_t section_name_size;

	    /*!
	     * \brief Default Constructor
	     */
	    pe_section_header();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~pe_section_header(){}

	    /*!
	     * \brief Return the bit size of this header
	     *
	     * MS_PE_COFF: Each section header size is 40 bytes per entry.
	     *
	     * \return Bit size of header
	     */
	    virtual boost::uint32_t get_size (void) const;

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void) const;

	    /*!
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();

	    std::string const get_name (void) const;

	    bool has_initialized_data (void) const;

	    bool has_uninitialized_data (void) const;

	    bool has_code (void) const;

	    boost::uint32_t get_virtual_size (void) const;

	    boost::uint32_t get_virtual_address (void) const;

	    boost::uint32_t get_size_of_raw_data (void) const;

	    boost::uint32_t get_pointer_to_raw_data (void) const;

	    boost::uint32_t get_pointer_to_relocations (void) const;

	    boost::uint32_t get_pointer_to_line_numbers (void) const;

	    boost::uint16_t get_relocation_count (void) const;

	    boost::uint16_t get_line_number_count (void) const;

	    boost::uint32_t get_characteristics_value (void) const;

	  private:

	    std::string get_characteristics_string (void) const;

	    /* MS_PE_COFF: An 8-byte, null-padded UTF-8 encoded string. If
	       the string is exactly 8 characters long, there is no
	       terminating null. For longer names, this field contains a
	       slash (/) that is followed by an ASCII representation of a
	       decimal number that is an offset into the string
	       table. Executable images do not use a string table and do not
	       support section names longer than 8 characters. Long names in
	       object files are truncated if they are emitted to an
	       executable file.
	    */
	    std::string m_name;

	    /* MS_PE_COFF: The total size of the section when loaded into
	       memory. If this value is greater than SizeOfRawData, the
	       section is zero-padded.  This field is valid only for
	       executable images and should be set to zero for object files.
	    */
	    boost::uint32_t m_virtual_size;

	    /* MS_PE_COFF: For executable images, the address of the first
	       byte of the section relative to the image base when the
	       section is loaded into memory. For object files, this field
	       is the address of the first byte before relocation is
	       applied; for simplicity, compilers should set this to
	       zero. Otherwise, it is an arbitrary value that is subtracted
	       from offsets during relocation.
	    */
	    boost::uint32_t m_virtual_address;

	    /* MS_PE_COFF: The size of the section (for object files) or the
	       size of the initialized data on disk (for image files). For
	       executable images, this must be a multiple of FileAlignment
	       from the optional header. If this is less than VirtualSize,
	       the remainder of the section is zero-filled. Because the
	       SizeOfRawData field is rounded but the VirtualSize field is
	       not, it is possible for SizeOfRawData to be greater than
	       VirtualSize as well. When a section contains only
	       uninitialized data, this field should be zero.
	    */
	    boost::uint32_t m_size_of_raw_data;

	    /*
	      MS_PE_COFF: The file pointer to the first page of the section
	      within the COFF file. For executable images, this must be a
	      multiple of FileAlignment from the optional header. For object
	      files, the value should be aligned on a 4-byte boundary for
	      best performance.  When a section contains only uninitialized
	      data, this field should be zero.
	    */
	    boost::uint32_t m_pointer_to_raw_data;

	    /*
	      MS_PE_COFF: The file pointer to the beginning of relocation
	      entries for the section. This is set to zero for executable
	      images or if there are no relocations.
	    */
	    boost::uint32_t m_pointer_to_relocations;

	    /*
	      MS_PE_COFF: The file pointer to the beginning of line- number
	      entries for the section. This is set to zero if there are no
	      COFF line numbers.  This value should be zero for an image
	      because COFF debugging information is deprecated.
	    */
	    boost::uint32_t m_pointer_to_line_numbers;

	    /*
	      MS_PE_COFF: The number of relocation entries for the
	      section. This is set to zero for executable images.
	    */
	    boost::uint16_t m_number_of_relocations;

	    /*
	      MS_PE_COFF: The number of line-number entries for the
	      section. This value should be zero for an image because COFF
	      debugging information is deprecated.
	    */
	    boost::uint16_t m_number_of_line_numbers;

	    /*
	      MS_PE_COFF: The flags that describe the characteristics of the
	      section.
	    */
	    boost::uint32_t m_characteristics;
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_PE_SECTION_HEADER_HPP_INCLUDED
