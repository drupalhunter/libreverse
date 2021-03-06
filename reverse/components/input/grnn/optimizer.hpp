/*  Optimizer.h

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

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Classifier_Types.h"
#include "Training_Set.h"
#include <vector>

namespace reverse {
  namespace classifier {

    template <template <typename Data_Type> class Classifier_Type, typename Data_Type>
      class Optimizer
    {
    public:

    Optimizer()
      : m_mutation_amount ( 0.0 ),
	m_iteration_limit ( 0 ),
	m_best_candidate_index ( 0 )
	  {}


      /*
	\brief Initialize Optimizer
	\pre Training Data objects are initialized
	\post The optimizer is prepared to do work.
      */
      void init ( typename classifier_types::Training_Set<Data_Type>::ptr_t data,
		  double mutation_amount = 0.125,
		  boost::uint32_t iteration_limit = 1000 )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Entering Optimizer::init" );
#endif /* LIBREVERSE_DEBUG */


	m_data = data;
	m_mutation_amount = mutation_amount;
	m_iteration_limit = iteration_limit;


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Exiting Optimizer::init" );
#endif /* LIBREVERSE_DEBUG */

      }

     
      /* \brief Process the Training Data in order to obtain the best sigma
         \pre The Training Data objects have been received (m_input_data is not empty)
         \post The best sigma has been found the optimizer. Tranining Data is unchanged.
      */
      void process (void)
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Entering Optimizer::process" );
#endif /* LIBREVERSE_DEBUG */


	// Generate candidate solutions gene pool
	this->populate_Gene_Pool();

	for ( boost::uint32_t i = 0;
	      i < m_iteration_limit;
	      ++i )
	  {


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				 TraceLevel::DATA,
				 boost::str ( boost::format ("Iteration #%1%" ) % i ) );
#endif /* LIBREVERSE_DEBUG */

	    // Evaluate each candidate solution in gene pool
	    for ( typename Pool_Type_t::iterator pos = m_gene_pool.begin();
		  pos != m_gene_pool.end();
		  ++pos )
	      {
		(*pos)->evaluate ( m_data );
	      }

	    // Get Parent #1
	    typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_one = this->get_Parent();

	    // Get Parent #2
	    typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_two = this->get_Parent();

	    this->m_child = this->breed ( parent_one, parent_two );

	    this->mutate_Attributes ();

	    boost::uint32_t mutate_sigma_chance = rand() % 10 + 1;
	  
	    if ( mutate_sigma_chance == 1 )
	      {
		this->mutate_Sigma ();
	      }

	    // Evaluate child
	    this->m_child->evaluate ( this->m_data );

	    this->m_child->set_Iteration_Count ( i + 1 );

	    // Replace worst solution with child
	    this->replace_Worst ();
	  }

	typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t best_solution = m_gene_pool[m_best_candidate_index];

	std::cout << boost::format ( "%1%,%2%,%3%,%4%," )
	  % best_solution->get_Sigma()
	  % best_solution->get_Fitness()
	  % best_solution->get_Mean_Distance_Squared()
	  % best_solution->get_Iteration_Count();

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Exiting Optimizer::process" );
#endif /* LIBREVERSE_DEBUG */

      }

      
      typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t test (void)
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::DETAIL,
			       "Entering Optimizer::test" );
#endif /* LIBREVERSE_DEBUG */


	  typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t best_solution = m_gene_pool[m_best_candidate_index];
	  best_solution->test ( m_data );

	  // TEST: REMOVE ME LATER
	  std::cout << boost::format ( "%1%,%2%,%3%" )
	    % best_solution->get_Sigma()
	    % best_solution->get_Fitness()
	    % best_solution->get_Mean_Distance_Squared()
		    << std::endl;

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::DETAIL,
			       "Exiting Optimizer::test" );
#endif /* LIBREVERSE_DEBUG */

	  return best_solution;
	}


    private:

      void mutate_Attributes ()
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Entering Optimizer::mutate_Attributes" );
#endif /* LIBREVERSE_DEBUG */


	// Pick a random attribute and flip it
	boost::uint32_t attribute_index = rand() % Data_Type::ATTRIBUTE_COUNT;
	typename classifier_types::Configuration<Data_Type>::ptr_t config_ptr = m_child->get_Config();
	bool flag = config_ptr->get_Attribute ( attribute_index );
	config_ptr->set_Attribute ( attribute_index, !flag );


#ifdef LIBREVERSE_DEBUG        
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Exiting Optimizer::mutate_Attributes" );
#endif /* LIBREVERSE_DEBUG */

      }
      
      void mutate_Sigma ()
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Entering Optimizer::mutate_Sigma" );
#endif /* LIBREVERSE_DEBUG */


	double random_number = ( 2 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) ) - 1;
	float old_sigma = m_child->get_Sigma();
	m_child->set_Sigma ( old_sigma + random_number * m_mutation_amount * old_sigma );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Old sigma: %1$1.10d" ) % old_sigma ) );
       
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Random Number: %1$1.10d" ) % random_number ) );
       
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Mutation amount: %1$1.10d" ) % m_mutation_amount ) );
       
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "New sigma: %1$1.10d" ) % ( old_sigma + random_number * m_mutation_amount * old_sigma ) ) );
       
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Exiting Optimizer::mutate_Sigma" );
#endif /* LIBREVERSE_DEBUG */

      }


      // Create N number of random Candidate Solutions
      void populate_Gene_Pool ( boost::uint32_t number = 10 )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Entering Optimizer::populate_Gene_Pool" );
#endif /* LIBREVERSE_DEBUG */


	m_gene_pool.clear();

	for ( boost::uint32_t i = 0;
	      i < number;
	      ++i )
	  {
	    typename classifier_types::Configuration<Data_Type>::ptr_t config ( new Configuration<Data_Type> ( false ) );
	  
	    config->set_Attribute ( Data_Type::CLASSIFIER_TARGET, true );

	    for ( boost::uint32_t index = 1;
		  index < Data_Type::ATTRIBUTE_COUNT;
		  ++index )
	      {
		double random_num = ( 2 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) ) - 1;

		if ( random_num > 0.5 )
		  {
		    config->set_Attribute ( index, true );
		  } 
	      }

	    typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t solution
	      ( new Candidate_Solution<Classifier_Type, Data_Type> ( 0.002, 0.0, config ) );

	    m_gene_pool.push_back ( solution );
	  }

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Exiting Optimizer::populate_Gene_Pool" );
#endif /* LIBREVERSE_DEBUG */

      }


      // Randomly select two parents from the gene pool. Return the parent with the best fitness
      typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t get_Parent ()
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::DETAIL,
			       "Entering Optimizer::get_Parent" );
#endif /* LIBREVERSE_DEBUG */

	  boost::uint32_t parent_one_index = rand() % static_cast<boost::uint32_t>( this->m_gene_pool.size() );
	  boost::uint32_t parent_two_index = rand() % static_cast<boost::uint32_t>( this->m_gene_pool.size() );

	  typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_one_sol = this->m_gene_pool[parent_one_index];
	  typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_two_sol = this->m_gene_pool[parent_two_index];

	  if ( parent_one_sol->get_Fitness() > parent_two_sol->get_Fitness() )
	    {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				   TraceLevel::DETAIL,
				   "Exiting Optimizer::get_Parent" );
#endif /* LIBREVERSE_DEBUG */

	      return parent_one_sol;
	    }
	  else
	    {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				   TraceLevel::DETAIL,
				   "Exiting Optimizer::get_Parent" );
#endif /* LIBREVERSE_DEBUG */

	      return parent_two_sol;
	    }
      
	}


      // Produce a child from the two parents
      typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t
	breed ( typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_one,
		typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t parent_two )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::DETAIL,
			       "Entering Optimizer::breed" );
#endif /* LIBREVERSE_DEBUG */

	  typename classifier_types::Configuration<Data_Type>::ptr_t child ( new Configuration<Data_Type> ( false ) );
	  child->set_Attribute ( Data_Type::CLASSIFIER_TARGET, true );

	  typename classifier_types::Configuration<Data_Type>::ptr_t parent_one_config = parent_one->get_Config();
	  typename classifier_types::Configuration<Data_Type>::ptr_t parent_two_config = parent_two->get_Config();

	  for ( boost::uint32_t index = 1;
		index < Data_Type::ATTRIBUTE_COUNT;
		++index )
	    {
	      double random_num = ( 2 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) ) - 1;
	  
	      if ( random_num > 0.5 )
		{
		  child->set_Attribute ( index, parent_one_config->get_Attribute ( index ) );
		}
	      else
		{
		  child->set_Attribute ( index, parent_two_config->get_Attribute ( index ) );
		}
	    }

	  typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t
	    child_solution ( new Candidate_Solution<Classifier_Type, Data_Type> ( 0.002, 0.0, child ) );

	  double random_num = ( 2 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) ) - 1;
	  
	  if ( random_num > 0.5 )
	    {
	      child_solution->set_Sigma ( parent_one->get_Sigma() );
	    }
	  else
	    {
	      child_solution->set_Sigma ( parent_two->get_Sigma() );
	    }

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			       TraceLevel::DETAIL,
			       "Exiting Optimizer::breed" );
#endif /* LIBREVERSE_DEBUG */

	  return child_solution;
	}


      // Replace the worst solution with the child
      void replace_Worst ()
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Entering Optimizer::replace_Worst" );
#endif /* LIBREVERSE_DEBUG */

	double worst_fitness = 1.0;
	double best_fitness = 0.0;
	boost::uint32_t replacement_index = 0;

	for ( typename Pool_Type_t::iterator pos = m_gene_pool.begin();
	      pos != m_gene_pool.end();
	      ++pos )
	  {
	    if ( (*pos)->get_Fitness() < worst_fitness )
	      {
		worst_fitness = (*pos)->get_Fitness();
		replacement_index = ( pos - m_gene_pool.begin() );

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "replacement index: %1%" ) % replacement_index ) );
#endif /* LIBREVERSE_DEBUG */

	      }

	    if ( (*pos)->get_Fitness() > best_fitness )
	      {
		m_best_candidate_index = ( pos - m_gene_pool.begin() );

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "best candidate index: %1%" ) % m_best_candidate_index ) );
#endif /* LIBREVERSE_DEBUG */

	      }
	  }

	m_gene_pool[replacement_index] = m_child;

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			     TraceLevel::DETAIL,
			     "Exiting Optimizer::replace_Worst" );
#endif /* LIBREVERSE_DEBUG */

      }


      //------------------------------------
      //             VARIABLES
      //------------------------------------
      typedef std::vector < typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t > Pool_Type_t;
      Pool_Type_t m_gene_pool;

      typename classifier_types::Candidate_Solution<Classifier_Type, Data_Type>::ptr_t m_child;
      
      typename classifier_types::Training_Set<Data_Type>::ptr_t m_data;
      
      double m_mutation_amount;
      
      boost::uint32_t m_iteration_limit;

      boost::uint32_t m_best_candidate_index;
    };

  } /* namespace classifier */
} /* namespace reverse */

#endif /* OPTIMIZER_H */
