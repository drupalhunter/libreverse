/*  Elf_Header_Eident.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_EIDENT_HEADER_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_EIDENT_HEADER_HPP

#include <boost/cstdint.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace reverse {
namespace io {
namespace input {
namespace file_readers {
namespace linux_elf {

struct elf_eident_header {

     //! \brief ELF class type
     boost::uint8_t class_type;

     //! \brief ELF data encoding
     boost::uint8_t data_encoding;

     //! \brief ELF file version
     boost::uint8_t file_version;

     //! \brief Operating system/ABI indication
     boost::uint8_t os_abi_identification;

     //! \brief ABI version
     boost::uint8_t abi_version;

};

} // namespace linux_elf
} // namespace file_readers
} // namespace input
} // namespace io
} // namespace reverse

BOOST_FUSION_ADAPT_STRUCT (
     reverse::io::input::file_readers::linux_elf::elf_eident_header,
     ( boost::uint8_t, class_type )
     ( boost::uint8_t, data_encoding )
//   (boost::uint8_t, file_version)
//   (boost::uint8_t, os_abi_identification)
//   (boost::uint8_t, abi_version)
)

#endif /* ELF_HEADER_EIDENT_ */
