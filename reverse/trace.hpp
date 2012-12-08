/*  Trace.h

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

#ifndef REVERSE_TRACE_HPP_INCLUDED
#define REVERSE_TRACE_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace reverse {

    class trace {
    public:

#ifdef LIBREVERSE_DEBUG
      static bool write_trace ( boost::uint32_t area,
				boost::uint32_t level,
				const char* message );

      static void api_detail ( const char* message );

      static void api_error ( const char* message );

      static void api_error ( const char* message, const char* filename, unsigned int line );

      static void candidate_solution_detail ( const char* message );

      template <typename T>
      static void candidate_solution_data ( const char* message, T const& value )
      {
	write_trace ( trace_area::candidate_solution,
		      trace_level::data,
		      boost::str ( boost::format ( message ) % value ) );
      }

      static void components_detail ( const char* );

#else
      static bool write_trace ( boost::uint32_t, boost::uint32_t, const char* ){}
      static void api_detail ( const char* ) {}
      static void api_error ( const char* ) {}
      static void api_error ( const char*, const char*, unsigned int ) {}

      static void candidate_solution_detail ( const char* ) {}

      template <typename T>
      static void candidate_solution_data ( const char*, T ) {}

      static void components_detail ( const char* ) {}
#endif

    };

} // namespace reverse

#endif // #ifndef REVERSE_TRACE_HPP_INCLUDED
