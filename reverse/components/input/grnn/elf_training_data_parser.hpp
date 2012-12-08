/*  Elf_Training_Data_Parser.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_ELF_TRAINING_DATA_PARSER_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_ELF_TRAINING_DATA_PARSER_HPP_INCLUDED

#include <reverse/components/input/grnn/xmlexpatparser.hpp>
#include <reverse/components/input/grnn/elf_training_data.hpp>
#include <reverse/components/input/grnn/elf_input_tag_names.hpp>
#include <reverse/components/input/grnn/training_set.hpp>

#include <boost/shared_ptr.hpp>

#include <list>
#include <stack>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {
   
	class elf_training_data_parser : public xml_expat_parser {
	public:

	  typedef boost::shared_ptr < reverse::components::input::grnn::training_data<elf_training_data> > training_data_ptr_t;

	  elf_training_data_parser();

	  virtual ~elf_training_data_parser();

	  virtual void start_element ( const std::string& element_name,
				       const attribute_map_t& attributes );
  
	  virtual void char_data ( const std::string& element_value );

	  virtual void end_element ( const std::string& element_name );

	  boost::shared_ptr < training_set<elf_training_data> > get_data ( std::string const& target_file );

	  variable_map::map_t& get_max_values ( void );

	private:

	  boost::uint32_t convert_string_to_uint ( std::string );

	  double convert_string_to_double ( std::string );

	  std::string get_attribute ( std::string name,
				      const attribute_map_t& attributes );

	  // A Elf_Training object is created for each <FILE> tag
	  // Reset at the end </FILE> tag
	  training_data_ptr_t m_training_data;
      
	  // There is no need to reset this variable since it will
	  // always be reset during normal operations.
	  std::stack<std::string> m_element_list;
      
	  // Constant variable
	  elf_input_tag_names m_tag;
      
	  // Reset at the end </DATA> tag
	  boost::shared_ptr < training_set<elf_training_data> > m_data;
	  variable_map::map_t m_max_values;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_ELF_TRAINING_DATA_PARSER_HPP_INCLUDED
