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

    trace_state& trace_state::instance()
    {
        static trace_state instance_obj;
        return instance_obj;
    }

    void
    trace_state::set_trace_file_name ( std::string name )
    {
      if ( ! name.empty() )
	{
	  m_file_name = name;
	}
      else
	{
	  throw errors::internal_exception ( errors::internal_exception::empty_string );
	}
    }

    void
    trace_state::set_trace_file_prefix ( std::string name )
    {
      if ( ! name.empty() )
	{
	  m_file_prefix = name;
	}
      else
	{
	  throw errors::internal_exception ( errors::internal_exception::empty_string );
	}
    }

    bool
    trace_state::is_valid_level ( boost::uint32_t lvl )
    {       
        switch ( lvl )
            {
            case trace_level::none:
            case trace_level::warn:
            case trace_level::error:
            case trace_level::info:
            case trace_level::debug:
            case trace_level::detail:
            case trace_level::data:
                {
                    return true;
                }
            default:
                {
                    return false;
                }
            }
    }

    bool
    trace_state::is_valid_area_mask ( boost::uint32_t )
    {       
        // Since we are using all the bits of the 8-bit byte any
        // combination of bits will be valid. Therefore we return
        // TRUE. In the future we may need to expand the bit mask
        // therefore there might be reason to check the given mask
        // later.
        return true;
    }

    void
    trace_state::set_trace_level ( boost::uint32_t level )
    {
        if ( this->is_valid_level ( level ) )
            {
                m_trace_level = level;
            }
        else
            {
                throw errors::internal_exception ( errors::internal_exception::invalid_value );
            }
    }

    void
    trace_state::set_trace_area_mask ( boost::uint32_t mask )
    {
        if ( this->is_valid_area_mask ( mask ) )
            {
                m_trace_area_mask = mask;
            }
        else
            {
                throw errors::internal_exception ( errors::internal_exception::invalid_value );
            }
    }

    void
    trace_state::open_trace_file ( void )
    {
        if ( ! m_log_stream.is_open() )
            {
	      if ( m_file_name.empty() )
		{
		  // Create file name
		  std::stringstream name;

		  name << boost::format("%s_%s.txt")
		    % m_file_prefix
		    % this->get_id_string();
		  
		  m_file_name = name.str();
		}
                
                m_log_stream.open ( m_file_name.c_str() );
            }
    }

    std::string
    trace_state::get_id_string ( void )
    {
        // Create id string
        std::stringstream name;

        // Get current time
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

        std::tm tm_ref = boost::posix_time::to_tm ( now );

        boost::gregorian::date today = now.date();

        name << boost::format ( "%1%_%2%:%3%:%4%" )
            % boost::gregorian::to_iso_extended_string ( today )
            % tm_ref.tm_hour
            % tm_ref.tm_min
            % tm_ref.tm_sec;

        return name.str();
    }

    void
    trace_state::close_trace_file ( void )
    {
        if ( m_log_stream.is_open() )
            {
                m_log_stream.close();
            }
    }

    boost::uint32_t
    trace_state::get_trace_level ( void ) const
    {
        return m_trace_level;
    }

    boost::uint32_t
    trace_state::get_trace_area_mask ( void ) const
    {
        return m_trace_area_mask;
    }

    void
    trace_state::write_message ( boost::uint32_t level, std::string msg )
    {
        // write id
        m_log_stream << boost::format("%s_%d: " )
	  % this->get_id_string()
#ifndef WIN32
	  % getpid()
#else
	  % GetCurrentProcessId()
#endif /* WIN32 */
                     << std::flush;
            
        // Write message prefix
        if ( level == trace_level::warn )
            {
                m_log_stream << "(ww) ";
            }
        else if ( level == trace_level::error )
            {
                m_log_stream << "(ee) ";
            }
        else if ( level == trace_level::info )
            {
                m_log_stream << "(ii) ";
            }
        else if ( level == trace_level::debug )
            {
                m_log_stream << "(debug) ";
            }
        else if ( level == trace_level::detail )
            {
                m_log_stream << "(detail) ";
            }
        else if ( level == trace_level::data )
            {
                m_log_stream << "(data) ";
            }
        else 
            {
                // we should not be here
                abort();
            }

        // Write to the file
        m_log_stream << msg << std::endl << std::flush;

        // Unlock the resource
    }
    
    trace_state::trace_state()
        : m_file_prefix ( "trace" ),
      m_file_name ( "" ),
      m_trace_level ( trace_level::none ),
      m_trace_area_mask ( trace_area::none )
    {}

    trace_state::~trace_state()
    {
        this->close_trace_file();
    }

#ifdef LIBREVERSE_DEBUG
    bool
    trace::write_trace ( boost::uint32_t area, 
                         boost::uint32_t level,
                         std::string message )
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
#else
    bool
    trace::write_trace ( boost::uint32_t,
                         boost::uint32_t,
                         std::string )
    {
        return true;
    }
#endif

} // namespace reverse

