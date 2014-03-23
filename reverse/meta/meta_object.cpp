/*  Meta_Object.cpp

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
#include <reverse/meta/meta_object.hpp>
#include <reverse/errors/configuration_exception.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace meta {

    boost::uint8_t const meta_object::string = 0;
    boost::uint8_t const meta_object::hex = 1;

    meta_object::meta_object ( void )
    {
      trace::meta_detail ( "Inside meta_object constructor" );
    }

    meta_object::meta_object ( meta_object const& rhs )
    {
      trace::meta_detail ( "Entering meta_object copy constructor" );

        /*
          std::string key = "";
          std::string value = "";
          boost::uint8_t type = 0;

          for ( Data_t::const_iterator cpos = rhs.m_info_map.begin();
          cpos != rhs.m_info_map.end();
          cpos++ )
          {
          key = std::string ( (*cpos).first );
          
          Data_Pair_t pair_ref = (*cpos).second;
          value = std::string ( pair_ref.first );
          type = ( pair_ref.second );
              
          this->add ( key, value, type );
          }
        */
        std::copy ( rhs.m_info_map.begin(),
                    rhs.m_info_map.end(),
                    std::inserter ( m_info_map, m_info_map.begin() ) );

	trace::meta_detail ( "Exiting meta_object copy constructor" );
    }

    void
    meta_object::add ( std::string key,
                       std::string value,
                       boost::uint8_t type )
    {
      trace::meta_detail ( "Entering meta_object::add" );

      assert::bool_check ( ! key.empty(), "Key must not be empty" );
      assert::bool_check ( ! value.empty(), "Input value must not be empty" );
      assert::bool_check ( this->is_valid_type ( type ), "Input type must be an a valid type" );

      data_pair_t data = std::make_pair ( value, type );

      std::pair<meta_object::iterator,bool> result =
	m_info_map.insert ( std::make_pair ( key, data ) );

      assert::bool_check ( result.second, "Insertion must be complete without error." );

      trace::meta_detail ( "Exiting meta_object::add" );
    }

    void
    meta_object::append ( meta_object::const_ptr_t meta_ptr )
    {
      trace::meta_detail ( "Entering meta_object::append" );

      assert::null_check ( meta_ptr.get(), "Input meta_ptr must not be NULL" );

      m_info_map.insert ( meta_ptr->begin(),
			  meta_ptr->end() );

      trace::meta_detail ( "Exiting meta_object::append" );
    }

    meta_object::data_pair_t
    meta_object::get_value ( std::string key ) const
    {
      trace::meta_detail ( "Entering meta_object::get_Value" );

      data_t::const_iterator pos = m_info_map.find ( key );

      if ( pos != m_info_map.end() )
	{
	  meta_object::data_pair_t data = pos->second;
	  assert::bool_check ( ! (data.first).empty(), "Meta data is empty" );
	  assert::bool_check ( this->is_valid_type ( data.second ), "Meta data is not valid" );
	  
	  return data;
	}
      else
	{
	  trace::meta_error ( "meta_object::get_Value - unknown key: %s", key );
	  throw errors::meta_exception ( errors::meta_exception::invalid_key );
	}

      trace::meta_detail ( "Exiting meta_object::get_Value" );
    }

    meta_object::iterator
    meta_object::begin (void)
    {
      trace::meta_detail ( "Inside meta_object::begin" );

      return m_info_map.begin();
    }

    meta_object::const_iterator const
    meta_object::begin (void) const
    {
      trace::meta_detail ( "Inside meta_object::begin (const)" );

      return m_info_map.begin();
    }

    meta_object::iterator
    meta_object::end (void)
    {
      trace::meta_detail ( "Inside meta_object::end" );

      return m_info_map.end();
    }

    meta_object::const_iterator const
    meta_object::end (void) const
    {
      trace::meta_detail ( "Inside meta_object::end (const)" );

      return m_info_map.end();
    }

    meta_object::size_t
    meta_object::size (void) const
    {
      trace::meta_detail ( "Inside meta_object::size" );

      return m_info_map.size();
    }


    std::string
    meta_object::to_string () const
    {
      trace::meta_detail ( "Entering meta_object::to_string" );

      std::stringstream output;
      
      if ( ! m_info_map.empty() )
	{
	  
	  output << "-----------------------" << std::endl
		 << "      meta_object" << std::endl
		 << "-----------------------" << std::endl;
	  
	  for ( data_t::const_iterator pos = m_info_map.begin();
		pos != m_info_map.end();
		pos++ )
	    {
	      data_pair_t data = pos->second;
	      
	      switch ( data.second )
		{
		case hex:
		  {
		    output << boost::format ( "%1% = %2$X" ) %
		      pos->first %
		      this->convert_to_uint32 ( data.first )
			   << std::endl;
		    break;
		  }
		case string:
		default:
		  {
		    output << boost::format ( "%1% = %2%" ) %
		      pos->first %
		      data.first
			   << std::endl;
		  }
		}
	    }
	}
      
      trace::meta_detail ( "Exiting meta_object::to_String" );

      return output.str();
    }

    bool
    meta_object::is_valid_type ( boost::uint8_t type ) const
    {
      trace::meta_detail ( "entering meta_object::is_valid_type" );

      bool result = false;
	
      switch ( type )
	{
	case string:
	case hex:
	  result = true;
	  break;
	default:
	  result = false;
	}
      
      trace::meta_detail ( "Exiting meta_object::is_valid_type" );

      return result;
    }

    meta_object&
    meta_object::operator= ( meta_object const& rhs )
    {
      trace::meta_detail ( "Entering meta_object::operator=" );

      meta_object temp ( rhs );
      swap ( temp );
      
      trace::meta_detail ( "Exiting meta_object::operator=" );
      
      return *this;
    }
    
    void
    meta_object::swap ( meta_object& rhs )
    {
      trace::meta_detail ( "Entering meta_object::swap" );
      
        m_info_map.swap ( rhs.m_info_map );
	
      trace::meta_detail ( "Exiting meta_object::swap" );
    }

  } /* namespace meta */
} /* namespace reverse */
