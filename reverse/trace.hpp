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
#include <boost/shared_ptr.hpp>
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

    template <typename T>
    static void components_data ( const char* message, T const& value )
    {
      write_trace ( trace_area::components,
		    trace_level::data,
		    boost::str ( boost::format ( message ) % value ) );
    }

    static void components_error ( const char* message );

    static void components_error ( const char* message, const char* filename, unsigned int line );

    static void classifier_detail ( const char* );

    template <typename T>
    static void classifier_data ( const char* message, T const& value )
    {
      write_trace ( trace_area::classifier,
		    trace_level::data,
		    boost::str ( boost::format ( message ) % value ) );
    }

    template <typename T1, typename T2>
    static void classifier_data ( const char* message, T1 const& value1, T2 const& value2 )
    {
      write_trace ( trace_area::classifier,
		    trace_level::data,
		    boost::str ( boost::format ( message )
				 % value1
				 % value2 ) );
    }

    static void classifier_data ( const char* message );

    template <typename T1, typename T2>
    static void classifier_error ( const char* message, T1 const& v1, T2 const& v2 )
    {
      write_trace ( trace_area::classifier,
		    trace_level::error,
		    boost::str ( boost::format ( message )
				 % v1
				 % v2 ) );
    }

    static void grnn_detail ( const char* message );

    template <typename T>
    static void grnn_data ( const char* message, T const& value )
    {
      write_trace ( trace_area::grnn_data,
		    trace_level::data,
		    boost::str ( boost::format ( message ) % value ) );
    }

    template <typename T1, typename T2>
    static void grnn_data ( const char* message, T1 const& value1, T2 const& value2 )
    {
      write_trace ( trace_area::grnn_data,
		    trace_level::data,
		    boost::str ( boost::format ( message )
				 % value1
				 % value2 ) );
    }

    template <typename T1>
    static void grnn_data_map ( T1 const& map_data )
    {
      for ( T1::const_iterator pos = data.begin();
	    pos != data.end();
	    ++pos )
        {
	  trace::grnn_data ( "Key (%1%) -> Data (%2%)", ( *pos ).first, ( *pos ).second );
        }
    }

    static void io_detail ( const char* message );

    static void io_error ( const char* message );

    template <typename T1>
    static void io_error ( const char* message, T1 const& v1 )
    {
      write_trace ( trace_area::io,
		    trace_level::error,
		    boost::str ( boost::format ( message )
				 % v1 ) );
    }

    static void io_error ( const char* message, const char* filename, int line );


    static void io_data ( const char* message );

    template <typename T>
    static void io_data ( const char* message, T const& value )
    {
      write_trace ( trace_area::io_data,
		    trace_level::data,
		    boost::str ( boost::format ( message ) % value ) );
    }

    template <typename T, typename S>
    static void io_data ( const char* message, T const& value1, S const& value2 )
    {
      write_trace ( trace_area::io_data,
		    trace_level::data,
		    boost::str ( boost::format ( message ) % value1 % value2 ) );
    }

    static void infrastructure_detail ( const char* message );

    static void infrastructure_error ( const char* message );

    static void infrastructure_data ( const char* message );

    template <typename T>
    static void infrastructure_data ( const char* message, T const& value )
    {
      write_trace ( trace_area::infrastructure_data,
		    trace_level::data,
		    boost::str ( boost::format ( message ) % value ) );
    }

    static void infrastructure_error ( const char* message, const char* filename, unsigned int line );
    
#else
    static bool write_trace ( boost::uint32_t, boost::uint32_t, const char* ) { return true; }
    static void api_detail ( const char* ) {}
    static void api_error ( const char* ) {}
    static void api_error ( const char*, const char*, unsigned int ) {}

    static void candidate_solution_detail ( const char* ) {}

    template <typename T>
    static void candidate_solution_data ( const char*, T ) {}

    static void components_detail ( const char* ) {}

    static void components_error ( const char* message ) {}

    static void components_error ( const char* message, const char* filename, unsigned int line ) {}

    template <typename T>
    static void components_data ( const char* message, T const& value ) {}

    static void classifier_detail ( const char* ) {}

    template <typename T1, typename T2>
    static void classifier_error ( const char*, T1 const& v1, T2 const& v2 ) {}

    template <typename T>
    static void classifier_data ( const char*, T const& ) {}

    static void classifier_data ( const char* ){}

    static void grnn_detail ( const char* ){}

    template <typename T>
    static void grnn_data ( const char*, T const& ) {}

    template <typename T1, typename T2>
    static void grnn_data  ( const char*, T1 const&, T2 const& ) {}

    template <typename T1>
    static void grnn_data_map ( T1 const& )
    {}

    static void io_detail ( const char* ) {}

    static void io_error ( const char* ) {}

    template <typename T1>
    static void io_error ( const char* message, T1 const& v1 ) {}

    static void io_error ( const char* message, const char* filename, int line ){}

    template <typename T>
    static void io_data ( const char*, T const& ) {}

    template <typename T, typename S>
    static void io_data ( const char*, T const&, S const& )
    {}

    static void infrastructure_detail ( const char* ){}

    static void infrastructure_error ( const char* ){}

    static void infrastructure_data ( const char* ){}

    template <typename T>
    static void infrastructure_data ( const char*, T const& )
    {}

    static void infrastructure_error ( const char*, const char*, unsigned int ) {}
    
#endif

  };

} // namespace reverse

#endif // #ifndef REVERSE_TRACE_HPP_INCLUDED
