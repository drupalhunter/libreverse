/*  Configurator.h

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


#ifndef REVERSE_INFRASTRUCTURE_CONFIGURATOR_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_CONFIGURATOR_HPP_INCLUDED

#include <reverse/include/config.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/infrastructure/formula_list.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class grnn_data_map;

      } // namespace grnn
    } // namespace input
  } // namespace components

  namespace infrastructure {

    class configuration_data;

    class configurator {
    public:

      /*! \brief Data type associated with a Formula map
       *
       * key 1: Input file type
       * key 2: Desired output type
       * value: File associated with the two key pairs.
       */
      typedef std::map < std::pair<boost::uint32_t, boost::uint32_t>, infrastructure::formula_list >
      formula_map_t;

      static configurator& instance ()
      {
	static configurator fact_ref;
	return fact_ref;
      }

      virtual ~configurator();

      /*! \brief Initialize the configurator from the given config object.
       * \param config_obj Input configuration data object used to initialize the framework.
       */
      void init ( boost::shared_ptr < const infrastructure::configuration_data > config_obj );

      boost::shared_ptr < infrastructure::component_graph::map_t >
      get_graph ( boost::uint32_t input_id,
		  boost::uint32_t output_id );

      boost::shared_ptr < components::input::grnn::grnn_data_map > get_grnn_data ( void );

    private:

      configurator (){}

      configurator ( const configurator& );
      
      configurator& operator= ( const configurator& );
      
      // system wide configuration
      static boost::shared_ptr < const infrastructure::configuration_data > m_config;

      boost::shared_ptr < const formula_map_t > m_formulas;

      // grnn information
      boost::shared_ptr < components::input::grnn::grnn_data_map > m_grnn_data_map;
    };


  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_CONFIGURATOR_HPP_INCLUDED
