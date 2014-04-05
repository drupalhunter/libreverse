/*  Memory_Data_Transfer.cpp

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

#include "Memory_Data_Transfer.h"
#include <iostream>
#include <boost/format.hpp>
#include "errors/component_exception.h"
#include "data_object.h"
#include "Memory_Data_Source_Config.h"

#include "Assert.h"
using namespace libreverse::assert;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Memory_Data_Transfer::Memory_Data_Transfer ( boost::shared_ptr < const Memory_Data_Source_Config> const & config )
        : m_config ( config ),
          m_data ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Transfer constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Data_Transfer::Memory_Data_Transfer ( Memory_Data_Transfer const& rhs )
        : Data_Transfer_Base ( rhs ),
          m_config ( new Memory_Data_Source_Config ( *rhs.m_config ) )
    {

        if ( rhs.m_data.get() != 0 )
            {
                m_data.reset ( new data_object ( *rhs.m_data ) );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Transfer copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Memory_Data_Transfer::~Memory_Data_Transfer ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Transfer destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::data_object::const_ptr_t
    Memory_Data_Transfer::get () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Memory_Data_Transfer::get" );
#endif /* LIBREVERSE_DEBUG */

        return m_data;
    }

    Memory_Data_Transfer&
    Memory_Data_Transfer::operator= ( Memory_Data_Transfer const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Memory_Data_Transfer::operator=" );
#endif /* LIBREVERSE_DEBUG */


        Memory_Data_Transfer temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Data_Transfer::operator=" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Memory_Data_Transfer::swap ( Memory_Data_Transfer& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Memory_Data_Transfer::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_config.swap ( rhs.m_config );
        m_data.swap ( rhs.m_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Memory_Data_Transfer::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Memory_Data_Transfer::put ( infrastructure_types::data_object::const_ptr_t data_ptr )
    {
        if ( data_ptr.get() == 0 )
            {
                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::component_exception
                    ( errors::component_exception::null_pointer );
            }

        m_data = data_ptr;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
