/*  Data_Object.cpp

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

#include "Data_Object.h"
#include "errors/Component_Exception.h"
#include "data_containers/Control_Flow_Graph_Sequence.h"
#include "data_containers/Memory_Map.h"
#include <sstream>
#include <boost/format.hpp>

#include "Assert.h"
using namespace libreverse::assert;


#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Data_Object::Data_Object ()
        : m_meta ( new meta::Meta_Object() ),
          m_filename(),
          m_graph(),
          m_map()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object constructor" );
#endif /* LIBREVERSE_DEBUG */


        Assert::null_check ( m_meta.get(), "m_meta.get() should not be null" );
        Assert::bool_check ( m_filename.get() == 0, "m_filename.get() == 0" );
        Assert::bool_check ( m_graph.get() == 0, "m_graph.get() == 0" );
        Assert::bool_check ( m_map.get() == 0, "m_map.get() == 0" );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Data_Object::Data_Object ( const boost::shared_ptr < const Filename>& data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::Data_Object (Filename)" );
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


                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

        m_filename = data;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::INFO,
			     boost::str ( boost::format("Data_Object::Data_Object - Filename = %s (Ptr count = %d, Input Ptr count = %d)")
					  % m_filename->to_String()
					  % m_filename.use_count()
					  % data.use_count() ) );

        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::Data_Object (Filename)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Data_Object::Data_Object ( boost::shared_ptr < const Control_Flow_Graph_Sequence>& data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::Data_Object (Control_Flow_Graph_Sequence)" );
#endif /* LIBREVERSE_DEBUG */

        if ( data.get() == 0 )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Component_Exception ( errors::Component_Exception::NULL_POINTER );
            }

        m_graph = data;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::Data_Object (Control_Flow_Graph_Sequence)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Data_Object::Data_Object ( boost::shared_ptr < const Memory_Map>& data )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::Data_Object (Memory_Map)" );
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

                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

        m_map = data;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::Data_Object (Memory_Map)" );
#endif /* LIBREVERSE_DEBUG */

    }


    Data_Object::Data_Object ( Data_Object const& rhs )
        : m_meta ( new meta::Meta_Object ( *rhs.m_meta ) )
    {
        // Test equality? We say that they are true copies but are they


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object copy constructor" );
#endif /* LIBREVERSE_DEBUG */


        if ( rhs.m_filename.get() != 0 )
            {
                m_filename.reset ( new data_containers::Filename ( *rhs.m_filename ) );
            }
        
        if ( rhs.m_graph.get() != 0 )
            {
                m_graph.reset ( new data_containers::Control_Flow_Graph_Sequence ( *rhs.m_graph ) );
            }

        if ( rhs.m_map.get() != 0 )
            {
                m_map.reset ( new data_containers::Memory_Map ( *rhs.m_map ) );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object copy constructor" );
#endif /* LIBREVERSE_DEBUG */

    }


    void
    Data_Object::put_Meta ( boost::shared_ptr < const Meta_Object>& meta_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::put_Meta" );
#endif /* LIBREVERSE_DEBUG */


        if ( meta_ptr.get() == 0 )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format("Exception throw in %s at line %d")
                                                  % __FILE__
                                                  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

        m_meta = meta_ptr;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::put_Meta" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::shared_ptr < const Meta_Object>
    Data_Object::getMeta() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Object::get_Meta" );
#endif /* LIBREVERSE_DEBUG */

        return m_meta;
    }

    std::string
    Data_Object::to_String ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::to_String" );
#endif /* LIBREVERSE_DEBUG */

        std::stringstream output;

        output << "--------------------------" << std::endl
               << "      Data Object" << std::endl
               << "--------------------------" << std::endl;

        if ( m_filename )
            {
                output << boost::format ( "  Filename: %s" ) % m_filename->to_String() << std::endl;
            }

        if ( m_graph )
            {
                output << "  Graph: " << std::endl
                       << m_graph->to_String() << std::endl;
            }

        if ( m_map )
            {
                output << m_map->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::to_String" );
#endif /* LIBREVERSE_DEBUG */

        return output.str();
    }

    boost::shared_ptr < const Filename>
    Data_Object::get_Filename ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Object::get_Filename" );
#endif /* LIBREVERSE_DEBUG */

        return m_filename;
    }
    
    boost::shared_ptr < const Control_Flow_Graph_Sequence>
    Data_Object::get_Control_Flow_Graph_Sequence (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Object::get_Control_Flow_Graph_Sequence" );
#endif /* LIBREVERSE_DEBUG */

        return m_graph;
    }

    boost::shared_ptr < const Memory_Map>
    Data_Object::get_Memory_Map () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Inside Data_Object::get_Memory_Map" );
#endif /* LIBREVERSE_DEBUG */

        return m_map;
    }

    Data_Object&
    Data_Object::operator= ( Data_Object const& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::operator=" );
#endif /* LIBREVERSE_DEBUG */


        Data_Object temp ( rhs );
        swap ( temp );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::operator=" );
#endif /* LIBREVERSE_DEBUG */

        return *this;
    }

    void
    Data_Object::swap ( Data_Object& rhs )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Entering Data_Object::swap" );
#endif /* LIBREVERSE_DEBUG */


        m_meta.swap ( rhs.m_meta );
        m_filename.swap ( rhs.m_filename );
        m_graph.swap ( rhs.m_graph );
        m_map.swap ( rhs.m_map );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
                             TraceLevel::DETAIL,
                             "Exiting Data_Object::swap" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace infrastructure */
} /* namespace libreverse */
