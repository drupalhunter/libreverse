/*  Configurator.cpp

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
#include <reverse/trace.hpp>
#include <reverse/errors/configuration_exception.hpp>
#include <reverse/errors/reverse_exception.hpp>
#include <reverse/infrastructure/configurator.hpp>
#include <reverse/infrastructure/configuration_data.hpp>
#include <reverse/infrastructure/formula_list.hpp>
#include <reverse/infrastructure/formula_parser.hpp>
#include <reverse/infrastructure/grnn_data_parser.hpp>
#include <reverse/infrastructure/master_formula_parser.hpp>
#include <reverse/infrastructure/data_source/data_source_factory_base.hpp>

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

#include <iostream>
#include <sstream>

namespace reverse {
  namespace infrastructure {

    boost::shared_ptr < const infrastructure::configuration_data > configurator::m_config =
      boost::make_shared < infrastructure::configuration_data > ();

    void configurator::init ( boost::shared_ptr < const infrastructure::configuration_data > config_obj )
    {
      m_config = config_obj;
    }

    void configurator::register_Factory ( boost::shared_ptr < infrastructure::data_source_factory_base > fact_ptr )
    {
      trace::infrastructure_detail ( "Entering configurator::register_Factory" );

      boost::shared_ptr < infrastructure::data_source_config_base > transfer_data =
	m_config->get_transfer_config();

      // Pass this information to the factory
      fact_ptr->init( transfer_data );

      trace::infrastructure_detail ( "Exiting configurator::register_Factory" );
    }

    boost::shared_ptr < infrastructure::component_graph::map_t >
    configurator::get_graph ( const boost::uint32_t input_type,
			      const boost::uint32_t output_type )
    {
      trace::infrastructure_detail ( "Entering configurator::get_Graph" );

      boost::shared_ptr < infrastructure::component_graph::map_t > master_map =
	boost::make_shared < infrastructure::component_graph::map_t> ();

      // If not set initialize the Master Formula map
      if ( ! this->m_formulas.get() )
	{ 
	  master_formula_parser mfp;
	  std::stringstream cfg_file;
	  cfg_file << m_config->get_formula_directory()
		   << "/" << "formula_master.xml";
	  m_formulas = mfp.get_formula_map ( cfg_file.str() );
	}

        // Once we have the master formula file we need the entry
        // for the files we need. This is based on the input_type
        // and output_type given in the Reverse class.
      infrastructure::configurator::formula_map_t::iterator pos = m_formulas->find ( std::make_pair ( input_type, output_type ) );

      if ( pos == m_formulas->end() )
	{
	  // throw exception, we should not be giving values we do not support.
	  trace::infrastructure_error ( "Input type: %d\tOutput type %d",
					input_type,
					output_type );

	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
					__LINE__ );

	  throw errors::configuration_exception ( errors::configuration_exception::unsupported_map );
	}

        formula_list files = (*pos).second;

        formula_parser frm_ref;

        (*master_map) ["input"] =
            frm_ref.get_graph (files.input,
                               m_config->get_formula_directory());

        (*master_map)["analysis"] =
            frm_ref.get_graph (files.analysis,
                               m_config->get_formula_directory());

        (*master_map)["output"] =
            frm_ref.get_graph (files.output,
                               m_config->get_formula_directory());

        trace::infrastructure_detail ( "Exiting configurator::get_Graph" );

        return master_map;
    }

    boost::shared_ptr < components::input::grnn::grnn_data_map >
    configurator::get_grnn_data ( void )
    {

      trace::infrastructure_detail ( "Entering configurator::get_GRNN_Data" );

      if ( ! m_grnn_data_map )
	{
	  grnn_data_parser grnn_ref;

	  m_grnn_data_map = grnn_ref.get_data_map ( m_config->get_grnn_data_file() );
	}

      trace::infrastructure_detail ( "Exiting configurator::get_GRNN_Data" );

      return m_grnn_data_map;
    }

  } /* namespace infrastructure */
} /* namespace reverse */
