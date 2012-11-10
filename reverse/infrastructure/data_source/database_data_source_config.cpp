
/*  Database_Data_Source_Config.cpp

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

/************************************************************************
  			database_data_source_config.cpp - Copyright storri

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/kde/3.2/share/apps/umbrello/headings/heading.cpp

-->Code Generators searches for heading files based on the file extension
   i.e. it will look for a file name ending in ".h" to include in C++ header
   files, and for a file name ending in ".java" to include in all generated
   java code.
   If you name the file "heading.<extension>", Code Generator will always
   choose this file even if there are other files with the same extension in the
   directory. If you name the file something else, it must be the only one with that
   extension in the directory to guarantee that Code Generator will choose it.

you can use variables in your heading files which are replaced at generation
time. possible variables are : author, date, time, filename and filepath.
just write %variable_name%

This file was generated on Fri Sep 10 2004 at 21:33:48
The original location of this file is 
**************************************************************************/

#include <reverse/infrastructure/data_source/database_data_source_config.hpp>
#include <reverse/reverse.hpp>

#include <string>
#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse {
namespace infrastructure {
namespace data_source {

    boost::uint32_t const database_data_source_config::type =
        api::transfer_types::database;

    database_data_source_config::database_data_source_config ( std::string host,
                                                               std::string user,
                                                               std::string password )
        : m_id ( 0 ),
          m_database_host (host),
          m_database_user (user),
          m_database_password (password)
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    database_data_source_config::database_data_source_config ( database_data_source_config const& rhs )
        : data_source_config_base ( rhs ),
          m_id ( rhs.m_id ),
          m_database_host ( rhs.m_database_host ),
          m_database_user ( rhs.m_database_user ),
          m_database_password ( rhs.m_database_password )
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    database_data_source_config::~database_data_source_config ()
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    database_data_source_config::get_host () const
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config::get_Host" );
#endif /* LIBREVERSE_DEBUG */

        return this->m_database_host;
    }

    std::string
    database_data_source_config::get_user () const
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config::get_User" );
#endif /* LIBREVERSE_DEBUG */

        return this->m_database_user;
    }

    std::string
    database_data_source_config::get_password () const
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config::get_Password" );
#endif /* LIBREVERSE_DEBUG */

        return this->m_database_password;
    }

    boost::uint32_t
    database_data_source_config::get_type() const
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config::get_Type" );
#endif /* LIBREVERSE_DEBUG */

        return this->type;
    }

    database_data_source_config&
    database_data_source_config::operator= ( database_data_source_config const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
			     trace_level::detail,
			     "Entering Database_Data_Source_Config::operator=" );
#endif /* LIBREVERSE_DEBUG */


        database_data_source_config temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        trace::write_trace
            ( trace_area::infrastructure,
              trace_level::detail,
              "Exiting Database_Data_Source_Config::operator=" );
#endif /* LIBREVERSE_DEBUG */


        return *this;
    }

    void
    database_data_source_config::swap ( database_data_source_config& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
			     trace_level::detail,
			     "Entering Database_Data_Source_Config::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_id, rhs.m_id );
        m_database_host.swap ( rhs.m_database_host );
        m_database_user.swap ( rhs.m_database_user );
        m_database_password.swap ( rhs.m_database_password );


#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
			     trace_level::detail,
			     "Exiting Database_Data_Source_Config::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    void database_data_source_config::set_id ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config::set_ID" );
#endif /* LIBREVERSE_DEBUG */

        m_id = id;
    }

    boost::uint32_t
    database_data_source_config::get_id (void) const
    {

#ifdef LIBREVERSE_DEBUG
        trace::write_trace ( trace_area::infrastructure,
                             trace_level::detail,
                             "Inside Database_Data_Source_Config::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return m_id;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
