/*  Reverse.cpp

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

#include <reverse/results.hpp>
#include <reverse/reverse.hpp>
#include <reverse/reverse_impl.hpp>
#include <reverse/results.hpp>
#include <reverse/components/component_factory.hpp>
#include <reverse/components/null_component.hpp>
#include <reverse/data_containers/filename.hpp>
#include <reverse/errors/parsing_exception.hpp>
#include <reverse/errors/reverse_exception.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/infrastructure/configurator.hpp>
#include <reverse/infrastructure/data_source/data_source_factory.hpp>
#include <reverse/infrastructure/data_source/file_data_source_config.hpp>
#include <reverse/infrastructure/data_source/memory_data_transfer.hpp>
#include <reverse/infrastructure/data_source/memory_data_source_config.hpp>
#include <reverse/trace.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>

namespace reverse {

    reverse::reverse ()
    {}

    reverse::~reverse ()
    {}

  void reverse::init ( boost::shared_ptr < const infrastructure::configuration_data > config_data )
  {
    infrastructure::configurator& config_ref = infrastructure::configurator::instance();
    config_ref.init ( config_data );
  }

    boost::int32_t
    reverse::execute ( std::string target_file,
                       input_types::values input_type,
                       output_types::values output_type,
                       trace_level::values trace_level,
                       trace_area::values trace_mask )
    {

#ifdef LIBREVERSE_DEBUG
        if ( trace_level != trace_level::none )
            {
	      reverse::trace_state::instance().set_trace_level ( trace_level );
	      reverse::trace_state::instance().set_trace_area_mask ( trace_mask );
	      reverse::trace_state::instance().open_trace_file ();
            }
#endif /* LIBREVERSE_DEBUG */

        boost::int32_t result = results::success;

        if ( target_file.empty() )
            {
                result = results::failure;
                return result;
            }

        if ( ! ( boost::filesystem::exists ( target_file ) ) )
            {
                result = results::failure;
                return result;
            }

        if ( ! ( this->valid_types ( input_types::binary,
                                     input_types::binary,
                                     input_type ) ) )
            {
                result = results::failure;
                return result;
            }

        if ( ! ( this->valid_types ( output_types::cplusplus,
                                     output_types::uml,
                                     output_type ) ) )
            {
                result = results::failure;
                return result;
            }

        try {

            //------------------------------
            // Prepare Initial Component
            //------------------------------
            // Create a Null Component object
            // Set output meta information to "target_filename"
            // Pass component object with meta information to execute_Input_Section
	  boost::shared_ptr < infrastructure::component_state > state_ptr = boost::make_shared<infrastructure::component_state>
                                                                     ( infrastructure::component::source_id );

	  boost::shared_ptr < infrastructure::component > comp_ptr =
	    infrastructure::component_factory::instance().get_null_component ( state_ptr );

            //------------------------------
            // Prepare Initial Data Source
            //------------------------------

            // The first component will receive its data via a file. The rest
            // of the components will receive it by memory for now. So we
            // create the input data source (file type)

	    boost::shared_ptr < const infrastructure::data_source::file_data_source_config > file_config =
	      boost::make_shared < const infrastructure::data_source::file_data_source_config > ( target_file );

	    boost::shared_ptr < infrastructure::data_source::data_source_factory > fact_ptr = infrastructure::data_source::data_source_factory::instance();
	    fact_ptr->init ( file_config );

	    boost::shared_ptr < const infrastructure::data_source::data_source_base > input_data_source_ptr = fact_ptr->get_data_source ( 0 );

            // Create component graph from suggested configuration files
            //  Configuration files are in three parts
	    boost::shared_ptr < infrastructure::component_graph::map_t > m_graph =
	      (infrastructure::configurator::instance()).get_graph ( input_type, output_type );

            reverse_impl m_executor;

            // ----------------------------------------
            //             INPUT Section
            // ----------------------------------------
            //
            // Input: Change input to send a Component with meta information
            //
            // Output: Change return type to give back a pair < Data_Source_Base, Component>
            // which contains the output data and the last component
            reverse_impl::return_type_t input_results_ptr =
                m_executor.execute_input_section ( m_graph, input_data_source_ptr, comp_ptr );


            // FUTURE: We could take the meta information from the
            // Input analysis phase and make decisions on it. For
            // example, choose the type of analysis graph to use based
            // on the compiler used to create the target executable.

            // ----------------------------------------
            //             ANALYSIS Section
            // ----------------------------------------
            // Input: Change input to send the component retrieved from the input section
            //
            // Change return type to give back a pair < Data_Source_Base, Component>
            // which contains the output data and the last component
            reverse_impl::return_type_t analysis_results_ptr =
                m_executor.execute_analysis_section ( m_graph, input_results_ptr );

            // ----------------------------------------
            //             OUTPUT Section
            // ----------------------------------------
            // Input: Change input to send the component retrieved from the input section
            m_executor.execute_output_section ( m_graph, analysis_results_ptr );

        }
        catch ( errors::reverse_exception& re )
	  {
                std::cerr << boost::format("exception:(%d) %s")
                    % re.name()
                    % re.id() << std::endl;
                std::cerr << re.what() << std::endl;

                result = results::failure;
                return result;
            }

#ifdef LIBREVERSE_DEBUG
        if ( trace_level != trace_level::none )
            {
                trace_state::instance().close_trace_file ();
            }
#endif /* LIBREVERSE_DEBUG */

        return result;

    }


    bool reverse::valid_types ( boost::uint32_t lower_limit,
                                boost::uint32_t upper_limit,
                                boost::uint32_t value )
    {
        bool result = false;

        if ( ( lower_limit <= value ) &&
             ( value <= upper_limit ) )
            {
                result = true;
            }

        return result;
    }

} /* namespace reverse */
