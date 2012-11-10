/*  Meta_Object.h

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

#ifndef REVERSE_META_META_OBJECT_HPP_INCLUDED 
#define REVERSE_META_META_OBJECT_HPP_INCLUDED 

#include <reverse/errors/meta_exception.hpp>

#include <boost/shared_ptr.hpp>

#include <map>
#include <sstream>
#include <iostream>


namespace reverse {
  namespace meta {

    class meta_object {
    public:

      /*---------------------------*/
      /*         typedefs          */
      /*---------------------------*/

      /* hash, object */
      typedef std::pair < std::string, boost::uint8_t > data_pair_t;

      typedef std::map< std::string, data_pair_t > data_t;

      typedef data_t::iterator iterator;
      typedef data_t::const_iterator const_iterator;
      typedef data_t::size_type size_t;
      typedef boost::shared_ptr < meta_object > ptr_t;
      typedef boost::shared_ptr < meta_object const > const_ptr_t;

      /*---------------------------*/
      /*         constants         */
      /*---------------------------*/
      static boost::uint8_t const string;
      static boost::uint8_t const hex;

      /*---------------------------*/
      /*         functions         */
      /*---------------------------*/
      explicit meta_object ( void );

      explicit meta_object ( meta_object const& rhs );

      virtual ~meta_object(){}

      meta_object& operator= ( meta_object const& rhs );

      void swap ( meta_object& rhs );

      /**
       * \brief insert value into data structure if type and value
       * pair do not already exist.
       *
       * (requires clause)
       * \pre key is not empty
       * \pre value is not empty
       * \pre type is one of the constant values (e.g. string or hex)
       *
       * (ensures clause)
       * \post key and value pair is stored in data structure
       */
      void add ( std::string key,
		 std::string value,
		 boost::uint8_t type );

      /**
       * meta_ptr contains a list of meta_object items to be added
       *
       * (requires clause)
       * \pre meta_ptr is not null
       * \pre meta_ptr contains 0 or more key and value pairs
       */
      void append ( meta_object::const_ptr_t meta_ptr );

      /**
       * \brief retrieve the data pair value stored at the given position
       *
       * (requires clause)
       * \pre key is not empty
       * \pre key is present in data structure
       *
       * (ensures clause)
       * \post value of data pair is not empty
       * \post type of data pair is valid
       */
      data_pair_t get_value ( std::string key ) const;

      /**
       * \brief returns a iterator to the start of the data structure
       */
      iterator begin (void);

      /**
       * \brief returns a constant iterator to the start of the data structure
       */
      const_iterator const begin (void) const;

      /**
       * \brief returns a iterator to the end of the data structure
       */
      iterator end (void);

      /**
       * \brief returns a constant iterator to the end of the data structure
       */
      const_iterator const end (void) const;

      /**
       * \brief returns the number of items stored in the data structure
       */
      size_t size (void) const;

      /**
       * \brief returns a string representing the contents of the data structure
       */
      std::string to_string (void) const;

      inline boost::uint32_t
        convert_to_uint32 ( std::string str_val ) const
      {
	std::istringstream input ( str_val );
	boost::uint32_t result;
	if ( ! ( input >> result ) )
	  {
	    std::cerr << "meta_object::convert_to_uint32 - failed for string = "
		      << str_val << std::endl;
	    throw errors::meta_exception
	      ( errors::meta_exception::bad_conversion );
	  }

	return result;
      }

    private:

      bool is_valid_type ( boost::uint8_t type ) const;

      data_t m_info_map;

    };

  } // namespace meta
} // namespace reverse

#endif // #ifndef REVERSE_META_META_OBJECT_HPP_INCLUDED 
