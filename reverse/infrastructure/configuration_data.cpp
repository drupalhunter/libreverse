/*  Configuration_Data.cpp

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
#include <reverse/errors/component_exception.hpp>
#include <reverse/infrastructure/configuration_data.hpp>
#include <reverse/infrastructure/data_source/memory_data_source_config.hpp>

#include <boost/format.hpp>

#include <iostream>

namespace reverse {
  namespace infrastructure {

    configuration_data::configuration_data()
      : m_data ( new infrastructure::data_source::memory_data_source_config() )
    {
      trace::infrastructure_detail ( "Inside Configuration_Data Constructor" );
    }

    boost::shared_ptr<infrastructure::data_source::data_source_config_base>
    configuration_data::get_transfer_config()
    {
      trace::infrastructure_detail ( "Inside Configuration_Data::get_Transfer_Config" );

      return m_data;
    }

    void
    configuration_data::set_transfer_config ( boost::shared_ptr < infrastructure::data_source::data_source_config_base > obj_ptr )
    {
      trace::infrastructure_detail ( "Entering Configuration_Data::set_Transfer_Config" );

      if ( obj_ptr.get() == 0 )
	{
	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
				        __LINE__ );

	  throw errors::component_exception ( errors::component_exception::null_pointer );
	}
      else
	{
	  m_data = obj_ptr;
	}

      trace::infrastructure_detail ( "Exiting Configuration_Data::set_Transfer_Config" );
    }

    void
    configuration_data::set_formula_directory ( std::string const& obj )
    {
      trace::infrastructure_detail ( "Entering Configuration_Data::set_Formula_Directory" );

      if ( obj.empty() )
	{
	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
					__LINE__ );

	  throw errors::configuration_exception ( errors::configuration_exception::EMPTY_INPUT );
	}
      else
	{
	  m_formula_directory = obj;
	}

      trace::infrastructure_detail ( "Exiting Configuration_Data::set_Formula_Directory" );
    }

    std::string
    configuration_data::get_formula_directory (void) const
    {
      trace::infrastructure_detail ( "Inside Configuration_Data::get_Formula_Directory" );

      return m_formula_directory;
    }

    void
    configuration_data::set_grnn_data_file ( std::string const& obj )
    {
      trace::infrastructure_detail ( "Entering Configuration_Data::set_GRNN_Data_Directory" );

      if ( obj.empty() )
	{
	  trace::infrastructure_error ( "Exception throw in %s at line %d",
					__FILE__,
				        __LINE__ );

	  throw errors::configuration_exception ( errors::configuration_exception::EMPTY_INPUT );
	}
      else
	{
	  m_grnn_data_file = obj;
	}

      trace::infrastructure_detail ( "Exiting Configuration_Data::set_DLL_Directory" );
    }

    std::string
    configuration_data::get_grnn_data_file (void) const
    {
      trace::infrastructure_detail ( "Inside Configuration_Data::get_GRNN_Data_File" );

      return m_grnn_data_file;
    }

    /*
      void Configuration_Data::add_DLL_Path ( std::string name,
      Path_t location )
      {
      boost::algorithm::to_lower ( name );

      m_dll_map.insert ( std::make_pair ( name, location ) );
      }

      Configuration_Data::Path_t const&
      Configuration_Data::get_DLL_Path ( std::string const& name )
      {
      DLL_Map_t::const_iterator pos = m_dll_map.find ( name );
      if ( pos == m_dll_map.end() )
      {
      std::cerr << boost::format("Exception throw in %s at line %d")
      % __FILE__
      % __LINE__
      << std::endl;

      throw errors::Configuration_Exception
      (errors::Configuration_Exception::DLL_NOT_FOUND);
      }
      return (*pos).second;
      }
    */

    void
    configuration_data::dump (void) const
    {
      trace::infrastructure_detail ( "Entering Configuration_Data::dump" );

      std::cout << "Configuration Data" << std::endl
		<< "--------------------------------" << std::endl
		<< std::endl
		<< "  Formula Directory: " << m_formula_directory << std::endl
		<< "  GRNN Data File: " << m_grnn_data_file << std::endl;

        /*
          for ( DLL_Map_t::const_iterator pos = m_dll_map.begin();
          pos != m_dll_map.end();
          pos++ )
          {
          std::cout << boost::format("    %1s: %2s") %
          (*pos).first %
          ((*pos).second).string()
          << std::endl;
          }
        */

      trace::infrastructure_detail ( "Exiting Configuration_Data::dump" );

    }

  } /* namespace infrastructure */
} /* namespace reverse */
