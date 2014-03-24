/*  Data_Source_T.h

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

#ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_HPP_INCLUDED

#include <reverse/infrastructure/data_source/data_source_base.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>
#include <reverse/data_containers/data_types.hpp>
#include <reverse/data_containers/filename.hpp>
#include <reverse/errors/component_exception.hpp>
#include <reverse/infrastructure/component_types.hpp>
#include <reverse/infrastructure/data_source/data_object.hpp>

#include <boost/format.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/smart_ptr/make_shared.hpp>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

    template <typename transfer_type>
    class data_source : public data_source_base,
			public boost::enable_shared_from_this< data_source < transfer_type > >
    {
    public:
      
        explicit data_source ( typename boost::shared_ptr<transfer_type> rhs )
	  : m_data_ptr ( new data_object() ),
          m_transfer_method ( new transfer_type ( *rhs ) )
	    {

#ifdef LIBREVERSE_DEBUG
	      trace::write_trace ( tracearea::infrastructure,
				   tracelevel::detail,
				   "Entering Data_Source constructor" );
#endif /* LIBREVERSE_DEBUG */


	      // open Transfer_Type
	      m_transfer_method->open();


#ifdef LIBREVERSE_DEBUG
	      trace::write_trace ( tracearea::infrastructure,
				   tracelevel::detail,
				   "Exiting Data_Source constructor" );
#endif /* LIBREVERSE_DEBUG */


	    }


        data_source ( data_source const& rhs )
	  : data_source_base ( rhs ),
          boost::enable_shared_from_this < data_source < transfer_type> > ( rhs ),
          m_data_ptr ( new data_object ( *rhs.m_data_ptr ) )
	    {

#ifdef LIBREVERSE_DEBUG
	      trace::write_trace ( tracearea::infrastructure,
				   tracelevel::detail,
				   "Inside Data_Source copy constructor" );
#endif /* LIBREVERSE_DEBUG */

	    }

        virtual ~data_source ()
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

      void put ( boost::shared_ptr < const infrastructure::data_source::data_object>& data )
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


       boost::shared_ptr < const infrastructure::data_source::data_object> get (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( tracearea::infrastructure,
				 tracelevel::detail,
				 "Inside Data_Source::get" );
#endif /* LIBREVERSE_DEBUG */

	    // Get data from Transfer_Type and Put data into Data_Type
	    return m_transfer_method->get();
	  }

        virtual std::string to_string (void) const
	{

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( tracearea::infrastructure,
			       tracelevel::detail,
			       "Entering Data_Source::to_String" );
#endif /* LIBREVERSE_DEBUG */


	  std::stringstream output;


	  boost::shared_ptr < const infrastructure::data_source::data_object > data_ptr = this->get();

	  if ( data_ptr.get() != 0 )
            {
	      meta::meta_object::const_ptr_t meta_ptr = data_ptr->getmeta();

	      output << "data source: " << std::endl
		     << "  - data - " << std::endl
		     << data_ptr->to_string() << std::endl
		     << std::endl
		     << "  - meta - " << std::endl
		     << meta_ptr->to_string() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			       TraceLevel::DETAIL,
			       "Exiting Data_Source::toString" );
#endif /* LIBREVERSE_DEBUG */


	  return output.str();
	}

        virtual boost::shared_ptr <infrastructure::data_source::data_object > get_deep_copy ( void )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			       TraceLevel::DETAIL,
			       "Inside Data_Source::get_Deep_Copy" );
#endif /* LIBREVERSE_DEBUG */

	  return boost::make_shared < infrastructure::data_source::data_object > (*this->m_data_ptr);
	}

        data_source& operator= ( data_source const& rhs )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				 TraceLevel::DETAIL,
				 "Entering Data_Source::operator=" );
#endif /* LIBREVERSE_DEBUG */


	    data_source temp ( rhs );
	    swap ( temp );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				 TraceLevel::DETAIL,
				 "Exiting Data_Source::operator=" );
#endif /* LIBREVERSE_DEBUG */

	    return *this;
	  }
            
        void swap ( data_source& rhs )
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

      private:

        /**
         * Fields
         */
        boost::shared_ptr <infrastructure::data_source::data_object> m_data_ptr;

        typename boost::shared_ptr<transfer_type> m_transfer_method;
      };

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_HPP_INCLUDED

