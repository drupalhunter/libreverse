/*  Code_Section_Detector.h

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

#ifndef REVERSE_COMPONENTS_INPUT_CODE_SECTION_DECTECTOR_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_CODE_SECTION_DECTECTOR_HPP_INCLUDED

#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/component_actor.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace reverse
{
  namespace infrastructure
  {
    class component_state;

    namespace data_source
    {
      class data_source_base;
    }

  } // namespace infrastructure

  namespace components
  {
    namespace input
    {

      class code_section_detector : public infrastructure::component,
				    public infrastructure::component_actor,
				    public boost::enable_shared_from_this<code_section_detector>
      {
      public:

	static const std::string code_section_address_meta_format;
	static const std::string code_section_size_meta_format;

	explicit code_section_detector ();

	explicit code_section_detector ( boost::shared_ptr < infrastructure::component_state > state_ptr );

	code_section_detector ( code_section_detector const& rhs );

	virtual ~code_section_detector();

	code_section_detector& operator= ( code_section_detector const& rhs );

	void swap ( code_section_detector& rhs );

	//------------------------------
	// Component required functions
	//------------------------------
	virtual void received_input_source_data ( boost::uint32_t id );

	virtual void add_input_source ( boost::uint32_t id );

	virtual std::string get_name ( void ) const;

	virtual void run ( infrastructure::component_graph::data_map_t* m_input_data );
	      
	virtual boost::shared_ptr< infrastructure::data_source::data_source_base > results ( void );

	virtual void set_state ( boost::uint32_t mode );


	virtual boost::uint32_t get_id ( void ) const;

	virtual infrastructure::component_data::input_token_t::const_iterator get_source_list_begin ( void ) const;

	virtual infrastructure::component_data::input_token_t::const_iterator get_source_list_end ( void ) const;

	//------------------------------
	// Component Actor required functions
	//------------------------------
	virtual void process ( void );

      protected:

	static const std::string m_name;

      private:

	boost::shared_ptr < infrastructure::component_state > m_state_ptr;
      };


    } // namespace input
  } // namespace components
} // namespace libreverse


#endif /* REVERSE_COMPONENTS_INPUT_CODE_SECTION_DECTECTOR_HPP_INCLUDED */
