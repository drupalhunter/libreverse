/*  Configuration.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_CONFIGURATION_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_CONFIGURATION_HPP_INCLUDED

#include <reverse/errors/internal_exception.hpp>
#include <reverse/components/input/grnn/training_data.hpp>
#include <reverse/trace.hpp>

#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <map>
#include <sstream>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {
    
	template <typename data_type>
	class configuration : public boost::enable_shared_from_this< configuration<data_type> >
	{
	public:
	  
	  configuration ( bool default_value = true )
	  {

	    trace::grnn_detail ( "Entering Configuration constructor" );
	  
	    for ( boost::uint32_t i = 0;
		  i < data_type::attribute_count;
		  ++i )
	      {
		m_attributes[i] = default_value;
	      }

	    trace::grnn_detail ( "Exiting Configuration constructor" );
	  }

	  configuration ( const configuration& rhs )
	    : boost::enable_shared_from_this< configuration<data_type> > ( rhs ),
	      m_attributes ( rhs.m_attributes )
	  {
	    trace::grnn_detail ( "Inside Configuration copy constructor" );
	  }

	  void set_attribute ( boost::uint32_t index, bool value )
	  {
	    trace::grnn_detail ( "Entering Configuration::set_Attribute" );

	    if ( index > m_attributes.size() )
	      {
		throw errors::internal_exception ( errors::internal_exception::invalid_index );
	      }

	    m_attributes[index] = value;

	    trace::grnn_detail ( "Exiting Configuration::set_Attribute" );
	  }

	  bool get_attribute ( boost::uint32_t index ) const
	  {
	    trace::grnn_detail ( "Entering Configuration::get_Attribute" );

	    if ( index > m_attributes.size() )
	      {
		throw errors::internal_exception ( errors::internal_exception::invalid_index );
	      }

	    trace::grnn_detail ( "Exiting Configuration::set_Attribute" );

	    return m_attributes.at(index);
	  }


	  std::string to_string (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::grnn_data,
				 trace_level::detail,
				 "Entering Configuration::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    std::stringstream output;
	    output << "---- configuration ----" << std::endl;
	    output << "    ";
	    output << training_data<data_type>::get_attribute_string_list ( this->shared_from_this() );

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::grnn_data,
				 trace_level::detail,
				 "Exiting Configuration::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    return output.str();
	  }
        
	private:

	  std::string bool_string ( bool value ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::grnn_data,
				 trace_level::detail,
				 "Entering Configuration::bool_String" );
#endif /* LIBREVERSE_DEBUG */

	    std::string result = "";

	    if ( value )
	      {
		result = "true";
	      }
	    else
	      {
		result = "false";
	      }


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::grnn_data,
				 trace_level::detail,
				 "Exiting Configuration::bool_String" );
#endif /* LIBREVERSE_DEBUG */


	    return result;
	  }

        
	  std::map<boost::uint32_t, bool> m_attributes;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_GRNN_CONFIGURATION_HPP_INCLUDED
