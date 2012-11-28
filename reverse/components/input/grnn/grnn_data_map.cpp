/*  GRNN_Data_Map.cpp

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

#include <reverse/components/input/grnn/grnn_data_map.hpp>
#include <reverse/preconditions.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	bool
	grnn_data_map::insert ( grnn_data_types::value_type key,
				boost::shared_ptr < const grnn_data_entry > data_obj )
	{
	  bool result = false;

	  preconditions::not_equal ( key, grnn_data_types::unknown );
	  preconditions::is_set ( data_obj );
      
	  if ( m_data.find ( key ) == m_data.end() )
	    {
	      m_data.insert ( std::make_pair ( key, data_obj ) );
	      result = true;
	    }

	  return result;
	}

	boost::shared_ptr < const grnn_data_entry >
	grnn_data_map::get_entry ( grnn_data_types::value_type key ) const
	{
	  preconditions::not_equal ( key, grnn_data_types::unknown );

	  grnn_data_map::data_type::const_iterator output = m_data.find ( key );

	  if ( output == m_data.end() )
	    {
	      throw errors::internal_exception ( errors::internal_exception::invalid_index );
	    }

	  preconditions::is_set ( (*output).second );

	  return (*output).second;
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

