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

#include "Training_Data.h"

#include <boost/format.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <typename Data_Type>
	class Training_Set
	{
	public:

	  void append ( boost::shared_ptr<reverse::components::input::grnn::Training_Set<Data_Type> >& data )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::append" );
#endif /* LIBREVERSE_DEBUG */


	    m_data.insert ( m_data.end(), data->data_Begin(), data->data_End() );
	    m_test.insert ( m_test.end(), data->test_Begin(), data->test_End() );
	    m_verification.insert ( m_verification.end(), data->verification_Begin(), data->verification_End() );


#ifdef LIBREVERSE_DEBUG       
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::append" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  std::vector < boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > const&
	    get_Training_Data ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Inside Training_Set<Data_Type>::get_Training_Data" );
#endif /* LIBREVERSE_DEBUG */

       
	    return m_data;
	  }


	  std::vector < boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > const&
	    get_Test_Data ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Inside Training_Set<Data_Type>::get_Test_Data" );
#endif /* LIBREVERSE_DEBUG */


	    return m_test;
	  }


	  std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > const&
	    get_Verification_Data ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Inside Training_Set<Data_Type>::get_Verification_Data" );
#endif /* LIBREVERSE_DEBUG */

       
	    return m_verification;
	  }


	  typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator data_Begin() const
	  {
	    return m_data.begin();
	  }

	  typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator data_End() const
	  {
	    return m_data.end();
	  }

	  inline void data_Push_Back ( boost::shared_ptr < reverse::components::input::grnn::Training_Data<Data_Type> >& data_ptr )
	  {
	    return m_data.push_back ( data_ptr );
	  }

	  void data_Insert ( std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > const& source_data )
	  {
	    return m_data.insert ( m_data.end(), source_data.begin(), source_data.end() );
	  }

	  typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator test_Begin() const
	  {
	    return m_test.begin();
	  }

	  typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator test_End() const
	  {
	    return m_test.end();
	  }
      
	  inline void test_Push_Back ( boost::shared_ptr < reverse::components::input::grnn::Training_Data<Data_Type> > const& data_ptr )
	  {
	    return m_test.push_back ( data_ptr );
	  }

	  typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator verification_Begin() const
	  {
	    return m_verification.begin();
	  }

	  typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator verification_End() const
	  {
	    return m_verification.end();
	  }

	  inline void verification_Push_Back ( boost::shared_ptr < reverse::components::input::grnn::Training_Data<Data_Type> > const& data_ptr )
	  {
	    return m_verification.push_back ( data_ptr );
	  }

	  std::string to_String ( boost::shared_ptr < reverse::components::input::grnn::Configuration<Data_Type> > config =
				  boost::shared_ptr < reverse::components::input::grnn::Configuration<Data_Type> >
				  ( new reverse::components::input::grnn::Configuration<Data_Type>() ) ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    std::stringstream output;

	    output << std::endl
		   << this->print_Maximum_Values () << std::endl
		   << this->print_Data ( m_data, config, "Data" ) << std::endl
		   << this->print_Data ( m_test, config, "Test" ) << std::endl
		   << this->print_Data ( m_verification, config, "Verification" ) << std::endl;


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::to_String" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  bool is_Valid ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::is_Valid" );
#endif /* LIBREVERSE_DEBUG */

       
	    bool valid = this->is_Valid_Impl ( m_data, "Training data" );
	    valid = this->is_Valid_Impl ( m_test, "Test data" );
	    valid = this->is_Valid_Impl ( m_verification, "Verification data" );
       
	    return valid;
	  }


	  void set_Attribute_Maximum ( boost::uint32_t key, double value )
	  {
	    m_max_values.insert ( std::make_pair ( key, value ) );
	  }

	  double get_Attribute_Maximum ( boost::uint32_t key ) const
	  {
	    typename std::map < boost::uint32_t, double>::const_iterator pos = m_max_values.find ( key );

	    if ( pos == m_max_values.end() )
	      {
		throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );	  
	      }

	    return (*pos).second;
	  }

	  std::string get_Attribute_Maximum_XML ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
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
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::get_Attribute_Maximum_XML" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  std::string print_Maximum_Values ( void ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::print_Maximum_Values" );
#endif /* LIBREVERSE_DEBUG */

       
	    std::stringstream output;

	    output << boost::format("------ Maximum Values (count = %1$d)-----") % m_max_values.size() << std::endl
		   << "-----------------" << std::endl;
        
	    for ( typename std::map < boost::uint32_t, double>::const_iterator cpos = m_max_values.begin();
		  cpos != m_max_values.end();
		  ++cpos )
	      {
		output << boost::format ( " %1$d: %2$1.10f" ) % ( *cpos ).first % ( *cpos ).second << std::endl;
	      }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::print_Maximum_Values" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  inline void max_Values_Insert ( std::map < boost::uint32_t, double> const& source_values )
	  {
	    return m_max_values.insert ( source_values.begin(), source_values.end() );
	  }

	private:

	  std::string print_Data ( std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > const& data,
				   boost::shared_ptr < reverse::components::input::grnn::Configuration<Data_Type> > const& config,
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
        
	    for ( typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator cpos = data.begin();
		  cpos != data.end();
		  ++cpos )
	      {
		output << ( *cpos )->to_String ( config ) << std::endl;
	      }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::print_Data" );
#endif /* LIBREVERSE_DEBUG */

        
	    return output.str();
	  }


	  bool is_Valid_Impl ( std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > const& data,
			       std::string type ) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Entering Training_Set<Data_Type>::is_Valid_Impl" );
#endif /* LIBREVERSE_DEBUG */


	    bool valid = true;

	    for ( typename std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > >::const_iterator cpos = data.begin();
		  cpos != data.end();
		  ++cpos )
	      {
		if ( ! ( *cpos )->is_Valid () )
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

          
		throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_DATA_SET );
	      }


#ifdef LIBREVERSE_DEBUG       
	    Trace::write_Trace ( TraceArea::CLASSIFIER,
				 TraceLevel::DETAIL,
				 "Exiting Training_Set<Data_Type>::is_Valid_Impl" );
#endif /* LIBREVERSE_DEBUG */

       
	    return valid;
	  }

	  std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > m_data;
	  std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > m_test;
	  std::vector< boost::shared_ptr < reverse::components::input::grnn::Training_Set<Data_Type> > > m_verification;
	  std::map < boost::uint32_t, double > m_max_values;

	};

      } // namespace input
    } // namespace grnn
  } // namespace classifier
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_SET_HPP_INCLUDED
