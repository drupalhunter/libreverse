/*  Component_Exception.cpp

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

#include "Component_Exception.h"

namespace libreverse { namespace errors {

    const char* Component_Exception::m_exception_name = "Component_Exception";

    const char* Component_Exception::m_messages [] = {
        "Number of Inputs allowed was exceed for this component.",  // INVALID_LIMIT_EXCEEDED
        "Error occurred while storing value in data storage object.", // DATA_STORAGE_ERROR
        "Invalid index given.", // INVALID_INDEX
        "Invalid Component state given.", // INVALID_STATE
        "Null pointer found.", // NULL_POINTER
    };

    Component_Exception::Component_Exception ( ERROR_ID message_id )
        : Reverse_Exception ( message_id )
    {}

    const char*
    Component_Exception::what (void) const throw ()
    {
        return m_messages[m_id];
    }

    const char*
    Component_Exception::name (void) const throw ()
    {
        return m_exception_name;
    }

} /* namespace errors */
} /* namespace libreverse */
