/*  Elf_Optimizer_Algorithm.cpp

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

#include "Elf_Optimizer_Algorithm.h"

#include "reverse/components/input/grnn/IO.h"
#include "reverse/components/input/grnn/Candidate_Solution.h"
#include "reverse/components/input/grnn/Optimizer.h"
#include "reverse/components/input/grnn/GRNN_Data_Map.h"
#include "reverse/components/input/grnn/GRNN_Data_Entry.h"
#include "reverse/components/input/grnn/Elf_Training_Data_Parser.h"

#include "reverse/infrastructure/Component_Types.h"

#include <boost/format.hpp>
#include <iostream>

using namespace reverse::classifier;

#ifdef LIBREVERSE_DEBUG
using namespace reverse::trace;
#include "reverse/Trace.h"
#endif /* LIBREVERSE_DEBUG */

namespace reverse
{
  namespace optimizer
  {

    template <template <typename Data_Type> class Classifier_Type>
    void
    Elf_Optimizer_Algorithm<Classifier_Type>::process ( std::list<std::string>& data_files )
    {
      //      Training_Set::ptr_t input_data
      this->m_input_data = IO<classifier::Elf_Training_Data,classifier::Elf_Training_Data_Parser>::get_Data ( data_files );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DATA,
			   "Dumping parsed input data" );

      Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
			   TraceLevel::DATA,
			   m_input_data->to_String() );
#endif /* LIBREVERSE_DEBUG */
      
      // Verify input data is correct before starting
      m_input_data->is_Valid();

      classifier::Optimizer<Classifier_Type, Elf_Training_Data> opt_ref;
      opt_ref.init ( m_input_data );
      opt_ref.process ();
        
      this->m_best_solution = opt_ref.test ();
    }

    template <template <typename Data_Type> class Classifier_Type>
    std::string
    Elf_Optimizer_Algorithm<Classifier_Type>::print_Results ( void )
    {
      std::stringstream output;

      classifier_types::Configuration<Elf_Training_Data>::ptr_t config_ptr = this->m_best_solution->get_Config();
        
      // Print results
      output << "---- Result ----" << std::endl
	     << config_ptr->to_String() << std::endl
	     << this->m_best_solution->to_String() << std::endl;

      return output.str();
    }

    template <template <typename Data_Type> class Classifier_Type>
    void
    Elf_Optimizer_Algorithm<Classifier_Type>::save_Data ( std::string output_string )
    {
      std::stringstream name;
      name << output_string << ".xml";

      std::ofstream output_file ( (name.str()).c_str() );

      classifier_types::Configuration<classifier::Elf_Training_Data>::ptr_t config_ptr = this->m_best_solution->get_Config();
      config_ptr->set_Attribute ( classifier::Elf_Training_Data::CLASSIFIER_TARGET, true );

      output_file << boost::format ( "<%1%>" ) % classifier::Elf_Input_Tag_Names::TAG_DATA << std::endl;

      output_file << m_input_data->get_Attribute_Maximum_XML ();
      
      for ( classifier_types::Training_Set<classifier::Elf_Training_Data>::Data_List_t::const_iterator cpos = m_input_data->data_Begin();
	    cpos != m_input_data->data_End();
	    ++cpos )
	{
	  output_file << (*cpos)->to_XML ( config_ptr );
	}

      output_file << boost::format ( "</%1%>" ) % classifier::Elf_Input_Tag_Names::TAG_DATA << std::endl;

      output_file.close();
    }

  } /* namespace optimizer */
} /* namespace reverse */
