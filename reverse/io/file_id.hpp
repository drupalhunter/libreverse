/*  File_ID.h

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

#ifndef REVERSE_IO_FILE_ID_HPP_INCLUDED
#define REVERSE_IO_FILE_ID_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {

    class file_id
    {
    public:

        file_id ( std::string const& fullname );

        file_id ( file_id const& rhs );

        /*!
         * \brief Return the full string name of the file
         * \return A string
         */
        std::string get_full_name () const;

        file_id& operator= ( file_id const& rhs );

        void swap ( file_id& rhs );

    private:

        /*!
         * \brief Full name of the file: full path to file + file name
         */
        std::string m_full_name;

    };

  } // namespace io
} // namespace reverse

#endif // REVERSE_IO_FILE_ID_HPP_INCLUDED
