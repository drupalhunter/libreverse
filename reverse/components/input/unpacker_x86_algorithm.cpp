/*  Unpacker_X86_Algorithm.cpp

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

#include "Unpacker_X86_Algorithm.h"
#include "data_containers/memory_map.h"
#include "meta/meta_object.h"
#include <boost/format.hpp>

using namespace reverse::meta;

namespace reverse { namespace component {

    const std::string Unpacker_X86_Algorithm::RED_STRING = "\033[1;31m";
    const std::string Unpacker_X86_Algorithm::GREEN_STRING = "\033[1;32m";
    const std::string Unpacker_X86_Algorithm::WHITE_STRING = "\033[1;37m";

    Unpacker_X86_Algorithm::Unpacker_X86_Algorithm ()
        : m_code_offset ( 0 ),
          m_code_length ( 0 ),
          m_data_offset ( 0 ),
          m_data_length ( 0 ),
          m_entry_point ( 0 ),
          m_base_address ( 0 )
    {}

    data_types::memory_map::const_ptr_t
    Unpacker_X86_Algorithm::run ( meta::meta_object::const_ptr_t meta_ptr,
                                  data_types::memory_map::const_ptr_t file_map_ptr )
    {
        m_file_map = file_map_ptr;

        // Grab input meta information
        // - code offset
        meta_object::Data_Pair_t value_pair = meta_ptr->get_Value ( "code_section_address" );
        assert ( value_pair.second == meta_object::STRING );
        std::string str_val = value_pair.first;
        m_code_offset = meta_ptr->convert_To_UInt32 ( str_val );

        // - code length
        value_pair = meta_ptr->get_Value ( "code_section_size" );
        assert ( value_pair.second == meta_object::HEX );
        str_val = value_pair.first;
        m_code_length = meta_ptr->convert_To_UInt32 ( str_val );

        // - data offset
        value_pair = meta_ptr->get_Value ( "data_section_address" );
        assert ( value_pair.second == meta_object::HEX );
        str_val = value_pair.first;
        m_data_offset = meta_ptr->convert_To_UInt32 ( str_val );

        // - data length
        value_pair = meta_ptr->get_Value ( "data_section_size" );
        assert ( value_pair.second == meta_object::HEX );
        str_val = value_pair.first;
        m_data_length = meta_ptr->convert_To_UInt32 ( str_val );

        // - get entry point
        value_pair = meta_ptr->get_Value ( "entry_point_address" );
        assert ( value_pair.second == meta_object::HEX );
        str_val = value_pair.first;
        m_entry_point = meta_ptr->convert_To_UInt32 ( str_val );

        // - get base point
        value_pair = meta_ptr->get_Value ( "base_address" );
        assert ( value_pair.second == meta_object::HEX );
        str_val = value_pair.first;
        m_base_address = meta_ptr->convert_To_UInt32 ( str_val );

        value_pair = meta_ptr->get_Value ( "arch_type" );
        assert ( value_pair.second == meta_object::STRING );
        std::string arch_str_val = value_pair.first;

        //cpu::CPU_Factory::ptr_t cpu_fact_ptr = cpu::CPU_Factory::get_Factory();
        //cpu::Simulator_Base::ptr_t sim_ptr =
        //cpu_fact_ptr->get_CPU ( arch_str_val );

        // Output DLLs required in this file.

        // Execute the binary
        //sim_ptr->init ( file_map_ptr, entry_point + base_address );

        return data_types::memory_map::ptr_t();
    }

    void
    Unpacker_X86_Algorithm::create_Color_Map ()
    {
        COLOR_VALUE c_val = WHITE;

        boost::uint32_t code_limit = m_code_offset + m_code_length;
        boost::uint32_t data_limit = m_data_offset + m_data_length;

        for ( boost::uint32_t index = 0;
              index < m_file_map->size();
              index++ )
            {
                if ( ( index >= m_code_offset ) && ( index < code_limit ) )
                    {
                        c_val = GREEN;
                    }
                else if ( ( index >= m_data_offset ) && ( index <= data_limit ) )
                    {
                        c_val = RED;
                    }
                else
                    {
                        c_val = WHITE;
                    }

                m_color_map.insert ( std::make_pair ( index, c_val ) );
            }
    }

    void
    Unpacker_X86_Algorithm::print_Color_Map (void)
    {
        if ( m_file_map.get() == 0 )
            {
                throw errors::component_exception
                    ( errors::component_exception::null_pointer );
            }

        boost::uint8_t byte_counter = 0;
        boost::uint32_t* address = 0;
        boost::uint32_t index = 0;
        boost::uint16_t value = 0;
        data_types::memory_map::const_iterator map_pos = m_file_map->begin();

        this->create_Color_Map();

        std::cout << "Unpacker - Color Map:" << std::endl
               << "----------------------------------------" << std::endl;

        for ( Color_Map_t::const_iterator cpos = m_color_map.begin();
              cpos != m_color_map.end();
              cpos++ )
            {
                value = (*cpos).second;

                switch ( value )
                    {
                    case GREEN:
                        {
                            std::cout << GREEN_STRING;
                            break;
                        }
                    case RED:
                        {
                            std::cout << RED_STRING;
                            break;
                        }
                    case WHITE:
                    default:
                        {
                            std::cout << WHITE_STRING;
                            break;
                        }
                    }

                if ( byte_counter == 0 )
                    {
                        address = reinterpret_cast<boost::uint32_t*>
                            ( const_cast<boost::uint8_t*>( &(*map_pos) ) );
                        std::cout << boost::format("%1p (%2X): ") %
                            address %
                            index;
                    }

                // Print out value
                std::cout << boost::format("%1%") %
                    boost::io::group ( std::hex,
                                       std::setw(2),
                                       std::setfill('0'),
                                       static_cast<boost::uint16_t>( *map_pos ) );

                if ( ( byte_counter == 3 ) ||
                     ( byte_counter == 7 ) ||
                     ( byte_counter == 11 ) )
                {
                    std::cout << "  ";
                    byte_counter++;
                }
                else if ( byte_counter != 15 )
                    {
                        std::cout << " ";
                        byte_counter++;
                    }
                else
                    {
                        byte_counter = 0;
                        std::cout << std::endl;
                    }

                map_pos++;
                index++;
            }
        std::cout << "\033[1;37m" << std::endl;
    }

    infrastructure_types::Component::Meta_List_t
    Unpacker_X86_Algorithm::get_Meta_Input_List_Impl (void)
    {
        infrastructure_types::Component::Meta_List_t result;
        result.push_back ( "code_section_address" );
        result.push_back ( "code_section_size" );
        result.push_back ( "data_section_address" );
        result.push_back ( "data_section_size" );
        result.push_back ( "entry_point_address" );
        result.push_back ( "base_address" );
        result.push_back ( "arch_type" );
        return result;
    }


} /* namespace component */
} /* namespace reverse */

