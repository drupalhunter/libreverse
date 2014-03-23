/*  Configuration_Exception.h

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

#ifndef REVERSE_ERRORS_CONFIGURATION_EXCEPTION_HPP_INCLUDED
#define REVERSE_ERRORS_CONFIGURATION_EXCEPTION_HPP_INCLUDED

#include <reverse/errors/reverse_exception.hpp>

#include <boost/cstdint.hpp>

namespace reverse {
  namespace errors {

    class configuration_exception : public virtual reverse_exception {
    public:

      configuration_exception ( boost::uint32_t message_id );

      /*!
       * \brief Destructor
       */
      virtual ~configuration_exception (void) throw(){}

      /*!
       * \brief Return the extra message accompanying the exception.
       */
      const char* what (void) const throw ();

      /*!
       * \brief Return tne name of the exception
       */
      const char* name (void) const throw();

      enum {
	OBJECT_NOT_FOUND,
	UNSUPPORTED_MAP,
	DLL_NOT_FOUND,
	DLL_PATH_ERROR,
	EMPTY_INPUT
      };

    private:

      static const char* m_exception_name;

      static const char* m_messages[];

    };

  } /* namespace errors */
} /* namespace reverse */

#endif /* REVERSE_ERRORS_CONFIGURATION_EXCEPTION_HPP_INCLUDED */
