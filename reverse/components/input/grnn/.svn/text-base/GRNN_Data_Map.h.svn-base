/*  GRNN_Data_Map.h

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

#ifndef GRNN_DATA_MAP_H
#define GRNN_DATA_MAP_H

#include "Training_Set.h"
#include "GRNN_Data_Types.h"

namespace libreverse
{

  namespace classifier
  {
    class GRNN_Data_Map {
    public:

      /*!
       * \brief Adds a new unseen GRNN_Data_Entry (no duplicates or updating allowed)
       * \param key Index where GRNN_Data_Entry is to be stored
       * \param data_obj GRNN_Data_Entry object to be stored
       * \pre key value is not set to UNKNOWN
       * \pre data_obj pointer is not null
       * \return boolean value marking success (true) or failure (false)
       */
      bool insert ( GRNN_Data_Types::Value_Type key, classifier_types::GRNN_Data_Entry::const_ptr_t data_obj );

      /*!
       * \brief Retrieves a new GRNN_Data_Entry
       * \param key Index where GRNN_Data_Entry is to be read
       * \pre key value is not set to UNKNOWN
       * \post Returned GRNN_Data_Entry object is not null
       * \return pointer to stored GRNN_Data_Entry object
       */
      classifier_types::GRNN_Data_Entry::const_ptr_t get_Entry ( GRNN_Data_Types::Value_Type key ) const;

    private:

      typedef std::map<GRNN_Data_Types::Value_Type, classifier_types::GRNN_Data_Entry::const_ptr_t > Data_Type;
      Data_Type m_data;

    };

  } /* namespace classifier */

} /* namespace libreverse */

#endif /* GRNN_DATA_MAP_H */
