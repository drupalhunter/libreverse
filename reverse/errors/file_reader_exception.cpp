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

#include <reverse/errors/File_Reader_Exception.h>

namespace reverse {
  namespace errors {

  const char* File_Reader_Exception::m_exception_name =
  "File_Reader_Exception";

  const char* File_Reader_Exception::m_messages [] = {
    "Unsupported file type given.",  // UNSUPPORTED_FILE_TYPE
    "Index given is outside the bounds of the data structure", // OUT_OF_BOUNDS
    "Unsupported arch type found.", //UNSUPPORTED_ARCH_TYPE,
  };

  File_Reader_Exception::File_Reader_Exception ( boost::uint32_t message_id )
    : Reverse_Exception ( message_id )
  {}

  const char*
  File_Reader_Exception::what (void) const throw ()
  {
    return m_messages[m_id];
  }

  const char*
  File_Reader_Exception::name (void) const throw ()
  {
    return m_exception_name;
  }

  } /* namespace errors */
} /* namespace libreverse */
