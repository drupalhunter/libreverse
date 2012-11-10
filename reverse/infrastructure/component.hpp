/*  Component.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_HPP_INCLUDED

#include <reverse/infrastructure/component_data.hpp>
#include <reverse/infrastructure/component_graph.hpp>

#include <string>

namespace reverse {
  namespace infrastructure {
    namespace data_source {
      class data_source_base;
    }
  } // namespace infrastructure
} // namespace reverse

namespace reverse {
  namespace infrastructure {

    class component
    {
    public:
      static boost::uint32_t const source_id = 0 ;
      static boost::uint32_t const working_mode = 1;
      static boost::uint32_t const source_mode = 0;

      virtual ~component() {}

      /**
       * \brief upsream component is providing input
       *
       * this is used during the creation of the component_graph. each
       * component providing data to a child component must be provided
       * to the child. the child uses this information to check to see
       * if it has all its required inputs before running its analysis.
       *
       * \param id identity of the component providing input
       * \param data input data.
       */
      virtual void add_input_source ( boost::uint32_t id ) = 0;

      /*! \brief This is used during the actual processing of the
       * component_graph. the parent component, identified by id,
       * is done with its analysis and has recorded its results
       * into the data_map_t in the graph_visitor. The child component
       * marks that it has received input from the parent component.
       *
       * \param id identity of the component that finished analsysis
       */
      virtual void received_input_source_data ( boost::uint32_t id ) = 0;

      virtual std::string get_name ( void ) const = 0;

      virtual void run ( infrastructure::component_graph::data_map_t* m_input_data ) = 0;

      virtual boost::shared_ptr<infrastructure::data_source::data_source_base> results ( void ) = 0;

      virtual void set_state ( boost::uint32_t mode ) = 0;

      virtual boost::uint32_t get_id ( void ) const = 0;

      virtual infrastructure::component_data::input_token_t::const_iterator get_source_list_begin ( void ) const = 0;

      virtual infrastructure::component_data::input_token_t::const_iterator get_source_list_end ( void ) const = 0;

    };

  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_COMPONENT_HPP_INCLUDED
