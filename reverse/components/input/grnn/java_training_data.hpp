/*  Java_Training_Data.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_JAVA_TRAINING_DATA_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_JAVA_TRAINING_DATA_HPP_INCLUDED


#include <reverse/components/input/grnn/variable_map.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	template <typename data_type>
	class configuration;

	class java_training_data
	{
	public:

	  static const boost::uint8_t attribute_count;
	  static const boost::uint8_t classifier_target;

	  enum attributes
	    {
	      attribute_target_id = 0,
	      attribute_filesize = 1,
	      attribute_this_index = 2,
	      attribute_super_index = 3,
	      attribute_version = 4,
	      attribute_constant_pool_count = 5,

	      // constant pool info
	      // #1 - constant_utf
	      attribute_constant_utf8_count = 6,
	      attribute_constant_utf8_ratio = 7,

	      // #2 - constant_reserved
	      attribute_constant_reserved_count = 8,
	      attribute_constant_reserved_ratio = 9,

	      // #3 - constant_integer
	      attribute_constant_integer_count = 10,
	      attribute_constant_integer_ratio = 11,

	      // #4 - constant_float
	      attribute_constant_float_count = 12,
	      attribute_constant_float_ratio = 13,

	      // #5 - constant_long
	      attribute_constant_long_count = 14,
	      attribute_constant_long_ratio = 15,

	      // #6 - constant_double
	      attribute_constant_double_count = 16,
	      attribute_constant_double_ratio = 17,

	      // #7 - constant_class
	      attribute_constant_class_count = 18,
	      attribute_constant_class_ratio = 19,

	      // #8 - constant_string
	      attribute_constant_string_count = 20,
	      attribute_constant_string_ratio = 21,

	      // #9 - constant_fieldref
	      attribute_constant_fieldref_count = 22,
	      attribute_constant_fieldref_ratio = 23,

	      // #10 - constant_methodref
	      attribute_constant_methodref_count = 24,
	      attribute_constant_methodref_ratio = 25,

	      // #11 - constant_interface_methodref
	      attribute_constant_interface_methodref_count = 26,
	      attribute_constant_interface_methodref_ratio = 27,

	      // #12 - constant_name_and_type
	      attribute_constant_name_and_type_count = 28,
	      attribute_constant_name_and_type_ratio = 29,

	      attribute_field_count = 30,
	      attribute_method_count = 31
	    };

	  friend class java_training_data_parser;

	  java_training_data ();

	  ~java_training_data();

	  static std::string get_attribute_string_list ( boost::shared_ptr < configuration<java_training_data> > config );

	  std::string to_string ( boost::shared_ptr < configuration<java_training_data> > config ) const;

	  std::string to_xml ( boost::shared_ptr < configuration<java_training_data> > config ) const;
      
	  variable_map::map_t::const_iterator begin ( void ) const;
	  variable_map::map_t::iterator begin ( void );

	  variable_map::map_t::const_iterator end ( void ) const;
	  variable_map::map_t::iterator end ( void );

	  void set_attribute ( boost::uint32_t index, double value );

	  double get_attribute ( boost::uint32_t index );

	  bool empty ( void ) const;

	private:

	  variable_map m_data;
	};

      } // namespace grnn
    } // namespace input 
  } // namespace components
} // namespace reverse

#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_JAVA_TRAINING_DATA_HPP_INCLUDED
