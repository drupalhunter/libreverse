/*  Configuration_Exception.cpp

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

#include "Configuration_Exception.h"

namespace libreverse { namespace errors {

  const char* Configuration_Exception::m_exception_name = "Configuration_Exception";

  const char* Configuration_Exception::m_messages [] = {
    "Unknown meta object requested.",  // OBJECT_NOT_FOUND
    "Master formula file missing map for given input and output types.",  // UNSUPPORTED_MAP
    "Requested DLL not found in specified DLL directory.", // DLL_NOT_FOUND
    "Specified DLL directory could not be found on this system.", // DLL_PATH_ERROR
    "Input given is empty.", // EMPTY_INPUT
  };

  Configuration_Exception::Configuration_Exception ( boost::uint32_t message_id )
    : Reverse_Exception ( message_id )
  {}

  const char*
  Configuration_Exception::what (void) const throw ()
  {
    return m_messages[m_id];
  }

  const char*
  Configuration_Exception::name (void) const throw ()
  {
    return m_exception_name;
  }

} /* namespace errors */
} /* namespace libreverse */

