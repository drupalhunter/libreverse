/*  PE_Section_Header.cpp

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

#include "PE_Section_Header.h"
#include "Section_Flags.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>

namespace libreverse
{
    namespace wpef_module
    {

        const boost::uint32_t PE_Section_Header::SECTION_NAME_SIZE = 8;

        PE_Section_Header::PE_Section_Header()
                : m_virtual_size ( 0 ),
                m_virtual_address ( 0 ),
                m_size_of_raw_data ( 0 ),
                m_pointer_to_raw_data ( 0 ),
                m_pointer_to_relocations ( 0 ),
                m_pointer_to_line_numbers ( 0 ),
                m_number_of_relocations ( 0 ),
                m_number_of_line_numbers ( 0 ),
                m_characteristics ( 0 )
        {}

        std::string const
        PE_Section_Header::get_Name ( void ) const
        {
            std::stringstream result;
            result << m_name;
            return result.str();
        }

        boost::uint32_t
        PE_Section_Header::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

      std::string
      PE_Section_Header::to_String ( void ) const
        {
            std::stringstream output_str;

            output_str << "PE Section Header:" << std::endl
            << "  Name:             " << m_name << std::endl;

            output_str << boost::format ( "  Virtual Size:            %1%" ) %
            boost::io::group ( std::hex,
                               m_virtual_size )
            << std::endl;

            output_str << boost::format ( "  Virtual Address:         %1%" ) %
            boost::io::group ( std::hex,
                               m_virtual_address )
            << std::endl;

            output_str << boost::format ( "  Size of raw data:        %1%" ) %
            boost::io::group ( std::hex,
                               m_size_of_raw_data )
            << std::endl;

            output_str << boost::format ( "  Pointer to raw data:     %1%" ) %
            boost::io::group ( std::hex,
                               m_pointer_to_raw_data )
            << std::endl;

            output_str << boost::format ( "  Pointer to relocations:  %1%" ) %
            boost::io::group ( std::hex,
                               m_pointer_to_relocations )
            << std::endl;

            output_str << boost::format ( "  Pointer to line numbers: %1%" ) %
            boost::io::group ( std::hex,
                               m_pointer_to_line_numbers )
            << std::endl;

            output_str << boost::format ( "  No. of Relocations:      %1%" ) %
            boost::io::group ( std::hex,
                               m_number_of_relocations )
            << std::endl;

            output_str << boost::format ( "  No. of Line Numbers:     %1%" ) %
            boost::io::group ( std::hex,
                               m_number_of_line_numbers )
            << std::endl;

            output_str << boost::format ( "  Characteristics:         %1%" ) %
            boost::io::group ( std::hex,
                               m_characteristics )
            << std::endl;

            output_str << get_Characteristics_String() << std::endl;

            return output_str.str();

        }

        void PE_Section_Header::convert ()
        {
            io::Byte_Converter::convert ( m_virtual_size );
            io::Byte_Converter::convert ( m_virtual_address );
            io::Byte_Converter::convert ( m_size_of_raw_data );
            io::Byte_Converter::convert ( m_pointer_to_raw_data );
            io::Byte_Converter::convert ( m_pointer_to_relocations );
            io::Byte_Converter::convert ( m_pointer_to_line_numbers );
            io::Byte_Converter::convert ( m_number_of_relocations );
            io::Byte_Converter::convert ( m_number_of_line_numbers );
            io::Byte_Converter::convert ( m_characteristics );
        }

        std::string
        PE_Section_Header::get_Characteristics_String ( void ) const
        {
            std::stringstream output_str;

            output_str << Section_Flags::get_Flag_Name_List ( m_characteristics )
            << std::endl;

            return output_str.str();
        }

        bool
        PE_Section_Header::has_Initialized_Data ( void ) const
        {
            return Section_Flags::has_Initialized_Data ( m_characteristics );
        }

        bool
        PE_Section_Header::has_Uninitialized_Data ( void ) const
        {
            return Section_Flags::has_Uninitialized_Data ( m_characteristics );
        }

        bool
        PE_Section_Header::has_Code ( void ) const
        {
            return Section_Flags::has_Code ( m_characteristics );
        }

        boost::uint32_t
        PE_Section_Header::get_Virtual_Size ( void ) const
        {
            return m_virtual_size;
        }

        boost::uint32_t
        PE_Section_Header::get_Virtual_Address ( void ) const
        {
            return m_virtual_address;
        }

        boost::uint32_t
        PE_Section_Header::get_Size_Of_Raw_Data ( void ) const
        {
            return m_size_of_raw_data;
        }

        boost::uint32_t
        PE_Section_Header::get_Pointer_To_Raw_Data ( void ) const
        {
            return m_pointer_to_raw_data;
        }

        boost::uint32_t
        PE_Section_Header::get_Pointer_To_Relocations ( void ) const
        {
            return m_pointer_to_relocations;
        }

        boost::uint32_t
        PE_Section_Header::get_Pointer_To_Line_Numbers ( void ) const
        {
            return m_pointer_to_line_numbers;
        }

        boost::uint16_t
        PE_Section_Header::get_Relocation_Count ( void ) const
        {
            return m_number_of_relocations;
        }

        boost::uint16_t
        PE_Section_Header::get_Line_Number_Count ( void ) const
        {
            return m_number_of_line_numbers;
        }

        boost::uint32_t
        PE_Section_Header::get_Characteristics_Value ( void ) const
        {
            return m_characteristics;
        }

    } /* namespace wpef_module */
} /* namespace libreverse */

