/*  Data_Source_Factory.h

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

#ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_FACTORY_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_FACTORY_HPP_INCLUDED

#include <reverse/infrastructure/data_source/data_source_factory_base.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

      class data_source_base;

      class data_source_factory : public data_source_factory_base {

      public:

	virtual ~data_source_factory(){}

	/**
	 *
	 */
	boost::shared_ptr < infrastructure::data_source::data_source_base > get_data_source ( boost::uint32_t id );
        
	/**
	 *
	 */
	static boost::shared_ptr < infrastructure::data_source::data_source_factory > instance ();
	
	/**
	 *
	 * @param transfer_type
	 * @param source_config
	 */
	void init ( boost::shared_ptr < infrastructure::data_source::data_source_config_base > source_config );

      private:
	
	data_source_factory();

	/**
	 * Fields
	 */
	static boost::shared_ptr < infrastructure::data_source::data_source_factory > m_factory;

	/**
	 *
	 */
	boost::shared_ptr < infrastructure::data_source::data_source_config_base > m_src_config;

      };
    } // namespace data_source
  } /* namespace infrastructure */
} /* namespace libreverse */

#endif // ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_FACTORY_HPP_INCLUDED

