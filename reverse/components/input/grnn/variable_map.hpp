/*  Variable_Map.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_VARIABLE_MAP_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_VARIABLE_MAP_HPP_INCLUDED

#include <boost/cstdint.hpp>

#include <map>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class variable_map {
	public:

	  typedef std::map <boost::uint32_t, double> map_t;

	  void set_attribute ( boost::uint32_t key, double value );

	  double get_attribute ( boost::uint32_t key ) const;

	  bool empty ( void ) const;

	  map_t::const_iterator begin() const
	  {
	    return m_data.begin();
	  }

	  map_t::iterator begin()
	  {
	    return m_data.begin();
	  }

	  map_t::const_iterator end() const
	  {
	    return m_data.end();
	  }

	  map_t::iterator end()
	  {
	    return m_data.end();
	  }

	private:

	  map_t m_data;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_VARIABLE_MAP_HPP_INCLUDED
