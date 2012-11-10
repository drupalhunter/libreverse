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

#include "Configuration_Data.h"
#include "errors/Configuration_Exception.h"
#include "errors/Component_Exception.h"
#include "infrastructure/data_source/Memory_Data_Source_Config.h"
#include "include/config.h"
#include <iostream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    Configuration_Data::Configuration_Data()
        : m_data ( new Memory_Data_Source_Config() )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			   TraceLevel::DETAIL,
			   "Inside Configuration_Data Constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::shared_ptr<Data_Source_Config_Base>
    Configuration_Data::get_Transfer_Config()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Configuration_Data::get_Transfer_Config" );
#endif /* LIBREVERSE_DEBUG */

        return m_data;
    }

    void
    Configuration_Data::set_Transfer_Config ( infrastructure_types::Data_Source_Config_Base::ptr_t obj_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Data::set_Transfer_Config" );
#endif /* LIBREVERSE_DEBUG */


        if ( obj_ptr.get() == 0 )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str(boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }
        else
            {
                m_data = obj_ptr;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Data::set_Transfer_Config" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Configuration_Data::set_Formula_Directory ( std::string const& obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Data::set_Formula_Directory" );
#endif /* LIBREVERSE_DEBUG */


        if ( obj.empty() )
            {


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str(boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::Configuration_Exception
                    ( errors::Configuration_Exception::EMPTY_INPUT );
            }
        else
            {
                m_formula_directory = obj;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Data::set_Formula_Directory" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Configuration_Data::get_Formula_Directory (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Configuration_Data::get_Formula_Directory" );
#endif /* LIBREVERSE_DEBUG */

        return m_formula_directory;
    }

    void
    Configuration_Data::set_GRNN_Data_File ( std::string const& obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Data::set_GRNN_Data_Directory" );
#endif /* LIBREVERSE_DEBUG */

        if ( obj.empty() )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
				     TraceLevel::ERROR,
				     boost::str(boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */


                throw errors::Configuration_Exception
                    ( errors::Configuration_Exception::EMPTY_INPUT );
            }
        else
            {
                m_grnn_data_file = obj;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Data::set_DLL_Directory" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Configuration_Data::get_GRNN_Data_File (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Inside Configuration_Data::get_GRNN_Data_File" );
#endif /* LIBREVERSE_DEBUG */

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
    Configuration_Data::dump (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Entering Configuration_Data::dump" );
#endif /* LIBREVERSE_DEBUG */


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


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			     TraceLevel::DETAIL,
                             "Exiting Configuration_Data::dump" );
#endif /* LIBREVERSE_DEBUG */

    }
} /* namespace infrastructure */
} /* namespace libreverse */
