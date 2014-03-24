/*  Data_Source_Factory.cpp

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
  			data_source_factory.cpp - Copyright Stephen Torri

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
time. possible variables are : author, date, time, filename and file path.
just write %variable_name%

This file was generated on Fri Sep 10 2004 at 21:33:48
The original location of this file is 
**************************************************************************/

#include "Data_Source_Factory.h"
#include "infrastructure/Configurator.h"
#include "Memory_Data_Transfer.h"
#include "Database_Data_Transfer.h"
#include "Data_Source_T.h"
#include "File_Data_Transfer.h"
#include "Database_Data_Source_Config.h"
#include "errors/Data_Source_Exception.h"
#include "errors/Component_Exception.h"
#include "infrastructure/data_source/File_Data_Source_Config.h"
#include "infrastructure/data_source/Memory_Data_Source_Config.h"
#include "infrastructure/data_source/Database_Data_Source_Config.h"
#include "Reverse.h"
#include <iostream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    infrastructure_types::Data_Source_Factory::ptr_t Data_Source_Factory::m_factory;

    Data_Source_Factory::Data_Source_Factory()
        : m_src_config ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Source_Factory constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Data_Source_Base::ptr_t
    Data_Source_Factory::get_Data_Source ( boost::uint32_t id )
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source_Factory::get_Data_Source" );
#endif /* LIBREVERSE_DEBUG */


        // Create the right factory
        if ( m_src_config->get_Type() == api::Transfer_Types::DATABASE )
            {
                // Create config object from generic information obtained
                // from Configurator
                infrastructure_types::Database_Data_Source_Config::ptr_t db_config =
                    boost::dynamic_pointer_cast<Database_Data_Source_Config> ( m_src_config );

                // Add  unique information from component
                db_config->set_ID ( id );

                infrastructure_types::Database_Data_Transfer::ptr_t temp ( new Database_Data_Transfer ( db_config ) );
                
                boost::shared_ptr < Data_Source < Database_Data_Transfer > >
                    temp_src  ( new Data_Source < Database_Data_Transfer> (temp) );


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::DETAIL,
                                     "Exiting Data_Source_Factory::get_Data_Source" );
#endif /* LIBREVERSE_DEBUG */


                return temp_src;
            }
        else if ( m_src_config->get_Type() == api::Transfer_Types::FILE )
            {

                // Create config object from generic information obtained
                // from Configurator
                infrastructure_types::File_Data_Source_Config::ptr_t file_config =
                    boost::dynamic_pointer_cast<File_Data_Source_Config> ( m_src_config );

                // Add  unique information from component
                file_config->set_ID (id);

                infrastructure_types::File_Data_Transfer::ptr_t temp ( new File_Data_Transfer ( file_config ) );

                boost::shared_ptr< Data_Source < File_Data_Transfer > > temp_src
                    (new Data_Source < File_Data_Transfer > (temp));


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::DETAIL,
                                     "Exiting Data_Source_Factory::get_Data_Source" );
#endif /* LIBREVERSE_DEBUG */

                return temp_src;

            }
        else if ( m_src_config->get_Type() == api::Transfer_Types::MEMORY )
            {
                // Create config object from generic information obtained
                // from Configurator. There are no unique ids required when
                // sending information in memory. The uniqueness needed to
                // identify where the data is stored is the memory location
                // itself.
                infrastructure_types::Memory_Data_Source_Config::ptr_t mem_config =
                    boost::dynamic_pointer_cast<Memory_Data_Source_Config> ( m_src_config );

                infrastructure_types::Memory_Data_Transfer::ptr_t temp ( new Memory_Data_Transfer ( mem_config ) );

                boost::shared_ptr<Data_Source < Memory_Data_Transfer > > temp_src
                    ( new Data_Source < Memory_Data_Transfer > ( temp ) );


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::DETAIL,
                                     "Exiting Data_Source_Factory::get_Data_Source" );
#endif /* LIBREVERSE_DEBUG */


                return temp_src;
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				   TraceLevel::ERROR,
				   boost::str ( boost::format ( "Data_Source_Factory - Type %d was requested." )
						% m_src_config->get_Type() ) );
	      
	      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				   TraceLevel::ERROR,
				   boost::str ( boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */
		
                throw errors::Data_Source_Exception
                    (errors::Data_Source_Exception::UNKNOWN_DATA_SOURCE_TYPE);
            }

    }


    infrastructure_types::Data_Source_Factory::ptr_t
    Data_Source_Factory::Instance ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source_Factory::Instance" );
#endif /* LIBREVERSE_DEBUG */


        if ( m_factory.get() == 0 ) {

            infrastructure_types::Data_Source_Factory::ptr_t new_factory_ptr ( new Data_Source_Factory () );

            m_factory.swap ( new_factory_ptr );

            (Configurator::Instance()).register_Factory ( m_factory );
        }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source_Factory::Instance" );
#endif /* LIBREVERSE_DEBUG */


        return m_factory;
    }

    void Data_Source_Factory::init ( boost::shared_ptr < const infrastructure::data_source::data_source_config_base > source_config )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source_Factory::init" );
#endif /* LIBREVERSE_DEBUG */


        if ( source_config.get() == 0 )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

        m_src_config = source_config;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source_Factory::init" );
#endif /* LIBREVERSE_DEBUG */


    }

} /* namespace infrastructure */
} /* namespace libreverse */
