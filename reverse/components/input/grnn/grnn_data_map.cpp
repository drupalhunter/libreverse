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

#include "GRNN_Data_Map.h"
#include "io/Preconditions.h"

namespace libreverse
{

  namespace classifier
  {
    bool
    GRNN_Data_Map::insert ( GRNN_Data_Types::Value_Type key, classifier_types::GRNN_Data_Entry::const_ptr_t data_obj )
    {
      bool result = false;

      io::Preconditions::not_equal ( key, GRNN_Data_Types::UNKNOWN );
      io::Preconditions::is_set ( data_obj );
      
      if ( m_data.find ( key ) == m_data.end() )
	{
	  m_data.insert ( std::make_pair ( key, data_obj ) );
	  result = true;
	}

      return result;
    }

    classifier_types::GRNN_Data_Entry::const_ptr_t
    GRNN_Data_Map::get_Entry ( GRNN_Data_Types::Value_Type key ) const
    {
      io::Preconditions::not_equal ( key, GRNN_Data_Types::UNKNOWN );

      GRNN_Data_Map::Data_Type::const_iterator output = m_data.find ( key );

      if ( output == m_data.end() )
	{
	  throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_INDEX );
	}

      io::Preconditions::is_set ( (*output).second );

      return (*output).second;
    }

  } /* namespace classifier */
} /* namespace libreverse */
