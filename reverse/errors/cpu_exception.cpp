/*  CPU_Exception.cpp

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

#include <reverse/errors/cpu_exception.hpp>

namespace reverse {
  namespace errors {

    const char* cpu_exception::m_exception_name = "cpu_exception";

    const char* cpu_exception::m_messages [] = {
      "Unsupport cpu architecture",  // UNSUPPORTED_ARCHITECTURE
    };

    cpu_exception::cpu_exception (boost::uint32_t message_id)
      : reverse_exception (message_id)
    {}

    const char*
    cpu_exception::what (void) const throw ()
    {
      return m_messages[m_id];
    }

    const char*
    cpu_exception::name (void) const throw ()
    {
      return m_exception_name;
    }

  } /* namespace errors */
} /* namespace reverse */
