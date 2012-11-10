/*  Data_Source_Exception.cpp

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

#include "Data_Source_Exception.h"

namespace libreverse { namespace errors {

  const char* Data_Source_Exception::m_exception_name = "Data_Source_Exception";

  const char* Data_Source_Exception::m_messages [] = {
    "Unknown data source type requested.",  // UNKNOWN_DATA_SOURCE_TYPE
  };

  Data_Source_Exception::Data_Source_Exception ( boost::uint32_t message_id )
    : Reverse_Exception ( message_id )
  {}

  const char*
  Data_Source_Exception::what (void) const throw ()
  {
    return m_messages[m_id];
  }

  const char*
  Data_Source_Exception::name (void) const throw ()
  {
    return m_exception_name;
  }

} /* namespace errors */
} /* namespace libreverse */
