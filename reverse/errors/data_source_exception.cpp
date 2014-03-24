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

#include <reverse/errors/data_source_exception.hpp>

namespace reverse {
  namespace errors {

    const char* data_source_exception::m_exception_name = "data_source_exception";

    const char* data_source_exception::m_messages [] = {
      "Unknown data source type requested.",  // UNKNOWN_DATA_SOURCE_TYPE
    };

    data_source_exception::data_source_exception ( boost::uint32_t message_id )
      : reverse_exception ( message_id )
    {}

    const char*
    data_source_exception::what (void) const throw ()
    {
      return m_messages[m_id];
    }

    const char*
    data_source_exception::name (void) const throw ()
    {
      return m_exception_name;
    }

  } /* namespace errors */
} /* namespace reverse */
