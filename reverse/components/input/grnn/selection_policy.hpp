/*  Selection_Policy.h

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

#ifndef SELECTION_POLICY_H
#define SELECTION_POLICY_H

#include <list>
#include "Classifier_Types.h"
#include <string>

namespace libreverse
{
  namespace classifier
  {

    /*!
     * \brief Selection Policy implements the division of training data into training, test and validation sets.
     *
     * \author Author: Stephen Torri, Winard Britt
     */
    template <typename Data_Type>
      class Selection_Policy
      {
      public:

	/*! \brief Execute the selection policy
	 *
	 * Training set (70% of input)
	 * Test set (20% of input)
	 * Validation set (20% of input)
	 *
	 * \param input_data Input training set with all the training data in the training set.
	 *
	 * \return Output training set with the input training data divided into training, test and validation sets
	 */
	static typename classifier_types::Training_Set<Data_Type>::ptr_t
	  execute ( typename classifier_types::Training_Set<Data_Type>::Data_List_t const& input_data )
	{
	  typename classifier_types::Training_Set<Data_Type>::ptr_t output_set = alloc::Create::shared_pointer< Training_Set<Data_Type> > ();

	  // WIN's COMPLETE AND CORRECT POLICY
	  //
	  // produce a random number (X)
	  // FOR ALL
	  //   IF X < 7 -> Training
	  //   ELSE IF X >= 7 && X <= 8 -> Verification
	  //   ELSE -> test

	  for ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator cpos = input_data.begin();
		cpos != input_data.end();
		++cpos )
	    {
	      boost::uint32_t random_number = rand() % 10 + 1;

	      if ( random_number < 7 )
		{
		  output_set->data_Push_Back ( *cpos );
		}
	      else if ( ( random_number == 7 ) || ( random_number == 8 ) )
		{
		  output_set->verification_Push_Back ( *cpos );
		}
	      else
		{
		  output_set->test_Push_Back ( *cpos );
		}
	    }

	  // Return results
	  return output_set;
	}

      };
  } /* namespace classifier */
} /* namespace libreverse */

#endif /* SELECTION_POLICY_H */
