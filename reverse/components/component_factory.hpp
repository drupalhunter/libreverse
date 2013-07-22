/*  Component_Factory.h

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

#ifndef REVERSE_ERRORS_COMPONENT_FACTORY_HPP_INCLUDED
#define REVERSE_ERRORS_COMPONENT_FACTORY_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include <map>


namespace reverse {
  namespace infrastructure {

    class component;
    class component_state;

    class component_factory {
    public:

      static component_factory& instance()
      {
	static component_factory fact_ref;
	return fact_ref;
      }

      virtual ~component_factory();

      /**
       * \brief create a new file type detector component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new file type detector
       */
      boost::shared_ptr < infrastructure::component >
      get_file_type_detector ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new arch type detector component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new arch type detector
       */
      boost::shared_ptr < infrastructure::component >
      get_arch_type_detector ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new meta writer component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new meta writer
       */
      boost::shared_ptr < infrastructure::component >
      get_meta_writer ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new unpacker component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new unpacker
       */
      boost::shared_ptr < infrastructure::component >
      get_unpacker ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new code section detector component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new code section detector
       */
      boost::shared_ptr < infrastructure::component >
      get_code_section ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new data section detector component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new data section detector
       */
      boost::shared_ptr < infrastructure::component >
      get_data_section ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new entry point detector component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new entry point detector
       */
      boost::shared_ptr < infrastructure::component >
      get_entry_point ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new null component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new null component
       */
      boost::shared_ptr < infrastructure::component >
      get_null_component ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new memory map producer component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new memory map producer
       */
      boost::shared_ptr < infrastructure::component >
      get_memory_map_producer ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new file header printer component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new file header printer
       */
      boost::shared_ptr < infrastructure::component >
      get_file_header_printer ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new tevis zero filled checker component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new tevis zero filled checker
       */
      boost::shared_ptr < infrastructure::component >
      get_tevis_zero_filled_checker ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new tevis unknown region checker component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new tevis unknown region checker
       */
      boost::shared_ptr < infrastructure::component >
      get_tevis_unknown_region_checker ( boost::shared_ptr < infrastructure::component_state > state_ptr );

      /**
       * \brief create a new compiler classifier component
       *
       * \pre none
       *
       * \post component pointer is non null
       *
       * \return return a component pointer to the new compiler classifier
       */
      boost::shared_ptr < infrastructure::component >
      get_compiler_classifier ( boost::shared_ptr < infrastructure::component_state > state_ptr );

    private:

      component_factory ();

      component_factory ( const component_factory& );
      
      component_factory& operator= ( const component_factory& );
      
    };

  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_ERRORS_COMPONENT_FACTORY_HPP_INCLUDED
