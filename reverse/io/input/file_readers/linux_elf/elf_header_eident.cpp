/*  Elf_Header_Eident.cpp

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

#include "Elf_Header_Eident.h"

#include <string>
#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    const boost::uint8_t Elf_Header_Eident::SIZE = 16;
    const boost::uint32_t Elf_Header_Eident::ELF_MAGIC = 0x464C457F;

    Elf_Header_Eident::Elf_Header_Eident ()
        : m_magic (0),
          m_class (0),
          m_data_encoding (0),
          m_file_version (0),
          m_os_abi (0),
          m_abi_version (0)
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Header_Eident constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Elf_Header_Eident::is_Elf_File ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Header_Eident::is_Elf_File" );
#endif /* LIBREVERSE_DEBUG */


        return ( m_magic == ELF_MAGIC );
    }

    bool
    Elf_Header_Eident::is_Little_Endian (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Header_Eident::is_Little_Endian" );
#endif /* LIBREVERSE_DEBUG */


        bool result = true;

        switch ( m_data_encoding )
            {
                // Sets the read method for the elf read
            case Elf_Common::ELFDATANONE: // fall through
            case Elf_Common::ELFDATA2LSB:
                result = true;
                break;
            case Elf_Common::ELFDATA2MSB:
                result = false;
                break;
            default:
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
                             boost::str ( boost::format ( "Result = %1$X" ) % static_cast<boost::uint16_t>(result) ) );

        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Header_Eident::is_Little_Endian" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    bool
    Elf_Header_Eident::is_32bit (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Inside Elf_Header_Eident::is_32bit" );
#endif /* LIBREVERSE_DEBUG */


        return ( m_class == Elf_Common::ELFCLASS32);
    }

    std::string
    Elf_Header_Eident::to_String (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Header_Eident::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        output_str << "Elf Header:" << std::endl;

        output_str << boost::format( "  Magic:   %1% ") %
            boost::io::group(std::hex,
                             m_magic)
                   << std::endl;

        output_str << "  Class:                             "
                   << get_Elf_Class () << std::endl
                   << "  Data:                              "
                   << get_Data_Encoding () << std::endl
                   << "  Version:                           "
                   << get_Version () << std::endl
                   << "  OS/ABI:                            "
                   << get_Osabi_Name () << std::endl;

        output_str << boost::format("  ABI Version:                       %1%") %
            static_cast<boost::uint16_t>(m_abi_version) << std::endl;

        output_str << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Header_Eident::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output_str.str();
    }

    std::string
    Elf_Header_Eident::get_Elf_Class (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Header_Eident::get_Elf_Class" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream result;

        switch ( m_class )
            {
            case Elf_Common::ELFCLASSNONE:
                result << "none";
                break;
            case Elf_Common::ELFCLASS32:
                result << "ELF32";
                break;
            case Elf_Common::ELFCLASS64:
                result << "ELF64";
                break;
            default:
                result << boost::format ("<unknown: %1%>") %
                    boost::io::group ( std::hex,
                                       static_cast<boost::uint16_t>(m_class) );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Header_Eident::get_Elf_Class" );
#endif /* LIBREVERSE_DEBUG */


        return result.str();
    }

    std::string
    Elf_Header_Eident::get_Data_Encoding ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Header_Eident::get_Data_Encoding" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream result;

        switch ( m_data_encoding )
            {
            case Elf_Common::ELFDATANONE:
                result << "none";
                break;
            case Elf_Common::ELFDATA2LSB:
                result << "2's complement, little endian";
                break;
            case Elf_Common::ELFDATA2MSB:
                result << "2's complement, big endian";
                break;
            default:
                result << boost::format ("<unknown: %1%>") %
                    boost::io::group ( std::hex,
                                       static_cast<boost::uint16_t>(m_data_encoding) );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Header_Eident::get_Data_Encoding" );
#endif /* LIBREVERSE_DEBUG */


        return result.str();
    }

    std::string
    Elf_Header_Eident::get_Version ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Header_Eident::get_Version" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream result;

        result << static_cast<boost::uint16_t>(m_file_version) << " ";

        switch ( m_file_version )
            {
            case  Elf_Common::EV_CURRENT:
                {
                    result << "(current)";
                    break;
                }
            case Elf_Common::EV_NONE:
                {
                    result << "(INVALID)";
                    break;
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Header_Eident::get_Version" );
#endif /* LIBREVERSE_DEBUG */


        return result.str();
    }

    std::string
    Elf_Header_Eident::get_Osabi_Name ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Header_Eident::get_Osabi_Name" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream result;

        switch ( m_os_abi )
            {
            case Elf_Common::ELFOSABI_NONE:
                result << "UNIX - System V";
                break;
            case Elf_Common::ELFOSABI_HPUX:
                result << "UNIX - HP-UX";
                break;
            case Elf_Common::ELFOSABI_NETBSD:
                result << "UNIX - NetBSD";
                break;
            case Elf_Common::ELFOSABI_LINUX:
                result << "UNIX - Linux";
                break;
            case Elf_Common::ELFOSABI_HURD:
                result << "GNU/Hurd";
                break;
            case Elf_Common::ELFOSABI_SOLARIS:
                result << "UNIX - Solaris";
                break;
            case Elf_Common::ELFOSABI_AIX:
                result << "UNIX - AIX";
                break;
            case Elf_Common::ELFOSABI_IRIX:
                result << "UNIX - IRIX";
                break;
            case Elf_Common::ELFOSABI_FREEBSD:
                result << "UNIX - FreeBSD";
                break;
            case Elf_Common::ELFOSABI_TRU64:
                result << "UNIX - TRU64";
                break;
            case Elf_Common::ELFOSABI_MODESTO:
                result << "Novell - Modesto";
                break;
            case Elf_Common::ELFOSABI_OPENBSD:
                result << "UNIX - OpenBSD";
                break;
            case Elf_Common::ELFOSABI_OPENVMS:
                result << "VMS - OpenVMS";
                break;
            case Elf_Common::ELFOSABI_NSK:
                result << "HP - Non-Stop Kernel";
                break;
            case Elf_Common::ELFOSABI_AROS:
                result << "Amiga Research OS";
                break;
            case Elf_Common::ELFOSABI_STANDALONE:
                result << "Standalone App";
                break;
            case Elf_Common::ELFOSABI_ARM:
                result << "ARM";
                break;
            default:
                result << "<unknown:"
                       << boost::format(" %1%") % boost::io::group ( std::hex, m_os_abi )
                       << ">" << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Header_Eident::get_Osabi_Name" );
#endif /* LIBREVERSE_DEBUG */


        return result.str();
    }

} /* namespace elf_module */
} /* namespace libreverse */
