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

#include "Variable_Map.h"
#include "errors/Internal_Exception.h"

namespace libreverse
{
  namespace classifier
  {

    void
    Variable_Map::set_Attribute ( boost::uint32_t key, double value )
    {
      m_data[key] = value;
    }

    double
    Variable_Map::get_Attribute ( boost::uint32_t key ) const
    {
      classifier_types::Variable_Map::map_type::const_iterator cpos = m_data.find ( key );

      if ( cpos == m_data.end() )
	{
	  throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );	  
	}

      return (*cpos).second;
    }

    bool
    Variable_Map::empty ( void ) const
    {
      return m_data.empty();
    }

  } /* namespace classifier */
} /* namespace libreverse */
