/*  Filename.h

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

#ifndef REVERSE_DATA_CONTAINERS_FILENAME_HPP_INCLUDED
#define REVERSE_DATA_CONTAINERS_FILENAME_HPP_INCLUDED

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace data_containers {

    class filename
    {
    public:

        explicit filename ( std::string data );

        explicit filename ( filename const& rhs );

        virtual ~filename (){}

        std::string data () const;

        filename& operator= ( filename const& rhs );

        void swap ( filename& rhs );

    private:

        /**
         * Fields
         */
        std::string m_data;
    };

    std::ostream& operator<< ( std::ostream& os, boost::shared_ptr < const filename> & rhs )
    {
      os << boost::format ( "  filename: %s" ) % rhs->data();
      return os;
    }

  } // namespace data_containers
} // namespace reverse

#endif // #ifndef REVERSE_DATA_CONTAINERS_FILENAME_HPP_INCLUDED

