/*  Trace.cpp

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

#include <reverse/trace.hpp>
#include <reverse/trace_area.hpp>
#include <reverse/trace_level.hpp>
#include <reverse/errors/internal_exception.hpp>

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sstream>

#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif /* WIN32 */

namespace reverse {

#ifdef LIBREVERSE_DEBUG

    bool
    trace::write_trace ( boost::uint32_t area, 
                         boost::uint32_t level,
                         const char* message )
    {
        if ( ! trace_state::instance().is_valid_level ( level ) )
            {
                throw errors::internal_exception ( errors::internal_exception::invalid_value );
            }

        if ( message.empty() )
            {
                throw errors::internal_exception ( errors::internal_exception::empty_string );
            }

        if ( ! trace_state::instance().is_valid_area_mask ( area ) )
            {
                throw errors::internal_exception ( errors::internal_exception::invalid_value );
            }

        // If the level is equal to or greater than the present
        // level we record out message.
        if ( ( trace_state::instance().get_trace_level() != trace_level::none ) && 
             ( level <= trace_state::instance().get_trace_level() ) &&
             ( ( trace_state::instance().get_trace_area_mask() & area ) != 0 ) )
            {
                trace_state::instance().write_message ( level, message );
            }

        return true;
    }

      static void api_detail ( const char* message )
      {
	write_trace ( trace_area::api, trace_level::detail, message );
      }

      static void api_error ( const char* message )
      {
	write_trace ( trace_area::api, trace_level::error, message );
      }

      static void api_error ( const char* message, const char* filename, unsigned int line )
      {
	trace::write_trace ( trace_area::api,
			     trace_level::error,
			     boost::str ( boost::format( message )
					  % filename
					  % line ) );
      }

      static void candidate_solution_detail ( const char* message )
      {
	write_trace ( trace_area::candidate_solution, trace_level::detail, message );
      }

      static void components_detail ( const char* message )
      {
	write_trace ( trace_area::components, trace_level::detail, message );
      }

      static void components_error ( const char* message )
      {
	write_trace ( trace_area::components, trace_level::error, message );
      }

      static void components_error ( const char* message, const char* filename, unsigned int line )
      {
	trace::write_trace ( trace_area::components,
			     trace_level::error,
			     boost::str ( boost::format( message )
					  % filename
					  % line ) );
      }

      static void classifier_detail ( const char* message )
      {
	write_trace ( trace_area::classifier, trace_level::detail, message );
      }

  static void classifier_data ( const char* message )
  {
    write_trace ( trace_area::classifier, trace_level::data, message );
  }

  static void grnn_detail ( const char* message )
  {
    write_trace ( trace_area::grnn_data, trace_level::detail, message );
  }

  static void grnn_data ( boost::shared_ptr < training_set<java_training_data> > data )
  {
    for ( classifier_types::training_set<java_training_data>::data_list_t::const_iterator cpos = m_data.begin();
	  cpos != m_data.end();
	  ++cpos )
      {
	grnn_detail ( ( *cpos )->to_String () );
      }
  }

#endif // ifdef LIBREVERSE_DEBUG

} // namespace reverse

