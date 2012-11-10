/*  Parsing_Exception.cpp

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

#include "Parsing_Exception.h"

namespace libreverse { namespace errors {

  const char* Parsing_Exception::m_exception_name = "Parsing_Exception";

  const char* Parsing_Exception::m_messages [] = {
    "Unknown parsing error received.",  // UNKNOWN_PARSING_ERROR
    "Unable to open target file.", // CANNOT_OPEN
    "Invalid format found in file", // INVALID_FORMAT
    "Internal parsing error.", // INTERNAL_PARSING_ERROR
    "Unknown component requested.", // UNKNOWN_COMPONENT
    "Unknwon XML element.", // UNKNOWN_ELEMENT
    "Unknown type requested.", // UNKNOWN_TYPE
    "Unknown CPU requested.", // UNKNOWN_CPU
    "File did not contain any data", // EMPTY_FILE
    "File missing from target location", // MISSING_FILE
  };

  Parsing_Exception::Parsing_Exception ( boost::uint32_t message_id )
    : Reverse_Exception ( message_id )
  {}

  const char*
  Parsing_Exception::what (void) const throw ()
  {
    return m_messages[m_id];
  }

  const char*
  Parsing_Exception::name (void) const throw ()
  {
    return m_exception_name;
  }

} /* namespace errors */
} /* namespace libreverse */

