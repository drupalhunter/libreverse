/*  Section_Flags.h

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

#ifndef SECTION_FLAGS_H_
#define SECTION_FLAGS_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace wpef_module {

  class Section_Flags {
  public:

      /* MS_PE_COFF: 0x00000000 - Reserved for future use */
      static const boost::uint32_t IMAGE_RESERVED_ZERO;

      /* MS_PE_COFF: 0x00000001 - Reserved for future use */
      static const boost::uint32_t IMAGE_RESERVED_ONE;

      /* MS_PE_COFF: 0x00000002 - Reserved for future use */
      static const boost::uint32_t IMAGE_RESERVED_TWO;

      /* MS_PE_COFF: 0x00000004 - Reserved for future use */
      static const boost::uint32_t IMAGE_RESERVED_FOUR;

      /* MS_PE_COFF: 0x00000008 - The section should not be padded to
         the next boundary.  This flag is obsolete and is replaced by
         IMAGE_SCN_ALIGN_1BYTE S. This is valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_TYPE_NO_PAD;

      /* MS_PE_COFF: 0x00000010 - Reserved for future use */
      static const boost::uint32_t IMAGE_RESERVED_TEN;

      /* MS_PE_COFF: 0x00000020 - The section contains executable
         code. */
      static const boost::uint32_t IMAGE_SCN_CNT_CODE;

      /* MS_PE_COFF: 0x00000040 - The section contains initialized
         data.
      */
      static const boost::uint32_t IMAGE_SCN_CNT_INITIALIZED_DATA;

      /* MS_PE_COFF: 0x00000080 - The section contains uninitialized
         data.
      */
      static const boost::uint32_t IMAGE_SCN_CNT_UNINITIALIZED_DATA;

      /* MS_PE_COFF: 0x00000100 - Reserved for future use */
      static const boost::uint32_t IMAGE_SCN_LNK_OTHER;

      /* MS_PE_COFF: 0x00000200 - The section contains comments or
         other information. The .drectve section has this type. This
         is valid for object files only.
      */
      static const boost::uint32_t IMAGE_SCN_LNK_INFO;

      /* MS_PE_COFF: 0x00000400 - Reserved for future use */
      static const boost::uint32_t IMAGE_RESERVED_FOUR_HUNDRED;

      /* MS_PE_COFF: 0x00000800 - The section will not become part of
         the image. This is valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_LNK_REMOVE;

      /* MS_PE_COFF: 0x00001000 - The section contains COMDAT
         data. For more information, see section 5.5.6, "COMDAT Sections
         (Object Only)." This is valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_LNK_COMDAT;

      /* MS_PE_COFF: 0x00008000 - The section contains data referenced
         through the global pointer (GP).
      */
      static const boost::uint32_t IMAGE_SCN_GPREL;

      /* MS_PE_COFF: 0x00020000 - Reserved for future use */
      static const boost::uint32_t IMAGE_SCN_MEM_PURGEABLE;

      /* MS_PE_COFF: 0x00020000 - Reserved for future use */
      static const boost::uint32_t IMAGE_SCN_MEM_16BIT;

      /* MS_PE_COFF: 0x00040000 - Reserved for future use */
      static const boost::uint32_t IMAGE_SCN_MEM_LOCKED;

      /* MS_PE_COFF: 0x00080000 - Reserved for future use */
      static const boost::uint32_t IMAGE_SCN_MEM_PRELOAD;

      /* MS_PE_COFF: 0x00100000 - Align data on a 1-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_1BYTES;

      /* MS_PE_COFF: 0x00200000 - Align data on a 2-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_2BYTES;

      /* MS_PE_COFF: 0x00300000 - Align data on a 4-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_4BYTES;

      /* MS_PE_COFF: 0x00400000 - Align data on a 8-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_8BYTES;

      /* MS_PE_COFF: 0x00500000 - Align data on a 16-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_16BYTES;

      /* MS_PE_COFF: 0x00600000 - Align data on a 32-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_32BYTES;

      /* MS_PE_COFF: 0x00700000 - Align data on a 64-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_64BYTES;

      /* MS_PE_COFF: 0x00800000 - Align data on a 128-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_128BYTES;

      /* MS_PE_COFF: 0x00900000 - Align data on a 256-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_256BYTES;

      /* MS_PE_COFF: 0x00A00000 - Align data on a 512-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_512BYTES;

      /* MS_PE_COFF: 0x00B00000 - Align data on a 1024-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_1024BYTES;

      /* MS_PE_COFF: 0x00C00000 - Align data on a 2048-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_2048BYTES;

      /* MS_PE_COFF: 0x00D00000 - Align data on a 4096-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_4096BYTES;

      /* MS_PE_COFF: 0x00E00000 - Align data on a 8192-byte
         boundary. Valid only for object files.
      */
      static const boost::uint32_t IMAGE_SCN_ALIGN_8192BYTES;

      /* MS_PE_COFF: 0x01000000 - The section contains extended
         relocations.

         IMAGE_SCN_LNK_NRELOC_OVFL indicates that the count of
         relocations for the section exceeds the 16 bits that are
         reserved for it in the section header. If the bit is set and
         the NumberOfRelocations field in the section header is
         0xffff, the actual relocation count is stored in the 32-bit
         VirtualAddress field of the first relocation. It is an error
         if IMAGE_SCN_LNK_NRELOC_OVFL is set and there are fewer than
         0xffff relocations in the section.
      */
      static const boost::uint32_t IMAGE_SCN_LNK_NRELOC_OVFL;

      /* MS_PE_COFF: 0x02000000 - The section can be discarded as
         needed.
      */
      static const boost::uint32_t IMAGE_SCN_MEM_DISCARDABLE;

      /* MS_PE_COFF: 0x04000000 - The section cannot be cached. */
      static const boost::uint32_t IMAGE_SCN_MEM_NOT_CACHED;

      /* MS_PE_COFF: 0x08000000 - The section is not pageable. */
      static const boost::uint32_t IMAGE_SCN_MEM_NOT_PAGED;

      /* MS_PE_COFF: 0x10000000 - The section can be shared in
         memory. */
      static const boost::uint32_t IMAGE_SCN_MEM_SHARED;

      /* MS_PE_COFF: 0x20000000 - The section can be executed as
         code. */
      static const boost::uint32_t IMAGE_SCN_MEM_EXECUTE;

      /* MS_PE_COFF: 0x40000000 - The section can be read */
      static const boost::uint32_t IMAGE_SCN_MEM_READ;

      /* MS_PE_COFF: 0x80000000 - The section can be written to */
      static const boost::uint32_t IMAGE_SCN_MEM_WRITE;

      static std::string get_Flag_Name ( boost::uint32_t const& flag );

      static std::string get_Flag_Name_List ( boost::uint32_t const& val );

      static bool has_Initialized_Data ( boost::uint32_t const& val );

      static bool has_Uninitialized_Data ( boost::uint32_t const& val );

      static bool has_Code ( boost::uint32_t const& val );
  };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* SECTION_FLAGS_H_ */
