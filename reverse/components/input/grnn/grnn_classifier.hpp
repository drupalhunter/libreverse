/*  GRNN.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_GRNN_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_GRNN_HPP_INCLUDED

#include <reverse/components/input/grnn/training_set.hpp>
#include <reverse/preconditions.hpp>

#include <math.h>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <typename data_type>
	class grnn_classifier
	{
	public:
	  
	  grnn_classifier ( double sigma,
			    typename training_set< data_type >::data_list_t const& training,
			    boost::shared_ptr < configuration<data_type> > config )
	    : m_sigma ( sigma ),
	      m_mean_distance_squared ( 0.0 ),
	      m_training ( training ),
	      m_config ( config )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering GRNN Constructor" );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Sigma: %1%" ) % m_sigma ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Size of training data: %1%" )
					      % ( training.end() - training.begin() ) ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting GRNN Constructor" );
#endif /* LIBREVERSE_DEBUG */
	  }


	  /*! \brief Classify the training set
	   * \return classification value representing the optimal sigma
	   */
	  double execute ( typename training_set<data_type>::data_list_t const& validation_list )
	  {

	    
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering GRNN::execute" );
      
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Size of validation list: %1%" )
					      % ( validation_list.end() - validation_list.begin() ) ) );

#endif /* LIBREVERSE_DEBUG */


	    double success_rate = 0.0;
	    double distance_squared_sum = 0.0;
	    double result = 0.0;
	    boost::uint32_t correct_classifications = 0;

	    // FOR_EACH item, X, in target set
	    //   call approximation_function(X)
	    for ( typename training_set<data_type>::data_list_t::const_iterator target_pos = validation_list.begin();
		  target_pos != validation_list.end();
		  ++target_pos )
	      {
		result = this->classify ( target_pos );

		// GENERIC: classifier target from the present Training_Data object pointed to by target_pos
		double classifier_target = ( *target_pos )->get_attribute ( data_type::classifier_target );


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "(target set index: %1%) Classifier target: %2%" )
						  % ( target_pos - validation_list.begin() )
						  % classifier_target ) );

		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "Result: %1%" )
						  % result ) );
#endif /* LIBREVERSE_DEBUG */


		// Calculate distance squared
		distance_squared_sum += pow ( ( classifier_target - result ), 2.0 );

		/*
		  std::cout << boost::format ( "%1%,%2%" )
		  % classifier_target
		  % result
		  << std::endl;
		*/

		// Use classifier target
		if ( fabs ( result - classifier_target ) < 0.5 )
		  {
		    ++correct_classifications;
		  }
	      }

	    success_rate = ( static_cast<double> ( correct_classifications ) / static_cast<double> ( validation_list.size() ) );

	    m_mean_distance_squared = distance_squared_sum / validation_list.size();

      
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Correct classifications: %1$d" ) % correct_classifications ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Total classifications: %1$d" ) % validation_list.size() ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Success rate: %1$1.10f" ) % success_rate ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Mean distance squared: %1$1.10f" ) % m_mean_distance_squared ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting GRNN::execute" );
#endif /* LIBREVERSE_DEBUG */

	    return success_rate;
	  }

	  /*! \brief Classify the training set
	   * \return classification value representing the GRNN's answer
	   */
	  double classify ( typename training_set<data_type>::data_list_t::const_iterator target_row )
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering GRNN::classify" );
#endif /* LIBREVERSE_DEBUG */


	    preconditions::not_empty ( m_training );

	    double result = 0.0;

	    result = this->approximation_function ( target_row );


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Result: %1$d" ) % result ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting GRNN::classify" );
#endif /* LIBREVERSE_DEBUG */

	    return result;
	  }

	  double get_mean_distance_squared ( void ) const
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Inside GRNN::get_Mean_Distance_Squared" );
#endif /* LIBREVERSE_DEBUG */

	    return m_mean_distance_squared;
	  }


	private:

	  /*!
	   * \brief Compute the approximation function value from the target row
	   * \param target_row Row of target data
	   * \return approximation function value
	   * \pre Target row is not empty
	   */
	  double approximation_function ( typename training_set<data_type>::data_list_t::const_iterator target_row )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering GRNN::approximation_function" );
#endif /* LIBREVERSE_DEBUG */


	    double weighted_sum_hfs = 0.0; // weighted sum of the results of the hiddenFunction based on desired output
	    double sum_hfs = 0.0; // sum of the hiddenFunction results


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Size of training data: %1%" ) % m_training.size() ) );
#endif /* LIBREVERSE_DEBUG */


	    // For all rows in training set
	    for ( typename training_set<data_type>::data_list_t::const_iterator training_pos = m_training.begin();
		  training_pos != m_training.end();
		  ++training_pos )
	      {
		// X = row in target data
		// t[i] = training data
 
		double hf = hidden_function ( target_row, training_pos );


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "(%1%) Hidden function: %2%" )
						  % ( training_pos - m_training.begin() )
						  % hf ) );
#endif /* LIBREVERSE_DEBUG */


		// GENERIC: Grab classifier target (e.g. Compiler ID for compiler classification)
		double classifier_target = ( *training_pos )->get_attribute ( data_type::classifier_target );


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "(%1%) Classifier target: %2%" )
						  % ( training_pos - m_training.begin() )
						  % classifier_target ) );
#endif /* LIBREVERSE_DEBUG */


		weighted_sum_hfs += hf * classifier_target;


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "(%1%) Weighted Sum Hidden function total: %2%" )
						  % ( training_pos - m_training.begin() )
						  % weighted_sum_hfs ) );
#endif /* LIBREVERSE_DEBUG */


		sum_hfs += hf;


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "(%1%) Sum Hidden function total: %2%" )
						  % ( training_pos - m_training.begin() )
						  % sum_hfs ) );
#endif /* LIBREVERSE_DEBUG */

	      }

	    double result = 0.0;

	    if ( sum_hfs != 0.0 )
	      {
		result = weighted_sum_hfs / sum_hfs;
	      }


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Result: %1$1.10d" ) % result ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting GRNN::approximation_function" );
#endif /* LIBREVERSE_DEBUG */

	    return result;
	  }

	  /*!
	   * \brief Compute the hidden function value from the two input rows
	   * \param target_row Row of target data
	   * \param training_row Row of training data
	   * \return hidden function value
	   * \pre Stored sigma is not zero
	   * \pre Target row is not empty
	   * \pre Training row is not empty
	   */
	  double hidden_function ( typename training_set<data_type>::data_list_t::const_iterator target_row ,
				   typename training_set<data_type>::data_list_t::const_iterator training_row )
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering GRNN::hiddenFunction" );
#endif /* LIBREVERSE_DEBUG */

	    preconditions::not_equal ( m_sigma, static_cast<double>(0.0) );

	    double distance_squared_value = this->distance_squared ( target_row, training_row );

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Distanced squared: %1$f" ) % distance_squared_value ) );
#endif /* LIBREVERSE_DEBUG */

	    double denominator = 2 * pow ( m_sigma, 2.0 );

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Sigma: %1$1.10f" ) % m_sigma ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Power: %1$1.10f" ) % ( pow ( m_sigma, 2.0 ) ) ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Denominator: %1$1.10f" ) % denominator ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Fraction: %1$1.10f" ) % ( ( -1 * ( distance_squared_value ) ) / denominator ) ) );
#endif /* LIBREVERSE_DEBUG */

	    double result = exp ( ( -1 * ( distance_squared_value ) ) / denominator );

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Result: %1$1.10f" ) % result ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting GRNN::hiddenFunction" );
#endif /* LIBREVERSE_DEBUG */

	    return result;
	  }

	  /*!
	   * \brief Compute the sum distance squared value from the two input rows
	   * \param target_row Row of target data
	   * \param training_row Row of training data
	   * \return sum distance squared value
	   * \pre Target row is not empty
	   * \pre Training row is not empty
	   */
	  double distance_squared ( typename training_set<data_type>::data_list_t::const_iterator target_row ,
				    typename training_set<data_type>::data_list_t::const_iterator training_row )
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering GRNN::distance_squared" );
#endif /* LIBREVERSE_DEBUG */


	    preconditions::is_set ( (*training_row) );
	    preconditions::not_equal ( (*training_row)->empty(), true );
	    preconditions::is_set ( (*target_row) );
	    preconditions::not_equal ( (*target_row)->empty(), true );

	    double distance_squared_value = 0.0;

	    typename boost::shared_ptr < training_data<data_type> > training_map = *training_row;
	    typename boost::shared_ptr < training_data<data_type> > target_map = *target_row;

	    // For all attributes in row
	    for ( boost::uint32_t index = 1;
		  index < data_type::attribute_count;
		  ++index )
	      {
		double target_value = 0.0;
		double training_value = 0.0;

		if ( m_config->get_attribute ( index ) )
		  {
		    target_value = target_map->get_attribute ( index );
		    training_value = training_map->get_attribute ( index );
		  }
		else
		  {
		    continue;
		  }

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "%1$d: target_value = %2$1.10f " )
						  % index
						  % target_value ) );

		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "%1$d: training_value = %2$1.10f " )
						  % index
						  % training_value ) );
#endif /* LIBREVERSE_DEBUG */

		double next_distance_squared = pow ( ( target_value - training_value ), 2.0 );

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "%1$d: next distance squared = %2$1.10f " )
						  % index
						  % next_distance_squared ) );
#endif /* LIBREVERSE_DEBUG */
	  
		distance_squared_value += next_distance_squared;

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "Sum distance squared = %1$1.10f " )
						  % distance_squared_value ) );
#endif /* LIBREVERSE_DEBUG */

	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting GRNN::distance_squared" );
#endif /* LIBREVERSE_DEBUG */

	    return distance_squared_value;
	  }

	  double m_sigma;

	  double m_mean_distance_squared;

	  typename training_set< data_type >::data_list_t const& m_training;

	  boost::shared_ptr < configuration<data_type> > m_config;

	};
  
      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_GRNN_HPP_INCLUDED
