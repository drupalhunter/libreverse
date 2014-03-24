/*  Meta_Exception.cpp

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

#include <reverse/errors/meta_exception.hpp>

namespace reverse {
  namespace errors {

    const char* meta_exception::m_exception_name = "meta_exception";

    const char* meta_exception::m_messages [] = {
      "Invalid key given. There is no such entry for that name.",  // INVALID_KEY
      "Bad conversion from string value to uint32_t.", // BAD_CONVERSION
    };

    meta_exception::meta_exception ( boost::uint32_t message_id )
      : reverse_exception ( message_id )
    {}

    const char*
    meta_exception::what (void) const throw ()
    {
      return m_messages[m_id];
    }

    const char*
    meta_exception::name (void) const throw ()
    {
      return m_exception_name;
    }

  } /* namespace errors */
} /* namespace reverse */
