/*  Arch_Type_Detector.h

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

#ifndef REVERSE_COMPONENT_INPUT_ARCH_TYPE_DECTECTOR_HPP_INCLUDED
#define REVERSE_COMPONENT_INPUT_ARCH_TYPE_DECTECTOR_HPP_INCLUDED

#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/component_actor.hpp>

#include <boost/enable_shared_from_this.hpp>

namespace reverse {

  namespace infrastructure {
    class component_state;

    namespace data_source {
      class data_source_base;
    }

  } // namespace infrastructure

  namespace components {
    namespace input {

      class arch_type_detector : public infrastructure::component,
				 public infrastructure::component_actor,
				 public boost::enable_shared_from_this<arch_type_detector>
      {
      public:
	
	explicit arch_type_detector ();
	
	explicit arch_type_detector ( boost::shared_ptr < infrastructure::component_state > input_ptr );

	arch_type_detector ( arch_type_detector const& rhs );

	virtual ~arch_type_detector();

	arch_type_detector& operator= ( arch_type_detector const& rhs );

	void swap ( arch_type_detector& rhs );

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

	//------------------------------
	// component creator required functions
	//------------------------------
	virtual boost::shared_ptr < infrastructure::component > operator() ( boost::shared_ptr < infrastructure::component_state > data_ptr );

	static const std::string name;

      private:

	boost::shared_ptr < infrastructure::component_state > m_state_ptr;
      };

    } // namespace input
  } // namespace components
} // namespace reverse

#endif // ifndef REVERSE_COMPONENT_INPUT_ARCH_TYPE_DECTECTOR_HPP_INCLUDED
