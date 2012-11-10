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

#include <reverse/errors/Internal_Exception.h>
#include <reverse/components/input/grnn/Training_Data.h>

#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <map>
#include <sstream>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {
    
	template <typename Data_Type>
	class Configuration : public boost::enable_shared_from_this< Configuration<Data_Type> >
	{
	public:
	  
	Configuration ( bool default_value = true )
	  {
	  
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_DATA,
				 TraceLevel::DETAIL,
				 "Entering Configuration constructor" );
#endif /* LIBREVERSE_DEBUG */
	  
	    for ( boost::uint32_t i = 0;
		  i < Data_Type::ATTRIBUTE_COUNT;
		  ++i )
	      {
		m_attributes[i] = default_value;
	      }
	  
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_DATA,
				 TraceLevel::DETAIL,
				 "Exiting Configuration constructor" );
#endif /* LIBREVERSE_DEBUG */
	  
	  }

	Configuration ( const Configuration& rhs )
	  : boost::enable_shared_from_this< Configuration<Data_Type> > ( rhs ),
	  m_attributes ( rhs.m_attributes )
	    {
#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_DATA,
				   TraceLevel::DETAIL,
				   "Inside Configuration copy constructor" );
#endif /* LIBREVERSE_DEBUG */
	    }

        
	void set_Attribute ( boost::uint32_t index, bool value )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Entering Configuration::set_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	  if ( index > m_attributes.size() )
	    {
	      throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );
	    }

	  m_attributes[index] = value;


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Exiting Configuration::set_Attribute" );
#endif /* LIBREVERSE_DEBUG */

	}


	bool get_Attribute ( boost::uint32_t index )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Entering Configuration::get_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	  if ( index > m_attributes.size() )
	    {
	      throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );
	    }


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Exiting Configuration::set_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	  return m_attributes[index];
	}


	std::string to_String (void)
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_DATA,
				 TraceLevel::DETAIL,
				 "Entering Configuration::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    std::stringstream output;
	    output << "---- Configuration ----" << std::endl;
	    output << "    ";
	    output << Training_Data<Data_Type>::get_Attribute_String_List ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_DATA,
				 TraceLevel::DETAIL,
				 "Exiting Configuration::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }

        
      private:

	std::string bool_String ( bool value )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_DATA,
				 TraceLevel::DETAIL,
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
	    Trace::write_Trace ( TraceArea::GRNN_DATA,
				 TraceLevel::DETAIL,
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
