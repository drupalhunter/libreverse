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

#include "Configurator.h"
#include "Configuration_Parser.h"
#include "Configuration_Data.h"
#include "Formula_List.h"
#include "Formula_Parser.h"
#include "GRNN_Data_Parser.h"
#include "Master_Formula_Parser.h"
#include "data_source/Data_Source_Factory_Base.h"

#include "errors/Configuration_Exception.h"
#include "errors/Reverse_Exception.h"

#include <iostream>
#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
using namespace libreverse::api;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    infrastructure_types::Configuration_Data::ptr_t Configurator::m_config =
        infrastructure_types::Configuration_Data::ptr_t ( new Configuration_Data() );

    Configurator::Configurator ( std::string file )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			   TraceLevel::DETAIL,
			   "Entering Configurator Constructor" );
#endif /* LIBREVERSE_DEBUG */


      try
	{
	  Configuration_Parser reader ( file );

	  m_config = reader.parse_Data();
	}
      catch ( errors::Reverse_Exception& )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			       TraceLevel::WARN,
			       "Unable to find the default setup files for the system.\nStarting the library using the default settings" );
#endif /* LIBREVERSE_DEBUG */


	}
    }

    void Configurator::register_Factory
    ( infrastructure_types::Data_Source_Factory_Base::ptr_t fact_ptr)
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			   TraceLevel::DETAIL,
			   "entering Configurator::register_Factory" );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Data_Source_Config_Base::ptr_t transfer_data =
            m_config->get_Transfer_Config();

        // Pass this information to the factory
        fact_ptr->init( transfer_data );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "exiting Configurator::register_Factory" );

#endif /* LIBREVERSE_DEBUG */

    }

    infrastructure_types::Component_Graph::Map_ptr_t
        Configurator::get_Graph ( const boost::uint32_t input_type,
        const boost::uint32_t output_type )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "entering Configurator::get_Graph" );
#endif /* LIBREVERSE_DEBUG */


        infrastructure_types::Component_Graph::Map_ptr_t master_map ( new infrastructure_types::Component_Graph::Map_t() );

        // If not set initialize the Master Formula map
        if ( this->m_formulas.get() == 0 )
            { 
	      Master_Formula_Parser mfp;
	      std::stringstream cfg_file;
	      cfg_file << m_config->get_Formula_Directory()
		       << "/" << "formula_master.xml";
	      m_formulas = mfp.get_Formula_Map ( cfg_file.str() );
            }

        // Once we have the master formula file we need the entry
        // for the files we need. This is based on the input_type
        // and output_type given in the Reverse class.
        infrastructure_types::Configurator::Formula_Map_t::iterator pos =
            m_formulas->find ( std::make_pair ( input_type, output_type ) );

        if ( pos == m_formulas->end() )
            {

#ifdef LIBREVERSE_DEBUG
                // throw exception, we should not be giving values we do not support.
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format ( "Input type: %d\tOutput type %d" )
						  % input_type
						  % output_type ) );

                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str ( boost::format("Exception throw in %s at line %d")
						  % __FILE__
						  % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Configuration_Exception ( errors::Configuration_Exception::UNSUPPORTED_MAP );
            }

        Formula_List files = (*pos).second;

        Formula_Parser frm_ref;

        (*master_map) ["input"] =
            frm_ref.get_Graph (files.input,
                               m_config->get_Formula_Directory());

        (*master_map)["analysis"] =
            frm_ref.get_Graph (files.analysis,
                               m_config->get_Formula_Directory());

        (*master_map)["output"] =
            frm_ref.get_Graph (files.output,
                               m_config->get_Formula_Directory());


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "exiting Configurator::get_Graph" );
#endif /* LIBREVERSE_DEBUG */

        return master_map;
    }

    classifier_types::GRNN_Data_Map::ptr_t
    Configurator::get_GRNN_Data ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configurator::get_GRNN_Data" );
#endif /* LIBREVERSE_DEBUG */


      if ( ! m_grnn_data_map )
	{
	  GRNN_Data_Parser grnn_ref;

	  m_grnn_data_map = grnn_ref.get_Data_Map ( m_config->get_GRNN_Data_File() );
	}


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configurator::get_GRNN_Data" );
#endif /* LIBREVERSE_DEBUG */


      return m_grnn_data_map;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
