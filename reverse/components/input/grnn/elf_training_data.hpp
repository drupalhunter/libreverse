/*  Elf_Training_Data.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_TYPES_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_TYPES_HPP_INCLUDED

#include <reverse/components/input/grnn/classifier_types.hpp>
#include <reverse/components/input/grnn/variable_map.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class elf_training_data
	{
	public:

	  static const boost::uint8_t attribute_count;
	  static const boost::uint8_t classifier_target;

	  enum attributes
	    {
	      attribute_target_id = 0,
	      attribute_filesize = 1,
	      attribute_entry_point_address = 2,
	      attribute_section_headers_start = 3,
	      attribute_program_header_count = 4,
	      attribute_section_header_count = 5,
	      attribute_section_header_string_table_index = 6,
	      attribute_text_section_size = 7
	    };

	  friend class elf_training_data_parser;

	  elf_training_data ();

	  ~elf_training_data();

	  static std::string get_attribute_string_list ( classifier_types::configuration<elf_training_data>::ptr_t config );

	  std::string to_string ( classifier_types::configuration<elf_training_data>::ptr_t config ) const;

	  std::string to_xml ( classifier_types::configuration<elf_training_data>::ptr_t config ) const;
      
	  classifier_types::variable_map::map_type::const_iterator begin ( void ) const;
	  classifier_types::variable_map::map_type::iterator begin ( void );

	  classifier_types::variable_map::map_type::const_iterator end ( void ) const;
	  classifier_types::variable_map::map_type::iterator end ( void );

	  void set_attribute ( boost::uint32_t index, double value );

	  double get_attribute ( boost::uint32_t index );

	  bool empty ( void ) const;

	private:

	  classifier::variable_map m_data;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_TYPES_HPP_INCLUDED
