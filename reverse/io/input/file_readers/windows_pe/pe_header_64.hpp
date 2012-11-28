/*  PE_Header_64.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_HEADER_64_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_HEADER_64_HPP_INCLUDED

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class coff_header;
	  class pe_optional_header_64;

	  /*!
	   * \class PE_Header_64
	   * \date 2003
	   * \author Stephen Torri

	   * Header variables names taken from
	   * http://www.csn.ul.ie/~caolan/publink/winresdump/winresdump/
	   *        doc/pefile.html
	   * Copyright 1996,1997 Johannes Plachy
	   *
	   * A major thanks to Johannes Plachy for such an excellent
	   * description of the PE format
	   */
	  class pe_header_64 : public io::input::base_header {
	  public:

	    friend class pe_file;

	    /* Functions */

	    /*!
	     * \brief Default Constructor
	     */
	    pe_header_64 ();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~pe_header_64 (){}

	    /*!
	     * \brief Return the bit size of this header
	     * \return Bit size of header
	     */
	    virtual boost::uint32_t get_size (void) const;

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void);

	    /*!
	     * \brief Convert the bit order of the stored data if host and data
	     * endian types differ
	     */
	    virtual void convert ();

	    bool needs_convert ();

	    bool is_pe_file (void) const;

	    std::string get_file_type (void) const;

	    std::string get_arch_type (void) const;

	    boost::shared_ptr < coff_header > get_coff_header (void) const;

	    void set_coff_header ( boost::shared_ptr < coff_header > c_ptr );

	    boost::shared_ptr < pe_optional_header_64 > get_optional_header (void) const;

	    void set_optional_header ( boost::shared_ptr < pe_optional_header_64 > o_ptr );

	    bool is_valid () const;

	    boost::uint32_t get_magic_number (void) const;

	    static boost::uint16_t const pe_magic_signature;
	    static boost::uint16_t const le_magic_signature;
	    static boost::uint16_t const ne_magic_signature;

	  private:

	    /* Data */
	    boost::uint32_t p_magic;

	    /* PE COFF Header */
	    boost::shared_ptr < coff_header > m_coff_hdr_ptr;

	    /* PE Optional Header */
	    boost::shared_ptr < pe_optional_header_64 > m_opt_hdr_ptr;

	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_HEADER_64_HPP_INCLUDED
