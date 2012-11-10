/*  PE_Information_Block.cpp

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

#include "PE_Information_Block.h"
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>
#include <iostream>
#include <iomanip>

namespace libreverse { namespace wpef_module {

    PE_Information_Block::PE_Information_Block()
        : p_magic (0),
          p_link_version (0),
          p_link_revision (0),
          p_entry_offset (0),
          p_entry_len (0),
          p_res (0),
          p_exe_flags (0),
          p_auto_data_seg_id (0),
          p_heap_size (0),
          p_stack_size (0),
          p_csip_offset (0),
          p_sssp_offset (0),
          p_seg_num (0),
          p_mod_ref_num (0),
          p_nonres_num (0),
          p_seg_offset (0),
          p_resource_offset (0),
          p_resident_name_offset (0),
          p_mod_ref_offset (0),
          p_import_name_offset (0),
          p_mov_entry_num (0),
          p_shift_count (0),
          p_res_seg_count (0),
          p_target_os (0),
          p_additional_info (0),
          p_fast_load_offset (0),
          p_fast_load_len (0),
          p_res2 (0),
          p_win_version (0)
    {}

    boost::uint32_t
    PE_Information_Block::get_size (void) const
    {
        return static_cast<boost::uint32_t>(32);
    }

    /*!
     * \brief Convert the header data into a string representation
     * \return String representation of header data
     */
    std::string
    PE_Information_Block::to_String (void)
    {
        std::stringstream output_str;

        output_str << "PE Information block:" << std::endl;

        output_str << boost::format("  Magic: 0x%1%") %
            boost::io::group(std::setfill('0'), std::hex, std::setw(4), p_magic)
                   << std::endl;

        output_str << "  Linker version:   " << p_link_version << std::endl
                   << "  Linker revision:        " << p_link_revision << std::endl
                   << "  Entry offset:     " << p_entry_offset << std::endl
                   << "  Length of entry table (bytes): " << p_entry_len
                   << std::endl
                   << "  Reserved space: " << p_res << std::endl
                   << "  EXE flags: " << p_exe_flags << std::endl
                   << "  Automatic data segment number: " << p_seg_num 
                   << std::endl
                   << "  Heap size (bytes): " << p_heap_size << std::endl
                   << "  Stack size (bytes): " << p_stack_size << std::endl;

        output_str << boost::format("  CS:IP offset: 0x%1%") %
            boost::io::group(std::setfill('0'),
                             std::hex,
                             std::setw(8),
                             p_csip_offset)
                   << std::endl;

        output_str << boost::format("  SS:SP offset: 0x%1%") %
            boost::io::group(std::setfill('0'),
                             std::hex,
                             std::setw(8),
                             p_sssp_offset)
                   << std::endl;

        output_str << "  Segment table size: " << p_seg_num << std::endl
                   << "  Module reference table size: " << p_mod_ref_num
                   << std::endl
                   << "  Nonresident name table size: " << p_nonres_num
                   << std::endl
                   << "  Segment offset: " << p_seg_offset
                   << std::endl
                   << "  Resource table offset: " << p_resource_offset
                   << std::endl
                   << "  Resident name table offset: " << p_resident_name_offset
                   << std::endl
                   << "  Module-reference table offset: " << p_mod_ref_offset
                   << std::endl
                   << "  Import name table offset: " << p_import_name_offset
                   << std::endl
                   << "  Non-resident table offset: " << p_nonres_name_offset
                   << std::endl
                   << "  Movable entry point size: " << p_mov_entry_num
                   << std::endl
                   << "  Shift count: " << p_shift_count
                   << std::endl
                   << "  Resource segment size: " << p_res_seg_count
                   << std::endl
                   << "  Target OS: " << p_target_os
                   << std::endl
                   << "  Additional Info: " << p_additional_info
                   << std::endl
                   << "  Fast load offset: " << p_fast_load_offset
                   << std::endl
                   << "  Fast load length: " << p_fast_load_len << std::endl
                   << "  Reserved2: " << p_res2 << std::endl
                   << "  Windows version: " << p_win_version << std::endl;

        return output_str.str();
    }

    /*!
     * \brief Convert the bit order of the stored data if host and data
     * endian types differ
     *
     * \param host_endian Endian type of host
     * \param data_endian Endian type of data
     */
    void
    PE_Information_Block::convert (bool host_endian, bool data_endian)
    {
        if (host_endian != data_endian) {
            io::Byte_Converter::convert (p_magic);
            io::Byte_Converter::convert (p_link_version);
            io::Byte_Converter::convert (p_link_revision);
            io::Byte_Converter::convert (p_entry_offset);
            io::Byte_Converter::convert (p_entry_len);
            io::Byte_Converter::convert (p_res);
            io::Byte_Converter::convert (p_exe_flags);
            io::Byte_Converter::convert (p_auto_data_seg_id);
            io::Byte_Converter::convert (p_heap_size);
            io::Byte_Converter::convert (p_stack_size);
            io::Byte_Converter::convert (p_csip_offset);
            io::Byte_Converter::convert (p_sssp_offset);
            io::Byte_Converter::convert (p_seg_num);
            io::Byte_Converter::convert (p_mod_ref_num);
            io::Byte_Converter::convert (p_nonres_num);
            io::Byte_Converter::convert (p_seg_offset);
            io::Byte_Converter::convert (p_resource_offset);
            io::Byte_Converter::convert (p_resident_name_offset);
            io::Byte_Converter::convert (p_mod_ref_offset);
            io::Byte_Converter::convert (p_import_name_offset);
            io::Byte_Converter::convert (p_mov_entry_num);
            io::Byte_Converter::convert (p_shift_count);
            io::Byte_Converter::convert (p_res_seg_count);
            io::Byte_Converter::convert (p_fast_load_offset);
            io::Byte_Converter::convert (p_fast_load_len);
            io::Byte_Converter::convert (p_res2);
            io::Byte_Converter::convert (p_win_version);
        }
    }

    bool PE_Information_Block::is_PE_File_Impl (void)
    {
        return (p_magic == PE_MAGIC_SIGNATURE);
    }

} /* namespace wpef_module */
} /* namespace libreverse */
