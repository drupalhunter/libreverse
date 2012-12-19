/*  Training_Set.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_SET_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_SET_HPP_INCLUDED

#include <reverse/components/input/grnn/training_data.hpp>
#include <reverse/errors/internal_exception.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <typename data_type>
	class training_set
	{
	public:

	  typedef std::vector< boost::shared_ptr < training_data<data_type> > > data_list_t;

	  training_set ()
	  {}

	  training_set ( training_set const& rhs )
	    : m_data ( rhs.m_data ),
	      m_test ( rhs.m_test ),
	      m_verification ( rhs.m_verification ),
	      m_max_values ( rhs.m_max_values )
	  {}

	  void swap ( training_set& rhs )
	  {
	    m_data.swap ( rhs.m_data );
	    m_test.swap ( rhs.m_test );
	    m_verification ( rhs.m_verification );
	    m_max_values ( rhs.m_max_values );
	  }


	  void append ( boost::shared_ptr<reverse::components::input::grnn::training_set<data_type> >& data )
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Set<Data_Type>::append" );
#endif /* LIBREVERSE_DEBUG */


	    m_data.insert ( m_data.end(), data->data_begin(), data->data_end() );
	    m_test.insert ( m_test.end(), data->test_begin(), data->test_end() );
	    m_verification.insert ( m_verification.end(), data->verification_begin(), data->verification_end() );


#ifdef LIBREVERSE_DEBUG       
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Set<Data_Type>::append" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  data_list_t const& get_training_data ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Set<Data_Type>::get_Training_Data" );
#endif /* LIBREVERSE_DEBUG */

       
	    return m_data;
	  }


	  data_list_t const& get_test_data ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Set<Data_Type>::get_Test_Data" );
#endif /* LIBREVERSE_DEBUG */


	    return m_test;
	  }

	  data_list_t const& get_verification_data ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Inside Training_Set<Data_Type>::get_Verification_Data" );
#endif /* LIBREVERSE_DEBUG */

	    return m_verification;
	  }


	  typename data_list_t::const_iterator data_begin() const
	  {
	    return m_data.begin();
	  }

	  typename data_list_t::const_iterator data_end() const
	  {
	    return m_data.end();
	  }

	  inline void data_push_back ( boost::shared_ptr < reverse::components::input::grnn::training_data<data_type> >& data_ptr )
	  {
	    m_data.push_back ( data_ptr );
	  }

	  void data_insert ( boost::shared_ptr < reverse::components::input::grnn::training_set<data_type> > source_data )
	  {
	    return m_data.insert ( m_data.end(), source_data->data_begin(), source_data->data_end() );
	  }

	  typename data_list_t::const_iterator test_begin() const
	  {
	    return m_test.begin();
	  }

	  typename data_list_t::const_iterator test_end() const
	  {
	    return m_test.end();
	  }
      
	  inline void test_push_back ( boost::shared_ptr < reverse::components::input::grnn::training_data<data_type> > data_ptr )
	  {
	    return m_test.push_back ( data_ptr );
	  }

	  typename data_list_t::const_iterator verification_begin() const
	  {
	    return m_verification.begin();
	  }

	  typename data_list_t::const_iterator verification_end() const
	  {
	    return m_verification.end();
	  }

	  inline void verification_push_back ( boost::shared_ptr < reverse::components::input::grnn::training_data<data_type> > const& data_ptr )
	  {
	    return m_verification.push_back ( data_ptr );
	  }

	  std::string to_string ( boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> > config =
				  boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> >
				  ( new reverse::components::input::grnn::configuration<data_type>() ) ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Set<Data_Type>::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream output;

	    output << std::endl
		   << this->print_maximum_values () << std::endl
		   << this->print_data ( m_data, config, "data" ) << std::endl
		   << this->print_data ( m_test, config, "test" ) << std::endl
		   << this->print_data ( m_verification, config, "verification" ) << std::endl;


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Set<Data_Type>::to_String" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  bool is_valid ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Set<Data_Type>::is_Valid" );
#endif /* LIBREVERSE_DEBUG */

	    bool valid = this->is_valid_impl ( m_data, "training data" );
	    valid = this->is_valid_impl ( m_test, "test data" );
	    valid = this->is_valid_impl ( m_verification, "verification data" );
       
	    return valid;
	  }

	  void set_attribute_maximum ( boost::uint32_t key, double value )
	  {
	    m_max_values.insert ( std::make_pair ( key, value ) );
	  }

	  double get_attribute_maximum ( boost::uint32_t key ) const
	  {
	    typename std::map < boost::uint32_t, double>::const_iterator pos = m_max_values.find ( key );

	    if ( pos == m_max_values.end() )
	      {
		throw errors::internal_exception ( errors::internal_exception::invalid_index );	  
	      }

	    return (*pos).second;
	  }

	  std::string get_attribute_maximum_xml ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Set<Data_Type>::get_Attribute_Maximum_XML" );
#endif /* LIBREVERSE_DEBUG */
       
	    std::stringstream output;

	    if ( ! m_max_values.empty() )
	      {
		output << "  <maximum>" << std::endl;
        
		for ( typename std::map < boost::uint32_t, double>::const_iterator cpos = m_max_values.begin();
		      cpos != m_max_values.end();
		      ++cpos )
		  {
		    output << boost::format ( "    <value key=\"%1$d\" float=\"%2$1.10f\"/>" ) % ( *cpos ).first % ( *cpos ).second << std::endl;
		  }

		output << "  </maximum>" << std::endl;
	      }


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Set<Data_Type>::get_Attribute_Maximum_XML" );
#endif /* LIBREVERSE_DEBUG */

	    return output.str();
	  }

	  std::string print_maximum_values ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Entering Training_Set<Data_Type>::print_Maximum_Values" );
#endif /* LIBREVERSE_DEBUG */

       
	    std::stringstream output;

	    output << boost::format("------ maximum values (count = %1$d)-----") % m_max_values.size() << std::endl
		   << "-----------------" << std::endl;
        
	    for ( typename std::map < boost::uint32_t, double>::const_iterator cpos = m_max_values.begin();
		  cpos != m_max_values.end();
		  ++cpos )
	      {
		output << boost::format ( " %1$d: %2$1.10f" ) % ( *cpos ).first % ( *cpos ).second << std::endl;
	      }


#ifdef LIBREVERSE_DEBUG
	    trace::write_trace ( trace_area::classifier,
				 trace_level::detail,
				 "Exiting Training_Set<Data_Type>::print_Maximum_Values" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  inline void max_values_insert ( std::map < boost::uint32_t, double> const& source_values )
	  {
	    return m_max_values.insert ( source_values.begin(), source_values.end() );
	  }

	  void clear ()
	  {
	    m_data.clear();
	    m_test.clear();
	    m_verification.clear();
	    m_max_values.clear();
	  }


	private:

	  std::string print_data ( std::vector< boost::shared_ptr < reverse::components::input::grnn::training_set<data_type> > > const& data,
				   boost::shared_ptr < reverse::components::input::grnn::configuration<data_type> > const& config,
				   std::string prefix ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::print_Data" );
#endif /* LIBREVERSE_DEBUG */

       
	    std::stringstream output;

	    output << boost::format("------ %1$s (count = %2$d)-----") % prefix % data.size() << std::endl
		   << "-----------------" << std::endl;
        
	    for ( typename std::vector< boost::shared_ptr < reverse::components::input::grnn::training_set<data_type> > >::const_iterator cpos = data.begin();
		  cpos != data.end();
		  ++cpos )
	      {
		output << ( *cpos )->to_string ( config ) << std::endl;
	      }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::print_Data" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  bool is_valid_impl ( data_list_t const& data,
			       std::string type ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::is_Valid_Impl" );
#endif /* LIBREVERSE_DEBUG */


	    bool valid = true;

	    for ( typename data_list_t::const_iterator cpos = data.begin();
		  cpos != data.end();
		  ++cpos )
	      {
		if ( ! ( *cpos )->is_valid () )
		  {

#ifdef LIBREVERSE_DEBUG
		    Trace::write_Trace ( TraceArea::CLASSIFIER,
					 TraceLevel::ERROR,
					 boost::str ( boost::format ( "(%1$s) Training Data #%2$d is not valid" )
						      % type
						      % ( cpos - data.begin() ) ) );
#endif /* LIBREVERSE_DEBUG */


		    valid = false;


#ifdef LIBREVERSE_DEBUG
		    Trace::write_Trace ( TraceArea::CLASSIFIER,
					 TraceLevel::ERROR,
					 (*cpos)->to_String () );
#endif /* LIBREVERSE_DEBUG */


		    break;
		  }
	      }


	    if ( valid )
	      {


#ifdef LIBREVERSE_DEBUG       
		Trace::write_Trace ( TraceArea::CLASSIFIER,
				     TraceLevel::DETAIL,
				     "Training Data is valid" );

#endif /* LIBREVERSE_DEBUG */

	      }
	    else
	      {

#ifdef LIBREVERSE_DEBUG       
		Trace::write_Trace ( TraceArea::CLASSIFIER,
				     TraceLevel::ERROR,
				     "Training Data is NOT valid" );
#endif /* LIBREVERSE_DEBUG */

          
		throw errors::internal_exception ( errors::internal_exception::invalid_data_set );
	      }


#ifdef LIBREVERSE_DEBUG       
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::is_Valid_Impl" );
#endif /* LIBREVERSE_DEBUG */

       
	    return valid;
	  }

	  data_list_t m_data;
	  data_list_t m_test;
	  data_list_t m_verification;
	  std::map < boost::uint32_t, double > m_max_values;

	};

      } // namespace input
    } // namespace grnn
  } // namespace classifier
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_SET_HPP_INCLUDED
