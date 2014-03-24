/*  Component_Data.h

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

#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_DATA_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_DATA_HPP_INCLUDED

#include <reverse/infrastructure/component_graph.hpp>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <map>

namespace reverse {

  namespace data_containers {

    class control_flow_graph_sequence;
    class filename;
    class memory_map;

  } // namespace data_containers

  namespace meta {

    class meta_object;

  }

  namespace infrastructure {

    namespace data_source {
      
      class data_object;
      
    } // namespace data_source

    class component_data
    {
    public:

      typedef std::map < boost::uint32_t const, bool> input_token_t;

      /*!
       * \brief constructor
       * \param id unique id for the instance of this filter
       */
      explicit component_data ( boost::uint32_t id );


      /*!
       * \brief copy constructor
       */
      component_data ( component_data const& ref );

      virtual ~component_data ();

      /**
       * \brief return the id number of this component
       *
       * \return id number
       */
      boost::uint32_t get_id (void) const;


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
       *
       * \pre the variable 'id' represents an component existing
       * in the component graph.
       *
       * \post new id is contains in the list of inputs
       */
      virtual void add_input_source ( boost::uint32_t id );

      /**
       * this is used during the actual processing of the
       * component_graph. the parent component, identified by id,
       * is done with its analysis and has recorded its results
       * into the data_map_t in the graph_visitor. the child component
       * marks that it has received input from the parent component.
       * 
       * \param id identity of the component that finished analsysis
       *
       * \pre id is in the list of inputs
       *
       * \post bool value of id set to true
       */
      virtual void received_input_source_data ( boost::uint32_t id );

      void gather_inputs ( infrastructure::component_graph::data_map_t* data_ptr );

      bool find ( boost::uint32_t id );

      boost::shared_ptr < infrastructure::data_source::data_source_base> get_data_source (void) const;

      void set_output_data ( boost::shared_ptr<const data_containers::filename> file_ptr );

      void set_output_data ( boost::shared_ptr<const data_containers::control_flow_graph_sequence> graph_ptr );

      void set_output_data ( boost::shared_ptr<const data_containers::memory_map> map_ptr );


      bool is_filename_set (void) const;

      bool is_control_flow_graph_sequence_set (void) const;

      bool is_memory_map_set (void) const;

      boost::shared_ptr<const data_containers::filename> get_input_filename(void) const;

      boost::shared_ptr<const data_containers::control_flow_graph_sequence> get_input_control_flow_graph_sequence(void) const;

      boost::shared_ptr<const data_containers::memory_map> get_input_memory_map(void) const;

      void set_append_meta_data ( boost::shared_ptr < const meta::meta_object >& meta_ptr );

      component_data::input_token_t::const_iterator get_source_list_begin (void) const;
      
      component_data::input_token_t::const_iterator get_source_list_end (void) const;

      boost::shared_ptr<meta::meta_object const> get_input_meta_data (void) const;

      component_data& operator= ( component_data const& ref);

      void swap ( component_data& ref);

      std::string to_string (void) const;

    private:

      //---------------------------------
      //      variables
      //---------------------------------
      boost::uint32_t m_id;

      component_data::input_token_t m_source_list;

      boost::shared_ptr < infrastructure::data_source::data_object > m_data_obj_ptr;

      boost::shared_ptr < const meta::meta_object > m_meta_ptr;
      boost::shared_ptr < const data_containers::filename > m_filename_ptr;
      boost::shared_ptr < const data_containers::control_flow_graph_sequence > m_graph_ptr;
      boost::shared_ptr < const data_containers::memory_map > m_map_ptr;

    };

  } // namespace infrastructure
} // namespace reverse

#endif // REVERSE_INFRASTRUCTURE_COMPONENT_DATA_HPP_INCLUDED
