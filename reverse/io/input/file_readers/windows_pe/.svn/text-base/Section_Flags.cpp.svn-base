/*  Section_Flags.cpp

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

#include "Section_Flags.h"
#include <sstream>

namespace libreverse { namespace wpef_module {

    const boost::uint32_t Section_Flags::IMAGE_RESERVED_ZERO              = 0x00000000 ;
    const boost::uint32_t Section_Flags::IMAGE_RESERVED_ONE               = 0x00000001 ;
    const boost::uint32_t Section_Flags::IMAGE_RESERVED_TWO               = 0x00000002 ;
    const boost::uint32_t Section_Flags::IMAGE_RESERVED_FOUR              = 0x00000004 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_TYPE_NO_PAD            = 0x00000008 ;
    const boost::uint32_t Section_Flags::IMAGE_RESERVED_TEN               = 0x00000010 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_CNT_CODE               = 0x00000020 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_CNT_INITIALIZED_DATA   = 0x00000040 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_LNK_OTHER              = 0x00000100 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_LNK_INFO               = 0x00000200 ;
    const boost::uint32_t Section_Flags::IMAGE_RESERVED_FOUR_HUNDRED      = 0x00000400 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_LNK_REMOVE             = 0x00000800 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_LNK_COMDAT             = 0x00001000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_GPREL                  = 0x00008000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_PURGEABLE          = 0x00020000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_16BIT              = 0x00020000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_LOCKED             = 0x00040000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_PRELOAD            = 0x00080000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_1BYTES           = 0x00100000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_2BYTES           = 0x00200000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_4BYTES           = 0x00300000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_8BYTES           = 0x00400000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_16BYTES          = 0x00500000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_32BYTES          = 0x00600000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_64BYTES          = 0x00700000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_128BYTES         = 0x00800000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_256BYTES         = 0x00900000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_512BYTES         = 0x00A00000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_1024BYTES        = 0x00B00000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_2048BYTES        = 0x00C00000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_4096BYTES        = 0x00D00000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_ALIGN_8192BYTES        = 0x00E00000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_LNK_NRELOC_OVFL        = 0x01000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_DISCARDABLE        = 0x02000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_NOT_CACHED         = 0x04000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_NOT_PAGED          = 0x08000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_SHARED             = 0x10000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_EXECUTE            = 0x20000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_READ               = 0x40000000 ;
    const boost::uint32_t Section_Flags::IMAGE_SCN_MEM_WRITE              = 0x80000000 ;

    std::string
    Section_Flags::get_Flag_Name ( boost::uint32_t const& flag )
    {
        std::string result = "";

        switch ( flag )
            {
            case IMAGE_RESERVED_ZERO:
                {
                    result = "PE:section_reserved_bit(0x00000000)";
                    break;
                }
            case IMAGE_RESERVED_ONE:
                {
                    result = "PE:section_reserved_bit(0x00000001)";
                    break;
                }
            case IMAGE_RESERVED_TWO:
                {
                    result = "PE:section_reserved_bit(0x00000002)";
                    break;
                }
            case IMAGE_RESERVED_FOUR:
                {
                    result = "PE:section_reserved_bit(0x00000004)";
                    break;
                }
            case IMAGE_SCN_TYPE_NO_PAD:
                {
                    result = "PE:section_not_padded";
                    break;
                }
            case IMAGE_RESERVED_TEN:
                {
                    result = "PE:section_reserved_bit(0x00000010)";
                    break;
                }
            case IMAGE_SCN_CNT_CODE:
                {
                    result = "PE:section_contains_code";
                    break;
                }
            case IMAGE_SCN_CNT_INITIALIZED_DATA:
                {
                    result = "PE:section_has_initialized_data";
                    break;
                }
            case IMAGE_SCN_CNT_UNINITIALIZED_DATA:
                {
                    result = "PE:section_has_uninitialized_data";
                    break;
                }
            case IMAGE_SCN_LNK_OTHER:
                {
                    result = "PE:section_reserved(LNK_OTHER)";
                    break;
                }
            case IMAGE_SCN_LNK_INFO:
                {
                    result = "PE:section_has_comments";
                    break;
                }
            case IMAGE_RESERVED_FOUR_HUNDRED:
                {
                    result = "PE:section_reserved_bit(0x00000400)";
                    break;
                }
            case IMAGE_SCN_LNK_REMOVE:
                {
                    result = "PE:section_linker_removable";
                    break;
                }
            case IMAGE_SCN_LNK_COMDAT:
                {
                    result = "PE:section_has_COMDAT_data";
                    break;
                }
            case IMAGE_SCN_GPREL:
                {
                    result = "PE:section_GP_relative_data";
                    break;
                }
            case IMAGE_SCN_MEM_PURGEABLE:
                //case IMAGE_SCN_MEM_16BIT: (Duplicate)
                {
                    result = "PE:section_reserved(MEM_PURGEABLE)";
                    break;
                }
            case IMAGE_SCN_MEM_LOCKED:
                {
                    result = "PE:section_reserved(MEM_LOCKED)";
                    break;
                }
            case IMAGE_SCN_MEM_PRELOAD:
                {
                    result = "PE:section_reserved(MEM_PRELOAD)";
                    break;
                }
            case IMAGE_SCN_ALIGN_1BYTES:
                {
                    result = "PE:section_aligned_1byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_2BYTES:
                {
                    result = "PE:section_aligned_2byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_4BYTES:
                {
                    result = "PE:section_aligned_4byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_8BYTES:
                {
                    result = "PE:section_aligned_8byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_16BYTES:
                {
                    result = "PE:section_aligned_16byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_32BYTES:
                {
                    result = "PE:section_aligned_32byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_64BYTES:
                {
                    result = "PE:section_aligned_64byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_128BYTES:
                {
                    result = "PE:section_aligned_128byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_256BYTES:
                {
                    result = "PE:section_aligned_256byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_512BYTES:
                {
                    result = "PE:section_aligned_512byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_1024BYTES:
                {
                    result = "PE:section_aligned_1024byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_2048BYTES:
                {
                    result = "PE:section_aligned_2048byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_4096BYTES:
                {
                    result = "PE:section_aligned_4096byte_boundary";
                    break;
                }
            case IMAGE_SCN_ALIGN_8192BYTES:
                {
                    result = "PE:section_aligned_8192byte_boundary";
                    break;
                }
            case IMAGE_SCN_LNK_NRELOC_OVFL:
                {
                    result = "PE:section_has_extended_relocations";
                    break;
                }
            case IMAGE_SCN_MEM_DISCARDABLE:
                {
                    result = "PE:section_can_be_discarded";
                    break;
                }
            case IMAGE_SCN_MEM_NOT_CACHED:
                {
                    result = "PE:section_not_cachable";
                    break;
                }
            case IMAGE_SCN_MEM_NOT_PAGED:
                {
                    result = "PE:section_not_pageable";
                    break;
                }
            case IMAGE_SCN_MEM_SHARED:
                {
                    result = "PE:section_sharable_in_memory";
                    break;
                }
            case IMAGE_SCN_MEM_EXECUTE:
                {
                    result = "PE:section_executable";
                    break;
                }
            case IMAGE_SCN_MEM_READ:
                {
                    result = "PE:section_readable";
                    break;
                }
            case IMAGE_SCN_MEM_WRITE:
                {
                    result = "PE:section_memory_writable";
                    break;
                }
            }

        return result;
    }

    std::string
    Section_Flags::get_Flag_Name_List ( boost::uint32_t const& val )
    {
        std::stringstream output;

        if ( val & IMAGE_RESERVED_ZERO )
            {
                output << get_Flag_Name ( IMAGE_RESERVED_ZERO ) << std::endl;
            }
        if ( val & IMAGE_RESERVED_ONE )
            {
                output << get_Flag_Name ( IMAGE_RESERVED_ONE ) << std::endl;
            }
        if ( val & IMAGE_RESERVED_TWO )
            {
                output << get_Flag_Name ( IMAGE_RESERVED_TWO ) << std::endl;
            }
        if ( val & IMAGE_RESERVED_FOUR )
            {
                output << get_Flag_Name ( IMAGE_RESERVED_FOUR ) << std::endl;
            }
        if ( val & IMAGE_SCN_TYPE_NO_PAD )
            {
                output << get_Flag_Name ( IMAGE_SCN_TYPE_NO_PAD ) << std::endl;
            }
        if ( val & IMAGE_RESERVED_TEN )
            {
                output << get_Flag_Name ( IMAGE_RESERVED_TEN ) << std::endl;
            }
        if ( val & IMAGE_SCN_CNT_CODE )
            {
                output << get_Flag_Name ( IMAGE_SCN_CNT_CODE ) << std::endl;
            }
        if ( val & IMAGE_SCN_CNT_INITIALIZED_DATA )
            {
                output << get_Flag_Name ( IMAGE_SCN_CNT_INITIALIZED_DATA ) << std::endl;
            }
        if ( val & IMAGE_SCN_CNT_UNINITIALIZED_DATA )
            {
                output << get_Flag_Name ( IMAGE_SCN_CNT_UNINITIALIZED_DATA ) << std::endl;
            }
        if ( val & IMAGE_SCN_LNK_OTHER )
            {
                output << get_Flag_Name ( IMAGE_SCN_LNK_OTHER ) << std::endl;
            }
        if ( val & IMAGE_SCN_LNK_INFO )
            {
                output << get_Flag_Name ( IMAGE_SCN_LNK_INFO ) << std::endl;
            }
        if ( val & IMAGE_RESERVED_FOUR_HUNDRED )
            {
                output << get_Flag_Name ( IMAGE_RESERVED_FOUR_HUNDRED ) << std::endl;
            }
        if ( val & IMAGE_SCN_LNK_REMOVE )
            {
                output << get_Flag_Name ( IMAGE_SCN_LNK_REMOVE ) << std::endl;
            }
        if ( val & IMAGE_SCN_LNK_COMDAT )
            {
                output << get_Flag_Name ( IMAGE_SCN_LNK_COMDAT ) << std::endl;
            }
        if ( val & IMAGE_SCN_GPREL )
            {
                output << get_Flag_Name ( IMAGE_SCN_GPREL ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_PURGEABLE )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_PURGEABLE ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_16BIT )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_16BIT ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_LOCKED )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_LOCKED ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_PRELOAD )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_PRELOAD ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_1BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_1BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_2BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_2BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_4BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_4BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_8BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_8BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_16BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_16BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_32BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_32BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_64BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_64BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_128BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_128BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_256BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_256BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_512BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_512BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_1024BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_1024BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_2048BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_2048BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_4096BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_4096BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_ALIGN_8192BYTES )
            {
                output << get_Flag_Name ( IMAGE_SCN_ALIGN_8192BYTES ) << std::endl;
            }
        if ( val & IMAGE_SCN_LNK_NRELOC_OVFL )
            {
                output << get_Flag_Name ( IMAGE_SCN_LNK_NRELOC_OVFL ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_DISCARDABLE )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_DISCARDABLE ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_NOT_CACHED )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_NOT_CACHED ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_NOT_PAGED )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_NOT_PAGED ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_SHARED )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_SHARED ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_EXECUTE )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_EXECUTE ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_READ )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_READ ) << std::endl;
            }
        if ( val & IMAGE_SCN_MEM_WRITE )
            {
                output << get_Flag_Name ( IMAGE_SCN_MEM_WRITE ) << std::endl;
            }

        return output.str();
    }

    bool
    Section_Flags::has_Initialized_Data ( boost::uint32_t const& val )
    {
        bool result = false;

        if ( val & IMAGE_SCN_CNT_INITIALIZED_DATA )
            {
                result = true;
            }
        return result;
    }

    bool
    Section_Flags::has_Uninitialized_Data ( boost::uint32_t const& val )
    {
        bool result = false;

        if ( val & IMAGE_SCN_CNT_UNINITIALIZED_DATA )
            {
                result = true;
            }
        return result;
    }

    bool
    Section_Flags::has_Code ( boost::uint32_t const& val )
    {
        bool result = false;

        if ( val & IMAGE_SCN_CNT_CODE )
            {
                result = true;
            }
        return result;
    }

} /* namespace wpef_module */
} /* namespace libreverse */
