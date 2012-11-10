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

#include "DOS_Header.h"
#include "DOS_Relocation_Header.h"
#include "PE_Meta_Info.h"

#include "io/Byte_Converter.h"

#include <iomanip>
#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace wpef_module {

    boost::uint16_t const DOS_Header::DOS_MAGIC_SIGNATURE = 0x5A4D;

    DOS_Header::DOS_Header()
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
    DOS_Header::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering DOS_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


            io::Byte_Converter::convert (e_cblp);
            io::Byte_Converter::convert (e_cp);
            io::Byte_Converter::convert (e_crlc);
            io::Byte_Converter::convert (e_cparhdr);
            io::Byte_Converter::convert (e_minalloc);
            io::Byte_Converter::convert (e_maxalloc);
            io::Byte_Converter::convert (e_ss);
            io::Byte_Converter::convert (e_sp);
            io::Byte_Converter::convert (e_csum);
            io::Byte_Converter::convert (e_ip);
            io::Byte_Converter::convert (e_cs);
            io::Byte_Converter::convert (e_lfarlc);
            io::Byte_Converter::convert (e_ovno);
            io::Byte_Converter::convert (e_behavior_bits);
            io::Byte_Converter::convert (e_lfanew);

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
    DOS_Header::needs_Convert ()
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering DOS_Header::needs_Convert" );
#endif /* LIBREVERSE_DEBUG */


      bool output = true;

      if ( e_magic == DOS_MAGIC_SIGNATURE )
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

    std::string DOS_Header::to_String ()
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
        for (boost::uint8_t i = 0; i < DOS_Header::RES_SIZE; ++i)
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

        for (boost::uint8_t i = 0; i < DOS_Header::RES2_SIZE; ++i)
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
    DOS_Header::is_DOS_File (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::is_DOS_File" );
#endif /* LIBREVERSE_DEBUG */

        return (e_magic == DOS_MAGIC_SIGNATURE);
    }

    bool
    DOS_Header::has_PE_Header (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::has_PE_Header" );
#endif /* LIBREVERSE_DEBUG */

        return (e_lfanew != 0);
    }

    std::string
    DOS_Header::get_File_Type (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_File_Type" );
#endif /* LIBREVERSE_DEBUG */

        return PE_Meta_Info::DOS_FILE_TYPE;
    }

    std::string
    DOS_Header::get_Arch_Type (void) const
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

    void DOS_Header::add_Reloc_Hdr ( wpef_types::DOS_Relocation_Header::ptr_t obj )
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
    DOS_Header::get_Relocation_Info (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Relocation_Info" );
#endif /* LIBREVERSE_DEBUG */

        return std::make_pair (e_crlc, e_lfarlc);
    }

    boost::uint32_t
    DOS_Header::get_PE_Offset (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_PE_Offset" );
#endif /* LIBREVERSE_DEBUG */

        return e_lfanew;
    }

    boost::uint16_t
    DOS_Header::get_Magic_Number (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Magic_Number" );
#endif /* LIBREVERSE_DEBUG */

        return e_magic;
    }

    boost::uint16_t
    DOS_Header::get_Size_Of_Last_Page (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Size_Of_Last_Page" );
#endif /* LIBREVERSE_DEBUG */

        return e_cblp;
    }

    boost::uint16_t
    DOS_Header::get_Page_Total (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Page_Total" );
#endif /* LIBREVERSE_DEBUG */

        return e_cp;
    }

    boost::uint16_t
    DOS_Header::get_Number_Of_Relocations (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Number_Of_Relocations" );
#endif /* LIBREVERSE_DEBUG */

        return e_crlc;
    }

    boost::uint16_t
    DOS_Header::get_Header_Size (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Header_Size" );
#endif /* LIBREVERSE_DEBUG */

        return e_cparhdr;
    }

    boost::uint16_t
    DOS_Header::get_Minimum_Alloc (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Minimum_Alloc" );
#endif /* LIBREVERSE_DEBUG */

        return e_minalloc;
    }

    boost::uint16_t
    DOS_Header::get_Maximum_Alloc (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Maximum_Alloc" );
#endif /* LIBREVERSE_DEBUG */

        return e_maxalloc;
    }

    boost::uint16_t
    DOS_Header::get_Initial_SS (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Initial_SS" );
#endif /* LIBREVERSE_DEBUG */

        return e_ss;
    }

    boost::uint16_t
    DOS_Header::get_Initial_SP (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Initial_SP" );
#endif /* LIBREVERSE_DEBUG */

        return e_sp;
    }

    boost::uint16_t
    DOS_Header::get_Checksum (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Checksum" );
#endif /* LIBREVERSE_DEBUG */

        return e_csum;
    }

    boost::uint16_t
    DOS_Header::get_IP_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_IP_Value" );
#endif /* LIBREVERSE_DEBUG */

        return e_ip;
    }

    boost::uint16_t
    DOS_Header::get_Initial_CS (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Initial_CS" );
#endif /* LIBREVERSE_DEBUG */

        return e_cs;
    }

    boost::uint16_t
    DOS_Header::get_File_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_File_Address" );
#endif /* LIBREVERSE_DEBUG */

        return e_lfarlc;
    }

    boost::uint16_t
    DOS_Header::get_Overlay_Number (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Overlay_Number" );
#endif /* LIBREVERSE_DEBUG */

        return e_ovno;
    }

    boost::uint8_t const*
    DOS_Header::get_Reserved_Word (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Reserved_Word" );
#endif /* LIBREVERSE_DEBUG */

        return e_res;
    }

    boost::uint16_t
    DOS_Header::get_Behavior_Bits (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Behavior_Bits" );
#endif /* LIBREVERSE_DEBUG */

        return e_behavior_bits;
    }

    boost::uint8_t const*
    DOS_Header::get_Reserved_Word2 (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_Reserved_Word2" );
#endif /* LIBREVERSE_DEBUG */

        return e_res2;
    }

    boost::uint32_t
    DOS_Header::get_EXE_Header_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside DOS_Header::get_EXE_Header_Address" );
#endif /* LIBREVERSE_DEBUG */

        return e_lfanew;
    }
} /* namespace wpef_module */
} /* namespace libreverse */
