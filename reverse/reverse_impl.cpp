/*  reverse_impl.cpp

   copyright (c) 2008 stephen torri

   this file is part of libreverse.

   libreverse is free software; you can redistribute it and/or modify
   it under the terms of the gnu general public license as published
   by the free software foundation; either version 3, or (at your
   option) any later version.

   libreverse is distributed in the hope that it will be useful, but
   without any warranty; without even the implied warranty of
   merchantability or fitness for a particular purpose.  see the gnu
   general public license for more details.

   you should have received a copy of the gnu general public license
   along with this program.  if not, see
   <http://www.gnu.org/licenses/>.
*/

#include <reverse/reverse_impl.hpp>

#include <reverse/data_containers/filename.hpp>
#include <reverse/errors/api_exception.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/infrastructure/data_source/data_source_base.hpp>
#include <reverse/infrastructure/visitor/graph_visitor.hpp>
#include <reverse/infrastructure/visitor/graphviz_visitor.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/graph/topological_sort.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

namespace reverse {

    reverse_impl::reverse_impl ()
    {
      trace::api_detail ( "inside reverse_impl constructor" );
    }

    reverse_impl::~reverse_impl ()
    {
      trace::api_detail ( "inside reverse_impl destructor" );
    }

    reverse_impl::return_type_t
    reverse_impl::execute_input_section ( boost::shared_ptr < infrastructure::component_graph::map_t > m_graph,
                                          boost::shared_ptr < infrastructure::data_source::data_source_base > init_data_ptr,
                                          boost::shared_ptr < infrastructure::component > init_comp_ptr )
    {
      trace::api_detail ( "entering reverse_impl::execute_input_section" );

      if ( ! m_graph )
	{
	  trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	  throw errors::internal_exception ( errors::internal_exception::null_pointer );
	  
	}

      if ( ! init_data_ptr )
	{
	  trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	  throw errors::internal_exception ( errors::internal_exception::null_pointer );
	  
	}

        if ( ! init_comp_ptr )
            {
	      trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	      throw errors::internal_exception ( errors::internal_exception::null_pointer );
            }
	
        reverse_impl::return_type_t results;

        std::cout << std::endl
                  << "// ----------------------------------------"
                  << std::endl
                  << "//             input section" << std::endl
                  << "// ----------------------------------------"
                  << std::endl;


	boost::shared_ptr < infrastructure::component_graph > graph_ptr = (*m_graph)["input"];

        // give input data source to head of component graph. there should
        // only be one. ('insert highlander jokes here').
        init_comp_ptr->set_state ( infrastructure::component::source_mode );

        // if the input graph is not empty
        if ( ! graph_ptr->empty() )
            {
                // print input graph
                this->print_graph ( *graph_ptr, "input" );

                graph_ptr->initialize_source ( init_comp_ptr );

                // perform work on input section
                results.first = this->process_graph ( graph_ptr, init_data_ptr );

                results.second = graph_ptr->get_end_component();
            }
        else
            {
	      trace::api_error ( "input graph is empty. double check the file." );
	      trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	      throw errors::api_exception ( errors::api_exception::internal_library_error );

            }

	trace::api_detail ( "exiting reverse_impl::execute_input_section" );

        return results;
    }

    reverse_impl::return_type_t
    reverse_impl::execute_analysis_section ( boost::shared_ptr < infrastructure::component_graph::map_t > m_graph,
                                             reverse_impl::return_type_t& input_results )
    {
      trace::api_detail ( "entering reverse_impl::execute_analysis_section" );

      if ( ! m_graph )
	{
	  trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	  throw errors::internal_exception ( errors::internal_exception::null_pointer );

	}

        std::cout << std::endl
                  << "// ----------------------------------------"
                  << std::endl
                  << "//             analysis section" << std::endl
                  << "// ----------------------------------------"
                  << std::endl;

        reverse_impl::return_type_t results;

        // at this point the input section has done its work. our
        // processed data is contained in the visitor. we need to pass
        // one the end node data source from the input section graph to
        // the source node of the analysis section.

        // get analysis section map
	boost::shared_ptr < infrastructure::component_graph > graph_ptr = (*m_graph)["analysis"];

        // give input section data source to head of component graph. there should
        // only be one. ('insert highlander jokes here').
        (input_results.second)->set_state ( infrastructure::component::source_mode );

        // print analysis graph
        this->print_graph ( *graph_ptr, "analysis" );

        // if the analysis graph is not empty
        if ( ! graph_ptr->empty() )
            {
                graph_ptr->initialize_source ( input_results.second );

                // perform work on analysis section
                results.first = this->process_graph ( graph_ptr, input_results.first );

                results.second = graph_ptr->get_end_component();
            }
        else
            {
	      trace::api_error ( "analysis graph is empty. double check the file." );
	      trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	      throw errors::api_exception ( errors::api_exception::internal_library_error );
            }
       
	trace::api_detail ( "exiting reverse_impl::execute_analysis_section" );

        return results;
    }

    void
    reverse_impl::execute_output_section ( boost::shared_ptr < infrastructure::component_graph::map_t > m_graph,
                                           reverse_impl::return_type_t& analysis_results )
    {
      trace::api_detail ( "entering reverse_impl::execute_output_section" );

      if ( ! m_graph )
	{
	  trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );
	  throw errors::internal_exception ( errors::internal_exception::null_pointer );
	}

        std::cout << std::endl
                  << "// ----------------------------------------"
                  << std::endl
                  << "//             output section" << std::endl
                  << "// ----------------------------------------"
                  << std::endl;

        // at this point the analysis section has done its work. our
        // processed data is contained in the visitor. we need to pass
        // one the end node data source from the analysis section graph to
        // the source node of the output section.

        // get analysis section map
	boost::shared_ptr < infrastructure::component_graph > graph_ptr = (*m_graph)["output"];

        // give input section data source to head of component graph. there should
        // only be one. ('insert highlander jokes here').
        ( analysis_results.second )->set_state ( infrastructure::component::source_mode );

        // if the analysis graph is not empty
        if ( ! graph_ptr->empty() )
            {
                // print output graph
                this->print_graph ( *graph_ptr, "output" );

                graph_ptr->initialize_source ( analysis_results.second );

                // perform work on output section
                this->process_graph ( graph_ptr, analysis_results.first );
            }
        else
            {
	      trace::api_error ( "output graph is empty. double check the file." );
	      trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );

	      throw errors::api_exception ( errors::api_exception::internal_library_error );

            }

	trace::api_detail ( "exiting reverse_impl::execute_output_section" );
    }


    void reverse_impl::print_graph ( infrastructure::component_graph const& graph_ref,
                                     std::string name ) const
    {
      trace::api_detail ( "entering reverse_impl::print_graph" );

      if ( name.empty() )
	{
	  trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );
	  throw errors::internal_exception ( errors::internal_exception::empty_string );
	}

        std::stringstream output_data;

        std::cout << graph_ref.to_string() << std::endl;

        typedef std::vector<infrastructure::component_graph::vertex_t> container;
        container c;
        boost::topological_sort( graph_ref.get_graph(),
                                 std::back_inserter(c) );

        std::cout << "a topological ordering: ";
        for ( container::iterator ii=c.begin();
              ii!=c.end();
              ++ii )
	  {
	    boost::shared_ptr < infrastructure::component > comp_ptr = graph_ref.get_component ( *ii );
	    std::cout << comp_ptr->get_id() << " ";
	  }
        std::cout << std::endl;

	infrastructure::visitor::graphviz_visitor::visit ( graph_ref, output_data );

        std::stringstream filename;
        filename << name << ".dot";
        std::string final_name = filename.str();
        std::ofstream output_file ( final_name.c_str() );

        output_file << "digraph " << name << " {" << std::endl;
        output_file << output_data.str();
        output_file << "}" << std::endl;

	trace::api_detail ( "exiting reverse_impl::print_graph" );

        output_file.close();
    }

  boost::shared_ptr < infrastructure::data_source::data_source_base >
  reverse_impl::process_graph ( boost::shared_ptr < const infrastructure::component_graph > graph_ptr,
				boost::shared_ptr < infrastructure::data_source::data_source_base > val ) const
    {
      trace::api_detail ( "entering reverse_impl::process_graph" );

        if ( ! graph_ptr )
            {
	      trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );
	      throw errors::internal_exception ( errors::internal_exception::null_pointer );
            }

        if ( ! val )
            {
	      trace::api_error ( "exception throw in %s at line %d", __FILE__, __LINE__ );
	      throw errors::internal_exception ( errors::internal_exception::null_pointer );
            }

        // prepare data
        infrastructure::component_graph::data_map_t m_data_map;
        m_data_map[0] = std::make_pair ( val, 1 );

        // process graph
	infrastructure::visitor::graph_visitor::visit ( *graph_ptr, &m_data_map );

        // grab the output of the last node
        // - get component for the last node
	boost::shared_ptr < infrastructure::component > last_comp = graph_ptr->get_end_component();

        // - use id to grab iterator to the appropriate position
        boost::uint32_t last_comp_id = last_comp->get_id();

        // - get the result data for last node
        infrastructure::component_graph::data_map_t::const_iterator pos =
            m_data_map.find ( last_comp_id );

        infrastructure::component_graph::result_data_t result = pos->second;

	trace::api_detail ( "exiting reverse_impl::process_graph" );

        return result.first;
    }

} /* namespace libreverse */
