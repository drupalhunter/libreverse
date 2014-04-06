/*  Statistical.h

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

#ifndef STATISTICAL_H
#define STATISTICAL_H

#include "Training_Set.h"

namespace reverse
{

  namespace classifier
  {
    template <typename Data_Type>
      class Statistical
      {
      public:

	/* This reference to Test_Statistical is only for regression testing */
	friend class Statistical_Test;
    
	Statistical ( double sigma,
		      typename classifier_types::Training_Set<Data_Type>::Data_List_t const& training,
		      typename classifier_types::Configuration<Data_Type>::ptr_t config )
	  : m_sigma ( sigma ),
	  m_mean_distance_squared ( 0.0 ),
	  m_training ( training ),
	  m_config ( config )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering Statistical Constructor" );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Sigma: %1%" ) % m_sigma ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Size of training data: %1%" )
					      % ( m_training.end() - m_training.begin() ) ) );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting Statistical Constructor" );
#endif /* LIBREVERSE_DEBUG */

	    io::Preconditions::is_set ( m_config );
	    io::Preconditions::not_empty ( m_training );
	  }


	/*! \brief Classify the training set
	 * \return classification value representing the optimal sigma
	 */
	double execute ( typename classifier_types::Training_Set<Data_Type>::Data_List_t const& target )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::execute" );
#endif /* LIBREVERSE_DEBUG */


	  double result = 0.0;
	  double success_rate = 0.0;
	  double distance_squared_sum = 0.0;

	  boost::uint32_t correct_classifications = 0;

	  this->calculate_Training_Stats ();

	  // FOR_EACH item, X, in target set
	  //   call approximation_function(X)
	  for ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator target_pos =
		  target.begin();
		target_pos != target.end();
		++target_pos )
	    {
	      result = this->classify ( target_pos );

	      // GENERIC: classifier target from the present Training_Data object pointed to by target_pos
	      double classifier_target = (*target_pos)->get_Attribute ( Data_Type::CLASSIFIER_TARGET );

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "(target set index: %1%) Classifier target: %2%" )
						% ( target_pos - target.begin() )
						% classifier_target ) );

	      Trace::write_Trace ( TraceArea::GRNN,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "Result: %1%" )
						% result ) );
#endif /* LIBREVERSE_DEBUG */

	      if ( fabs ( result - classifier_target ) < 0.5 )
		{
		  ++correct_classifications;
		}

	    }

	  success_rate = ( static_cast<double> ( correct_classifications ) / static_cast<double> ( target.size() ) );

	  m_mean_distance_squared = distance_squared_sum / target.size();

      
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Correct classifications: %1$d" ) % correct_classifications ) );

	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Total classifications: %1$d" ) % target.size() ) );

	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Success rate: %1$1.10f" ) % success_rate ) );

	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Mean distance squared: %1$1.10f" ) % m_mean_distance_squared ) );

	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::execute" );
#endif /* LIBREVERSE_DEBUG */

	  return success_rate;
	}


	/*! \brief Classify the training set
	 * \return classification value representing the Statistical's answer
	 */
	double classify ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator& target_row )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::classify" );
#endif /* LIBREVERSE_DEBUG */

	  bool matched = false;
	  std::vector<double> score_list ( m_column_ub.size() + 1 );

	  for ( boost::uint32_t attribute_index = 1;
		attribute_index < Data_Type::ATTRIBUTE_COUNT;
		++attribute_index )
	    {
	      if ( ! m_config->get_Attribute ( attribute_index ) )
		{
		  continue;
		}

	      for ( boost::uint32_t compiler_index = 0;
		    compiler_index < m_column_ub.size();
		    ++compiler_index )
		{
		  // Get the lower and upper bound associated with the compiler id
		  Double_List_t& lb_ref = this->get_List ( m_column_lb, compiler_index );
		  Double_List_t& ub_ref = this->get_List ( m_column_ub, compiler_index );

		  double value = (*target_row)->get_Attribute ( attribute_index );
#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "(lb=%1$1.10f -> ub=%2$1.10f), value=%3$1.10f" )
						    % lb_ref[attribute_index]
						    % ub_ref[attribute_index]
						    % value ) );
#endif /* LIBREVERSE_DEBUG */

		  if ( ( value >= lb_ref[attribute_index] ) &&
		       ( value <= ub_ref[attribute_index] ) )
		    {
		      score_list[compiler_index] += static_cast<double>(1.0);
		      matched = true;
		    }
		}

	      if ( ! matched )
		{
		  score_list[m_column_ub.size()] += static_cast<double>(1.0);
		}

	      matched = false;
	    }

	  // Find largest value
	  double result = 0.0;
	  double compiler_id = 0.0;
	  for ( std::vector<double>::const_iterator cpos = score_list.begin();
		cpos != score_list.end();
		++cpos )
	    {
#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "score (#%1%) = %2%" )
						% ( cpos - score_list.begin() )
						% (*cpos) ) );
#endif /* LIBREVERSE_DEBUG */

	      if ( (*cpos) > result )
		{
		  result = (*cpos);
		  compiler_id = cpos - score_list.begin();
		}
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Classify result: %1$d" ) % compiler_id ) );

	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::classify" );
#endif /* LIBREVERSE_DEBUG */

	  return compiler_id;
	}


	double get_Mean_Distance_Squared ( void ) const
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Inside Statistical::get_Mean_Distance_Squared" );
#endif /* LIBREVERSE_DEBUG */

	  return m_mean_distance_squared;
	}


      private:

	typedef std::vector<double> Double_List_t;
	typedef std::map < double, Double_List_t > Compiler_Map_t;

	/*!
	 * \brief Compute the training stats
	 */
	void calculate_Training_Stats ( void )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::calculate_Training_Stats" );

	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Size of training data: %1%" ) % m_training.size() ) );
#endif /* LIBREVERSE_DEBUG */

	  this->calculate_Column_Totals();
	  this->calculate_Column_Averages();
	  this->calculate_Column_Variances();
	  this->calculate_Column_Standard_Deviations();
	  this->calculate_Column_Bounds();

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::calculate_Training_Stats" );
#endif /* LIBREVERSE_DEBUG */
	}

	void calculate_Column_Totals ( void )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::calculate_Column_Totals" );
#endif /* LIBREVERSE_DEBUG */

	  // For all rows in training set
	  for ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator training_pos = m_training.begin();
		training_pos != m_training.end();
		++training_pos )
	    {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "Processing #%1%" ) % ( training_pos - m_training.begin() ) ) );
#endif /* LIBREVERSE_DEBUG */

	      // Get current training data pointer from list
	      typename classifier_types::Training_Data<Data_Type>::ptr_t data_ptr = (*training_pos);

	      // Grab the compiler id for the current training data pointer
	      double compiler_id = data_ptr->get_Attribute ( Data_Type::CLASSIFIER_TARGET );

	      // Get the double list associated with the compiler id
	      Double_List_t& total_ref = this->get_List ( m_column_sum, compiler_id );
	      Double_List_t& count_ref = this->get_List ( m_column_count, compiler_id );

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "Attribute count #%1%" ) % Data_Type::ATTRIBUTE_COUNT ) );
#endif /* LIBREVERSE_DEBUG */

	      for ( boost::uint32_t index = 1;
		    index < Data_Type::ATTRIBUTE_COUNT;
		    ++index )
		{


#ifdef LIBREVERSE_DEBUG
		  double previous_total = total_ref[index];
#endif /* LIBREVERSE_DEBUG */


		  // Add attribute to the present attribute total for that column
		  total_ref[index] += data_ptr->get_Attribute ( index );
		  count_ref[index]++;


#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "Total(%1%:%2%) = %3% + %4% = %5%" )
						    % compiler_id
						    % index
						    % previous_total
						    % data_ptr->get_Attribute ( index )
						    % total_ref[index] ) );
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "Count (%1%:%2%) = %3%" )
						    % compiler_id
						    % index
						    % count_ref[index] ) );
#endif /* LIBREVERSE_DEBUG */

		}
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::calculate_Column_Totals" );
#endif /* LIBREVERSE_DEBUG */
	}

	void calculate_Column_Averages ( void )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::calculate_Column_Averages" );
#endif /* LIBREVERSE_DEBUG */

	  // For each compiler
	  //   Calculate the average for each attributes
	  for ( unsigned int compiler_index = 0;
		compiler_index < m_column_sum.size();
		++compiler_index )
	    {
	      Double_List_t& total_ref = this->get_List ( m_column_sum, compiler_index );
	      Double_List_t& count_ref = this->get_List ( m_column_count, compiler_index );
	      Double_List_t& avg_ref = this->get_List ( m_column_avg, compiler_index );

	      for ( boost::uint32_t index = 1;
		    index < Data_Type::ATTRIBUTE_COUNT;
		    ++index )
		{
		  avg_ref[index] = total_ref[index] / count_ref[index];

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "Compiler(%1$d:%2$d): total (%3$1.10f) / count(%4$1.10f) = %5$1.10f" )
						    % compiler_index
						    % index
						    % total_ref[index]
						    % count_ref[index]
						    % avg_ref[index] ) );
#endif /* LIBREVERSE_DEBUG */

		}
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::calculate_Column_Averages" );
#endif /* LIBREVERSE_DEBUG */
	}

	void calculate_Column_Variances ( void )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::calculate_Column_Variances" );
#endif /* LIBREVERSE_DEBUG */

	  // For each training entry
	  //   Calcaluate the Standard Deviation
	  for ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator training_pos = m_training.begin();
		training_pos != m_training.end();
		++training_pos )
	    {
	      // Get current training data pointer from list
	      typename classifier_types::Training_Data<Data_Type>::ptr_t data_ptr = (*training_pos);

	      // Grab the compiler id for the current training data pointer
	      double compiler_id = data_ptr->get_Attribute ( Data_Type::CLASSIFIER_TARGET );

	      // Get the average list associated with the compiler id
	      Double_List_t& avg_ref = this->get_List ( m_column_avg, compiler_id );

	      // Get the variance list associated with the compiler id
	      Double_List_t& var_ref = this->get_List ( m_column_var, compiler_id );

	      for ( boost::uint32_t index = 1;
		    index < Data_Type::ATTRIBUTE_COUNT;
		    ++index )
		{
		  double value = pow ( ( data_ptr->get_Attribute ( index ) - avg_ref[index] ), static_cast<double>(2.0) );

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "(%1$d:%2$d) (%3$1.10f - %4$1.10f)^2 = %5$1.10f" )
						    % compiler_id
						    % index
						    % data_ptr->get_Attribute ( index )
						    % avg_ref[index]
						    % value ) );
#endif /* LIBREVERSE_DEBUG */
	      
		  // Add attribute to the present attribute total for that column
		  var_ref[index] += value;
		}
	    }

	  for ( unsigned int compiler_index = 0;
		compiler_index < m_column_sum.size();
		++compiler_index )
	    {
	      // Get the variance list associated with the compiler id
	      Double_List_t& var_ref = this->get_List ( m_column_var, compiler_index );

	      // Get the count list associated with the compiler id
	      Double_List_t& count_ref = this->get_List ( m_column_count, compiler_index );

	      for ( boost::uint32_t index = 1;
		    index < Data_Type::ATTRIBUTE_COUNT;
		    ++index )
		{
		  double value = var_ref[index] / count_ref[index];


#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "(%1$d:%2$d) %3$1.10f / %4$1.10f = %5$1.10f" )
						    % compiler_index
						    % index
						    % var_ref[index]
						    % count_ref[index]
						    % value ) );
#endif /* LIBREVERSE_DEBUG */


		  var_ref[index] = value;
		}
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::calculate_Column_Variances" );
#endif /* LIBREVERSE_DEBUG */
	}

	void calculate_Column_Standard_Deviations ( void )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::calculate_Column_Standard_Deviations" );
#endif /* LIBREVERSE_DEBUG */

	  // For each compiler
	  //   Calculate the standard deviation
	  for ( unsigned int compiler_index = 0;
		compiler_index < m_column_sum.size();
		++compiler_index )
	    {
	      Double_List_t& var_ref = this->get_List ( m_column_var, compiler_index );

	      Double_List_t& stdev_ref = this->get_List ( m_column_stdev, compiler_index );

	      for ( boost::uint32_t index = 1;
		    index < Data_Type::ATTRIBUTE_COUNT;
		    ++index )
		{
		  stdev_ref[index] = sqrt ( var_ref[index] );

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "stdev(%1$d): sqrt(%2$1.10f) = %3$1.10f" )
						    % index
						    % var_ref[index]
						    % stdev_ref[index] ) );
#endif /* LIBREVERSE_DEBUG */

		}
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::calculate_Column_Standard_Deviations" );
#endif /* LIBREVERSE_DEBUG */
	}


	void calculate_Column_Bounds ( void )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Entering Statistical::calculate_Column_Bounds" );
#endif /* LIBREVERSE_DEBUG */

	  // For each compiler
	  //   Calculate the lower and upper bound
	  for ( unsigned int compiler_index = 0;
		compiler_index < m_column_sum.size();
		++compiler_index )
	    {
	      Double_List_t& lb_ref = this->get_List ( m_column_lb, compiler_index );
	      Double_List_t& ub_ref = this->get_List ( m_column_ub, compiler_index );
	      Double_List_t& avg_ref = this->get_List ( m_column_avg, compiler_index );
	      Double_List_t& stdev_ref = this->get_List ( m_column_stdev, compiler_index );

	      for ( boost::uint32_t index = 1;
		    index < Data_Type::ATTRIBUTE_COUNT;
		    ++index )
		{

		  lb_ref[index] = avg_ref[index] - ( stdev_ref[index] * m_sigma );
		  ub_ref[index] = avg_ref[index] + ( stdev_ref[index] * m_sigma );

#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "lb_ref[%1$d]: %2$1.10f - ( %3$1.10f * %4$1.10f ) = %5$1.10f" )
						    % index
						    % avg_ref[index]
						    % stdev_ref[index]
						    % m_sigma
						    % lb_ref[index] ) );


		  Trace::write_Trace ( TraceArea::GRNN,
				       TraceLevel::DATA,
				       boost::str ( boost::format ( "ub_ref[%1$d]: %2$1.10f + ( %3$1.10f * %4$1.10f ) = %5$1.10f" )
						    % index
						    % avg_ref[index]
						    % stdev_ref[index]
						    % m_sigma
						    % ub_ref[index] ) );
#endif /* LIBREVERSE_DEBUG */

		}
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN,
			       TraceLevel::DETAIL,
			       "Exiting Statistical::calculate_Column_Bounds" );
#endif /* LIBREVERSE_DEBUG */
	}


	/*!
	 * \brief Retrieve the list for a compiler. If it does not exist
	 * then an entry is created.
	 */
	Double_List_t&  get_List ( Compiler_Map_t& map_ref, double compiler_id )
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering Statistical::get_List" );

	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "compiler id: %1%" ) % compiler_id ) );
#endif /* LIBREVERSE_DEBUG */

	    typename Compiler_Map_t::iterator pos = map_ref.find ( compiler_id );
	    if ( pos == map_ref.end() )
	      {

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "No compiler map found for compiler_id=%1%" ) % compiler_id ) );

		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "Size before adding new compiler map: %1%" ) % map_ref.size() ) );
#endif /* LIBREVERSE_DEBUG */

       
		Double_List_t tmp_list ( Data_Type::ATTRIBUTE_COUNT );
		map_ref.insert ( std::make_pair ( compiler_id,
						  tmp_list ) );

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "Size after adding new compiler map: %1%" ) % map_ref.size() ) );
#endif /* LIBREVERSE_DEBUG */

	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting Statistical::get_List" );
#endif /* LIBREVERSE_DEBUG */

	    return map_ref[compiler_id];
	  }


	/*!
	 * \brief Retrieve thecolumn average list for a compiler. If it
	 * does not exist then an entry is created.
	 */
	Double_List_t&  get_Average_List ( double compiler_id )
	  {
#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Entering Statistical::get_Average_List" );
#endif /* LIBREVERSE_DEBUG */

	    typename Compiler_Map_t::iterator pos = m_column_avg.find ( compiler_id );
	    if ( pos == m_column_avg.end() )
	      {
		Double_List_t tmp_list ( Data_Type::ATTRIBUTE_COUNT );
		m_column_avg.insert ( std::make_pair ( compiler_id,
						       tmp_list ) );	  
	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN,
				 TraceLevel::DETAIL,
				 "Exiting Statistical::get_Average_List" );
#endif /* LIBREVERSE_DEBUG */

	    return m_column_avg[compiler_id];

	  }


	double m_sigma;
      
	double m_mean_distance_squared;

	typename classifier_types::Training_Set<Data_Type>::Data_List_t const& m_training;

	typename classifier_types::Configuration<Data_Type>::ptr_t m_config;

	/*!
	 * \brief Map that keeps a total of each of the attributes for a particular compiler
	 */
	Compiler_Map_t m_column_sum;

	/*!
	 * \brief Map that keeps a count of the number of files for a particular compiler
	 */
	Compiler_Map_t m_column_count;

	/*!
	 * \brief Map that keeps the attribute averages for each compiler
	 */
	Compiler_Map_t m_column_avg;

	/*!
	 * \brief Map that keeps the variance of each attribute for each compiler
	 */
	Compiler_Map_t m_column_var;

	/*!
	 * \brief Map that keeps the standard deviation for each compiler attribute
	 */
	Compiler_Map_t m_column_stdev;

	/*!
	 * \brief Maps that keep the upper and lower bounds for each compiler attribute
	 */
	Compiler_Map_t m_column_lb;
	Compiler_Map_t m_column_ub;

      };
  
  } /* namespace classifier */
} /* namespace reverse */

#endif /* STATISTICAL_H */
