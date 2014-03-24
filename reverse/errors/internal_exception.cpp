/*  Internal_Exception.cpp

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

#include <reverse/errors/internal_exception.hpp>

namespace reverse {
  namespace errors {

    const char* internal_exception::m_exception_name = "internal_exception";

    const char* internal_exception::m_messages [] = {
        "String Parameter given was empty.\nThe parameter must NOT be empty.",  // EMPTY_STRING
        "Input value was not an acceptable value for this function.\nDouble check the calling function to confirm the parameter value.", // INVALID_VALUE
        "Input pointer is not initialized. Double check where the call is make to this function to ensure the pointer is initialized.", // NULL_POINTER
        "Unable to allocate memory for the required object. This may be a indicator of a memory leak or non-enough system memory to process the input file.", // BAD_ALLOC
        "Unsupported feature was requested. Contact the developers of libreverse if you feel that this feature should be supported", // UNSUPPORTED_FEATURE
        "Unable to perform I/O operation", // IO_ERROR
        "Invalid index given. It is outside the bounds of the range of the list.", // INVALID_INDEX
        "Invalid data set found. A value in the problem data set is not within the range of 0.0 to 1.0", // INVALID_DATA_SET
	"Empty data set found.", // EMPTY_DATA_SET
    };

    internal_exception::internal_exception ( boost::uint32_t message_id )
        : reverse_exception ( message_id )
    {}

    const char*
    internal_exception::what (void) const throw ()
    {
        return m_messages[m_id];
    }

    const char*
    internal_exception::name (void) const throw ()
    {
        return m_exception_name;
    }

  } /* namespace errors */
} /* namespace reverse */

