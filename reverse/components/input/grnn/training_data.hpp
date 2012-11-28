/*  Training_Data.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_DATA_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_DATA_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <map>
#include <sstream>
#include <string>


namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <typename data_type> class configuration;

	template <typename data_type>
	class training_data
	{
	public:

	  training_data ()
	    : m_data ( boost::make_shared<data_type>() )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Data constructor" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  ~training_data()
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Data destructor" );
#endif /* LIBREVERSE_DEBUG */
	  }

	  void set_attribute ( boost::uint32_t key, double value )
	  {
	    m_data->set_attribute ( key, value );
	  }


	  double get_attribute ( boost::uint32_t key ) const
	  {
	    return m_data->get_attribute ( key );
	  }


	  bool empty ( void ) const
	  {
	    return m_data->empty();
	  }


	  static std::string get_attribute_string_list
	    ( boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> > config =
	      boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> >
	      ( new  reverse::components::input::grnn::configuration<data_type>() ) )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */


	    std::string output;

	    output = data_type::get_attribute_string_list ( config );


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Data::get_Attribute_String_List" );
#endif /* LIBREVERSE_DEBUG */


	    return output;
	  }

	  std::string to_string ( boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> > config =
				  boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> >
				  ( new reverse::components::input::grnn::configuration<data_type>() ) ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream output;

	    output << "---- training_data ----" << std::endl;

	    output << m_data->to_string ( config );


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Data::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    return output.str();
	  }
      
	  std::string to_xml ( boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> > config =
			       boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> >
			       ( new reverse::components::input::grnn::configuration<data_type>() ) ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream output;

	    output << m_data->to_xml ( config );


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Data::to_XML" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }


	  std::map<boost::uint32_t,double>::const_iterator begin ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Data::begin (const)" );
#endif /* LIBREVERSE_DEBUG */


	    return m_data->begin();
	  }

	  std::map<boost::uint32_t,double>::iterator begin ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Data::begin" );
#endif /* LIBREVERSE_DEBUG */


	    return m_data->begin();
	  }

	  std::map<boost::uint32_t,double>::const_iterator end ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Data::end (const)" );
#endif /* LIBREVERSE_DEBUG */


	    return m_data->end();
	  }

	  std::map<boost::uint32_t,double>::iterator end ( void )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Data::end" );
#endif /* LIBREVERSE_DEBUG */


	    return m_data->end();
	  }

	  bool is_valid (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Data::is_Valid" );
#endif /* LIBREVERSE_DEBUG */

	    bool valid = true;

	    boost::uint32_t index = 0;

	    for ( boost::uint32_t key = 1;
		  key < data_type::attribute_count;
		  ++key )
	      {
		if ( ! ( m_data->get_attribute ( key ) >= 0.0 && m_data->get_attribute ( key ) <= 1.0 ) )
		  {

#ifdef LIBREVERSE_DEBUG
		    trace::write_trace ( trace_area::classifier,
					 trace_level::error,
					 boost::str ( boost::format ( "Item #%1$d is not valid" )
						      % index ) );
#endif /* LIBREVERSE_DEBUG */

		    valid = false;
		    break;
		  }
          
		++index;
	      }


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Data::is_Valid" );  
#endif /* LIBREVERSE_DEBUG */

       
	    return valid;
	  }


	private:

	  boost::shared_ptr<data_type> m_data;
	};

      } // namespace input
    } // namespace grnn
  } // namespace components
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_DATA_HPP_INCLUDED
