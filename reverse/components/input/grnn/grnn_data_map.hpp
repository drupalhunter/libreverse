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

#include <reverse/components/input/grnn/training_set.hpp>
#include <reverse/components/input/grnn/grnn_data_types.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class grnn_data_entry;

	class grnn_data_map {
	public:

	  /*!
	   * \brief Adds a new unseen GRNN_Data_Entry (no duplicates or updating allowed)
	   * \param key Index where GRNN_Data_Entry is to be stored
	   * \param data_obj GRNN_Data_Entry object to be stored
	   * \pre key value is not set to UNKNOWN
	   * \pre data_obj pointer is not null
	   * \return boolean value marking success (true) or failure (false)
	   */
	  bool insert ( grnn_data_types::value_type key, boost::shared_ptr < const grnn_data_entry > data_obj );

	  /*!
	   * \brief Retrieves a new GRNN_Data_Entry
	   * \param key Index where GRNN_Data_Entry is to be read
	   * \pre key value is not set to UNKNOWN
	   * \post Returned GRNN_Data_Entry object is not null
	   * \return pointer to stored GRNN_Data_Entry object
	   */
	  boost::shared_ptr < const grnn_data_entry > get_entry ( grnn_data_types::value_type key ) const;

	private:

	  typedef std::map<grnn_data_types::value_type, boost::shared_ptr < const grnn_data_entry > > data_type;
	  data_type m_data;

	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif /* GRNN_DATA_MAP_H */
