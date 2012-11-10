/*  Base_Header.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_BASE_HEADER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_BASE_HEADER_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace reverse {
  namespace io {
    namespace input {

      /*!
       * \class Base_Header
       * \date 2003
       * \author Stephen Torri
       */
      class base_header {

      public:
	/*!
	 * \fn ~Base_Header()
	 * \brief Default destructor
	 */
	virtual ~base_header(){};

	/*!
	 * brief Convert the bit ordering from the target file bit ordering
	 * to the host system.
	 */
	virtual void convert () = 0;

      };

    } // namspace input
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_BASE_HEADER_HPP_INCLUDED
