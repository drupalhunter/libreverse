/*  Reverse_Exception.h

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

#ifndef REVERSE_ERRORS_REVERSE_EXCEPTION_HPP_INCLUDED
#define REVERSE_ERRORS_REVERSE_EXCEPTION_HPP_INCLUDED

#include <boost/cstdint.hpp>

#include <exception>

namespace reverse { 
  namespace errors {

    class reverse_exception : public virtual std::exception {
    public:

        reverse_exception ( boost::uint32_t message_id );

        /*!
         * \brief destructor
         */
        virtual ~reverse_exception (void) throw(){}

        /*!
         * \brief return the extra message accompanying the exception.
         */
        virtual const char* what (void) const throw () = 0;

        /*!
         * \brief return tne name of the exception
         */
        virtual const char* name (void) const throw() = 0 ;

        /*!
         * \brief return the id of the exception
         */
        boost::uint32_t const& id (void) const throw();

    protected:

        boost::uint32_t m_id;

    };

  } // namespace errors
} // namespace reverse

#endif // #ifndef REVERSE_ERRORS_REVERSE_EXCEPTION_HPP_INCLUDED
