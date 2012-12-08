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

#include <reverse/reverse.hpp>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <fstream>

namespace reverse {

    /* Idea taken from http://www.codeproject.com/debug/xytrace.asp
     * (28 Jan 2002 - Xiangyang Liu)
     *
     * I have modified this so that we don't use varargs and use constant types
     */
    class trace_state {
    public:

        typedef boost::shared_ptr<trace_state> ptr_t;

        static trace_state& instance();

        void set_trace_file_name ( std::string name );

        void set_trace_file_prefix ( std::string name );

        void set_trace_level ( boost::uint32_t level );

        void set_trace_area_mask ( boost::uint32_t mask );

        void open_trace_file ( void );

        std::string get_id_string ( void );

        void close_trace_file ( void );

        boost::uint32_t get_trace_level ( void ) const;

        boost::uint32_t get_trace_area_mask ( void ) const;

        bool is_valid_level ( boost::uint32_t lvl );

        bool is_valid_area_mask ( boost::uint32_t mask );

        void write_message ( boost::uint32_t level, std::string msg );

    private:

        trace_state();

        virtual ~trace_state();

        std::string m_file_prefix;

	std::string m_file_name;

        boost::uint32_t m_trace_level;

        boost::uint32_t m_trace_area_mask;

        std::ofstream m_log_stream;
    };

} // namespace reverse

#endif // #ifndef REVERSE_TRACE_HPP_INCLUDED
