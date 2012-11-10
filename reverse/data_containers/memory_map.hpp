/*  Memory_Map.h

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

#ifndef REVERSE_DATA_CONTAINERS_MEMORY_MAP_HPP_INCLUDED
#define REVERSE_DATA_CONTAINERS_MEMORY_MAP_HPP_INCLUDED

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

namespace reverse {
  namespace data_container {

    class memory_map : public boost::enable_shared_from_this<memory_map>
    {
    public:
      
      static boost::int8_t const success;
      static boost::int8_t const invalid_index;
      static boost::int8_t const out_of_range;

      // !\brief this type represents a byte
      typedef boost::uint8_t data_t;

      // !\brief The internal data structure of a Memory Map
      typedef std::vector <data_t> values_t;

      // !\brief Iterator into the internal data structure of a Memory Map
      typedef values_t::const_iterator const_iterator;

      // !\brief Map key is a 32-bit address in memory
      typedef boost::uint32_t map_key_t;

      // !\brief index where the data is in the Values_t list
      typedef boost::uint32_t index_t;

      // !\brief Table use for normal lookups ( address => index )
      typedef std::map<map_key_t, index_t> address_map_t;

      // !\brief Table used for reverse lookups ( index => address )
      //
      // Map key is the index where the data is in the Values_t list
      // Data value is the 32-bit address in memory
      typedef std::map<index_t, map_key_t> reverse_address_map_t;

      /**
       * \brief Set up a blank memory map of a set size
       *
       * \param size Size of memory map to allocate
       *
       * \param base_address The memory address of the first byte
       *
       * \pre size has a value of 0 or more
       *
       * \pre base_address has a value of 0 or more
       *
       * \post Size of memory map has been set to the value of the
       * input variable 'size'
       *
       * \post Base addres of the memory map has been set to the
       * value of the input variable 'base_address' or the default
       * value of zero
       */
      explicit memory_map ( boost::uint32_t size,
			    boost::uint32_t base_address = 0 );

      /**
       * \brief Set up a memory map of a set size with the contents
       * of the input file stream.
       *
       * \param input_ref Input file stream where data is stored.
       *
       * \param base_address The memory address of the first byte
       *
       * \pre size has a value of 0 or more
       *
       * \pre base_address has a value of 0 or more
       *
       * \post Size of memory map has been set to the value of the
       * size of the input file stream.
       *
       * \post Base addres of the memory map has been set to the
       * value of the input variable 'base_address' or the default
       * value of zero
       */
      explicit memory_map ( std::ifstream& input_ref,
			    boost::uint32_t base_address = 0 );

      /**
       * \brief Copy constructor
       *
       * \pre The input reference is a fully initialized Memory_Map
       *
       * \post The output Memory_Map is a deep copy of the input
       */
      explicit memory_map ( memory_map const& rhs );

      virtual ~memory_map();

      /**
       * \brief assignment operator
       *
       * This function handles copying the rhs reference even if the rhs
       * is a reference to this object.
       *
       * \pre The input reference is a fully initialized Memory_Map
       *
       * \post The output Memory_Map is a deep copy of the input
       */
      memory_map& operator= ( memory_map const& rhs );

      /**
       * \brief assignment operator
       *
       * \pre The input reference is a fully initialized Memory_Map
       *
       * \post The output Memory_Map is a deep copy of the input
       */
      void swap ( memory_map& rhs );

      /**
       * \brief Adjust the pointer into the memory to the location
       * specified in by the address.
       *
       * \post The present position is set to the new location.
       */
      boost::int8_t address_seek ( boost::uint32_t address );

      /**
       * \brief Adjust the pointer into the memory to the location
       * specified in by the index.
       *
       * \post The present position is set to the new location.
       */
      template <typename offset_type>
      boost::int8_t
      index_seek ( offset_type offset )
      {
	if ( offset > m_data.size() - 1 )
	  {
	    std::cerr << "The offset given, " << offset
		      << " is invalid. Its pointing to a "
		      << std::endl
		      << "memory location outside of space "
		      << "allocated to"
		      << std::endl
		      << "this Memory Map. ("
		      << m_data.size() << ")"
		      << std::endl;

	    return memory_map::out_of_range;
	  }

	m_present_pos = offset;

	return memory_map::success;
      }

      /**
       * \brief Read 'length' units of data from this Memory Map.
       *
       * The read data will be placed into the destination startin
       * at the beginning.
       *
       * \pre The destination pointer is initialized.
       *
       * \pre Read length is non-zero
       *
       * \post The present position is set to the new location.
       */
      boost::int8_t read ( boost::uint8_t* dest_addr_ptr,
			   boost::uint32_t length );

      /**
       * \brief This copies from the src_ptr to the local Memory
       * Map. It is assumed that the local Memory Map has been
       * adjusted to the position where data will be store. It is
       * also assumed that the src_ptr has been adjusted to the
       * position where we will start reading data.
       *
       * \pre The destination pointer is initialized.
       *
       * \pre Read length is non-zero
       *
       * \post The present position is set to the new location.
       */
      boost::int8_t copy ( boost::shared_ptr< const memory_map>& src_ptr,
			   boost::uint32_t length );

      /**
       * \brief This produces a new Memory Map containing a subset
       * of the parent map. It is assumed that the parent Memory Map
       * has been adjusted to the position where we will start
       * reading data.
       *
       * \pre Present Position of the pointer into the data will not
       * go past the boundary with the given length.
       *
       * \pre Length is non-zero
       */
      std::pair < boost::shared_ptr < memory_map >, boost::int8_t>
      subset ( boost::uint32_t length );

      values_t::iterator begin();

      const_iterator begin() const;

      const_iterator end() const;

      boost::uint32_t get_present_position_value ( void ) const;

      const_iterator get_present_position ( void ) const;

      boost::uint32_t get_present_position_address ( void ) const;

      boost::uint32_t get_position_address ( const_iterator ) const;

      boost::uint32_t get_previous_position_value ( void ) const;

      const_iterator get_previous_position ( void ) const;

      boost::uint32_t get_previous_position_address ( void ) const;
      
      boost::uint32_t size ( void ) const;

      std::string to_string ( void ) const;

      bool operator== ( memory_map& rhs_ref ) const;

      bool allocate_range ( boost::uint32_t address, boost::uint32_t size );

    private:

      memory_map();
      
      values_t m_data;

      boost::uint32_t m_present_pos; // Present index
      
      boost::uint32_t m_previous_pos; // Previous index
      
      boost::uint32_t m_base_address;
      
    };

  } // namespace data_container
} // namespace reverse

#endif // #ifndef REVERSE_DATA_CONTAINERS_MEMORY_MAP_HPP_INCLUDED
