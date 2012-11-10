/*  Data_Source_Exception.h

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

#ifndef DATA_SOURCE_EXCEPTION_H_
#define DATA_SOURCE_EXCEPTION_H_

#include "Reverse_Exception.h"

namespace libreverse { namespace errors {

  class Data_Source_Exception : public virtual Reverse_Exception {
  public:

    Data_Source_Exception ( boost::uint32_t message_id );

    /*!
     * \brief Destructor
     */
    virtual ~Data_Source_Exception (void) throw(){}

    /*!
     * \brief Return the extra message accompanying the exception.
     */
    const char* what (void) const throw ();

    /*!
     * \brief Return tne name of the exception
     */
    const char* name (void) const throw();

    enum {
      UNKNOWN_DATA_SOURCE_TYPE
    };

  private:

    static const char* m_exception_name;

    static const char* m_messages[];

  };

} /* namespace errors */
} /* namespace libreverse */

#endif /* DATA_SOURCE_EXCEPTION_H_ */
