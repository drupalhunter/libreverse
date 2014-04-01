/*  Code_Section_Detector_Elf32_Algorithm.cpp

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

#include <reverse/components/input/code_section_detector_elf32_algorithm.hpp>
#include <reverse/components/input/code_section_detector.hpp>

#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_reader_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_header_32.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

namespace reverse {
  namespace components {
    namespace input {

      boost::shared_ptr < meta::meta_object >
      code_section_detector_elf32_algorithm::run ( boost::shared_ptr < const io::file_id > file_ptr )
      {
	trace::components_detail ( "Entering Code_Section_Detector_Elf32_Algorithm::run" );

	boost::shared_ptr < io::input::file_readers::linux_elf::elf_reader_32 > file_reader_ptr =
	  boost::make_shared < io::input::file_readers::linux_elf::elf_reader_32 > ( file_ptr );

	file_reader_ptr->read_headers();

	boost::shared_ptr < io::input::file_readers::linux_elf::elf_header_32 > elf_hdr_ptr = file_reader_ptr->get_header();

	boost::shared_ptr < meta::meta_object > meta_ptr = boost::make_shared < meta::meta_object> ();

	// Exception is thrown if a '.text' section is not found. We
	// will not catch it because we are expecting a section header
	// to contain the executable code. Therefore we will stop
	// processing the target file.
	boost::shared_ptr < const io::input::file_readers::linux_elf::elf_section_header_32 > elf_sec_hdr_ptr =
	  elf_hdr_ptr->get_section_header ( ".text" );

	std::string code_section_address = boost::str ( boost::format ("%1%" ) % elf_sec_hdr_ptr->get_section_offset() );
	std::string code_section_size = boost::str ( boost::format ( "%1%" ) % elf_sec_hdr_ptr->get_section_size() );

	meta_ptr->add ( "code_section_address",
			code_section_address,
			meta::meta_object::HEX );
	meta_ptr->add ( "code_section_size",
			code_section_size,
			meta::meta_object::HEX );

	trace::components_detail ( "Exiting Code_Section_Detector_Elf32_Algorithm::run" );

	return meta_ptr;
      }

    } // namespace input
  } /* namespace components */
} /* namespace libreverse */

