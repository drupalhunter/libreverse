/*  File_Data_Source_Config.cpp

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
  			file_data_source_config.cpp - Copyright storri

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

#include "File_Data_Source_Config.h"
#include "Reverse.h"
#include "Data_Object.h"
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    boost::uint32_t const File_Data_Source_Config::type = api::Transfer_Types::FILE;

    File_Data_Source_Config::File_Data_Source_Config ( std::string prefix )
        : m_id ( 0 ),
          m_prefix ( prefix )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside File_Data_Source_Config constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    File_Data_Source_Config::File_Data_Source_Config ( File_Data_Source_Config const& rhs )
        : Data_Source_Config_Base ( rhs ),
          m_id ( rhs.m_id ),
          m_prefix ( rhs.m_prefix )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside File_Data_Source_Config copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    File_Data_Source_Config::~File_Data_Source_Config ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside File_Data_Source_Config destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    File_Data_Source_Config::get_Filename () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering File_Data_Source_Config get_Filename" );
#endif /* LIBREVERSE_DEBUG */

        std::string name = boost::str ( boost::format ( "%s_%d.dat" )
                                        % m_prefix
                                        % this->get_ID() );
        return name;
    }

    boost::uint32_t
    File_Data_Source_Config::get_Type() const
    {
        return type;
    }

    File_Data_Source_Config&
    File_Data_Source_Config::operator= ( File_Data_Source_Config const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering File_Data_Source_Config::operator=" );
#endif /* LIBREVERSE_DEBUG */

        File_Data_Source_Config temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting File_Data_Source_Config::operator=" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    File_Data_Source_Config::swap ( File_Data_Source_Config& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering File_Data_Source_Config::swap" );
#endif /* LIBREVERSE_DEBUG */


        std::swap ( m_id, rhs.m_id );
        m_prefix.swap ( rhs.m_prefix );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting File_Data_Source_Config::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    void File_Data_Source_Config::set_ID ( boost::uint32_t id )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside File_Data_Source_Config::set_ID" );
#endif /* LIBREVERSE_DEBUG */

        m_id = id;
    }

    boost::uint32_t
    File_Data_Source_Config::get_ID (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside File_Data_Source_Config::get_ID" );
#endif /* LIBREVERSE_DEBUG */

        return m_id;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
