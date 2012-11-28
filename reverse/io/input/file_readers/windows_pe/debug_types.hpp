/*  Debug_Types.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DEBUG_TYPES_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DEBUG_TYPES_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/cstdint.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class debug_types {
	  public:

	    enum values {

	      /* ms_pe_coff: 0x00000000 - an unknown value that is ignored
		 by all tools.
	      */
	      image_debug_type_unknown  = 0x00000000,

	      /* ms_pe_coff: 0x00000001 - the coff debug information (line
		 numbers, symbol table, and string table). this type of
		 debug information is also pointed to by fields in the
		 file headers.
	      */
	      image_debug_type_coff      = 0x1,

	      /* ms_pe_coff: 0x00000002 - the visual c++ debug
		 information. */
	      image_debug_type_codeview  = 0x2,

	      /* ms_pe_coff: 0x00000003 - the frame pointer omission (fpo)
		 information. this information tells the debugger how to
		 interpret nonstandard stack frames, which use the ebp
		 register for a purpose other than as a frame pointer.
	      */
	      image_debug_type_fpo       = 0x3,

	      /* ms_pe_coff: 0x00000004 - the location of dbg file. */
	      image_debug_type_misc      = 0x4,

	      /* ms_pe_coff: 0x00000005 - a copy of .pdata section. */
	      image_debug_type_exception = 0x5,

	      /* ms_pe_coff: 0x00000006 - reserved. */
	      image_debug_type_fixup     = 0x6,

	      /* ms_pe_coff: 0x00000007 - the mapping from an rva in image
		 to an rva in source image.
	      */
	      image_debug_type_omap_to_src = 0x7,

	      /* ms_pe_coff: 0x00000008 - the mapping from an rva in
		 source image to an rva in image.
	      */
	      image_debug_type_omap_from_src = 0x8,

	      /* ms_pe_coff: 0x00000009 - reserved for borland */
	      image_debug_type_borland = 0x9,
          
	      /* ms_pe_coff: 0x0000000a - reserved.*/
	      image_debug_type_reserved10 = 0xa,

	      /* ms_pe_coff: 0x0000000b - reserved. */
	      image_debug_type_clsid = 0xb
	    };

	    //----------------------
	    //     functions
	    //----------------------
	    static std::string get_type_name ( boost::uint32_t type );
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_DEBUG_TYPES_HPP_INCLUDED
