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

#include "IO_Exception.h"

namespace libreverse { namespace errors {

    const char* IO_Exception::m_exception_name = "IO_Exception";

    const char* IO_Exception::m_messages [] = {
        "Invalid file name given.",  // INVALID_FILE_NAME
        "Fatal IO error occured during file operation.", // FATAL_IO_ERROR
        "Invalid path name given for file.", // INVALID_PATH_NAME
        "Invalid pointer given. The pointer is referring to an address out of the range of the data structure.", // OUT_OF_RANGE
        "Invalid index given.", // INVALID_INDEX
        "Shared pointer passed with unitialized contents", // NULL_POINTER
	"Bad input received from input file", // BAD_INPUT
    };

    IO_Exception::IO_Exception ( boost::uint32_t message_id )
        : Reverse_Exception ( message_id )
    {}

    const char*
    IO_Exception::what (void) const throw ()
    {
        return m_messages[m_id];
    }

    const char*
    IO_Exception::name (void) const throw ()
    {
        return m_exception_name;
    }

} /* namespace errors */
} /* namespace libreverse */

