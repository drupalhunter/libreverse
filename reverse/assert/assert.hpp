/*  Assert.h

    Copyright (C) 2008 Stephen Torri

    This file is part of Reverse.

    Reverse is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation; either version 3, or (at your
    option) any later version.

    Reverse is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef REVERSE_ASSERT_H
#define REVERSE_ASSERT_H

/* Idea taken from Dr. Doug Schmidt presentation titled
   "Object-Oriented Design and Programming: Programming with
   Assertions and Exceptions".  It was modified to use templates
   instead of macros for checking types. */

#include "reverse/bad_assert.hpp"
#include "reverse/Trace.h"

#include <boost/cstdint.hpp>

#include <iostream>
#include <sstream>
#include <string>


namespace reverse {
  namespace assert {

    template <typename Exception>
    class __bool_assert {
    public:
    
      __bool_assert ( bool bool_expression,
		      const char* file,
		      boost::int32_t line,
		      std::string message )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering __bool_assert" );

	if ( ! bool_expression )
	  {
	    throw Exception ( file,
			      line,
			      message );
	  }
      }
    };

    template <typename Pointer_Type, typename Exception>
    class __null_assert {
    public:

      __null_assert ( Pointer_Type* ptr,
		      const char* file,
		      boost::int32_t line,
		      std::string message )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering __null_assert" );

	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    boost::str ( boost::format ( " The pointer value is equal to %X" ) % ptr ) );

	if ( ! ptr )
	  {
	    throw Exception ( file,
			      line,
			      message );
	  }
      }
    };
    
    
    class Assert {
    public:
#ifdef REVERSE_DEBUG
      template <typename Exception>
      static inline void bool_check ( bool expression,
				      std::string message = "" )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering Assert::bool_check (Custom Exception)" );

	__bool_assert<Exception>::__bool_assert ( expression,
						  __FILE__,
						  __LINE__ ,
						  message );
      }

      static inline void bool_check ( bool expression,
				      std::string message = "" )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering Assert::bool_check (Default Exception)" );

	__bool_assert<bad_assert>::__bool_assert ( expression,
						      __FILE__,
						      __LINE__ ,
						      message );
      }

      template <typename Pointer_Type, typename Exception>
      static inline void null_check ( Pointer_Type* expression,
				      std::string message = "" )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering Assert::null_check (Custom Exception)" );

	typename __null_assert<Pointer_Type, Exception>::__null_assert ( expression,
									 __FILE__,
									 __LINE__ ,
									 message );
      }

      template <typename Pointer_Type>
      static inline void null_check ( Pointer_Type* expression,
				      std::string message = "" )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering Assert::null_check (Default Exception)" );

	typename __null_assert<Pointer_Type, bad_assert>::__null_assert ( expression,
									     __FILE__,
									     __LINE__ ,
									     message );
      }
#else
      template <typename Exception>
      static inline void bool_check ( bool,
				      std::string )
      {}

      static inline void bool_check ( bool,
				      std::string )
      {}

      template <typename Pointer_Type, typename Exception>
      static inline void null_check ( Pointer_Type*,
				      std::string )
      {}

      template <typename Pointer_Type>
      static inline void null_check ( Pointer_Type*,
				      std::string )
      {}
#endif /* REVERSE_DEBUG */
    };

  } /* namespace assert */
} /* namespace reverse */

#endif /* REVERSE_ASSERT_H */
