/*  memory_map.cpp

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

#include <reverse/assert/assert.hpp>
#include <reverse/data_containers/memory_map.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>
#include <boost/concept_check.hpp>

namespace reverse {
    namespace data_containers {

        memory_map::memory_map ()
            : m_data (),
              m_present_pos ( 0 ),
              m_previous_pos ( 0 ),
              m_base_address ( 0 )
        {
            trace::data_containers_detail ( "Inside memory_map constructor" );
        }

        memory_map::memory_map ( boost::uint32_t size,
                                 boost::uint32_t base_address )
            : m_data ( size, 0 ),
              m_present_pos ( 0 ),
              m_previous_pos ( 0 ),
              m_base_address ( base_address )
        {
            trace::data_containers_detail ( "Entering memory_map constructor (uint32,uint32)" );
            trace::data_containers_data ( "paramaters: size = 0x%1X    base address = 0x%2X",
                                          size,
                                          base_address );

            assert::bool_check ( size != 0, "Size of memory map is zero." );

            assert::bool_check ( ( m_data.size() == size ), "Size of the image data array is not equal to the requested size." );
            assert::bool_check ( ( m_base_address == base_address ), "Base address of image is not equal to the requested address." );

            trace::data_containers_detail ( "Exiting memory_map constructor (uint32,uint32)" );
        }

        memory_map::memory_map ( boost::uint8_t* input_address,
			    std::size_t size,
			    boost::uint32_t base_address )
            : m_present_pos ( 0 ),
              m_previous_pos ( 0 ),
              m_base_address ( base_address )
        {
            trace::data_containers_detail ( "Entering memory_map constructor (ifstream,uint32)" );
            trace::data_containers_data ( "paramaters: ifstream = 0x%1X    base address = 0x%2X",
                                          &input_address,
                                          base_address );

            char byte = 0;

	    std::copy ( input_address,
			input_address + size,
			m_data.begin() );

            trace::data_containers_data ( " data size: 0x%1d", m_data.size() );
            trace::data_containers_detail ( "Exiting memory_map constructor (ifstream,uint32)" );
        }

        memory_map::memory_map ( memory_map const& rhs )
            : m_data ( rhs.m_data.size() ),
              m_present_pos ( rhs.m_present_pos ),
              m_previous_pos ( rhs.m_previous_pos )
        {
            trace::data_containers_detail ( "Entering memory_map copy constructor" );

            std::copy ( rhs.m_data.begin(),
                        rhs.m_data.end(),
                        m_data.begin() );

            trace::data_containers_detail ( "Exiting memory_map copy constructor" );
        }

        memory_map::~memory_map ()
        {
            trace::data_containers_detail ( "memory_map destructor called" );
        }

        boost::int8_t
        memory_map::read ( boost::uint8_t* dest_addr_ptr,
                           boost::uint32_t length )
        {
            trace::data_containers_detail ( "Entering memory_map::read" );

            assert ( dest_addr_ptr != 0 );
            assert ( length != 0 );

            if ( m_present_pos + length > m_data.size() ) {
                trace::data_containers_data ( "Present Position: %d", m_present_pos );
                trace::data_containers_data ( "Input read length: %d", length );
                trace::data_containers_data ( "Data size: %d", m_data.size() );
                trace::data_containers_data ( "The resulting pointer is invalid. %d + %d > %d",
                                               m_present_pos,
                                               length,
                                               m_data.size() );

                return memory_map::invalid_index;
            }

            memory_map::values_t::const_iterator pos = m_data.begin();

            std::copy ( pos + m_present_pos,
                        pos + m_present_pos + length,
                        dest_addr_ptr );

            m_previous_pos = m_present_pos;
            m_present_pos += length;

            trace::data_containers_detail ( "Exiting memory_map::read" );

            return memory_map::success;
        }

        memory_map::values_t::iterator
        memory_map::begin()
        {
            trace::data_containers_detail ( "Inside memory_map::begin" );

            return m_data.begin();
        }

        memory_map::values_t::const_iterator
        memory_map::begin() const
        {
            trace::data_containers_detail ( "Inside memory_map::begin (const)" );

            return m_data.begin();
        }

        memory_map::values_t::const_iterator
        memory_map::end() const
        {
            trace::data_containers_detail ( "Inside memory_map::end (const)" );
            return m_data.end();
        }

        boost::uint32_t
        memory_map::get_base_address ( void ) const
        {
	  trace::data_containers_detail ( "Inside memory_map::get_base_address" );
          return m_base_address;
	}
        
        boost::uint32_t
        memory_map::get_present_position_value ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Present_Position_Value" );
            return m_present_pos;
        }

        memory_map::values_t::const_iterator
        memory_map::get_present_position ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Present_Position" );
            return m_data.begin() + m_present_pos;
        }

        boost::uint32_t
        memory_map::get_present_position_address ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Present_Position_Address" );

            boost::uint32_t position_address = m_base_address + m_present_pos;

            return position_address;
        }

        boost::uint32_t
        memory_map::get_position_address ( memory_map::values_t::const_iterator pos ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Position_Address" );

            boost::uint32_t position_address = m_base_address + ( pos - m_data.begin() );

            return position_address;
        }

        boost::uint32_t
        memory_map::get_previous_position_value ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Previous_Position_Value" );
            return m_previous_pos;
        }

        memory_map::values_t::const_iterator
        memory_map::get_previous_position ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Previous_Position" );
            return m_data.begin() + m_previous_pos;
        }

        boost::uint32_t
        memory_map::get_previous_position_address ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::get_Previous_Position_Address" );
            boost::uint32_t position_address = m_base_address + m_previous_pos;

            return position_address;
        }

        boost::uint32_t
        memory_map::size ( void ) const
        {
            trace::data_containers_detail ( "Inside memory_map::size" );
            return m_data.size();
        }

        boost::int8_t
        memory_map::copy ( boost::shared_ptr < const memory_map> src_ptr,
                           boost::uint32_t length )
        {
            trace::data_containers_detail ( "Entering memory_map::copy" );
            trace::data_containers_data ( "parameters: src_ptr address = 0x%1p  length=0x%2X (%3d)",
                                          src_ptr.get(),
                                          length,
                                          length );

            assert ( src_ptr.get() != 0 );
            assert ( length != 0 );

            // Off the end check
            if ( m_present_pos + length > m_data.size() ) {

                trace::data_containers_data ( "The present position pointer will be invalid if we write from the present\nposition with the given length. It will cause an segfault. Recheck the value\ngiven for length (%d) or check the setting of the present position.",
                                               length );

                return memory_map::out_of_range;
            }

            std::copy ( src_ptr->get_present_position(),
                        src_ptr->get_present_position() + length,
                        m_data.begin() + m_present_pos );

            trace::data_containers_detail ( "Exiting memory_map::copy" );

            return memory_map::success;
        }

        std::pair < boost::shared_ptr< memory_map >, boost::int8_t>
        memory_map::subset ( boost::uint32_t length ) const
        {
            trace::data_containers_detail ( "Entering memory_map::subset" );

            assert ( length != 0 );

            boost::shared_ptr < memory_map > result_ptr =
                boost::make_shared < memory_map > ( length,
                                                    this->get_present_position_address() );

            /*
             * There is something wrong with the m_data. Its
             */
            std::copy ( this->get_present_position(),
			this->get_present_position() + length,
			result_ptr->begin() );

            trace::data_containers_detail ( "Exiting memory_map::subset" );

            return std::make_pair ( result_ptr , memory_map::success );
        }

        std::ostream& operator<< ( std::ofstream& os, memory_map const& rhs )
        {
            trace::data_containers_detail ( "Entering memory_map::to_String" );

            std::stringstream char_output;

            os << "----------------------------------------" << std::endl;

            boost::uint8_t byte_counter = 0;

            for ( memory_map::values_t::const_iterator cpos = rhs.begin();
                    cpos != rhs.end();
                    ++cpos ) {
	      
                if ( byte_counter == 0 ) {
                    os << boost::format ( "%1X: " ) % ( rhs.get_position_address(cpos) );
                }

                
                os << boost::format ( "%1X" ) %
                   boost::io::group ( std::hex,
                                      std::setw ( 2 ),
                                      std::setfill ( '0' ),
                                      static_cast<boost::uint16_t> ( *cpos ) );

                if ( ( *cpos > 0x1F ) &&
                        ( *cpos < 0x7F ) ) {
                    char_output << boost::format ( "%1c" ) % *cpos;
                } else {
                    char_output << ".";
                }

                if ( ( byte_counter == 3 ) ||
                        ( byte_counter == 7 ) ||
                        ( byte_counter == 11 ) ) {
                    os << "  ";
                    byte_counter++;
                } else if ( byte_counter != 15 ) {
                    os << " ";
                    byte_counter++;
                } else {
                    byte_counter = 0;
                    os << "  " << char_output.str();
                    char_output.str ( "" );
                    os << std::endl;
                }
            }

            if ( byte_counter != 15 ) {
                for ( ;
                        byte_counter <= 15;
                        byte_counter++ ) {

                    os << "  ";
                    char_output << ".";

                    if ( ( byte_counter == 3 ) ||
                            ( byte_counter == 7 ) ||
                            ( byte_counter == 11 ) ) {
                        os << "  ";
                    } else if ( byte_counter != 15 ) {
                        os << " ";
                    } else {
                        os << "  " << char_output.str();
                        os << std::endl;
                    }
                }
            }

            trace::data_containers_detail ( "Exiting memory_map::to_String" );

            return os;
        }

        bool
        memory_map::operator== ( memory_map& rhs_ref ) const
        {
            trace::data_containers_detail ( "Inside memory_map::operator== (equality)" );
            return ( m_data == rhs_ref.m_data );
        }

        boost::int8_t
        memory_map::address_seek ( boost::uint32_t address )
        {
            trace::data_containers_detail ( "Entering memory_map::address_Seek" );

            // If index is outside the range of the map
            if ( ( address < m_base_address ) ||
                    ( address > m_base_address + m_data.size() ) ) {

                trace::data_containers_data ( "The address given, 0x%1X is invalid. Its pointing to a memory location outside of space allocated to this Memory Map. (0x%2X - 0x%3X)",
                                              address,
                                              m_base_address,
                                              ( m_base_address + m_data.size() ) );


                return memory_map::out_of_range;
            }

            m_previous_pos = m_present_pos;
            m_present_pos = address - m_base_address;

            trace::data_containers_detail ( "Exiting memory_map::address_Seek" );

            return memory_map::success;
        }

        memory_map&
        memory_map::operator= ( memory_map const& rhs )
        {
            trace::data_containers_detail ( "Entering memory_map::operator= (assignment)" );

            memory_map temp ( rhs );
            swap ( temp );

            trace::data_containers_detail ( "Exiting memory_map::operator= (assignment)" );

            return *this;
        }

        void
        memory_map::swap ( memory_map& rhs )
        {
            trace::data_containers_detail ( "Entering memory_map::swap" );

            std::swap ( m_data, rhs.m_data );

            trace::data_containers_detail ( "Exiting memory_map::swap" );
        }

    } /* Namespace data_containers */
} /* namespace reverse */

