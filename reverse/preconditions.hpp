/*  Preconditions.h

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

#ifndef REVERSE_PRECONDITIONS_HPP_INCLUDED
#define REVERSE_PRECONDITIONS_HPP_INCLUDED

#include <reverse/errors/internal_exception.hpp>

#include <boost/cstdint.hpp>

namespace reverse
{

    /*!
     * \class Preconditions
     * \date 2008
     * \author Stephen Torri
     */
    class preconditions
    {
    public:

      /*!
       * \brief Check that the pointer has been initialized. If not then an exception is thrown.
       * \param obj_ptr Pointer to be checked
       * \exception Internal_Exception(NULL_POINTER)
       */
      template <typename pointer_type>
      static inline void is_set ( boost::shared_ptr<pointer_type>& obj_ptr )
	{
	  if ( ! obj_ptr )
	    {
	      throw errors::internal_exception ( errors::internal_exception::null_pointer );
	    }
	}

      template <typename pointer_type>
      static inline void is_set ( const boost::shared_ptr< const pointer_type>& obj_ptr )
	{
	  if ( ! obj_ptr )
	    {
	      throw errors::internal_exception ( errors::internal_exception::null_pointer );
	    }
	}

      /*!
       * \brief Check that the pointer has been initialized. If not then an exception is thrown.
       * \param obj_ptr Pointer to be checked
       * \exception Internal_Exception(NULL_POINTER)
       */
      template <typename pointer_type>
      static inline void is_set ( pointer_type* obj_ptr )
	{
	  if ( obj_ptr == 0x0 )
	    {
	      throw errors::internal_exception ( errors::internal_exception::null_pointer );
	    }
	}

      /*! \brief Check that the values are not equal. If they are then an exception is thrown.
       *  \param lhs First value to check
       *  \param rhs Second value to check
       *  \exception Internal_Exception(INVALID_VALUE)
       */
      template <typename left_type, typename right_type>
      static inline void not_equal ( left_type lhs, right_type rhs )
      {
	if ( lhs == rhs )
	  {
	    throw errors::internal_exception ( errors::internal_exception::invalid_value );
	  }
      }

      template <typename left_type, typename right_type>
      static inline void equals ( left_type lhs, right_type rhs )
      {
	if ( lhs != rhs )
	  {
	    throw errors::internal_exception ( errors::internal_exception::invalid_value );
	  }
      }
		
      template <typename limit_type>
      static inline void in_range ( boost::uint32_t value, limit_type limit )
	{
	  if ( value > limit )
	    {
	      throw errors::internal_exception ( errors::internal_exception::invalid_value );
	    }
	}

      template <typename data_type>
      static inline void not_empty ( data_type object )
	{
	  if ( object.empty() )
	    {
	      throw errors::internal_exception ( errors::internal_exception::empty_data_set );
	    }
	}

    };

} // namespace reverse

#endif // #ifndef REVERSE_PRECONDITIONS_HPP_INCLUDED
