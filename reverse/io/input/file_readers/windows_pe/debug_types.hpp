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

#ifndef DEBUG_TYPES_H_
#define DEBUG_TYPES_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace wpef_module {

  class Debug_Types {
  public:

      enum Values {

          /* MS_PE_COFF: 0x00000000 - An unknown value that is ignored
             by all tools.
          */
          IMAGE_DEBUG_TYPE_UNKNOWN  = 0x00000000,

          /* MS_PE_COFF: 0x00000001 - The COFF debug information (line
             numbers, symbol table, and string table). This type of
             debug information is also pointed to by fields in the
             file headers.
          */
          IMAGE_DEBUG_TYPE_COFF      = 0x1,

          /* MS_PE_COFF: 0x00000002 - The Visual C++ debug
             information. */
          IMAGE_DEBUG_TYPE_CODEVIEW  = 0x2,

          /* MS_PE_COFF: 0x00000003 - The frame pointer omission (FPO)
             information. This information tells the debugger how to
             interpret nonstandard stack frames, which use the EBP
             register for a purpose other than as a frame pointer.
          */
          IMAGE_DEBUG_TYPE_FPO       = 0x3,

          /* MS_PE_COFF: 0x00000004 - The location of DBG file. */
          IMAGE_DEBUG_TYPE_MISC      = 0x4,

          /* MS_PE_COFF: 0x00000005 - A copy of .pdata section. */
          IMAGE_DEBUG_TYPE_EXCEPTION = 0x5,

          /* MS_PE_COFF: 0x00000006 - Reserved. */
          IMAGE_DEBUG_TYPE_FIXUP     = 0x6,

          /* MS_PE_COFF: 0x00000007 - The mapping from an RVA in image
             to an RVA in source image.
          */
          IMAGE_DEBUG_TYPE_OMAP_TO_SRC = 0x7,

          /* MS_PE_COFF: 0x00000008 - The mapping from an RVA in
             source image to an RVA in image.
          */
          IMAGE_DEBUG_TYPE_OMAP_FROM_SRC = 0x8,

          /* MS_PE_COFF: 0x00000009 - Reserved for Borland */
          IMAGE_DEBUG_TYPE_BORLAND = 0x9,
          
          /* MS_PE_COFF: 0x0000000A - Reserved.*/
          IMAGE_DEBUG_TYPE_RESERVED10 = 0xA,

          /* MS_PE_COFF: 0x0000000B - Reserved. */
          IMAGE_DEBUG_TYPE_CLSID = 0xB
      };

      //----------------------
      //     FUNCTIONS
      //----------------------
      static std::string get_Type_Name ( boost::uint32_t type );
  };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* DEBUG_TYPES_H_ */
