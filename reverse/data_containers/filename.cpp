/*  filename.cpp

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

#include <reverse/data_containers/filename.hpp>
#include <reverse/trace.hpp>

namespace reverse {
    namespace data_containers {

        filename::filename ( std::string data )
            : m_data ( data )
        {
            trace::data_containers_detail ( "Inside filename constructor" );
        }

        filename::filename ( filename const& rhs )
            : m_data ( rhs.m_data )
        {
            trace::data_containers_detail ( "Inside filename copy constructor" );
        }

        filename&
        filename::operator= ( filename const& rhs )
        {
            trace::data_containers_detail ( "Entering filename::operator= (assignment)" );

            filename temp ( rhs );
            swap ( temp );

            trace::data_containers_detail ( "Exiting filename::operator= (assignment)" );

            return *this;
        }

        void
        filename::swap ( filename& rhs )
        {
            trace::data_containers_detail ( "Entering filename::swap" );

            std::swap ( m_data, rhs.m_data );

            trace::data_containers_detail ( "Exiting filename::swap" );
        }

        std::string
        filename::data () const
        {
            trace::data_containers_detail ( "Inside filename::data" );

            return m_data;
        }

    }  /* namespace data_containers */
} /* namespace reverse */
