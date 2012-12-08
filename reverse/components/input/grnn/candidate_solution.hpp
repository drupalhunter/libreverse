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
	    trace::candidate_solution_detail ( "Entering Candidate_Solution constructor" );
	    trace::candidate_solution_data ( "sigma: %1%", sigma );
	    trace::candidate_solution_data ( "fitness: %1%", fitness );
	    trace::candidate_solution_data ( "Configuration: %1%", config->to_String() );
	    trace::candidate_solution_detail ( "Exiting Candidate_Solution constructor" );
	  }

	  candidate_solution ( const candidate_solution& rhs )
	    : m_sigma ( rhs.m_sigma ),
	      m_fitness ( rhs.m_fitness ),
	      m_mean_distance_squared ( rhs.m_mean_distance_squared ),
	      m_iteration_count ( rhs.m_iteration_count ),
	      m_config ( new components::input::grnn::configuration<data_type>( *rhs.m_config ) )
	  {
	    trace::candidate_solution_detail ( "Inside candidate solution copy constructor" );
	  }


	  void evaluate ( boost::shared_ptr < components::input::grnn::training_set<data_type> > data )
	  {
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::evaluate" );

	    classifier_type<data_type> classifier_ref ( m_sigma,
							data->get_training_data(),
							m_config );

	    m_fitness = classifier_ref.execute ( data->get_verification_data() );
	    m_mean_distance_squared = classifier_ref.get_mean_distance_squared();
	    
	    trace::candidate_solution_data ( "Guess Sigma: %1$1.10f", % m_sigma );
	    trace::candidate_solution_data ( "Guess Fitness: %1$1.10f", % m_fitness );
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::evaluate" );
	  }

	  void test ( boost::shared_ptr < components::input::grnn::training_set<data_type> > data )
	  {
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::test" );

	    classifier_type<data_type> classifier_ref ( m_sigma,
							data->get_training_data(),
							m_config );

	    m_fitness = classifier_ref.execute ( data->get_test_data() );
	    m_mean_distance_squared = classifier_ref.get_mean_distance_squared();
	    m_iteration_count = 0;

	    trace::candidate_solution_data ( "Final Sigma: %1$1.10f", m_sigma );
	    trace::candidate_solution_data ( "Final Fitness: %1$1.10d", m_fitness );
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::test" );
	  }

	  void set_sigma ( double new_sigma )
	  {
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::set_Sigma" );
	    trace::candidate_solution_data ( "New Sigma = %1%", new_sigma );

	    m_sigma = new_sigma;

	    trace::candidate_solution_detail ( "Exiting Candidate_Solution<Classifier_Type, Data_Type>::set_Sigma" );
	  }

	  double get_sigma (void) const
	  {

	    trace::candidate_solution_detail ( "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Sigma" );

	    return m_sigma;
	  }

        
	  double get_fitness (void) const
	  {
	    trace::candidate_solution_detail ( "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Fitness" );

	    return m_fitness;
	  }


	  double get_mean_distance_squared (void) const
	  {
	    trace::candidate_solution_detail ( "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Mean_Distance_Squared" );

	    return m_mean_distance_squared;
	  }

	  void set_iteration_count (boost::uint32_t count)
	  {
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::set_Iteration_Count" );
	    trace::candidate_solution_data ( "New Iteration Count = %1%", count );

	    m_iteration_count = count;

	    trace::candidate_solution_detail ( "Exiting Candidate_Solution<Classifier_Type, Data_Type>::set_Iteration_Count" );
	  }

	  boost::uint32_t get_iteration_count (void) const
	  {
	    trace::candidate_solution_detail ( "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Mean_Distance_Squared" );

	    return m_mean_distance_squared;
	  }


	  boost::shared_ptr < components::input::grnn::configuration<data_type> > get_config (void) const
	  {
	    trace::candidate_solution_detail ( "Inside Candidate_Solution<Classifier_Type, Data_Type>::get_Config" );

	    return m_config;
	  }

        
	  std::string to_string (void)
	  {
	    trace::candidate_solution_detail ( "Entering Candidate_Solution<Classifier_Type, Data_Type>::to_String" );

	    std::stringstream output;
       
	    output << "---------------------------------------" << std::endl
		   << "--------- Candidate Solution ----------" << std::endl
		   << "---------------------------------------" << std::endl
		   << boost::format("  Sigma.....%1$1.10f") % m_sigma << std::endl
		   << boost::format("  Fitness:..%1$1.10f") % m_fitness << std::endl
		   << boost::format("  Mean Distance Squared:..%1$1.10f") % m_mean_distance_squared << std::endl
		   << boost::format("  Iteration Count:..%1$1.10f") % m_iteration_count << std::endl
		   << m_config->to_string() << std::endl;


	    trace::candidate_solution_detail ( "Exiting Candidate_Solution<Classifier_Type, Data_Type>::to_String" );

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
