
/*  Windows_Training_Data.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_WINDOWS_TRAINING_DATA_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_WINDOWS_TRAINING_DATA_HPP_INCLUDED

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

	class windows_training_data
	{
	public:

	  static const boost::uint8_t attribute_count;
	  static const boost::uint8_t classifier_target;

	  enum attributes
	    {
	      attribute_target_id = 0,
	      attribute_filesize = 1,
	      attribute_exe_header_address = 2,
	      attribute_coff_section_count = 3,
	      attribute_pe_opt_code_size = 4,
	      attribute_pe_opt_base_of_data = 5,
	      attribute_pe_opt_entry_point = 6,
	      attribute_pe_opt_image_size = 7
	    };

	  friend class windows_training_data_parser;

	  windows_training_data ();

	  ~windows_training_data();

	  variable_map::map_t
	  get_candidate_data ( boost::shared_ptr < configuration<windows_training_data> > config ) const;

	  static std::string get_attribute_string_list ( boost::shared_ptr < configuration<windows_training_data> > config );


	  std::string to_string ( boost::shared_ptr < configuration<windows_training_data> > config ) const;

	  std::string to_xml ( boost::shared_ptr < configuration<windows_training_data> > config ) const;

	  variable_map::map_t::const_iterator begin ( void ) const;

	  variable_map::map_t::iterator begin ( void );

	  variable_map::map_t::const_iterator end ( void ) const;
	  variable_map::map_t::iterator end ( void );

	  void set_attribute ( boost::uint32_t index, double value );

	  double get_attribute ( boost::uint32_t index ) const;

	  bool empty ( void ) const;

	private:

	  variable_map m_data;

	};

      } // namespace input
    } // namespace grnn
  } // namespace components
} // namespace reverse

#endif /* ifdef REVERSE_COMPONENTS_INPUT_GRNN_WINDOWS_TRAINING_DATA_HPP_INCLUDED */
