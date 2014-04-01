/*  Data_Source_T.cpp

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

#include <string>
#include "Data_Source_T.h"
#include <iostream>
#include "data_containers/filename.h"
#include "data_containers/Control_Flow_Graph.h"
#include "data_containers/memory_map.h"
#include "errors/component_exception.h"

#include "meta/meta_object.h"
#include <boost/format.hpp>


#ifdef LIBREVERSE_DEBUG
#include "libreverse/Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    template <typename Transfer_Type>
    Data_Source<Transfer_Type>::Data_Source ( typename boost::shared_ptr<Transfer_Type> rhs )
        : m_data_ptr ( new data_object() ),
          m_transfer_method ( new Transfer_Type ( *rhs ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source constructor" );
#endif /* LIBREVERSE_DEBUG */


        // open Transfer_Type
        m_transfer_method->open();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source constructor" );
#endif /* LIBREVERSE_DEBUG */


    }

    template <typename Transfer_Type>
    Data_Source<Transfer_Type>::Data_Source ( Data_Source const& rhs )
        : Data_Source_Base ( rhs ),
          boost::enable_shared_from_this < Data_Source < Transfer_Type> > ( rhs ),
          m_data_ptr ( new data_object ( *rhs.m_data_ptr ) )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Source copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    template <typename Transfer_Type>
    Data_Source<Transfer_Type>::~Data_Source ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source destructor" );
#endif /* LIBREVERSE_DEBUG */


        // close Transfer_Type
        m_transfer_method->close();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    template < typename Transfer_Type>
    void Data_Source<Transfer_Type>::put ( infrastructure_types::data_object::const_ptr_t data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source::put" );
#endif /* LIBREVERSE_DEBUG */


        if ( data.get() == 0 )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format("Exception throw in %s at line %d")
                                                  % __FILE__
                                                  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                
                throw errors::component_exception
                    ( errors::component_exception::null_pointer );
            }

        // Get data from Data_Type and Put data into Transfer_Type
        m_transfer_method->put (data);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source::put" );
#endif /* LIBREVERSE_DEBUG */

    }

    template < typename Transfer_Type>
    infrastructure_types::data_object::const_ptr_t
    Data_Source<Transfer_Type>::get () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Source::get" );
#endif /* LIBREVERSE_DEBUG */

        // Get data from Transfer_Type and Put data into Data_Type
        return m_transfer_method->get();
    }

    template <typename Transfer_Type>
    std::string
    Data_Source<Transfer_Type>::to_String () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

        infrastructure_types::data_object::const_ptr_t data_ptr = this->get();

        if ( data_ptr.get() != 0 )
            {
                meta::meta_object::const_ptr_t meta_ptr = data_ptr->get_meta();

                output << "Data Source: " << std::endl
                       << "  - Data - " << std::endl
                       << data_ptr->to_String() << std::endl
                       << std::endl
                       << "  - Meta - " << std::endl
                       << meta_ptr->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source::toString" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    template <typename Transfer_Type>
    typename infrastructure_types::Data_Source_Base::ptr_t
    Data_Source<Transfer_Type>::get_Deep_Copy ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Source::get_Deep_Copy" );
#endif /* LIBREVERSE_DEBUG */

        return typename infrastructure_types::Data_Source<Transfer_Type>::ptr_t ( new Data_Source<Transfer_Type>(*this) );
    }

    template <typename Transfer_Type>
    Data_Source<Transfer_Type>&
    Data_Source<Transfer_Type>::operator= ( Data_Source const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source::operator=" );
#endif /* LIBREVERSE_DEBUG */


        Data_Source temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source::operator=" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    template <typename Transfer_Type>
    void
    Data_Source<Transfer_Type>::swap ( Data_Source& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Source::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_data_ptr.swap ( rhs.m_data_ptr );
        m_transfer_method.swap ( rhs.m_transfer_method );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Source::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
