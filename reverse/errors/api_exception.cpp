/*  API_Exception.cpp

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

#include "API_Exception.h"

namespace libreverse { namespace errors {

    const char* API_Exception::m_exception_name = "API_Exception";

    const char* API_Exception::m_messages [] = {
        "Invalid input given to API.",  // INVALID_API_INPUT
        "Unable to find the target file.", // CANNOT_FIND_TARGET,
        "Internal library error has occurred. At this point consider the library unreliable.", // INTERNAL_LIBRARY_ERROR,
    };

    API_Exception::API_Exception ( API_Exception::ERROR_ID message_id )
        : Reverse_Exception ( message_id )
    {}

    const char*
    API_Exception::what (void) const throw ()
    {
        return m_messages[m_id];
    }

    const char*
    API_Exception::name (void) const throw ()
    {
        return m_exception_name;
    }

} /* namespace errors */
} /* namespace libreverse */
