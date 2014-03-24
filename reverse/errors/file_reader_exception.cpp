/*  File_Reader_Exception.cpp

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

#include <reverse/errors/file_reader_exception.hpp>

namespace reverse {
  namespace errors {

  const char* file_reader_exception::m_exception_name =
  "file_reader_exception";

  const char* file_reader_exception::m_messages [] = {
    "Unsupported file type given.",  // UNSUPPORTED_FILE_TYPE
    "Index given is outside the bounds of the data structure", // OUT_OF_BOUNDS
    "Unsupported arch type found.", //UNSUPPORTED_ARCH_TYPE,
  };

  file_reader_exception::file_reader_exception ( boost::uint32_t message_id )
    : reverse_exception ( message_id )
  {}

  const char*
  file_reader_exception::what (void) const throw ()
  {
    return m_messages[m_id];
  }

  const char*
  file_reader_exception::name (void) const throw ()
  {
    return m_exception_name;
  }

  } /* namespace errors */
} /* namespace libreverse */
