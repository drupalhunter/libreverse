/*  DOS_Header.cpp

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

#include <reverse/io/input/file_readers/windows_pe/dos_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/dos_relocation_header.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_meta_info.hpp>

#include <reverse/io/byte_converter.hpp>

#include <boost/format.hpp>

#include <iomanip>
#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  boost::uint16_t const dos_header::dos_magic_signature = 0x5a4d;

	  dos_header::dos_header()
	    : e_magic (0),
	      e_cblp (0),
	      e_cp (0),
	      e_crlc (0),
	      e_cparhdr (0),
	      e_minalloc (0),
	      e_maxalloc (0),
	      e_ss (0),
	      e_sp (0),
	      e_csum (0),
	      e_ip (0),
	      e_cs (0),
	      e_lfarlc (0),
	      e_ovno (0),
	      e_behavior_bits (0),
	      e_lfanew (0)
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering DOS_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

	    for (boost::uint8_t i = 0; i < 4; i++)
	      {
                e_res[i] = 0;
	      }

	    for (boost::uint8_t i = 0; i < 10; i++)
	      {
                e_res2[i] = 0;
	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting DOS_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  void
	  dos_header::convert ()
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering DOS_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


            io::byte_converter::convert (e_cblp);
            io::byte_converter::convert (e_cp);
            io::byte_converter::convert (e_crlc);
            io::byte_converter::convert (e_cparhdr);
            io::byte_converter::convert (e_minalloc);
            io::byte_converter::convert (e_maxalloc);
            io::byte_converter::convert (e_ss);
            io::byte_converter::convert (e_sp);
            io::byte_converter::convert (e_csum);
            io::byte_converter::convert (e_ip);
            io::byte_converter::convert (e_cs);
            io::byte_converter::convert (e_lfarlc);
            io::byte_converter::convert (e_ovno);
            io::byte_converter::convert (e_behavior_bits);
            io::byte_converter::convert (e_lfanew);

            // Don't need to convert byte types:
            // - e_res[]
            // - e_res2[]

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting DOS_Header::convert" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  bool
	  dos_header::needs_convert ()
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering DOS_Header::needs_Convert" );
#endif /* LIBREVERSE_DEBUG */


	    bool output = true;

	    if ( e_magic == dos_magic_signature )
	      {
		output = false;
	      }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting DOS_Header::needs_Convert" );
#endif /* LIBREVERSE_DEBUG */

	    return output;
	  }

	  std::string dos_header::to_string ()
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering DOS_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    std::stringstream output_str;

	    output_str << "DOS Header:" << std::endl;

	    output_str << boost::format("  Magic: %1%") %
	      boost::io::group(std::hex, std::showbase, e_magic) << std::endl;

	    output_str << "  Bytes on last page:   " << e_cblp << std::endl
		       << "  Pages in File:        " << e_cp << std::endl
		       << "  Relocation Count:     " << e_crlc << std::endl
		       << "  Size of header:       " << e_cparhdr << std::endl
		       << "  Min extra:            " << e_minalloc << std::endl
		       << "  Max extra:            " << e_maxalloc << std::endl
		       << "  Initial SS:           " << e_ss << std::endl
		       << "  Initial SP:           " << e_sp << std::endl
		       << "  Checksum:             " << e_csum << std::endl
		       << "  Initial IP:           " << e_ip << std::endl
		       << "  Initial CS:           " << e_cs << std::endl;

	    output_str << boost::format("  Reloc Token Addr:     0x%1%") %
	      boost::io::group(std::setfill('0'),
			       std::hex,
			       std::setw(4),
			       e_lfarlc) << std::endl;

	    output_str << "  Overlay number:        " << e_ovno << std::endl;

	    output_str << "  Reserved words:       ";
	    for (boost::uint8_t i = 0; i < dos_header::res_size; ++i)
	      {
                output_str << boost::format(" %1% ") %
		  boost::io::group(std::setfill('0'),
				   std::hex,
				   std::setw(2),
				   static_cast<boost::uint16_t>(e_res[i]));
	      }

	    output_str << std::endl
		       << "  Behavior bits:        "
		       << e_behavior_bits << std::endl
		       << "  Reserve Words2:        ";

	    for (boost::uint8_t i = 0; i < dos_header::res2_size; ++i)
	      {
                output_str << boost::format("%1% ") %
		  boost::io::group(std::setfill('0'),
				   std::hex,
				   std::setw(2),
				   static_cast<boost::uint16_t>(e_res2[i]));
	      }

	    output_str << std::endl;

	    output_str << boost::format("  EXE Header Token Addr: 0x%1%") %
	      boost::io::group(std::setfill('0'),
			       std::hex,
			       std::setw(8),
			       e_lfanew) << std::endl << std::endl;


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting DOS_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    return output_str.str();
	  }

	  bool
	  dos_header::is_dos_file (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::is_DOS_File" );
#endif /* LIBREVERSE_DEBUG */

	    return (e_magic == dos_magic_signature);
	  }

	  bool
	  dos_header::has_pe_header (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::has_PE_Header" );
#endif /* LIBREVERSE_DEBUG */

	    return (e_lfanew != 0);
	  }

	  std::string
	  dos_header::get_file_type (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_File_Type" );
#endif /* LIBREVERSE_DEBUG */

	    return pe_meta_info::dos_file_type;
	  }

	  std::string
	  dos_header::get_arch_type (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Arch_Type" );
#endif /* LIBREVERSE_DEBUG */

	    /* Since DOS was only compiled for the 32-Bit Intel Architecture
	       coupled with the fact that the DOS EXE Format has not
	       architecture field we simply return Intel as the architecture
	       type.
	    */
	    return std::string("intel:i386");
	  }

	  void dos_header::add_reloc_hdr ( boost::shared_ptr < dos_relocation_header > obj )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering DOS_Header::add_Reloc_Hdr" );
#endif /* LIBREVERSE_DEBUG */


	    m_relocs.push_back (obj);


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting DOS_Header::add_Reloc_Hdr" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  std::pair<boost::uint16_t,boost::uint16_t>
	  dos_header::get_relocation_info (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Relocation_Info" );
#endif /* LIBREVERSE_DEBUG */

	    return std::make_pair (e_crlc, e_lfarlc);
	  }

	  boost::uint32_t
	  dos_header::get_pe_offset (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_PE_Offset" );
#endif /* LIBREVERSE_DEBUG */

	    return e_lfanew;
	  }

	  boost::uint16_t
	  dos_header::get_magic_number (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Magic_Number" );
#endif /* LIBREVERSE_DEBUG */

	    return e_magic;
	  }

	  boost::uint16_t
	  dos_header::get_size_of_last_page (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Size_Of_Last_Page" );
#endif /* LIBREVERSE_DEBUG */

	    return e_cblp;
	  }

	  boost::uint16_t
	  dos_header::get_page_total (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Page_Total" );
#endif /* LIBREVERSE_DEBUG */

	    return e_cp;
	  }

	  boost::uint16_t
	  dos_header::get_number_of_relocations (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Number_Of_Relocations" );
#endif /* LIBREVERSE_DEBUG */

	    return e_crlc;
	  }

	  boost::uint16_t
	  dos_header::get_header_size (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Header_Size" );
#endif /* LIBREVERSE_DEBUG */

	    return e_cparhdr;
	  }

	  boost::uint16_t
	  dos_header::get_minimum_alloc (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Minimum_Alloc" );
#endif /* LIBREVERSE_DEBUG */

	    return e_minalloc;
	  }

	  boost::uint16_t
	  dos_header::get_maximum_alloc (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Maximum_Alloc" );
#endif /* LIBREVERSE_DEBUG */

	    return e_maxalloc;
	  }

	  boost::uint16_t
	  dos_header::get_initial_ss (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Initial_SS" );
#endif /* LIBREVERSE_DEBUG */

	    return e_ss;
	  }

	  boost::uint16_t
	  dos_header::get_initial_sp (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Initial_SP" );
#endif /* LIBREVERSE_DEBUG */

	    return e_sp;
	  }

	  boost::uint16_t
	  dos_header::get_checksum (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Checksum" );
#endif /* LIBREVERSE_DEBUG */

	    return e_csum;
	  }

	  boost::uint16_t
	  dos_header::get_ip_value (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_IP_Value" );
#endif /* LIBREVERSE_DEBUG */

	    return e_ip;
	  }

	  boost::uint16_t
	  dos_header::get_initial_cs (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Initial_CS" );
#endif /* LIBREVERSE_DEBUG */

	    return e_cs;
	  }

	  boost::uint16_t
	  dos_header::get_file_address (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_File_Address" );
#endif /* LIBREVERSE_DEBUG */

	    return e_lfarlc;
	  }

	  boost::uint16_t
	  dos_header::get_overlay_number (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Overlay_Number" );
#endif /* LIBREVERSE_DEBUG */

	    return e_ovno;
	  }

	  boost::uint8_t const*
	  dos_header::get_reserved_word (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Reserved_Word" );
#endif /* LIBREVERSE_DEBUG */

	    return e_res;
	  }

	  boost::uint16_t
	  dos_header::get_behavior_bits (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Behavior_Bits" );
#endif /* LIBREVERSE_DEBUG */

	    return e_behavior_bits;
	  }

	  boost::uint8_t const*
	  dos_header::get_reserved_word2 (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_Reserved_Word2" );
#endif /* LIBREVERSE_DEBUG */

	    return e_res2;
	  }

	  boost::uint32_t
	  dos_header::get_exe_header_address (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Inside DOS_Header::get_EXE_Header_Address" );
#endif /* LIBREVERSE_DEBUG */

	    return e_lfanew;
	  }

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

