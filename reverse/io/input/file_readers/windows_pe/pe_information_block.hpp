/*  PE_Information_Block.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_INFORMATION_BLOCK_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_INFORMATION_BLOCK_HPP_INCLUDED

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class pe_information_block : public io::input::base_header {
	  public:

	    friend class pe_file;

	    /*!
	     * \brief Default Constructor
	     */
	    pe_information_block();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~pe_information_block(){}

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
	     *
	     * \param host_endian Endian type of host
	     * \param data_endian Endian type of data
	     */
	    virtual void convert (bool host_endian, bool data_endian);

	    bool is_pe_file_impl (void);

	  private:

	    static boost::uint16_t const pe_magic_signature = 0x4550;

	    /*! \brief  WPEF "magic number".
	     *
	     * The initial bytes mark the file as an object file and provide
	     * machine-indepenedent data with which to decode and interpret the
	     * file's contents.[WPEF Format]
	     */
	    boost::uint16_t p_magic;        /* Typically these values are 'P','E' */
	    boost::uint16_t p_link_version; /* Linker version number */
	    boost::uint16_t p_link_revision; /* Linker revision number */
	    boost::uint16_t p_entry_offset; /* offset to the entry table (relative to
					       the beginning of the header) */
	    boost::uint16_t p_entry_len;    /* length of the entry table, in bytes */
	    boost::uint16_t p_res;          /* Reserved space */

	    /* Specifies flags that describe the contents of the executable
	       file. This value can be one or more of the following bits:

	       Bit     Meaning

	       0 - The linker sets this bit if the executable-file format is
	       SINGLEDATA. An executable file wi th this format contains one
	       data segment. This bit is set if the file is a dynamic-link
	       library (DLL).

	       1 - The linker sets this bit if the executable-file format is
	       MULTIPLEDATA. An executable file with this format contains
	       multiple data segments. This bit is set if the file is a
	       Windows application.

	       If neither bit 0 nor bit 1 is set, the executable-file format
	       is NOAUTODATA. An executable file wit h this format does not
	       contain an automatic data segment.

	       2 - Reserved.
	       3 - Reserved.
	       8 - Reserved.
	       9 - Reserved.

	       11 - If this bit is set, the first segment in the executable
	       file contains code that loads the application.

	       13 - If this bit is set, the linker detects errors at link time
	       but still creates an executable file.

	       14 - Reserved.

	       15 - If this bit is set, the executable file is a library
	       module.
	    */
	    boost::uint16_t p_exe_flags;

	    boost::uint16_t p_auto_data_seg_id; /* Specifies the automatic
						   data segment number. (0Eh
						   is zero if the SINGLEDATA
						   and MULTIPLEDAT A bits are
						   cleared.)
						*/

	    boost::uint16_t p_heap_size; /* Specifies the initial size, in
					    bytes, of the local heap. This
					    value is zero if there is no local
					    allocation.
					 */

	    boost::uint16_t p_stack_size; /* Specifies the initial size, in
					     bytes, of the stack. This value is
					     zero if the SS register v alue
					     does not equal the DS register
					     value.
					  */

	    boost::uint32_t p_csip_offset; /* Specifies the segment:offset
					      value of CS:IP. */

	    /* Specifies the segment:offset value of SS:SP.

	       The value specified in SS is an index to the module's segment
	       table. The first entry in the segment table corresponds to segment
	       number 1.  If SS addresses the automatic data segment and SP is
	       zero, SP is set to the address obtained by add ing the size of the
	       automatic data segment to the size of the stack.
	    */
	    boost::uint32_t p_sssp_offset;

	    boost::uint16_t p_seg_num; /* Specifies the number of entries in
					  the segment table. */

	    boost::uint16_t p_mod_ref_num; /* Specifies the number of entries
					      in the module-reference
					      table. */

	    boost::uint16_t p_nonres_num; /* Specifies the number of bytes in
					     the nonresident-name table. */

	    boost::uint16_t p_seg_offset; /* Specifies a relative offset from
					     the beginning of the Windows
					     header to the beginning of the
					     segment table. */

	    boost::uint16_t p_resource_offset; /* Specifies a relative offset
						  from the beginning of the
						  Windows header to the
						  beginning of the resource
						  table. */

	    boost::uint16_t p_resident_name_offset; /* Specifies a relative
						       offset from the
						       beginning of the
						       Windows header to the
						       beginning of the
						       resident-name table. */

	    boost::uint16_t p_mod_ref_offset; /* Specifies a relative offset
						 from the beginning of the
						 Windows header to the
						 beginning of the
						 module-reference table. */

	    boost::uint16_t p_import_name_offset; /* Specifies a relative
						     offset from the beginning
						     of the Windows header to
						     the beginning of the
						     imported-name table. */

	    boost::uint32_t p_nonres_name_offset; /* Specifies a relative
						     offset from the beginning
						     of the file to the
						     beginning of the
						     nonresident-name
						     table. */

	    boost::uint16_t p_mov_entry_num; /* Specifies the number of
						movable entry points. */

	    /* Specifies a shift count that is used to align the logical
	       sector. This count is log2 of the segment sector size. It is
	       typically 4, although the default count is 9. (This value
	       corresponds to the /alignment [/a] linker switch. When the
	       linker command line contains /a:16, the shift count is 4. When
	       the linker command line contains /a:512, the shift count is
	       9.)*/
	    boost::uint16_t p_shift_count;

	    boost::uint16_t p_res_seg_count; /* Specifies the number of
						resource segments. */

	    /* Specifies the target operating system, depending on which bits
	       are set:

	       0       Operating system format is unknown.
	       1       Reserved.
	       2       Operating system is Microsoft Windows.
	       3       Reserved.
	       4       Reserved.
	    */
	    boost::uint8_t p_target_os;

	    /* Specifies additional information about the executable file. It
	       can be one or more of the following values:

	       Bit     Meaning

	       1 - If this bit is set, the executable file contains a Windows
	       2.x application that runs in ver sion 3.x protected mode.

	       2 - If this bit is set, the executable file contains a Windows
	       2.x application that supports pr oportional fonts.

	       3 - If this bit is set, the executable file contains a fast-load area.
	    */
	    boost::uint8_t p_additional_info;

	    boost::uint16_t p_fast_load_offset; /* Specifies the offset, in
						   sectors, to the beginning
						   of the fast-load
						   area. (Only Windows use s
						   this value.) */

	    boost::uint16_t p_fast_load_len; /* Specifies the length, in
						sectors, of the fast-load
						area. (Only Windows uses this
						value.) */

	    boost::uint16_t p_res2; /* Reserved space */

	    boost::uint16_t p_win_version; /* Specifies the expected version
					      number for Windows. (Only
					      Windows uses this value.) */

	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_INFORMATION_BLOCK_HPP_INCLUDED
