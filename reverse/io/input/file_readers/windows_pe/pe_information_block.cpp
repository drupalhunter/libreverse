/*  PE_Information_Block.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_information_block.hpp>
#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>

#include <sstream>
#include <iomanip>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  pe_information_block::pe_information_block()
	    : p_magic (0),
	      p_link_version (0),
	      p_link_revision (0),
	      p_entry_offset (0),
	      p_entry_len (0),
	      p_res (0),
	      p_exe_flags (0),
	      p_auto_data_seg_id (0),
	      p_heap_size (0),
	      p_stack_size (0),
	      p_csip_offset (0),
	      p_sssp_offset (0),
	      p_seg_num (0),
	      p_mod_ref_num (0),
	      p_nonres_num (0),
	      p_seg_offset (0),
	      p_resource_offset (0),
	      p_resident_name_offset (0),
	      p_mod_ref_offset (0),
	      p_import_name_offset (0),
	    p_mov_entry_num (0),
	    p_shift_count (0),
	    p_res_seg_count (0),
	    p_target_os (0),
	    p_additional_info (0),
	    p_fast_load_offset (0),
	    p_fast_load_len (0),
	    p_res2 (0),
	    p_win_version (0)
	  {}

	  boost::uint32_t
	  pe_information_block::get_size (void) const
	  {
	    return static_cast<boost::uint32_t>(32);
	  }

	  /*!
	   * \brief convert the header data into a string representation
	   * \return string representation of header data
	   */
	  std::string
	  pe_information_block::to_string (void)
	  {
	    std::stringstream output_str;

	    output_str << "pe information block:" << std::endl;

	    output_str << boost::format("  magic: 0x%1%") %
	      boost::io::group(std::setfill('0'), std::hex, std::setw(4), p_magic)
		       << std::endl;

	    output_str << "  linker version:   " << p_link_version << std::endl
		       << "  linker revision:        " << p_link_revision << std::endl
		       << "  entry offset:     " << p_entry_offset << std::endl
		       << "  length of entry table (bytes): " << p_entry_len
		       << std::endl
		       << "  reserved space: " << p_res << std::endl
		       << "  exe flags: " << p_exe_flags << std::endl
		       << "  automatic data segment number: " << p_seg_num 
		       << std::endl
		       << "  heap size (bytes): " << p_heap_size << std::endl
		       << "  stack size (bytes): " << p_stack_size << std::endl;

	    output_str << boost::format("  cs:ip offset: 0x%1%") %
	      boost::io::group(std::setfill('0'),
			       std::hex,
			       std::setw(8),
			       p_csip_offset)
		       << std::endl;

	    output_str << boost::format("  ss:sp offset: 0x%1%") %
	      boost::io::group(std::setfill('0'),
			       std::hex,
			       std::setw(8),
			       p_sssp_offset)
		       << std::endl;

	    output_str << "  segment table size: " << p_seg_num << std::endl
		       << "  module reference table size: " << p_mod_ref_num
		       << std::endl
		       << "  nonresident name table size: " << p_nonres_num
		       << std::endl
		       << "  segment offset: " << p_seg_offset
		       << std::endl
		       << "  resource table offset: " << p_resource_offset
		       << std::endl
		       << "  resident name table offset: " << p_resident_name_offset
		       << std::endl
		       << "  module-reference table offset: " << p_mod_ref_offset
		       << std::endl
		       << "  import name table offset: " << p_import_name_offset
		       << std::endl
		       << "  non-resident table offset: " << p_nonres_name_offset
		       << std::endl
		       << "  movable entry point size: " << p_mov_entry_num
		       << std::endl
		       << "  shift count: " << p_shift_count
		       << std::endl
		       << "  resource segment size: " << p_res_seg_count
		       << std::endl
		       << "  target os: " << p_target_os
		       << std::endl
		       << "  additional info: " << p_additional_info
		       << std::endl
		       << "  fast load offset: " << p_fast_load_offset
		       << std::endl
		       << "  fast load length: " << p_fast_load_len << std::endl
		       << "  reserved2: " << p_res2 << std::endl
		       << "  windows version: " << p_win_version << std::endl;

	    return output_str.str();
	  }

	  /*!
	   * \brief convert the bit order of the stored data if host and data
	   * endian types differ
	   *
	   * \param host_endian endian type of host
	   * \param data_endian endian type of data
	   */
	  void
	  pe_information_block::convert (bool host_endian, bool data_endian)
	  {
	    if (host_endian != data_endian) {
	      io::byte_converter::convert (p_magic);
	      io::byte_converter::convert (p_link_version);
	      io::byte_converter::convert (p_link_revision);
	      io::byte_converter::convert (p_entry_offset);
	      io::byte_converter::convert (p_entry_len);
	      io::byte_converter::convert (p_res);
	      io::byte_converter::convert (p_exe_flags);
	      io::byte_converter::convert (p_auto_data_seg_id);
	      io::byte_converter::convert (p_heap_size);
	      io::byte_converter::convert (p_stack_size);
	      io::byte_converter::convert (p_csip_offset);
	      io::byte_converter::convert (p_sssp_offset);
	      io::byte_converter::convert (p_seg_num);
	      io::byte_converter::convert (p_mod_ref_num);
	      io::byte_converter::convert (p_nonres_num);
	      io::byte_converter::convert (p_seg_offset);
	      io::byte_converter::convert (p_resource_offset);
	      io::byte_converter::convert (p_resident_name_offset);
	      io::byte_converter::convert (p_mod_ref_offset);
	      io::byte_converter::convert (p_import_name_offset);
	      io::byte_converter::convert (p_mov_entry_num);
	      io::byte_converter::convert (p_shift_count);
	      io::byte_converter::convert (p_res_seg_count);
	      io::byte_converter::convert (p_fast_load_offset);
	      io::byte_converter::convert (p_fast_load_len);
	      io::byte_converter::convert (p_res2);
	      io::byte_converter::convert (p_win_version);
	    }
	  }

	  bool pe_information_block::is_pe_file_impl (void)
	  {
	    return (p_magic == pe_magic_signature);
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

