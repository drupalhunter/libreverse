/*  PE_Header_32.cpp

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

#include "PE_Header_32.h"
#include "Coff_Header.h"
#include "PE_Meta_Info.h"
#include "PE_Optional_Header_32.h"

#include "io/Byte_Converter.h"

#include <iomanip>
#include <sstream>
#include <boost/format.hpp>
#include <iostream>

namespace libreverse { namespace wpef_module {

    boost::uint16_t const PE_Header_32::PE_MAGIC_SIGNATURE = 0x4550;

    boost::uint16_t const PE_Header_32::LE_MAGIC_SIGNATURE = 0x454C;

    boost::uint16_t const PE_Header_32::NE_MAGIC_SIGNATURE = 0x454E;

    PE_Header_32::PE_Header_32 ()
    {}

    void PE_Header_32::convert ()
    {
        m_coff_hdr_ptr->convert ();
        m_opt_hdr_ptr->convert ();
    }

    bool PE_Header_32::needs_Convert ()
    {
        bool output = true;

        if ( ( p_magic == PE_MAGIC_SIGNATURE ) ||
             ( p_magic == LE_MAGIC_SIGNATURE ) ||
             ( p_magic == NE_MAGIC_SIGNATURE ) )
        {
            output = false;
        }

        return output;
    }

    boost::uint32_t
    PE_Header_32::get_size () const
    {
        return static_cast<boost::uint32_t>(32);
    }

    std::string
    PE_Header_32::to_String ()
    {
        std::stringstream output_str;

        output_str << "PE Header:" << std::endl;

        output_str << boost::format("  Magic: 0x%1%") %
            boost::io::group(std::setfill('0'), std::hex, std::setw(8), p_magic)
                   << std::endl;

        output_str << m_coff_hdr_ptr->to_String() << std::endl;

        output_str << m_opt_hdr_ptr->to_String() << std::endl;

        return output_str.str();

    }

    bool PE_Header_32::is_PE_File () const
    {
        return (p_magic == PE_MAGIC_SIGNATURE);
    }

    std::string
    PE_Header_32::get_File_Type (void) const
    {
        /* I don't know if DOS EXE files were statically linked or
           not. For now we simply return that all EXE files are Executable
           files. */

      return PE_Meta_Info::PE_FILE_TYPE_32BIT;
    }

    std::string
    PE_Header_32::get_Arch_Type (void) const
    {
        /* TODO: We need to determine CPU architecture if possible. For
           now we simply say i386 */
        return "intel:i386";
    }

    wpef_types::COFF_Header::ptr_t
    PE_Header_32::get_COFF_Header (void) const
    {
        return m_coff_hdr_ptr;
    }

    void
    PE_Header_32::set_COFF_Header ( wpef_types::COFF_Header::ptr_t c_ptr )
    {
        m_coff_hdr_ptr = c_ptr;
    }

    wpef_types::PE_Optional_Header_32::ptr_t
    PE_Header_32::get_Optional_Header (void) const
    {
        return m_opt_hdr_ptr;
    }

    void
    PE_Header_32::set_Optional_Header ( wpef_types::PE_Optional_Header_32::ptr_t o_ptr )
    {
        m_opt_hdr_ptr = o_ptr;
    }

    bool
    PE_Header_32::is_Valid () const
    {
        return this->is_PE_File() &
            m_coff_hdr_ptr->is_Valid();
    }

    boost::uint32_t
    PE_Header_32::get_Magic_Number (void) const
    {
        return p_magic;
    }

} /* namespace wpef_module */
} /* namespace libreverse */
