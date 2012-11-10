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

#ifndef VARIABLE_MAP_H
#define VARIABLE_MAP_H

#include "Classifier_Types.h"

namespace libreverse
{
  namespace classifier
  {

    class Variable_Map {
    public:

      void set_Attribute ( boost::uint32_t key, double value );

      double get_Attribute ( boost::uint32_t key ) const;

      bool empty ( void ) const;

      classifier_types::Variable_Map::map_type::const_iterator begin() const
	{
	  return m_data.begin();
	}

      classifier_types::Variable_Map::map_type::iterator begin()
	{
	  return m_data.begin();
	}

      classifier_types::Variable_Map::map_type::const_iterator end() const
	{
	  return m_data.end();
	}

      classifier_types::Variable_Map::map_type::iterator end()
	{
	  return m_data.end();
	}

    private:

      classifier_types::Variable_Map::map_type m_data;
    };

  } /* namespace classifier */
} /* namespace libreverse */

#endif /* VARIABLE_MAP */
