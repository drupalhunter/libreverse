/*  Variable_Map.cpp

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

#include <reverse/components/input/grnn/variable_map.hpp>
#include <reverse/errors/internal_exception.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	void
	variable_map::set_attribute ( boost::uint32_t key, double value )
	{
	  m_data[key] = value;
	}

	double
	variable_map::get_attribute ( boost::uint32_t key ) const
	{
	  variable_map::map_t::const_iterator cpos = m_data.find ( key );

	  if ( cpos == m_data.end() )
	    {
	      throw errors::internal_exception ( errors::internal_exception::invalid_index );	  
	    }

	  return (*cpos).second;
	}

	bool
	variable_map::empty ( void ) const
	{
	  return m_data.empty();
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

