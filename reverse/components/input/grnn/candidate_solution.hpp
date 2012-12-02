/*  Candidate_Solution.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_CANDIDATE_SOLUTION_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_CANDIDATE_SOLUTION_HPP_INCLUDED

#include <reverse/components/input/grnn/configuration.hpp>
#include <reverse/components/input/grnn/training_set.hpp>
#include <reverse/trace.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <template <typename data_type> class classifier_type, typename data_type>
	class candidate_solution
	{
	public:

	  candidate_solution ( double sigma = 0.002,
			       double fitness = 0.0,
			       boost::shared_ptr < components::input::grnn::configuration<data_type> > config =
			       boost::make_shared < components::input::grnn::configuration<data_type> > () )
	    : m_sigma ( sigma ),
	      m_fitness ( fitness ),
	      m_mean_distance_squared ( 0.0 ),
	      m_iteration_count ( 0 ),
	      m_config ( config )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution constructor" );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "sigma: %1%" ) % sigma ) );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "fitness: %1%" ) % fitness ) );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Configuration: %1%" ) % config->to_String() ) );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Solution constructor" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  candidate_solution ( const candidate_solution& rhs )
	    : m_sigma ( rhs.m_sigma ),
	      m_fitness ( rhs.m_fitness ),
	      m_mean_distance_squared ( rhs.m_mean_distance_squared ),
	      m_iteration_count ( rhs.m_iteration_count ),
	      m_config ( new components::input::grnn::configuration<data_type>( *rhs.m_config ) )
	  {}


	  void evaluate ( boost::shared_ptr < components::input::grnn::training_set<data_type> > data )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::evaluate" );
#endif /* LIBREVERSE_DEBUG */


	    classifier_type<data_type> classifier_ref ( m_sigma,
							data->get_training_data(),
							m_config );

	    m_fitness = classifier_ref.execute ( data->get_verification_data() );
	    m_mean_distance_squared = classifier_ref.get_mean_distance_squared();


#ifdef LIBREVERSE_DEBGU
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Guess Sigma: %1$1.10f" ) % m_sigma ) );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Guess Fitness: %1$1.10f" ) % m_fitness ) );


	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::evaluate" );
#endif /* LIBREVERSE_DEBUG */

	  }

	  void test ( boost::shared_ptr < components::input::grnn::training_set<data_type> > data )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::test" );
#endif /* LIBREVERSE_DEBUG */


	    classifier_type<data_type> classifier_ref ( m_sigma,
							data->get_training_data(),
							m_config );

	    m_fitness = classifier_ref.execute ( data->get_test_data() );
	    m_mean_distance_squared = classifier_ref.get_mean_distance_squared();
	    m_iteration_count = 0;


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Final Sigma: %1$1.10f" ) % m_sigma ) );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Final Fitness: %1$1.10d" ) % m_fitness ) );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::test" );
#endif /* LIBREVERSE_DEBUG */

	  }


	  void set_sigma ( double new_sigma )
	  {

#ifdef LIBREVERSE_DEBUG       
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::set_Sigma" );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "New Sigma = %1%" ) % new_sigma ) );
#endif /* LIBREVERSE_DEBUG */


	    m_sigma = new_sigma;


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Solution<Classifier_Type, Data_Type>::set_Sigma" );
#endif /* LIBREVERSE_DEBUG */

	  }


	  double get_sigma (void) const
	  {


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Sigma" );
#endif /* LIBREVERSE_DEBUG */


	    return m_sigma;
	  }

        
	  double get_fitness (void) const
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Fitness" );
#endif /* LIBREVERSE_DEBUG */


	    return m_fitness;
	  }


	  double get_mean_distance_squared (void) const
	  {


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Mean_Distance_Squared" );
#endif /* LIBREVERSE_DEBUG */


	    return m_mean_distance_squared;

	  }


	  void set_iteration_count (boost::uint32_t count)
	  {


#ifdef LIBREVERSE_DEBUG       
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::set_Iteration_Count" );

	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "New Iteration Count = %1%" ) % count ) );
#endif /* LIBREVERSE_DEBUG */


	    m_iteration_count = count;


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Solution<Classifier_Type, Data_Type>::set_Iteration_Count" );
#endif /* LIBREVERSE_DEBUG */
	  }


	  boost::uint32_t get_iteration_count (void) const
	  {


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Mean_Distance_Squared" );
#endif /* LIBREVERSE_DEBUG */


	    return m_mean_distance_squared;

	  }


	  boost::shared_ptr < components::input::grnn::configuration<data_type> > get_config (void) const
	  {


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Config" );
#endif /* LIBREVERSE_DEBUG */


	    return m_config;
	  }

        
	  std::string to_string (void)
	  {


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Entering Candidate_Solution<Classifier_Type, Data_Type>::to_String" );
#endif /* LIBREVERSE_DEBUG */

	    std::stringstream output;
       
	    output << "---------------------------------------" << std::endl
		   << "--------- Candidate Solution ----------" << std::endl
		   << "---------------------------------------" << std::endl
		   << boost::format("  Sigma.....%1$1.10f") % m_sigma << std::endl
		   << boost::format("  Fitness:..%1$1.10f") % m_fitness << std::endl
		   << boost::format("  Mean Distance Squared:..%1$1.10f") % m_mean_distance_squared << std::endl
		   << boost::format("  Iteration Count:..%1$1.10f") % m_iteration_count << std::endl
		   << m_config->to_string() << std::endl;


#ifdef LIBREVERSE_DEBUG       
	    Trace::write_Trace ( TraceArea::CANDIDATE_SOLUTION,
				 TraceLevel::DETAIL,
				 "Exiting Candidate_Solution<Classifier_Type, Data_Type>::to_String" );
#endif /* LIBREVERSE_DEBUG */


	    return output.str();
	  }

        
	private:

	  double m_sigma;

	  double m_fitness;

	  double m_mean_distance_squared;

	  boost::uint32_t m_iteration_count;

	  boost::shared_ptr < components::input::grnn::configuration<data_type> > m_config;
	};
    
      } // namespace input
    } // namespace grnn
  } // namespace components
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_GRNN_CANDIDATE_SOLUTION_HPP_INCLUDED
