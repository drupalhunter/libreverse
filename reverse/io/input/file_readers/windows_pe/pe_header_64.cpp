/*  PE_Header_64.cpp

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

#include <reverse/io/input/file_readers/windows_pe/pe_header_64.hpp>
#include <reverse/io/input/file_readers/windows_pe/coff_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_meta_info.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_optional_header_64.hpp>
#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>

#include <iomanip>
#include <sstream>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  boost::uint16_t const pe_header_64::pe_magic_signature = 0x4550;

	  boost::uint16_t const pe_header_64::le_magic_signature = 0x454c;

	  boost::uint16_t const pe_header_64::ne_magic_signature = 0x454e;

	  pe_header_64::pe_header_64()
	  {}

	  void pe_header_64::convert ()
	  {
	    m_coff_hdr_ptr->convert ();
	    m_opt_hdr_ptr->convert ();
	  }

	  bool pe_header_64::needs_convert ()
	  {
	    bool output = true;

	    if ( ( p_magic == pe_magic_signature ) ||
		 ( p_magic == le_magic_signature ) ||
		 ( p_magic == ne_magic_signature ) )
	      {
		output = false;
	      }

	    return output;
	  }

	  boost::uint32_t
	  pe_header_64::get_size () const
	  {
	    return static_cast<boost::uint32_t>(32);
	  }

	  std::string
	  pe_header_64::to_string ()
	  {
	    std::stringstream output_str;

	    output_str << "pe header:" << std::endl;

	    output_str << boost::format("  magic: 0x%1%") %
	      boost::io::group(std::setfill('0'), std::hex, std::setw(8), p_magic)
		       << std::endl;

	    output_str << m_coff_hdr_ptr->to_string() << std::endl;

	    output_str << m_opt_hdr_ptr->to_string() << std::endl;

	    return output_str.str();

	  }

	  bool pe_header_64::is_pe_file () const
	  {
	    return (p_magic == pe_magic_signature);
	  }

	  std::string
	  pe_header_64::get_file_type (void) const
	  {
	    /* I don't know if DOS EXE files were statically linked or
	       not. For now we simply return that all EXE files are Executable
	       files. */

	    return pe_meta_info::pe_file_type_64bit;
	  }

	  std::string
	  pe_header_64::get_arch_type (void) const
	  {
	    /* TODO: We need to determine CPU architecture if possible. For
	       now we simply say i386 */
	    return "intel:i386";
	  }

	  boost::shared_ptr < coff_header >
	  pe_header_64::get_coff_header (void) const
	  {
	    return m_coff_hdr_ptr;
	  }

	  void
	  pe_header_64::set_coff_header ( boost::shared_ptr < coff_header > c_ptr )
	  {
	    m_coff_hdr_ptr = c_ptr;
	  }

	  boost::shared_ptr < pe_optional_header_64 >
	  pe_header_64::get_optional_header (void) const
	  {
	    return m_opt_hdr_ptr;
	  }

	  void
	  pe_header_64::set_optional_header ( boost::shared_ptr < pe_optional_header_64 > o_ptr )
	  {
	    m_opt_hdr_ptr = o_ptr;
	  }

	  bool
	  pe_header_64::is_valid () const
	  {
	    return this->is_pe_file() &
	      m_coff_hdr_ptr->is_valid();
	  }

	  boost::uint32_t
	  pe_header_64::get_magic_number (void) const
	  {
	    return p_magic;
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

