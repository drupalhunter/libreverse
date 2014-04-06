/*  data_object.cpp

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

#include <reverse/assert/assert.hpp>
#include <reverse/trace.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>
#include <reverse/errors/component_exception.hpp>
#include <reverse/data_containers/control_flow_graph_sequence.hpp>
#include <reverse/data_containers/filename.hpp>
#include <reverse/data_containers/memory_map.hpp>

#include <boost/format.hpp>

#include <sstream>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

    data_object::data_object ()
        : m_meta ( new meta::meta_object() ),
          m_filename(),
          m_graph(),
          m_map()
    {
        trace::infrastructure_detail( "Entering data_object constructor" );

	reverse::assert::null_check ( m_meta.get(), "m_meta.get() should not be null" );
        reverse::assert::bool_check ( m_filename.get() == 0, "m_filename.get() == 0" );
        reverse::assert::bool_check ( m_graph.get() == 0, "m_graph.get() == 0" );
        reverse::assert::bool_check ( m_map.get() == 0, "m_map.get() == 0" );

	trace::infrastructure_detail( "Exiting data_object constructor" );
    }

    data_object::data_object ( boost::shared_ptr < const data_containers::filename >& data )
    {
      trace::infrastructure_detail("Entering data_object::data_object (filename)" );

        if ( data.get() == 0 )
            {

	      trace::infrastructure_error( "Exception throw in %s at line %d",
				__FILE__,
                                __LINE__ );

              throw errors::component_exception ( errors::component_exception::null_pointer);
            }

        m_filename = data;

	trace::infrastructure_detail( "Exiting data_object::data_object (filename)" );
    }

    data_object::data_object ( boost::shared_ptr < const data_containers::control_flow_graph_sequence >& data )
    {
	trace::infrastructure_detail( "Entering data_object::data_object (control_flow_graph_sequence)" );

        if ( data.get() == 0 )
            {
		trace::infrastructure_error( "Exception throw in %s at line %d",
                                   __FILE__,
                                   __LINE__ );

                throw errors::component_exception ( errors::component_exception::null_pointer );
            }

        m_graph = data;

        trace::infrastructure_detail( "Exiting data_object::data_object (control_flow_graph_sequence)" );
    }

    data_object::data_object ( boost::shared_ptr < const data_containers::memory_map >& data )
    {
        trace::infrastructure_detail( "Entering data_object::data_object (memory_map)" );

        if ( data.get() == 0 )
            {
	      trace::infrastructure_error ( "Exception throw in %s at line %d",
                                            __FILE__,
                                            __LINE__ );

	      throw errors::component_exception ( errors::component_exception::null_pointer );
            }

        m_map = data;

        trace::infrastructure_detail ( "Exiting data_object::data_object (memory_map)" );
    }

    data_object::data_object ( data_object const& rhs )
        : m_meta ( new meta::meta_object ( *rhs.m_meta ) )
    {
        // Test equality? We say that they are true copies but are they

      trace::infrastructure_detail ( "Entering data_object copy constructor" );

        if ( rhs.m_filename.get() != 0 )
            {
                m_filename.reset ( new data_containers::filename ( *rhs.m_filename ) );
            }
        
        if ( rhs.m_graph.get() != 0 )
            {
                m_graph.reset ( new data_containers::control_flow_graph_sequence ( *rhs.m_graph ) );
            }

        if ( rhs.m_map.get() != 0 )
            {
                m_map.reset ( new data_containers::memory_map ( *rhs.m_map ) );
            }

      trace::infrastructure_detail( "Exiting data_object copy constructor" );
    }


    void
    data_object::put_meta ( boost::shared_ptr < const meta::meta_object>& meta_ptr )
    {
      trace::infrastructure_detail ( "Entering data_object::put_meta" );

        if ( meta_ptr.get() == 0 )
            {

	      trace::infrastructure_error<>( "Exception throw in %s at line %d",
                                                  __FILE__,
                                                  __LINE__ );


                throw errors::component_exception ( errors::component_exception::null_pointer );
            }

        m_meta = meta_ptr;

      trace::infrastructure_detail( "Exiting data_object::put_meta" );
    }

    boost::shared_ptr < const meta::meta_object>
    data_object::get_meta() const
    {
      trace::infrastructure_detail( "Inside data_object::get_Meta" );
      return m_meta;
    }


    boost::shared_ptr < const data_containers::filename >
    data_object::get_filename ( void ) const
    {
	trace::infrastructure_detail( "Inside data_object::get_filename" );
        return m_filename;
    }
    
    boost::shared_ptr < const data_containers::control_flow_graph_sequence >
    data_object::get_control_flow_graph_sequence (void) const
    {
	trace::infrastructure_detail( "Inside data_object::get_control_flow_graph_sequence" );
        return m_graph;
    }

    boost::shared_ptr < const data_containers::memory_map >
    data_object::get_memory_map () const
    {
	trace::infrastructure_detail( "Inside data_object::get_memory_map" );
        return m_map;
    }

    data_object&
    data_object::operator= ( data_object const& rhs )
    {
	trace::infrastructure_detail( "Entering data_object::operator=" );

	data_object temp ( rhs );
        swap ( temp );

	trace::infrastructure_detail( "Exiting data_object::operator=" );

	return *this;
    }

    void
    data_object::swap ( data_object& rhs )
    {
	trace::infrastructure_detail ( "Entering data_object::swap" );

        m_meta.swap ( rhs.m_meta );
        m_filename.swap ( rhs.m_filename );
        m_graph.swap ( rhs.m_graph );
        m_map.swap ( rhs.m_map );

	trace::infrastructure_detail ( "Exiting data_object::swap" );
    }
    
    std::ostream& operator<< ( std::ostream& os, data_object const& rhs )
    {
	trace::infrastructure_detail( "Entering operator<<(data_object)" );


        os << "--------------------------" << std::endl
               << "      Data Object" << std::endl
               << "--------------------------" << std::endl;

        if ( rhs.get_filename() )
            {
                os << rhs.get_filename() << std::endl;
            }

        if ( rhs.get_control_flow_graph_sequence() )
            {
                os << rhs.get_control_flow_graph_sequence() << std::endl;
            }

        if ( rhs.get_memory_map() )
            {
                os << rhs.get_memory_map() << std::endl;
            }


	  trace::infrastructure_detail( "Exiting data_object::to_String" );

        return os;
    }

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse