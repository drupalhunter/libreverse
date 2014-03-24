
/*  Component_Data.cpp

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
#include <reverse/data_containers/filename.hpp>
#include <reverse/data_containers/control_flow_graph_sequence.hpp>
#include <reverse/data_containers/memory_map.hpp>
#include <reverse/errors/api_exception.hpp>
#include <reverse/errors/component_exception.hpp>
#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_actor.hpp>
#include <reverse/infrastructure/data_source/data_source_factory.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>
#include <reverse/infrastructure/data_source/data_source_base.hpp>
#include <reverse/meta/meta_object.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

namespace reverse {
  namespace infrastructure {

    component_data::component_data ( boost::uint32_t id )
        : m_id ( id ),
	  m_data_obj_ptr ( new data_source::data_object () ),
          m_meta_ptr ( new meta::meta_object() ),
          m_filename_ptr (),
          m_graph_ptr (),
          m_map_ptr ()
    {
      trace::infrastructure_detail ( "Inside component_data constructor" );
    }

    component_data::component_data ( component_data const& rhs )
        : m_id ( rhs.m_id ),
          m_data_obj_ptr ( new data_source::data_object ( *rhs.m_data_obj_ptr ) ),
          m_meta_ptr ( new meta::meta_object ( *rhs.m_meta_ptr ) )
    {
      trace::infrastructure_detail ( "Entering component_data copy constructor" );

      if ( rhs.m_filename_ptr.get() != 0 )
	{
	  m_filename_ptr.reset ( new data_containers::filename ( *rhs.m_filename_ptr ) );
	}

      if ( rhs.m_graph_ptr.get() != 0 )
	{
	  m_graph_ptr.reset ( new data_containers::control_flow_graph_sequence ( *rhs.m_graph_ptr ) );
	}

      if ( rhs.m_map_ptr.get() != 0 )
	{
	  m_map_ptr.reset ( new data_containers::memory_map ( *rhs.m_map_ptr ) );
	}

      std::copy ( rhs.m_source_list.begin(),
		  rhs.m_source_list.end(),
		  std::inserter ( m_source_list, m_source_list.begin() ) );
      
      trace::infrastructure_detail ( "Exiting component_data copy constructor" );
    }

    component_data::~component_data ()
    {
      trace::infrastructure_detail ( "Entering component_data destructor" );

      m_source_list.clear();

      trace::infrastructure_detail ( "Exiting component_data destructor" );
    }

    boost::uint32_t
    component_data::get_id (void) const
    {
      trace::infrastructure_detail ( "Inside component_data::get_ID" );

      return m_id;
    }

    void
    component_data::add_input_source ( boost::uint32_t id )
    {
      trace::infrastructure_detail ( "Entering component_data::add_Input_Source" );

      if ( ! m_source_list.insert ( std::make_pair ( id, false ) ).second )
	{
	  trace::infrastructure_error ( "Attempted to add a duplicate component id (%d). Ignoring component.", id );
	}

      trace::infrastructure_detail ( "Exiting component_data::add_Input_Source" );
    }

    void
    component_data::received_input_source_data ( boost::uint32_t id )
    {

      trace::infrastructure_detail ( "Entering component_data::received_Input_Source_Data" );
      trace::infrastructure_data ( "Component(%d)::init", m_id );

      infrastructure::component_data::input_token_t::iterator pos = m_source_list.find ( id );

      if ( pos != m_source_list.end() )
	{
	  pos->second = true;

	  trace::infrastructure_data ( "(%d) - initialized with data from component #%d", m_id, id );
	}
      else
	{
	  trace::infrastructure_data ( "Invalid index given was %d", id );
	  trace::infrastructure_error ( "Exception throw in %s at line %d", __FILE__, __LINE__ );

	  throw errors::component_exception ( errors::component_exception::invalid_index );
	}

      trace::infrastructure_detail ( "Exiting component_data::received_Input_Source_Data" );
    }

    void
    component_data::gather_inputs ( infrastructure::component_graph::data_map_t* data_ptr )
    {
      trace::infrastructure_detail ( "Entering component_data::gather_Inputs" );
      trace::infrastructure_data ( "component_data::gather_Inputs - size of source list = %d", m_source_list.size() );
      boost::shared_ptr < meta::meta_object > input_meta_ptr = boost::make_shared < meta::meta_object > ();

      for ( infrastructure::component_data::input_token_t::iterator pos = m_source_list.begin();
	    pos != m_source_list.end();
	    ++pos )
	{
	  infrastructure::component_graph::data_map_t::const_iterator cpos = data_ptr->find ( pos->first );

	  if ( cpos == data_ptr->end() )
	    {
	      trace::infrastructure_error ( "(%d)::gather_Inputs (EE) - input data %d missing from node #%d", m_id, pos->first );
	      trace::infrastructure_error ( "  Dumping data_ref\n  Src, (Data ptr, # of children)\n  ------------------" );
	      
	      for ( infrastructure::component_graph::data_map_t::const_iterator content_pos = data_ptr->begin();
		    content_pos != data_ptr->end();
		    ++content_pos )
		{
		  trace::infrastructure_error ( "%d, (%p, %d )", content_pos->first, content_pos->second.first, content_pos->second.second );
		}

	      trace::infrastructure_error ( "Exception throw in %s at line %d", __FILE__, __LINE__ );
                      
	      // At this point we have not found the filename somehow
	      // the Precondition visitor did not work. So we will
	      // will throw an exception
	      throw ( errors::api_exception ( errors::api_exception::internal_library_error ) );
	    }
	  else
	    {
	      trace::infrastructure_data ( "Found data from node %d", pos->first );
	    }

	  infrastructure::component_graph::result_data_t data_pos = cpos->second;

	  boost::shared_ptr < const infrastructure::data_source::data_source_base > input_data_ptr = data_pos.first;

	  assert::null_check ( input_data_ptr.get(), "input_data_ptr.get())" );
                
#ifdef LIBREVERSE_DEBUG
	  trace::infrastructure_data ( input_data_ptr->to_string().c_str() );
#endif
                
	  // Get input data from data source
	  boost::shared_ptr < const infrastructure::data_source::data_object > d_obj_ptr = input_data_ptr->get();

	  m_filename_ptr = d_obj_ptr->get_filename();
	  m_graph_ptr = d_obj_ptr->get_control_flow_graph_sequence();
	  m_map_ptr = d_obj_ptr->get_memory_map();

	  // Copy meta information
	  meta::meta_object::const_ptr_t m_obj_ptr = d_obj_ptr->getmeta();

	  input_meta_ptr->append ( m_obj_ptr );
	}

      m_meta_ptr = input_meta_ptr;

      trace::infrastructure_detail ( "Exiting component_data::gather_Inputs" );
    }

    bool
    component_data::find ( boost::uint32_t id )
    {
      trace::infrastructure_detail ( "Entering component_data::find" );
      
      bool result = false;
      
      infrastructure::component_data::input_token_t::iterator pos = m_source_list.find ( id );
      if ( pos != m_source_list.end() )
	{
	  result = true;
	}
      
      trace::infrastructure_detail ( "Exiting component_data::find" );
      
      return result;
    }

    boost::shared_ptr < infrastructure::data_source::data_source_base >
    component_data::get_data_source (void) const
    {
      trace::infrastructure_detail ( "Entering component_data::get_Data_Source" );

      boost::shared_ptr < infrastructure::data_source::data_source_factory > fact_ptr = infrastructure::data_source::data_source_factory::instance();

      boost::shared_ptr < infrastructure::data_source::data_source_base > data_source_ptr = fact_ptr->get_data_source ( m_id );

#ifdef LIBREVERSE_DEBUG
	trace::infrastructure_data ( data_source_ptr->to_String() );
#endif /* LIBREVERSE_DEBUG */

	trace::infrastructure_detail ( "Exiting component_data::get_Data_Source" );

        return data_source_ptr;
    }

    void
    component_data::set_output_data ( boost::shared_ptr < const data_containers::filename > file_ptr )
    {
      trace::infrastructure_detail ( "Entering component_data::component_data (Filename)" );
      
      m_data_obj_ptr->set_data ( file_ptr );

      trace::infrastructure_detail ( "Exiting component_data::component_data (Filename)" );
    }

    void
    component_data::set_output_data ( boost::shared_ptr < const data_containers::control_flow_graph_sequence > graph_ptr )
    {
      trace::infrastructure_detail ( "Entering component_data::set_Output_Data (Control_Flow_Graph_Sequence)" );

      m_data_obj_ptr->set_data ( graph_ptr );

      trace::infrastructure_detail ( "Exiting component_data::set_Output_Data (Control_Flow_Graph_Sequence)" );
    }

    void
    component_data::set_output_data ( boost::shared_ptr < const data_containers::memory_map > map_ptr )
    {
      trace::infrastructure_detail ( "Entering component_data::set_Output_Data (Memory_Map)" );

      m_data_obj_ptr->set_data ( map_ptr );

      trace::infrastructure_detail ( "Exiting component_data::set_Output_Data (Memory_Map)" );
    }

    bool
    component_data::is_filename_set (void) const
    {
      trace::infrastructure_detail ( "Entering component_data::is_Filename_Set" );

      bool result = false;
      
      if ( m_filename_ptr.get() != 0 )
	{
	  result = true;
	}

      trace::infrastructure_detail ( "Exiting component_data::is_Filename_Set" );

      return result;
    }

    bool
    component_data::is_control_flow_graph_sequence_set (void) const
    {
      trace::infrastructure_detail ( "Entering component_data::is_Control_Flow_Graph_Sequence_Set" );

      bool result = false;
      
      if ( m_graph_ptr.get() != 0 )
	{
	  result = true;
	}

      trace::infrastructure_detail ( "Exiting component_data::is_Control_Flow_Graph_Sequence_Set" );

      return result;
    }

    bool
    component_data::is_memory_map_set (void) const
    {
      trace::infrastructure_detail ( "Entering component_data::is_memory_map_set" );

      bool result = false;
      
      if ( m_map_ptr.get() != 0 )
	{
	  result = true;
	}

      trace::infrastructure_detail ( "Exiting component_data::is_memory_map_set" );

      return result;
    }

    boost::shared_ptr<const data_containers::filename>
    component_data::get_input_filename(void) const
    {
      trace::infrastructure_detail ( "Inside component_data::get_Input_Filename" );

      return m_filename_ptr;
    }

    boost::shared_ptr<const data_containers::control_flow_graph_sequence>
    component_data::get_input_control_flow_graph_sequence ( void ) const
    {
      trace::infrastructure_detail ( "Inside component_data::get_input_control_flow_graph_sequence" );

      return m_graph_ptr;
    }

    boost::shared_ptr<const data_containers::memory_map>
    component_data::get_input_memory_map(void) const
    {
      trace::infrastructure_detail ( "Inside component_data::get_input_memory_map" );

      return m_map_ptr;
    }

    void
    component_data::set_append_meta_data ( boost::shared_ptr < const meta::meta_object >& meta_ptr )
    {
      trace::infrastructure_detail ( "Entering component_data::set_output_data" );
      boost::shared_ptr < meta::meta_object > input_meta_ptr = boost::make_shared < meta::meta_object > ( *m_meta_ptr );      
      input_meta_ptr->append ( meta_ptr );
      m_meta_ptr = input_meta_ptr;
      m_data_obj_ptr->put_meta ( m_meta_ptr );

      trace::infrastructure_detail ( "Exiting component_data::set_Output_Data" );
    }


    component_data::input_token_t::const_iterator
    component_data::get_source_list_begin (void) const
    {
      trace::infrastructure_detail ( "Inside component_data::get_Source_List_Begin (const)" );

      return m_source_list.begin();
    }

    component_data::input_token_t::const_iterator
    component_data::get_source_list_end (void) const
    {
      trace::infrastructure_detail ( "Inside component_data::get_Source_List_End (const)" );

      return m_source_list.end();
    }
    
    boost::shared_ptr < const meta::meta_object >
    component_data::get_input_meta_data (void) const
    {

      trace::infrastructure_detail ( "Inside component_data::get_Input_Meta_Data" );

      return m_meta_ptr;
    }

    component_data&
    component_data::operator= ( component_data const& rhs )
    {

      trace::infrastructure_detail ( "Entering component_data::operator= (assignment)" );

      component_data temp ( rhs );
      swap ( temp );

      trace::infrastructure_detail ( "Exiting component_data::operator= (assignment)" );

      return *this;
    }

    void
    component_data::swap ( component_data& rhs )
    {

      trace::infrastructure_detail ( "Entering component_data::swap" );

      std::swap ( m_id, rhs.m_id );
      std::swap ( m_source_list, rhs.m_source_list );

      m_data_obj_ptr.swap ( rhs.m_data_obj_ptr );
      m_meta_ptr.swap ( rhs.m_meta_ptr );
      m_filename_ptr.swap ( rhs.m_filename_ptr );
      m_graph_ptr.swap ( rhs.m_graph_ptr );
      m_map_ptr.swap ( rhs.m_map_ptr );

      trace::infrastructure_detail ( "Exiting component_data::swap" );
    }

    std::string
    component_data::to_string (void) const
    {
      trace::infrastructure_detail ( "Entering component_data::to_string" );

      std::stringstream output;

      output << boost::format ( "ID: %d" ) % m_id << std::endl
	     << "  Input sources: " << std::endl;
      
      for ( infrastructure::component_data::input_token_t::const_iterator cpos = m_source_list.begin();
	    cpos != m_source_list.end();
	    ++cpos )
	{
	  std::string found = "true";
	  
	  if ( ! cpos->second )
	    {
	      found = "false";
	    }
	  
	  output << boost::format("    id: %d => %s")
	    % cpos->first
	    % found << std::endl;
	}
      
      if ( m_data_obj_ptr )
	{
	  output << m_data_obj_ptr->to_string() << std::endl;
	}
      
      if ( m_meta_ptr )
	{
	  output << m_meta_ptr->to_string() << std::endl;
	}
      
      if ( m_filename_ptr )
	{
	  output << m_filename_ptr << std::endl;
	}
      
      if ( m_graph_ptr )
	{
	  output << m_graph_ptr->to_string() << std::endl;
	}
      
      if ( m_map_ptr )
	{
	  output << m_map_ptr->to_string() << std::endl;
	}
      
      trace::infrastructure_detail ( "Exiting component_data::to_string" );

      return output.str();
    }

  } /* namespace infrastructure */
} /* namespace libreverse */

