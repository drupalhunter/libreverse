/*  IO_Exception.h

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

#ifndef IO_EXCEPTION_H_
#define IO_EXCEPTION_H_

#include "Reverse_Exception.h"
#include <boost/shared_ptr.hpp>

namespace libreverse { namespace errors {

  class IO_Exception : virtual public Reverse_Exception
  {
  public:

    enum {
      INVALID_FILE_NAME,
      FATAL_IO_ERROR,
      INVALID_PATH_NAME,
      OUT_OF_RANGE,
      INVALID_INDEX,
      NULL_POINTER,
      BAD_INPUT
    };

    IO_Exception ( boost::uint32_t message_id );

    /*!
     * \brief Destructor
     */
    virtual ~IO_Exception (void) throw(){}

    /*!
     * \brief Return the extra message accompanying the exception.
     */
    const char* what (void) const throw ();

    /*!
     * \brief Return tne name of the exception
     */
    const char* name (void) const throw();

  private:

    static const char* m_exception_name;

    static const char* m_messages[];
  };

} /* namespace errors */
} /* namespace libreverse */
#endif /* IO_EXCEPTION_H_ */
