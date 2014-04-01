/*  Database_Data_Transfer.cpp

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
  			database_data_transfer.cpp - Copyright storri

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

#include "Database_Data_Transfer.h"
#include "errors/component_exception.h"
#include "Database_Data_Source_Config.h"
#include "data_object.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Database_Data_Transfer::Database_Data_Transfer ( infrastructure_types::Database_Data_Source_Config::ptr_t cfg )
        : m_config (cfg),
          m_data ( new data_object() )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Database_Data_Transfer constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Database_Data_Transfer::Database_Data_Transfer ( Database_Data_Transfer const& rhs )
        : Data_Transfer_Base ( rhs ),
          m_config ( new Database_Data_Source_Config ( *rhs.m_config ) ),
          m_data ( new data_object( *rhs.m_data ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Database_Data_Transfer copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Database_Data_Transfer::~Database_Data_Transfer ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Database_Data_Transfer destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void Database_Data_Transfer::close ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Database_Data_Transfer::close" );
#endif /* LIBREVERSE_DEBUG */

        // close database connection
    }

    void Database_Data_Transfer::open ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Database_Data_Transfer::open" );
#endif /* LIBREVERSE_DEBUG */

        // open database connection
    }

    void Database_Data_Transfer::put ( infrastructure_types::data_object::const_ptr_t data_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Database_Data_Transfer::put" );
#endif /* LIBREVERSE_DEBUG */


        if ( data_ptr.get() == 0 )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format ( "Exception throw in %s at line %d" )
                                                  % __FILE__
                                                  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::component_exception
                    ( errors::component_exception::null_pointer );
            }

        // transform data into form for insertion into database
        // execute SQL command


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Database_Data_Transfer::put" );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::data_object::const_ptr_t
    Database_Data_Transfer::get () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Database_Data_Transfer::get" );

        // obtain sql command to get data
        // execute SQL command
        // Create data structure
        // Return data structure

        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Database_Data_Transfer::get" );
#endif /* LIBREVERSE_DEBUG */
      
        return m_data;
    }

    Database_Data_Transfer&
    Database_Data_Transfer::operator= ( Database_Data_Transfer const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Database_Data_Transfer::operator=" );
#endif /* LIBREVERSE_DEBUG */

        
        Database_Data_Transfer temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Database_Data_Transfer::operator=" );
#endif /* LIBREVERSE_DEBUG */


        return *this;
    }

    void
    Database_Data_Transfer::swap ( Database_Data_Transfer& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Database_Data_Transfer::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_config.swap ( rhs.m_config );
        m_data.swap ( rhs.m_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Database_Data_Transfer::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
