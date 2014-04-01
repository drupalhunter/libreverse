/*  IO_Exception.cpp

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

#include <reverse/errors/io_exception.hpp>

namespace reverse {
  namespace errors {

    const char* io_exception::m_exception_name = "io_exception";

    const char* io_exception::m_messages [] = {
        "Invalid file name given.",  // INVALID_FILE_NAME
        "Fatal IO error occured during file operation.", // FATAL_io_eRROR
        "Invalid path name given for file.", // INVALID_PATH_NAME
        "Invalid pointer given. The pointer is referring to an address out of the range of the data structure.", // OUT_OF_RANGE
        "Invalid index given.", // INVALID_INDEX
        "Shared pointer passed with unitialized contents", // null_pointer
	"Bad input received from input file", // BAD_INPUT
    };

    io_exception::io_exception ( boost::uint32_t message_id )
        : reverse_exception ( message_id )
    {}

    const char*
    io_exception::what (void) const throw ()
    {
        return m_messages[m_id];
    }

    const char*
    io_exception::name (void) const throw ()
    {
        return m_exception_name;
    }

  } /* namespace errors */
} /* namespace reverse */

