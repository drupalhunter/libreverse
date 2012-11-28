/*  DOS_Header.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DOS_HEADER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DOS_HEADER_HPP_INCLUDED

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

#include <string>
#include <vector>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class dos_relocation_header;

	  /*!
	   * \class DOS_Header
	   * \date 2003
	   * \author Stephen Torri

	   * Header variables names taken from
	   * http://www.csn.ul.ie/~caolan/publink/winresdump/winresdump/doc/pefile.html
	   * Copyright 1996,1997 Johannes Plachy
	   *
	   * A major thanks to Johannes Plachy for such an excellent description of the PE format
	   */
	  class dos_header : public io::input::base_header {
	  public:

	    friend class pe_file;

	    static boost::uint8_t const res_size = 4;
	    static boost::uint8_t const res2_size = 26;

	    /* Functions */

	    /*!
	     * \brief Default Constructor
	     */
	    dos_header();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~dos_header(){}

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    std::string to_string (void);

	    /*!
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();

	    bool needs_convert ();

	    bool is_dos_file (void) const;

	    bool has_pe_header (void) const;

	    std::string get_file_type (void) const;

	    std::string get_arch_type (void) const;

	    /* Returns the relocation information
	       first value: Number of relocations
	       second value: Offset position where relocation entries begin
	    */
 	    std::pair<boost::uint16_t,boost::uint16_t> get_relocation_info (void) const;

	    void add_reloc_hdr ( boost::shared_ptr < dos_relocation_header > obj );

	    boost::uint32_t get_pe_offset (void) const;

	    boost::uint16_t get_magic_number (void) const;

	    boost::uint16_t get_size_of_last_page (void) const;

	    boost::uint16_t get_page_total (void) const;

	    boost::uint16_t get_number_of_relocations (void) const;

	    boost::uint16_t get_header_size (void) const;

	    boost::uint16_t get_minimum_alloc (void) const;

	    boost::uint16_t get_maximum_alloc (void) const;

	    boost::uint16_t get_initial_ss (void) const;

	    boost::uint16_t get_initial_sp (void) const;

	    boost::uint16_t get_checksum (void) const;

	    boost::uint16_t get_ip_value (void) const;

	    boost::uint16_t get_initial_cs (void) const;

	    boost::uint16_t get_file_address (void) const;

	    boost::uint16_t get_overlay_number (void) const;

	    boost::uint8_t const* get_reserved_word (void) const;

	    boost::uint16_t get_behavior_bits (void) const;

	    boost::uint8_t const* get_reserved_word2 (void) const;

	    boost::uint32_t get_exe_header_address (void) const;

	    static boost::uint16_t const dos_magic_signature;

	  private:

	    /* Data */

	    /*! \brief  WPEF "magic number".
	     *
	     * The initial bytes mark the file as an object file and provide
	     * machine-indepenedent data with which to decode and interpret the
	     * file's contents.[WPEF Format]
	     */


	    /* Typically these values are 'ZM' or 'MZ' */
	    boost::uint16_t e_magic;

	    // Number of bytes in last 512-byte page of executable
	    boost::uint16_t e_cblp;

	    // Total number of 512-byte pages in executable (includes and
	    // partial last page
	    boost::uint16_t e_cp;

	    // Number of relocation entries
	    boost::uint16_t e_crlc;

	    // Header size in paragraphs
	    boost::uint16_t e_cparhdr;

	    // Minimum paragraphs of memory required to allocate in
	    // addition to the executable's size
	    boost::uint16_t e_minalloc;

	    // Mimum paragraphs of memory required to allocate in addition
	    // to the executable's size
	    boost::uint16_t e_maxalloc;

	    boost::uint16_t e_ss;            // Initial (relative) SS value

	    boost::uint16_t e_sp;            // Initial SP value

	    boost::uint16_t e_csum;          // Checksum

	    boost::uint16_t e_ip;            // Initial IP value

	    boost::uint16_t e_cs;            // Initial (relative) CS value

	    boost::uint16_t e_lfarlc;        // File address of relocation table

	    boost::uint16_t e_ovno;          // Overlay number

	    boost::uint8_t e_res[res_size]; // reserved words

	    boost::uint16_t e_behavior_bits;

	    boost::uint8_t e_res2[res2_size]; // reserved words

	    boost::uint32_t e_lfanew;        // File address of new exe header

	    typedef std::vector < boost::shared_ptr < dos_relocation_header > > list_t;
	    list_t m_relocs;
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DOS_HEADER_HPP_INCLUDED
