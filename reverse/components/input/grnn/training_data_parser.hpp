/*  IO.h

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

//
// C++ Interface: IO
//
// Description: 
//
//
// Author: Stephen Torri, Winard Britt <storri@dell>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_DATA_PARSER_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_DATA_PARSER_HPP_INCLUDED

#include <reverse/components/input/grnn/selection_policy.hpp>
#include <reverse/errors/io_exception.hpp>

#include <boost/filesystem.hpp>

#include <list>
#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <typename data_type, typename parser_type>
	class training_data_parser {
	public:

	  // TODO: If we are going to put the sigma into the training data file then we will have to either put the
	  //       sigma field from the Candidate Solution OR return a Candidate Solution
	  //
	  // Input: file name of the training data
	  static boost::shared_ptr < training_set<data_type> > get_data ( std::list<std::string> const& filenames )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering IO::get_Data" );
#endif /* LIBREVERSE_DEBUG */


	    parser_type parser;

	    typename training_set<data_type>::data_list_t output_data;

	    // For each XML file we want to
	    for ( std::list<std::string>::const_iterator cpos = filenames.begin();
		  cpos != filenames.end();
		  ++cpos )
	      {
		// If file does not exist throw exception
		if ( ! boost::filesystem::exists ( *cpos ) )
		  {


#ifdef LIBREVERSE_DEBUG
		    Trace::write_Trace ( TraceArea::IO,
					 TraceLevel::ERROR,
					 boost::str ( boost::format ( "Cannot find %s%" ) % *cpos ) );
#endif /* LIBREVERSE_DEBUG */


		    throw errors::io_exception ( errors::io_exception::invalid_file_name );
		  }

		// - parse input
		typename training_set<data_type>::data_list_t input_data = parser.get_data ( *cpos );
         

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "Size of input: %1%" ) % input_data.size() ) );
#endif /* LIBREVERSE_DEBUG */

         
		output_data.insert ( output_data.end(), input_data.begin(), input_data.end() );

	      }
	    // End loop

#ifdef LIBREVERSE_DEBUG
         
	    for ( typename training_set<data_type>::data_list_t::const_iterator data_pos = output_data.begin();
		  data_pos != output_data.end();
		  ++data_pos )
	      {
		trace::write_trace ( tracearea::io, tracelevel::data, (*data_pos)->to_string() );
	      }

#endif /* LIBREVERSE_DEBUG */
         
	    // - normalize input data
	    std::vector<double> max_list ( data_type::attribute_count, 0.0 );

	    normalize ( output_data, max_list );

#ifdef LIBREVERSE_DEBUG
	    //count = 0;
         
	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, "****************************" );
	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, "  Dump AFTER normalizing" );
	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, "****************************" );
         
	    for ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator data_pos = output_data.begin();
		  data_pos != output_data.end();
		  ++data_pos )
	      {
		//Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, (*data_pos)->to_String(count) );
		//++count;
		Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, (*data_pos)->to_String() );
	      }
#endif /* LIBREVERSE_DEBUG */

	    // - apply Selection Policy
	    typename training_set<data_type>::ptr_t output_set = selection_policy<data_type>::execute ( output_data );

	    // Save maximum values
	    for ( std::vector<double>::const_iterator cpos = max_list.begin();
		  cpos != max_list.end();
		  ++cpos )
	      {
		boost::uint32_t key = ( cpos - max_list.begin() );
		output_set->set_attribute_maximum ( key, (*cpos) );
	      }


#ifdef LIBREVERSE_DEBUG      

	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, "****************************" );
	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, "  Dump AFTER selection policy" );
	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, "****************************" );
	    Trace::write_Trace ( TraceArea::IO, TraceLevel::DATA, output_set->to_String() );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting IO::get_Data" );

#endif /* LIBREVERSE_DEBUG */


	    // Return results
	    return output_set;
	  }

	  static boost::shared_ptr < training_set<data_type> > get_data ( std::string training_data_file )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Entering IO::get_Data" );
#endif /* LIBREVERSE_DEBUG */


	    // If file does not exist throw exception
	    if ( ! boost::filesystem::exists ( training_data_file ) )
	      {

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::ERROR,
				     boost::str ( boost::format ( "Cannot find %s%" ) % training_data_file ) );
#endif /* LIBREVERSE_DEBUG */

	  
		throw errors::io_exception ( errors::io_exception::invalid_file_name );
	      }

	    parser_type parser;

	    boost::shared_ptr < training_set<data_type> > input_data = parser.get_data ( training_data_file );

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "Dumping input data" );

	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 boost::str ( boost::format ( "Input data size: %1%" ) % input_data.size() ) );

	    for ( typename classifier_types::Training_Set<Data_Type>::Data_List_t::const_iterator cpos = input_data.begin();
		  cpos != input_data.end();
		  ++cpos )
	      {
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     (*cpos)->to_String() );
	      }

#endif /* LIBREVERSE_DEBUG */

	    boost::shared_ptr < training_set<data_type> > output_set ( new training_set<data_type>() );
	    output_set->data_insert ( input_data );
	    output_set->max_values_insert ( parser.get_max_values() );
	    return output_set;
	  }

          
	  static void normalize ( typename training_set<data_type>::data_list_t& input_set,
				  std::vector<double>& max_list )
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting IO::normalize" );
#endif /* LIBREVERSE_DEBUG */


	    for ( typename training_set<data_type>::data_list_t::const_iterator set_pos = input_set.begin();
		  set_pos != input_set.end();
		  ++set_pos )
	      {

		// We skip the first entry in the training data since it is the compiler id (desired output)
		for ( boost::uint32_t key = 1;
		      key < data_type::attribute_count;
		      ++key )
		  {

#ifdef LIBREVERSE_DEBUG
		    Trace::write_Trace ( TraceArea::IO,
					 TraceLevel::DATA,
					 boost::str ( boost::format( "Pos (%1$d) => Value (%2$f)" )
						      % key
						      % (*set_pos)->get_Attribute ( key ) ) );
#endif /* LIBREVERSE_DEBUG */


		    // If the input_set value (pos.second) at the present position is greater than
		    // the preivously stored maximum value for this variable (max_list[pos.first])
		    // then save the greater value
		    if ( (*set_pos)->get_attribute ( key ) > max_list[ key ] )
		      {
			max_list [ key ] = (*set_pos)->get_attribute ( key );
		      }
		  }
	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "----- Max List -----" );

	    for ( boost::uint32_t index = 0;
		  index < max_list.size();
		  ++index )
	      {
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     boost::str ( boost::format ( "  #%1$d:   %2$s" )
						  % index
						  % max_list[index] ) );
	      }
#endif /* LIBREVERSE_DEBUG */


	    for ( typename training_set<data_type>::data_list_t::iterator reset_pos = input_set.begin();
		  reset_pos != input_set.end();
		  ++reset_pos )
	      {
		for ( boost::uint32_t key = 1;
		      key < data_type::attribute_count;
		      ++key )
		  {

		    // if our denominator is not zero we divide
		    if ( max_list [ key ] > 0 )
		      {
			double value = (*reset_pos)->get_attribute ( key ) / max_list [ key ];
               
			if ( value > 1 )
			  {
			    std::cout << boost::format ("%1$8f / %2$8f > 1 (value = %3$8f)")
			      % (*reset_pos)->get_attribute ( key )
			      % max_list [ key ]
			      % value << std::endl;

			    exit(1);
			  }

			(*reset_pos)->set_attribute ( key , value );
		      }
		  }
	      }

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DETAIL,
				 "Exiting IO::normalize" );
#endif /* LIBREVERSE_DEBUG */
	  }

	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // REVERSE_COMPONENTS_INPUT_GRNN_TRAINING_DATA_PARSER_HPP_INCLUDED 
