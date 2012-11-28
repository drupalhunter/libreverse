/*  DOS_Relocation_Header.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DOS_RELOCATION_HEADER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DOS_RELOCATION_HEADER_HPP_INCLUDED

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  /*!
	   * \class WPEF_DOS_RELOCATION_Header
	   * \date 2003
	   * \author Stephen Torri

	   * Header variables names taken from
	   * http://www.csn.ul.ie/~caolan/publink/winresdump/winresdump/doc/pefile.html
	   * Copyright 1996,1997 Johannes Plachy
	   *
	   * A major thanks to Johannes Plachy for such an excellent description of the PE format
	   */

	  class dos_relocation_header : public io::input::base_header {
	  public:

	    friend class pe_file;

	    /* Functions */
	    
	    /*!
	     * \brief Default Constructor
	     */
	    dos_relocation_header();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~dos_relocation_header(){}

	    /*!
	     * \brief Return the bit size of this header
	     * \return Bit size of header
	     */
	    virtual boost::uint32_t const get_size (void);

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void);

	    /*!
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();


	    /* Data */

	    boost::uint16_t m_offset;

	    boost::uint16_t m_segment;

	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DOS_RELOCATION_HEADER_HPP_INCLUDED
