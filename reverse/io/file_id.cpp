/*  File_ID.cpp

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

#include <reverse/io/file_id.hpp>

#include <boost/format.hpp>

#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace io {

    file_id::file_id ( std::string const& name )
      : m_full_name ( name )
    {

#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Inside File_ID constructor" );

      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   boost::str ( boost::format ( "Filename = %1%" ) % name ) );
#endif /* LIBREVERSE_DEBUG */

    }

    file_id::file_id ( file_id const& rhs )
      : m_full_name ( rhs.m_full_name )
    {

#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Inside File_ID copy constructor" );

      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   boost::str ( boost::format ( "Filename = %1%" ) % rhs.m_full_name ) );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    file_id::get_full_name () const
    {

#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Inside File_ID::get_Full_Name" );
#endif /* LIBREVERSE_DEBUG */

      return m_full_name;
    }

    file_id&
    file_id::operator= ( file_id const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Entering File_ID::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */


      file_id temp ( rhs );
      swap ( temp );


#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Exiting File_ID::operator= (assignment)" );
#endif /* LIBREVERSE_DEBUG */

      return *this;
    }

    void
    file_id::swap ( file_id& rhs )
    {

#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Entering File_ID::swap" );

      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   "Before swap" );
      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   boost::str ( boost::format ( "(LHS) Filename = %1%" ) % m_full_name ) );
      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   boost::str ( boost::format ( "(RHS) Filename = %1%" ) % rhs.m_full_name ) );
#endif /* LIBREVERSE_DEBUG */


      std::swap ( m_full_name, rhs.m_full_name );


#ifdef LIBREVERSE_DEBUG
      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   "After swap" );
      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   boost::str ( boost::format ( "(LHS) Filename = %1%" ) % m_full_name ) );
      trace::write_trace ( trace_area::io,
			   trace_level::data,
			   boost::str ( boost::format ( "(RHS) Filename = %1%" ) % rhs.m_full_name ) );

      trace::write_trace ( trace_area::io,
			   trace_level::detail,
			   "Exiting File_ID::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

  } // namespace io
} // namespace reverse
