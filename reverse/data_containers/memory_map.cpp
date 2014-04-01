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

#include "memory_map.h"
#include <sstream>
#include <fstream>
#include <boost/format.hpp>

#include "Assert.h"


using namespace libreverse::assert;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse {
  namespace data_containers {

    memory_map::memory_map ()
        : m_data (),
          m_present_pos ( 0 ),
          m_previous_pos ( 0 ),
          m_base_address ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    memory_map::memory_map ( boost::uint32_t size,
                             boost::uint32_t base_address )
        : m_data ( size, 0 ),
          m_present_pos ( 0 ),
          m_previous_pos ( 0 ),
          m_base_address ( base_address )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map constructor (uint32,uint32)" );

        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
                              boost::str ( boost::format ( "paramaters: size = 0x%1X    base address = 0x%2X")
                                           % size
                                           % base_address ) );
#endif /* LIBREVERSE_DEBUG */


        Assert::bool_check ( size != 0, "Size of memory map is zero." );

        Assert::bool_check ( ( m_data.size() == size ), "Size of the image data array is not equal to the requested size." );
        Assert::bool_check ( ( m_base_address == base_address ), "Base address of image is not equal to the requested address.");


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map constructor (uint32,uint32)" );
#endif /* LIBREVERSE_DEBUG */

    }

    memory_map::memory_map ( void* start,
			     std::size_t size,
                             boost::uint32_t base_address )
        : m_present_pos ( 0 ),
          m_previous_pos ( 0 ),
          m_base_address ( base_address )
    {

#ifdef LIBREVERSE_DEBUG
         Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map constructor (ifstream,uint32)" );

         Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
                              boost::str ( boost::format ( "paramaters: ifstream = 0x%1X    base address = 0x%2X")
                                           % &input_ref
                                           % base_address ) );
#endif /* LIBREVERSE_DEBUG */


        Assert::bool_check ( input_ref.good(), "Input file stream is not ready for I/O operations." );

        
        char byte = 0;

        while ( !input_ref.eof() )
            {
                input_ref.read ( &byte, sizeof(byte) );
                m_data.push_back ( byte );


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                                     TraceLevel::DATA,
                                     boost::str ( boost::format (" byte: 0x%1X" )
                                                  % static_cast<boost::uint16_t>(byte) ) );
#endif /* LIBREVERSE_DEBUG */

            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
                             boost::str ( boost::format (" data size: 0x%1d" ) % m_data.size() ) );
#endif /* LIBREVERSE_DEBUG */

        
        input_ref.clear();
        input_ref.seekg ( std::ios_base::beg );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map constructor (ifstream,uint32)" );
#endif /* LIBREVERSE_DEBUG */

    }

    memory_map::memory_map ( memory_map const& rhs )
        : boost::enable_shared_from_this<memory_map>(rhs),
          m_data ( rhs.m_data.size() ),
          m_present_pos ( rhs.m_present_pos ),
          m_previous_pos ( rhs.m_previous_pos )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map copy constructor" );
#endif /* LIBREVERSE_DEBUG */


        std::copy ( rhs.m_data.begin(),
                    rhs.m_data.end(),
                    m_data.begin() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }  

    memory_map::~memory_map ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "memory_map destructor called" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::int8_t
    memory_map::read ( boost::uint8_t* dest_addr_ptr,
                       boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::read" );
#endif /* LIBREVERSE_DEBUG */


        assert ( dest_addr_ptr != 0 );
        assert ( length != 0 );

        if ( m_present_pos + length > m_data.size() )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::DATA_CONTAINERS,
                      TraceLevel::ERROR,
                      boost::str(boost::format("Present Position: %d") %
                                 m_present_pos) );

                Trace::write_Trace
                    ( TraceArea::DATA_CONTAINERS,
                      TraceLevel::ERROR,
                      boost::str(boost::format("Input read length: %d") %
                                 length) );

                Trace::write_Trace
                    ( TraceArea::DATA_CONTAINERS,
                      TraceLevel::ERROR,
                      boost::str(boost::format("Data size: %d") %
                                 m_data.size()) );

                Trace::write_Trace
                    ( TraceArea::DATA_CONTAINERS,
                      TraceLevel::ERROR,
                      boost::str(boost::format("The resulting pointer is invalid. %d + %d > %d")
                                 % m_present_pos
                                 % length
                                 % m_data.size() ) );

                Trace::write_Trace
                    ( TraceArea::DATA_CONTAINERS,
                      TraceLevel::ERROR,
                      "Its pointing to a memory location out side of space allocated to this Memory Map.");
#endif /* LIBREVERSE_DEBUG */


                return data_types::memory_map::INVALID_INDEX;
            }

        data_types::memory_map::Values_t::const_iterator pos = m_data.begin();

        std::copy ( pos + m_present_pos,
                    pos + m_present_pos + length,
                    dest_addr_ptr );

        m_previous_pos = m_present_pos;
        m_present_pos += length;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::read" );
#endif /* LIBREVERSE_DEBUG */


        return data_types::memory_map::SUCCESS;
    }

    data_types::memory_map::iterator
    memory_map::begin()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin();
    }

    data_types::memory_map::const_iterator
    memory_map::begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::begin (const)" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin();
    }

    data_types::memory_map::const_iterator
    memory_map::end() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::end (const)" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.end();
    }

    boost::uint32_t 
    memory_map::get_Present_Position_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Present_Position_Value" );
#endif /* LIBREVERSE_DEBUG */


        return m_present_pos;
    }

    data_types::memory_map::const_iterator
    memory_map::get_Present_Position (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Present_Position" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin() + m_present_pos;
    }

    boost::uint32_t
    memory_map::get_Present_Position_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Present_Position_Address" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t position_address = m_base_address + m_present_pos;

        return position_address;
    }

  boost::uint32_t
  memory_map::get_Position_Address ( data_types::memory_map::const_iterator pos ) const
  {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Position_Address" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t position_address = m_base_address + ( pos - m_data.begin() );

        return position_address;
  }

    boost::uint32_t 
    memory_map::get_Previous_Position_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Previous_Position_Value" );
#endif /* LIBREVERSE_DEBUG */


        return m_previous_pos;
    }

    data_types::memory_map::const_iterator
    memory_map::get_Previous_Position (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Previous_Position" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin() + m_previous_pos;
    }

    boost::uint32_t
    memory_map::get_Previous_Position_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::get_Previous_Position_Address" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t position_address = m_base_address + m_previous_pos;

        return position_address;
    }

    boost::uint32_t
    memory_map::size (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::size" );
#endif /* LIBREVERSE_DEBUG */

        return m_data.size();
    }

    boost::int8_t
    memory_map::copy ( boost::shared_ptr < const memory_map> src_ptr,
                       boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::copy" );

        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DATA,
                             boost::str ( boost::format ("parameters: src_ptr address = 0x%1p  length=0x%2X (%3d)" )
                                          % src_ptr.get()
                                          % length
                                          % length ) );
#endif /* LIBREVERSE_DEBUG */


        assert ( src_ptr.get() != 0 );
        assert ( length != 0 );

        // Off the end check
        if ( m_present_pos + length > m_data.size() )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::DATA_CONTAINERS,
                      TraceLevel::ERROR,
                      boost::str(boost::format("The present position pointer will be invalid if we write from the present\nposition with the given length. It will cause an segfault. Recheck the value\ngiven for length (%d) or check the setting of the present position.")
                                 % length ) );
#endif /* LIBREVERSE_DEBUG */


                return data_types::memory_map::OUT_OF_RANGE;
            }

        std::copy ( src_ptr->get_Present_Position(),
                    src_ptr->get_Present_Position() + length,
                    m_data.begin() + m_present_pos );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::copy" );
#endif /* LIBREVERSE_DEBUG */


        return data_types::memory_map::SUCCESS;
    }

    std::pair<data_types::memory_map::ptr_t, boost::int8_t>
    memory_map::subset ( boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::subset" );
#endif /* LIBREVERSE_DEBUG */


        assert ( length != 0 );

        data_types::memory_map::ptr_t result_ptr
            ( new memory_map ( length,
                               this->get_Present_Position_Address() ) );
        
        /*
         * There is something wrong with the m_data. Its 
         */
        boost::int8_t result = 
            result_ptr->copy ( this->shared_from_this(), length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::subset" );
#endif /* LIBREVERSE_DEBUG */


        return std::make_pair ( result_ptr , result );
    }

    std::string
    memory_map::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;
        std::stringstream char_output;

        output << "----------------------------------------" << std::endl;

        boost::uint8_t byte_counter = 0;

        for ( boost::uint32_t index = 0;
              index < m_data.size();
              ++index )
            {
                if ( byte_counter == 0 )
                    {
                        output << boost::format("%1X: ") % ( m_base_address + index );
                    }

                output << boost::format("%1X") %
                    boost::io::group ( std::hex,
                                       std::setw(2),
                                       std::setfill('0'),
                                       static_cast<boost::uint16_t>(m_data[index]));

                if ( ( m_data[index] > 0x1F ) &&
                     ( m_data[index] < 0x7F ) )
                    {
                        char_output << boost::format("%1c") % m_data[index];
                    }
                else
                    {
                        char_output << ".";
                    }

                if ( ( byte_counter == 3 ) ||
                     ( byte_counter == 7 ) ||
                     ( byte_counter == 11 ) )
                    {
                        output << "  ";
                        byte_counter++;
                    }
                else if ( byte_counter != 15 )
                    {
                        output << " ";
                        byte_counter++;
                    }
                else
                    {
                        byte_counter = 0;
                        output << "  " << char_output.str();
                        char_output.str("");
                        output << std::endl;
                    }
            }

        if ( byte_counter != 15 )
            {
                for ( ;
                      byte_counter <= 15;
                      byte_counter++ )
                    {

                        output << "  ";
                        char_output << ".";

                        if ( ( byte_counter == 3 ) ||
                             ( byte_counter == 7 ) ||
                             ( byte_counter == 11 ) )
                            {
                                output << "  ";
                            }
                        else if ( byte_counter != 15 )
                            {
                                output << " ";
                            }
                        else
                            {
                                output << "  " << char_output.str();
                                output << std::endl;
                            }
                    }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    bool
    memory_map::operator== ( memory_map& rhs_ref ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside memory_map::operator== (equality)" );
#endif /* LIBREVERSE_DEBUG */


        return ( m_data == rhs_ref.m_data );
    }

    boost::int8_t
    memory_map::address_Seek ( boost::uint32_t address )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::address_Seek" );
#endif /* LIBREVERSE_DEBUG */


        // If index is outside the range of the map
        if ( ( address < m_base_address ) ||
             ( address > m_base_address + m_data.size() ) )
            {


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
				   TraceLevel::ERROR,
				   boost::str ( boost::format ( "The address given, 0x%1X is invalid. Its pointing to a memory location outside of space allocated to this Memory Map. (0x%2X - 0x%3X)" )
						% address
						% m_base_address
						% ( m_base_address + m_data.size() ) ) );
#endif /* LIBREVERSE_DEBUG */
	      

                return data_types::memory_map::OUT_OF_RANGE;
            }

        m_previous_pos = m_present_pos;
        m_present_pos = address - m_base_address;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::address_Seek" );
#endif /* LIBREVERSE_DEBUG */


        return data_types::memory_map::SUCCESS;
    }

    memory_map&
    memory_map::operator= ( memory_map const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        memory_map temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    memory_map::swap ( memory_map& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering memory_map::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_data, rhs.m_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting memory_map::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

  } /* Namespace data_containers */
} /* namespace libreverse */

