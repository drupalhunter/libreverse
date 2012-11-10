/*  Null_Component.h

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

#ifndef REVERSE_COMPONENT_NULL_COMPONENT_HPP_INCLUDED
#define REVERSE_COMPONENT_NULL_COMPONENT_HPP_INCLUDED

#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/component_actor.hpp>
#include <reverse/infrastructure/component_graph.hpp>

#include <boost/enable_shared_from_this.hpp>

#include <string>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

      class data_source_base;

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse 

namespace reverse {
  namespace component {

    class component_state;

    class null_component : public infrastructure::component,
			   public infrastructure::component_actor,
			   public boost::enable_shared_from_this<null_component>
    {
    public:

      explicit null_component ();

      explicit null_component ( boost::shared_ptr < infrastructure::component_state >& state_ptr );

      null_component ( null_component const& rhs );

      virtual ~null_component();

      void add_data_output ( std::string name );

      null_component& operator= ( null_component const& rhs );

      void swap ( null_component& rhs );

      //------------------------------
      // component required functions
      //------------------------------
      virtual void received_input_source_data ( boost::uint32_t id );

      virtual void add_input_source ( boost::uint32_t id );

      virtual std::string get_name (void) const;

      virtual void run ( infrastructure::component_graph::data_map_t* m_input_data );

      virtual boost::shared_ptr < infrastructure::data_source::data_source_base > results (void);

      virtual void set_state ( boost::uint32_t mode );

      virtual boost::uint32_t get_id (void) const;

      virtual infrastructure::component_data::input_token_t::const_iterator get_source_list_begin (void) const;

      virtual infrastructure::component_data::input_token_t::const_iterator get_source_list_end (void) const;

      //------------------------------
      // component actor required functions
      //------------------------------
      virtual void process (void);

      static const std::string name;

    private:

      boost::shared_ptr < infrastructure::component_state > m_state_ptr;
    };
  } // namespace component
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENT_NULL_COMPONENT_HPP_INCLUDED
