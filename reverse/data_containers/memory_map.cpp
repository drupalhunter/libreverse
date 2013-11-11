/*  Memory_Map.cpp

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

#include "Memory_Map.h"
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

    Memory_Map::Memory_Map ()
        : m_data (),
          m_present_pos ( 0 ),
          m_previous_pos ( 0 ),
          m_base_address ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Map::Memory_Map ( boost::uint32_t size,
                             boost::uint32_t base_address )
        : m_data ( size, 0 ),
          m_present_pos ( 0 ),
          m_previous_pos ( 0 ),
          m_base_address ( base_address )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map constructor (uint32,uint32)" );

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
                             "Exiting Memory_Map constructor (uint32,uint32)" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Map::Memory_Map ( void* start,
			     std::size_t size,
                             boost::uint32_t base_address )
        : m_present_pos ( 0 ),
          m_previous_pos ( 0 ),
          m_base_address ( base_address )
    {

#ifdef LIBREVERSE_DEBUG
         Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map constructor (ifstream,uint32)" );

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
                             "Exiting Memory_Map constructor (ifstream,uint32)" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Map::Memory_Map ( Memory_Map const& rhs )
        : boost::enable_shared_from_this<Memory_Map>(rhs),
          m_data ( rhs.m_data.size() ),
          m_present_pos ( rhs.m_present_pos ),
          m_previous_pos ( rhs.m_previous_pos )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map copy constructor" );
#endif /* LIBREVERSE_DEBUG */


        std::copy ( rhs.m_data.begin(),
                    rhs.m_data.end(),
                    m_data.begin() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }  

    Memory_Map::~Memory_Map ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Memory_Map destructor called" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::int8_t
    Memory_Map::read ( boost::uint8_t* dest_addr_ptr,
                       boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::read" );
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


                return data_types::Memory_Map::INVALID_INDEX;
            }

        data_types::Memory_Map::Values_t::const_iterator pos = m_data.begin();

        std::copy ( pos + m_present_pos,
                    pos + m_present_pos + length,
                    dest_addr_ptr );

        m_previous_pos = m_present_pos;
        m_present_pos += length;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map::read" );
#endif /* LIBREVERSE_DEBUG */


        return data_types::Memory_Map::SUCCESS;
    }

    data_types::Memory_Map::iterator
    Memory_Map::begin()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin();
    }

    data_types::Memory_Map::const_iterator
    Memory_Map::begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::begin (const)" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin();
    }

    data_types::Memory_Map::const_iterator
    Memory_Map::end() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::end (const)" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.end();
    }

    boost::uint32_t 
    Memory_Map::get_Present_Position_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Present_Position_Value" );
#endif /* LIBREVERSE_DEBUG */


        return m_present_pos;
    }

    data_types::Memory_Map::const_iterator
    Memory_Map::get_Present_Position (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Present_Position" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin() + m_present_pos;
    }

    boost::uint32_t
    Memory_Map::get_Present_Position_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Present_Position_Address" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t position_address = m_base_address + m_present_pos;

        return position_address;
    }

  boost::uint32_t
  Memory_Map::get_Position_Address ( data_types::Memory_Map::const_iterator pos ) const
  {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Position_Address" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t position_address = m_base_address + ( pos - m_data.begin() );

        return position_address;
  }

    boost::uint32_t 
    Memory_Map::get_Previous_Position_Value (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Previous_Position_Value" );
#endif /* LIBREVERSE_DEBUG */


        return m_previous_pos;
    }

    data_types::Memory_Map::const_iterator
    Memory_Map::get_Previous_Position (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Previous_Position" );
#endif /* LIBREVERSE_DEBUG */


        return m_data.begin() + m_previous_pos;
    }

    boost::uint32_t
    Memory_Map::get_Previous_Position_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::get_Previous_Position_Address" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint32_t position_address = m_base_address + m_previous_pos;

        return position_address;
    }

    boost::uint32_t
    Memory_Map::size (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::size" );
#endif /* LIBREVERSE_DEBUG */

        return m_data.size();
    }

    boost::int8_t
    Memory_Map::copy ( boost::shared_ptr < const Memory_Map> src_ptr,
                       boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::copy" );

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


                return data_types::Memory_Map::OUT_OF_RANGE;
            }

        std::copy ( src_ptr->get_Present_Position(),
                    src_ptr->get_Present_Position() + length,
                    m_data.begin() + m_present_pos );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map::copy" );
#endif /* LIBREVERSE_DEBUG */


        return data_types::Memory_Map::SUCCESS;
    }

    std::pair<data_types::Memory_Map::ptr_t, boost::int8_t>
    Memory_Map::subset ( boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::subset" );
#endif /* LIBREVERSE_DEBUG */


        assert ( length != 0 );

        data_types::Memory_Map::ptr_t result_ptr
            ( new Memory_Map ( length,
                               this->get_Present_Position_Address() ) );
        
        /*
         * There is something wrong with the m_data. Its 
         */
        boost::int8_t result = 
            result_ptr->copy ( this->shared_from_this(), length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map::subset" );
#endif /* LIBREVERSE_DEBUG */


        return std::make_pair ( result_ptr , result );
    }

    std::string
    Memory_Map::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::to_String" );
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
                             "Exiting Memory_Map::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    bool
    Memory_Map::operator== ( Memory_Map& rhs_ref ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Inside Memory_Map::operator== (equality)" );
#endif /* LIBREVERSE_DEBUG */


        return ( m_data == rhs_ref.m_data );
    }

    boost::int8_t
    Memory_Map::address_Seek ( boost::uint32_t address )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::address_Seek" );
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
	      

                return data_types::Memory_Map::OUT_OF_RANGE;
            }

        m_previous_pos = m_present_pos;
        m_present_pos = address - m_base_address;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map::address_Seek" );
#endif /* LIBREVERSE_DEBUG */


        return data_types::Memory_Map::SUCCESS;
    }

    Memory_Map&
    Memory_Map::operator= ( Memory_Map const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


        Memory_Map temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Memory_Map::swap ( Memory_Map& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Entering Memory_Map::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_data, rhs.m_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Map::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

  } /* Namespace data_containers */
} /* namespace libreverse */

